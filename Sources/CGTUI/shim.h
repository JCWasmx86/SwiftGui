#pragma once

#include <adwaita.h>
#include <stdint.h>

static char **artificial_args = { "SwiftGui", NULL };

static void
application_on_activate_cb (void *, void *);
static void
button_on_click_cb (void *, void *);

static uint64_t
gtui_init_application (const char *name)
{
  g_assert_nonnull (name);

  AdwApplication *app = adw_application_new (strdup (name), G_APPLICATION_FLAGS_NONE);
  return (uint64_t)app;
}

static void
gtui_run_application (uint64_t ptr, uint64_t self)
{
  g_assert_nonnull (ptr);
  g_assert_nonnull (self);
  AdwApplication *app = ADW_APPLICATION ((void *)ptr);
  char          **args = { "foo", NULL };
  g_signal_connect (app, "activate", G_CALLBACK (application_on_activate_cb), (void *)self);
  g_application_run (G_APPLICATION (app), 0, NULL);
}

static uint64_t
gtui_create_window (uint64_t app)
{
  g_assert_nonnull (app);
  GApplication *application = app ? G_APPLICATION (app) : g_application_get_default ();
  GValue        value = G_VALUE_INIT;

  g_assert (G_IS_APPLICATION (application));

  g_value_init_from_instance (&value, application);
  AdwWindow *window = adw_window_new ();
  g_object_set_property (window, "application", &value);
  return (uint64_t)window;
}

static void
gtui_show_window (uint64_t ptr)
{
  g_assert_nonnull (ptr);
  AdwWindow *window = (void *)ptr;
  g_assert (ADW_IS_WINDOW (window));
  gtk_window_present (GTK_WINDOW (window));
}

static uint64_t
gtui_create_box (gboolean horizontal, int spacing)
{
  GtkWidget *ret = gtk_box_new (horizontal ? GTK_ORIENTATION_HORIZONTAL : GTK_ORIENTATION_VERTICAL, spacing);
  return ret;
}

static void
gtui_box_append (uint64_t box, uint64_t widget)
{
  g_assert_nonnull (box);
  g_assert_nonnull (widget);
  g_assert (GTK_IS_BOX (GTK_BOX ((void *)box)));
  g_assert (GTK_IS_WIDGET (GTK_WIDGET ((void *)widget)));

  gtk_box_append ((GtkBox *)box, (GtkWidget *)widget);
}

static void
gtui_box_prepend (uint64_t box, uint64_t widget)
{
  g_assert_nonnull (box);
  g_assert_nonnull (widget);
  g_assert (GTK_IS_BOX (GTK_BOX ((void *)box)));
  g_assert (GTK_IS_WIDGET (GTK_WIDGET ((void *)widget)));

  gtk_box_append ((GtkBox *)box, (GtkWidget *)widget);
}

static void
gtui_window_set_child (uint64_t window, uint64_t widget)
{
  g_assert_nonnull (window);
  g_assert_nonnull (widget);
  g_assert (ADW_IS_WINDOW (ADW_WINDOW ((void *)window)));
  g_assert (GTK_IS_WIDGET (GTK_WIDGET ((void *)widget)));

  adw_window_set_content (ADW_WINDOW (window), GTK_WIDGET (widget));
}

static uint64_t
gtui_create_label (const char *label)
{
  g_assert_nonnull (label);
  return (uint64_t)gtk_label_new (strdup (label));
}

static uint64_t
gtui_create_markup_label (const char *label)
{
  g_assert_nonnull (label);
  GtkLabel *lbl = GTK_LABEL (gtk_label_new (strdup (label)));
  gtk_label_set_use_markup (lbl, TRUE);
  return lbl;
}

static uint64_t
gtui_create_headerbar ()
{
  return (uint64_t)gtk_header_bar_new ();
}

