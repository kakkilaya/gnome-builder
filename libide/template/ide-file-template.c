/* ide-file-template.c
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

#define G_LOG_DOMAIN "ide-file-template"

#include "ide-file-template.h"

G_DEFINE_INTERFACE (IdeFileTemplate, ide_file_template, G_TYPE_OBJECT)

static void
ide_file_template_default_init (IdeFileTemplateInterface *iface)
{
}

gchar *
ide_file_template_get_id (IdeFileTemplate *self)
{
  g_return_val_if_fail (IDE_IS_FILE_TEMPLATE (self), NULL);

  return IDE_FILE_TEMPLATE_GET_IFACE (self)->get_id (self);
}

gchar *
ide_file_template_get_name (IdeFileTemplate *self)
{
  g_return_val_if_fail (IDE_IS_FILE_TEMPLATE (self), NULL);

  return IDE_FILE_TEMPLATE_GET_IFACE (self)->get_name (self);
}

gchar *
ide_file_template_get_description (IdeFileTemplate *self)
{
  g_return_val_if_fail (IDE_IS_FILE_TEMPLATE (self), NULL);

  return IDE_FILE_TEMPLATE_GET_IFACE (self)->get_description (self);
}

/**
 * ide_file_template_expand_async:
 * @self: an #IdeFileTemplate
 * @params: (element-type utf8 GLib.Variant): A hashtable of template parameters.
 * @cancellable: (nullable): A #GCancellable or %NULL.
 * @callback: the callback for the asynchronous operation.
 * @user_data: user data for @callback.
 *
 * Asynchronously requests expansion of the template.
 *
 * This may involve creating files on disk as well as
 * expanding files based on the contents of @params.
 *
 * It is expected that this method is only called once on an #IdeFileTemplate.
 */
void
ide_file_template_expand_async (IdeFileTemplate     *self,
                                GHashTable          *params,
                                GCancellable        *cancellable,
                                GAsyncReadyCallback  callback,
                                gpointer             user_data)
{
  g_return_if_fail (IDE_IS_FILE_TEMPLATE (self));
  g_return_if_fail (params != NULL);
  g_return_if_fail (g_hash_table_contains (params, "name"));
  g_return_if_fail (g_hash_table_contains (params, "path"));
  g_return_if_fail (!cancellable || G_IS_CANCELLABLE (cancellable));

  IDE_FILE_TEMPLATE_GET_IFACE (self)->expand_async (self, params, cancellable, callback, user_data);
}

gboolean
ide_file_template_expand_finish (IdeFileTemplate  *self,
                                 GAsyncResult        *result,
                                 GError             **error)
{
  g_return_val_if_fail (IDE_IS_FILE_TEMPLATE (self), FALSE);
  g_return_val_if_fail (G_IS_ASYNC_RESULT (result), FALSE);

  return IDE_FILE_TEMPLATE_GET_IFACE (self)->expand_finish (self, result, error);
}
