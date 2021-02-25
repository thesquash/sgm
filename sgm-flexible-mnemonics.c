/*
 * SGM -- The STLWRT-ian GTK Modules
 * Copyright (C) 2021 Gordon N. Squash.
 *
 * This module is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This module is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this module; see the file COPYING.  If not,
 * write to the Free Software Foundation, Inc., 51 Franklin Street,
 * Fifth Floor, Boston, MA  02110-1301  USA.
 */

/*
 * This module, "sgm-flexible-mnemonics", adds the code back to GTK to
 * configure the display of mnemonics -- mnemonics being the underlined
 * letters in menu items and buttons which, when the corresponding letter
 * key is pressed, activates the menu item or button in question.
 * Historically, GTK has allowed the user to alter whether mnemonics are
 * displayed at all and whether mnemonics are displayed all the time, or
 * only when the user presses a modifier key, seemingly about to activate
 * one of the widgets with a mnemonic.  Since GTK+ 3.9.8 (development
 * version of GTK+ 3.10), however, the behavior of mnemonics has been
 * hard-coded in GTK, and people who don't like the new default GTK
 * behavior are left frustrated that they, for example, can't see menu
 * mnemonics all the time.  This module adds the configurability back
 * to GTK.
 *
 * This module uses a slightly round-about hack to always display mnemonics.
 * This module hooks into the "size_allocate" function of each and every
 * GtkLabel, and ensures the label's toplevel window has the
 * "mnemonics-visible" property set to TRUE.  It would be nice to simply
 * hook into a GtkWindow's "mnemonics-visible" property and reset the
 * property to TRUE if it is ever set to FALSE by GTK.  However, this
 * doesn't work so well in practice, since in reality mnemonics are
 * displayed globally and then hidden on a per-label basis.  Hence we need
 * to ensure that no label has mnemonics turned off, if "gtk-auto-mnemonics"
 * is set to FALSE.
 */


#include <gtk/gtk.h>
#include <glib.h>


#undef   G_LOG_DOMAIN
#define  G_LOG_DOMAIN "SGM-Flexible-Mnemonics-Module"


static void (*original_gtk_label_size_allocate) (GtkWidget     *widget,
                                                 GtkAllocation *allocation);

static void sgm_gtk_label_size_allocate         (GtkWidget     *widget,
                                                 GtkAllocation *allocation);


/* Function definitions */
G_MODULE_EXPORT const char *
g_module_check_init (GModule *module)
{
  /*
   * Exit immediately on GTK+ versions prior to 3.9.8.  This is because
   * configurable mnemonics support was removed in 3.9.8, and this
   * module is unnecessary on earlier versions of GTK+.
   */
  if (gtk_check_version (3,9,8) != NULL)
  {
    g_warning ("\n   Your version of GTK+ is old enough that this module is redundant.\n"
               "   This module will therefore not load.");
    return "";
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
  GtkWidgetClass *gtk_label_class;

  (void) argc;
  (void) argv;

  gtk_label_class = g_type_class_ref (GTK_TYPE_LABEL);
  original_gtk_label_size_allocate = gtk_label_class->size_allocate;
  gtk_label_class->size_allocate = sgm_gtk_label_size_allocate;
  g_type_class_unref (gtk_label_class);

  return 0;
}


static void
sgm_gtk_label_size_allocate (GtkWidget     *widget,
                             GtkAllocation *allocation)
{
  GtkWidget   *toplevel_window;
  GtkSettings *settings;
  gboolean     auto_mnemonics;
  gboolean     mnemonics_visible;

  original_gtk_label_size_allocate (widget, allocation);

  toplevel_window = gtk_widget_get_toplevel (widget);
  settings = gtk_widget_get_settings (toplevel_window);
  g_object_get (settings, "gtk-auto-mnemonics", &auto_mnemonics, NULL);
  g_object_get (toplevel_window, "mnemonics-visible", &mnemonics_visible, NULL);

  if (!mnemonics_visible && !auto_mnemonics)
    g_object_set (toplevel_window, "mnemonics-visible", TRUE, NULL);
}
