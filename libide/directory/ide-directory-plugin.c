/* ide-directory-plugin.c
 *
 * Copyright (C) 2015 Christian Hergert <christian@hergert.me>
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

#define G_LOG_DOMAIN "ide-directory-plugin"

#include <libpeas/peas.h>

#include "buildsystem/ide-build-system.h"
#include "directory/ide-directory-build-system.h"
#include "directory/ide-directory-genesis-addin.h"
#include "directory/ide-directory-vcs.h"
#include "genesis/ide-genesis-addin.h"

void
ide_directory_register_types (PeasObjectModule *module)
{
  peas_object_module_register_extension_type (module,
                                              IDE_TYPE_BUILD_SYSTEM,
                                              IDE_TYPE_DIRECTORY_BUILD_SYSTEM);
  peas_object_module_register_extension_type (module,
                                              IDE_TYPE_GENESIS_ADDIN,
                                              IDE_TYPE_DIRECTORY_GENESIS_ADDIN);
  peas_object_module_register_extension_type (module,
                                              IDE_TYPE_VCS,
                                              IDE_TYPE_DIRECTORY_VCS);
}
