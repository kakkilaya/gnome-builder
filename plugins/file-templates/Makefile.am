if ENABLE_FILE_TEMPLATES

plugindir = $(libdir)/gnome-builder/plugins
dist_plugin_DATA = file-templates.plugin

moduledir = $(libdir)/gnome-builder/plugins/file_templates
dist_module_DATA = file_templates/__init__.py

resourcedir = $(datadir)/gnome-builder/plugins/
nobase_resource_DATA = \
	file_templates/resources/new-gobject.c \
	file_templates/resources/new-gobject.h \
	$(NULL)

EXTRA_DIST = $(nobase_resource_DATA)

endif

-include $(top_srcdir)/git.mk
