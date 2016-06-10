#ifndef {{NAME_}}_H
#define {{NAME_}}_H

#include <glib-object.h>

G_BEGIN_DECLS

#define {{prefix}}_TYPE_{{suffix}} ({{name_}}_get_type())

G_DECLARE_FINAL_TYPE ({{name}}, {{name_}}, {{prefix}}, {{suffix}}, GObject)

G_END_DECLS

#endif /* {{NAME_}}_H */
