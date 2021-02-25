#include <gtk/gtk.h>
#include <glib.h>


enum
{
  /*
   * In GTK+ 3.24.9 and later, the "overlay-scrolling" property is assigned
   * a property number of 85.  We might as well follow that convention here
   * and avoid any property number collisions.
   */
  PROP_OVERLAY_SCROLLING = 85
};


static gboolean     overlay_scrolling_enabled = TRUE;

static GParamSpec * gtk_overlay_scrolling_pspec;


static void (*original_gtk_settings_set_property) (GObject      *object,
                                                   guint         property_id,
                                                   const GValue *value,
                                                   GParamSpec   *pspec);

static void (*original_gtk_settings_get_property) (GObject      *object,
                                                   guint         property_id,
                                                   const GValue *value,
                                                   GParamSpec   *pspec);


static void overridden_gtk_settings_set_property (GObject      *object,
                                                  guint         property_id,
                                                  const GValue *value,
                                                  GParamSpec   *pspec);

static void overridden_gtk_settings_get_property (GObject      *object,
                                                  guint         property_id,
                                                  const GValue *value,
                                                  GParamSpec   *pspec);


G_MODULE_EXPORT const char *
g_module_check_init (GModule *module)
{
  /*
   * Exit immediately on GTK+ versions prior to 3.15.0, since overlay
   * scrolling hadn't been introduced yet!
   */
  if (gtk_check_version (3,15,0) != NULL)
  {
    return "Your version of GTK+ is too old to support overlay scrolling.\n"
           "This module is thus unnecessary and you should remove it.";
  }

  /*
   * Similarly, a property was introduced in GTK+ 3.24.9 to disable overlay
   * scrolling globally, making this module redundant.
   */
  else if (gtk_check_version (3,24,9) == NULL)
  {
    return "Your version of GTK+ already supports globally disabling overlay scrolling.\n"
           "This module is thus redundant and you should remove it.";
  }

  /*
   * Otherwise, this module is useful for the current version of GTK+, so
   * proceed with loading it.
   */
  else
  {
    g_module_make_resident (module);
    return NULL;
  }
}

G_MODULE_EXPORT int
gtk_module_init (gint * argc, char *** argv)
{
  GtkSettingsClass *gtk_settings_class;
  GtkScrolledWindowClass *gtk_scrolled_window_class;

  (void) argc;
  (void) argv;

  gtk_settings_class = g_type_class_ref (GTK_TYPE_SETTINGS);

  gtk_overlay_scrolling_pspec = g_param_spec_boolean ("gtk-overlay-scrolling",
                                                      "Overlay Scrolling",
                                                      "Whether to enable overlay scrolling mode globally",
                                                      overlay_scrolling_enabled,
                                                      G_PARAM_READWRITE);

  g_object_class_install_property (gtk_settings_class,
                                   PROP_OVERLAY_SCROLLING,
                                   gtk_overlay_scrolling_pspec);

  original_gtk_settings_set_property = G_OBJECT_CLASS (gtk_settings_class)->set_property;
  G_OBJECT_CLASS (gtk_settings_class)->set_property = overridden_gtk_settings_class_set_property;

  original_gtk_settings_get_property = G_OBJECT_CLASS (gtk_settings_class)->get_property;
  G_OBJECT_CLASS (gtk_settings_class)->get_property = overridden_gtk_settings_class_get_property;

  g_type_class_unref (gtk_settings_class);


  

  return 0;
}


static void overridden_gtk_settings_set_property (GObject      *object,
                                                  guint         property_id,
                                                  const GValue *value,
                                                  GParamSpec   *pspec)
{
  switch (property_id)
  {
  case PROP_OVERLAY_SCROLLING:
    overlay_scrolling_enabled = g_value_get_boolean (value);
    break;

  default:
    original_gtk_settings_set_property (object, property_id, value, pspec);
  }
}


static void overridden_gtk_settings_get_property (GObject      *object,
                                                  guint         property_id,
                                                  const GValue *value,
                                                  GParamSpec   *pspec)
{
  switch (property_id)
  {
  case PROP_OVERLAY_SCROLLING:
    g_value_set_boolean (value, overlay_scrolling_enabled);
    break;

  default:
    original_gtk_settings_get_property (object, property_id, value, pspec);
  }
}
