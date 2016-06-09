/* ide-file-template-provider.c
 *
 * Copyright (C) 2016 Akshaya Kakkilaya <akshaya.kakkilaya@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "ide-file-template-provider.h"

G_DEFINE_INTERFACE (IdeFileTemplateProvider, ide_file_template_provider, G_TYPE_OBJECT)

static GList *
ide_file_template_provider_real_get_file_templates (IdeFileTemplateProvider *self)
{
  return NULL;
}

static void
ide_file_template_provider_default_init (IdeFileTemplateProviderInterface *iface)
{
  iface->get_file_templates = ide_file_template_provider_real_get_file_templates;
}

/**
 * ide_file_template_provider_get_file_templates:
 * @self: An #IdeFileTemplateProvider
 *
 * Gets a list of templates for this provider.
 *
 * Plugins should implement this interface to feed #IdeFileTemplate's into
 * the file creation workflow.
 *
 * Returns: (transfer full) (element-type Ide.FileTemplate): A #GList of
 *   #IdeFileTemplate instances.
 */
GList *
ide_file_template_provider_get_file_templates (IdeFileTemplateProvider *self)
{
  g_return_val_if_fail (IDE_IS_FILE_TEMPLATE_PROVIDER (self), NULL);

  return IDE_FILE_TEMPLATE_PROVIDER_GET_IFACE (self)->get_file_templates (self);
}
