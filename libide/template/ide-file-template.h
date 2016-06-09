/* ide-file-template.h
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

#ifndef IDE_FILE_TEMPLATE_H
#define IDE_FILE_TEMPLATE_H

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define IDE_TYPE_FILE_TEMPLATE (ide_file_template_get_type())

G_DECLARE_INTERFACE (IdeFileTemplate, ide_file_template, IDE, FILE_TEMPLATE, GObject)

struct _IdeFileTemplateInterface
{
  GTypeInterface parent;

  gchar      *(*get_id)          (IdeFileTemplate      *self);
  gchar      *(*get_name)        (IdeFileTemplate      *self);
  gchar      *(*get_description) (IdeFileTemplate      *self);
  void        (*expand_async)    (IdeFileTemplate      *self,
                                  GHashTable           *params,
                                  GCancellable         *cancellable,
                                  GAsyncReadyCallback   callback,
                                  gpointer              user_data);
  gboolean    (*expand_finish)   (IdeFileTemplate      *self,
                                  GAsyncResult         *result,
                                  GError              **error);
};

gchar      *ide_file_template_get_id          (IdeFileTemplate      *self);
gchar      *ide_file_template_get_name        (IdeFileTemplate      *self);
gchar      *ide_file_template_get_description (IdeFileTemplate      *self);
void        ide_file_template_expand_async    (IdeFileTemplate      *self,
                                               GHashTable           *params,
                                               GCancellable         *cancellable,
                                               GAsyncReadyCallback   callback,
                                               gpointer              user_data);
gboolean    ide_file_template_expand_finish   (IdeFileTemplate      *self,
                                               GAsyncResult         *result,
                                               GError              **error);

G_END_DECLS

#endif /* IDE_FILE_TEMPLATE_H */
