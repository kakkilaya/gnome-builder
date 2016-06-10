#!/usr/bin/env python3

#
# __init__.py
#
# Copyright (C) 2016 Akshaya Kakkilaya <akshaya.kakkilaya@gmail.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

from gettext import gettext as _

import gi
import os
import re

gi.require_version('Ide', '1.0')
gi.require_version('Template', '1.0')

from gi.repository import Ide
from gi.repository import Gio
from gi.repository import GLib
from gi.repository import GObject
from gi.repository import Peas
from gi.repository import Template

def get_module_data_path(name):
    engine = Peas.Engine.get_default()
    plugin = engine.get_plugin_info('file_templates')
    data_dir = plugin.get_data_dir()
    return GLib.build_filenamev([data_dir, name])

class FileTemplateProvider(GObject.Object, Ide.FileTemplateProvider):
    def do_get_project_templates(self):
        return [GObjectTemplate()]

class GObjectTemplate(Ide.TemplateBase, Ide.ProjectTemplate):
    def do_get_id(self):
        return 'gobject'

    def do_get_name(self):
        return 'GObject'

    def do_get_description(self):
        return 'Add a new GObject'

    def do_expand_async(self, params, cancellable, callback, data):
        self.reset()

        task = Gio.Task.new(self, cancellable, callback)

        name = params['name'].get_string()
        dir_path = params['path'].get_string()

        name_ = re.sub(r'([a-z])([A-Z])', r'\1_\2', name).lower()
        NAME_ = name_.upper()
        prefix = NAME_.split('_')[0]
        suffix = '_'.join(NAME_.split('_')[1:])
        file_name = name_.replace('_', '-')

        directory = Gio.File.new_for_path(dir_path)

        scope = Template.Scope.new()

        scope.get('name').assign_string(name)
        scope.get('name_').assign_string(name_)
        scope.get('NAME_').assign_string(NAME_)
        scope.get('prefix').assign_string(prefix)
        scope.get('suffix').assign_string(suffix)
        scope.get('file_name').assign_string(file_name)

        expands = {
            'name': file_name
        }

        files = {
            'resources/new-gobject.c': '%(name)s.c',
            'resources/new-gobject.h': '%(name)s.h'
        }

        modes = {}

        for src,dst in files.items():
            destination = directory.get_child(dst % expands)
            path = get_module_data_path(src)
            self.add_path(path, destination, scope, modes.get(src, 0))

        self.expand_all_async(cancellable, self.expand_all_cb, task)

    def do_expand_finish(self, result):
        return result.propagate_boolean()

    def expand_all_cb(self, obj, result, task):
        try:
            self.expand_all_finish(result)
            task.return_boolean(True)
        except Exception as exc:
            if isinstance(exc, GLib.Error):
                task.return_error(exc)
            else:
                task.return_error(GLib.Error(repr(exc)))

        