static void
gtui_headerbar_set_title_widget (uint64_t bar, uint64_t widget)
{
  g_assert_nonnull (bar);
  g_assert_nonnull (widget);
  g_assert (GTK_IS_HEADER_BAR (GTK_HEADER_BAR ((void *)bar)));
  g_assert (GTK_IS_WIDGET (GTK_WIDGET ((void *)widget)));

  gtk_header_bar_set_title_widget (bar, widget);
}

static void
gtui_headerbar_pack_start (uint64_t bar, uint64_t widget)
{
  g_assert_nonnull (bar);
  g_assert_nonnull (widget);
  g_assert (GTK_IS_HEADER_BAR (GTK_HEADER_BAR ((void *)bar)));
  g_assert (GTK_IS_WIDGET (GTK_WIDGET ((void *)widget)));

  gtk_header_bar_pack_start (bar, widget);
}

static void
gtui_headerbar_pack_end (uint64_t bar, uint64_t widget)
{
  g_assert_nonnull (bar);
  g_assert_nonnull (widget);
  g_assert (GTK_IS_HEADER_BAR (GTK_HEADER_BAR ((void *)bar)));
  g_assert (GTK_IS_WIDGET (GTK_WIDGET ((void *)widget)));

  gtk_header_bar_pack_end (bar, widget);
}

static void
gtui_headerbar_set_show_title_buttons (uint64_t bar, gboolean enabled)
{
  g_assert_nonnull (bar);
  g_assert (GTK_IS_HEADER_BAR (GTK_HEADER_BAR ((void *)bar)));

  gtk_header_bar_set_show_title_buttons (bar, enabled);
}

static uint64_t
gtui_create_button (const char *label)
{
  return (uint64_t)gtk_button_new_with_label (strdup (label));
}

static uint64_t
gtui_button_init_signals (uint64_t btn, uint64_t data)
{
  GtkButton *button;

  g_assert_nonnull (btn);
  g_assert_nonnull (data);
  g_assert (GTK_IS_BUTTON (GTK_BUTTON ((void *)btn)));

  button = GTK_BUTTON (btn);
  swift_retain (data);
  g_signal_connect (button, "clicked", G_CALLBACK (button_on_click_cb), (void *)data);
}

static uint64_t
gtui_create_title_bar_widget (const char *title, const char *subtitle)
{
  return (uint64_t)adw_window_title_new (strdup (title), strdup (subtitle));
}

static uint64_t
gtui_create_scrolled ()
{
  return (uint64_t)gtk_scrolled_window_new ();
}

static uint64_t
gtui_scrolled_set_child (uint64_t scrolled, uint64_t widget)
{
  g_assert_nonnull (scrolled);
  g_assert_nonnull (widget);
  g_assert (GTK_IS_SCROLLED_WINDOW (GTK_SCROLLED_WINDOW ((void *)scrolled)));
  g_assert (GTK_IS_WIDGET (GTK_WIDGET ((void *)widget)));

  gtk_scrolled_window_set_child ((GtkScrolledWindow *)scrolled, (GtkWidget *)widget);
}

static uint64_t
gtui_create_textview ()
{
  return (uint64_t)gtk_text_view_new ();
}

static uint64_t
gtui_create_stringlist ()
{
  return (uint64_t)gtk_string_list_new (NULL);
}

static uint64_t
gtui_create_text_dropdown (uint64_t list)
{
  g_assert (GTK_IS_STRING_LIST (list));

  return (uint64_t)gtk_drop_down_new (GTK_STRING_LIST (list), NULL);
}

static uint64_t
gtui_stringlist_append (uint64_t list, const char *str)
{
  g_assert (GTK_IS_STRING_LIST (list));

  gtk_string_list_take (list, strdup (str));
}

static void
gtui_box_remove (uint64_t box, uint64_t widget)
{
  g_assert_nonnull (box);
  g_assert_nonnull (widget);
  g_assert (GTK_IS_BOX (GTK_BOX ((void *)box)));
  g_assert (GTK_IS_WIDGET (GTK_WIDGET ((void *)widget)));

  gtk_box_remove ((GtkBox *)box, (GtkWidget *)widget);
}
