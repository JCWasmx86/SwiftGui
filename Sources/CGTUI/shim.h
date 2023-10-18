#pragma once

#include <adwaita.h>
#include <stdint.h>

static char **artificial_args = { "SwiftGui", NULL };

static void
application_on_activate_cb (void *, void *);
static void
application_on_action_cb (void *, const char *, void *);
static void
application_window_on_action_cb (void *, const char *, void *);
static void
banner_on_click_cb (void *, void *);
static void
button_on_click_cb (void *, void *);
static void
entryrow_on_submit_cb (void *, void *);
static void
messagedialog_on_click_cb (void *, void *, void *);
static void
splitbutton_on_click_cb (void *, void *);
static uint64_t
taboverview_on_create_tab_cb (void *, void *);
static void
tabbutton_on_click_cb (void *, void *);
static void
toast_on_click_cb (void *, void *);
static gboolean
window_close_cb (void *, void *);
static void
listbox_on_select_row_cb (void *, void *, void *);

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

static void
gtui_quit_application (uint64_t ptr)
{
  g_assert_nonnull (ptr);
  AdwApplication *app = ADW_APPLICATION ((void *)ptr);
  g_application_quit (G_APPLICATION (app));
}

typedef struct
{
  uint64_t    ptr;
  uint64_t    self;
  const char *id;
} CallbackData;

static void
gtui_application_run_action_handler (gpointer user_data)
{
  CallbackData *data = (CallbackData *)user_data;
  application_on_action_cb (data->ptr, data->id, data->self);
}

static void
gtui_application_add_keyboard_shortcut (uint64_t    ptr,
                                        uint64_t    self,
                                        const char *shortcut,
                                        const char *id,
                                        const char *full_id)
{
  g_assert_nonnull (ptr);
  AdwApplication *app = ADW_APPLICATION ((void *)ptr);
  GSimpleAction  *action = g_simple_action_new (id, NULL);

  CallbackData *data = g_new0 (CallbackData, 1);
  data->ptr = ptr;
  data->self = self;
  data->id = id;
  g_signal_connect_data (action,
                         "activate",
                         G_CALLBACK (gtui_application_run_action_handler),
                         (gpointer)data,
                         (GDestroyNotify)g_free,
                         G_CONNECT_SWAPPED);

  g_action_map_add_action (app, action);
  const char *shortcuts[] = { shortcut, NULL };
  gtk_application_set_accels_for_action (app, full_id, shortcuts);
}

static void
gtui_application_window_run_action_handler (gpointer user_data)
{
  CallbackData *data = (CallbackData *)user_data;
  application_window_on_action_cb (data->ptr, data->id, data->self);
}

static void
gtui_application_window_add_keyboard_shortcut (uint64_t    ptr,
                                               uint64_t    self,
                                               uint64_t    app_ptr,
                                               const char *shortcut,
                                               const char *id,
                                               const char *full_id)
{
  g_assert_nonnull (ptr);
  g_assert_nonnull (app_ptr);
  AdwApplicationWindow *window = ADW_APPLICATION_WINDOW ((void *)ptr);
  AdwApplication       *app = ADW_APPLICATION ((void *)app_ptr);
  GSimpleAction        *action = g_simple_action_new (id, NULL);

  CallbackData *data = g_new0 (CallbackData, 1);
  data->ptr = ptr;
  data->self = self;
  data->id = id;
  g_signal_connect_data (action,
                         "activate",
                         G_CALLBACK (gtui_application_window_run_action_handler),
                         (gpointer)data,
                         (GDestroyNotify)g_free,
                         G_CONNECT_SWAPPED);

  g_action_map_add_action (window, action);
  const char *shortcuts[] = { shortcut, NULL };
  gtk_application_set_accels_for_action (app, full_id, shortcuts);
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

static uint64_t
gtui_create_application_window (uint64_t app)
{
  g_assert_nonnull (app);
  GtkApplication *application = GTK_APPLICATION (app);

  g_assert (G_IS_APPLICATION (application));

  AdwApplicationWindow *window = adw_application_window_new (application);
  return (uint64_t)window;
}

static void
gtui_window_init_signals (uint64_t win, uint64_t data)
{
  GtkWindow *window;

  g_assert_nonnull (win);
  g_assert_nonnull (data);
  g_assert (GTK_IS_WINDOW (GTK_WINDOW ((void *)win)));

  window = GTK_WINDOW (win);
  swift_retain (data);
  g_signal_connect (window, "close-request", G_CALLBACK (window_close_cb), (void *)data);
}

static void
gtui_show_window (uint64_t ptr)
{
  g_assert_nonnull (ptr);
  GtkWindow *window = (void *)ptr;
  g_assert (GTK_IS_WINDOW (window));
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

  gtk_box_prepend ((GtkBox *)box, (GtkWidget *)widget);
}

static void
gtui_box_insert_after (uint64_t box, uint64_t widget, uint64_t previous_widget)
{
  g_assert_nonnull (box);
  g_assert_nonnull (widget);
  g_assert (GTK_IS_BOX (GTK_BOX ((void *)box)));
  g_assert (GTK_IS_WIDGET (GTK_WIDGET ((void *)widget)));

  gtk_box_insert_child_after ((GtkBox *)box, (GtkWidget *)widget, (GtkWidget *)previous_widget);
}

static uint64_t
gtui_create_listbox ()
{
  return (uint64_t)gtk_list_box_new ();
}

static void
gtui_listbox_init_signals (uint64_t bx, uint64_t data)
{
  GtkListBox *box;

  g_assert_nonnull (bx);
  g_assert_nonnull (data);
  g_assert (GTK_IS_LIST_BOX (GTK_LIST_BOX ((void *)bx)));

  box = GTK_LIST_BOX (bx);
  swift_retain (data);
  g_signal_connect (box, "row-selected", G_CALLBACK (listbox_on_select_row_cb), (void *)data);

  gtk_list_box_set_selection_mode (box, GTK_SELECTION_BROWSE);
}

static void
gtui_listbox_append (uint64_t box, uint64_t widget)
{
  g_assert_nonnull (box);
  g_assert_nonnull (widget);
  g_assert (GTK_IS_LIST_BOX (GTK_LIST_BOX ((void *)box)));
  g_assert (GTK_IS_WIDGET (GTK_WIDGET ((void *)widget)));

  gtk_list_box_append ((GtkListBox *)box, (GtkWidget *)widget);
}

static void
gtui_listbox_prepend (uint64_t box, uint64_t widget)
{
  g_assert_nonnull (box);
  g_assert_nonnull (widget);
  g_assert (GTK_IS_LIST_BOX (GTK_LIST_BOX ((void *)box)));
  g_assert (GTK_IS_WIDGET (GTK_WIDGET ((void *)widget)));

  gtk_list_box_prepend ((GtkListBox *)box, (GtkWidget *)widget);
}

static void
gtui_listbox_insert (uint64_t box, uint64_t widget, int position)
{
  g_assert_nonnull (box);
  g_assert_nonnull (widget);
  g_assert (GTK_IS_LIST_BOX (GTK_LIST_BOX ((void *)box)));
  g_assert (GTK_IS_WIDGET (GTK_WIDGET ((void *)widget)));

  gtk_list_box_insert ((GtkListBox *)box, (GtkWidget *)widget, position);
}

static uint64_t
gtui_listbox_get_selected_row (uint64_t box)
{
  g_assert_nonnull (box);
  g_assert (GTK_IS_LIST_BOX (GTK_LIST_BOX ((void *)box)));

  return (uint64_t)gtk_list_box_get_selected_row ((GtkListBox *)box);
}

static void
gtui_listbox_select_row (uint64_t box, int index)
{
  g_assert_nonnull (box);
  g_assert (GTK_IS_LIST_BOX (GTK_LIST_BOX ((void *)box)));

  GtkListBoxRow *row = gtk_list_box_get_row_at_index (box, index);
  gtk_list_box_select_row (box, row);
}

static uint64_t
gtk_listboxrow_get_child (uint64_t row)
{
  g_assert_nonnull (row);
  g_assert (GTK_IS_LIST_BOX_ROW (GTK_LIST_BOX_ROW ((void *)row)));

  return (uint64_t)gtk_list_box_row_get_child (row);
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

static void
gtui_application_window_set_child (uint64_t window, uint64_t widget)
{
  g_assert_nonnull (window);
  g_assert_nonnull (widget);
  g_assert (ADW_IS_APPLICATION_WINDOW (ADW_APPLICATION_WINDOW ((void *)window)));
  g_assert (GTK_IS_WIDGET (GTK_WIDGET ((void *)widget)));

  adw_application_window_set_content (ADW_APPLICATION_WINDOW (window), GTK_WIDGET (widget));
}

static void
gtui_window_set_transient_for (uint64_t window, uint64_t parent)
{
  g_assert_nonnull (window);
  g_assert_nonnull (parent);
  g_assert (GTK_IS_WINDOW (GTK_WINDOW ((void *)window)));
  g_assert (GTK_IS_WINDOW (GTK_WINDOW ((void *)parent)));

  gtk_window_set_transient_for (window, parent);
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
  return (uint64_t)adw_header_bar_new ();
}

static void
gtui_headerbar_set_title_widget (uint64_t bar, uint64_t widget)
{
  g_assert_nonnull (bar);
  g_assert_nonnull (widget);
  g_assert (ADW_IS_HEADER_BAR (ADW_HEADER_BAR ((void *)bar)));
  g_assert (GTK_IS_WIDGET (GTK_WIDGET ((void *)widget)));

  adw_header_bar_set_title_widget (bar, widget);
}

static void
gtui_headerbar_pack_start (uint64_t bar, uint64_t widget)
{
  g_assert_nonnull (bar);
  g_assert_nonnull (widget);
  g_assert (ADW_IS_HEADER_BAR (ADW_HEADER_BAR ((void *)bar)));
  g_assert (GTK_IS_WIDGET (GTK_WIDGET ((void *)widget)));

  adw_header_bar_pack_start (bar, widget);
}

static void
gtui_headerbar_pack_end (uint64_t bar, uint64_t widget)
{
  g_assert_nonnull (bar);
  g_assert_nonnull (widget);
  g_assert (ADW_IS_HEADER_BAR (ADW_HEADER_BAR ((void *)bar)));
  g_assert (GTK_IS_WIDGET (GTK_WIDGET ((void *)widget)));

  adw_header_bar_pack_end (bar, widget);
}

static void
gtui_headerbar_remove (uint64_t bar, uint64_t widget)
{
  g_assert_nonnull (bar);
  g_assert_nonnull (widget);
  g_assert (ADW_IS_HEADER_BAR (ADW_HEADER_BAR ((void *)bar)));
  g_assert (GTK_IS_WIDGET (GTK_WIDGET ((void *)widget)));

  adw_header_bar_remove ((AdwHeaderBar *)bar, (GtkWidget *)widget);
}

static void
gtui_headerbar_set_show_title_buttons (uint64_t bar, gboolean enabled)
{
  g_assert_nonnull (bar);
  g_assert (ADW_IS_HEADER_BAR (ADW_HEADER_BAR ((void *)bar)));

  adw_header_bar_set_show_end_title_buttons (bar, enabled);
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

static void
gtui_button_set_child (uint64_t button, uint64_t widget)
{
  g_assert_nonnull (button);
  g_assert_nonnull (widget);
  g_assert (GTK_IS_BUTTON (GTK_BUTTON ((void *)button)));
  g_assert (GTK_IS_WIDGET (GTK_WIDGET ((void *)widget)));

  gtk_button_set_child (button, widget);
}

static void
gtui_button_set_label (uint64_t button, const char *label)
{
  g_assert_nonnull (button);
  g_assert_nonnull (label);
  g_assert (GTK_IS_BUTTON (GTK_BUTTON ((void *)button)));

  gtk_button_set_label (button, strdup (label));
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
gtui_create_statuspage ()
{
  return (uint64_t)adw_status_page_new ();
}

static void
gtui_statuspage_set_title (uint64_t statuspage, const char *title)
{
  g_assert_nonnull (statuspage);
  g_assert_nonnull (title);
  g_assert (ADW_IS_STATUS_PAGE (ADW_STATUS_PAGE ((void *)statuspage)));

  adw_status_page_set_title (statuspage, strdup (title));
}

static void
gtui_statuspage_set_description (uint64_t statuspage, const char *description)
{
  g_assert_nonnull (statuspage);
  g_assert_nonnull (description);
  g_assert (ADW_IS_STATUS_PAGE (ADW_STATUS_PAGE ((void *)statuspage)));

  adw_status_page_set_description (statuspage, strdup (description));
}

static void
gtui_statuspage_set_icon_name (uint64_t statuspage, const char *icon)
{
  g_assert_nonnull (statuspage);
  g_assert_nonnull (icon);
  g_assert (ADW_IS_STATUS_PAGE (ADW_STATUS_PAGE ((void *)statuspage)));

  adw_status_page_set_icon_name (statuspage, strdup (icon));
}

static void
gtui_statuspage_set_child (uint64_t statuspage, uint64_t child)
{
  g_assert_nonnull (statuspage);
  g_assert_nonnull (child);
  g_assert (ADW_IS_STATUS_PAGE (ADW_STATUS_PAGE ((void *)statuspage)));
  g_assert (GTK_IS_WIDGET (GTK_WIDGET ((void *)child)));

  adw_status_page_set_child (statuspage, child);
}

static uint64_t
gtui_create_toast (const char *title)
{
  g_assert_nonnull (title);
  return (uint64_t)adw_toast_new (strdup (title));
}

static void
gtui_toast_init_signals (uint64_t tst, uint64_t data)
{
  AdwToast *toast;

  g_assert_nonnull (tst);
  g_assert_nonnull (data);
  g_assert (ADW_IS_TOAST (ADW_TOAST ((void *)tst)));

  toast = ADW_TOAST (tst);
  swift_retain (data);
  g_signal_connect (tst, "button-clicked", G_CALLBACK (toast_on_click_cb), (void *)data);
}

static void
gtui_toast_dismiss (uint64_t tst)
{
  AdwToast *toast;

  g_assert_nonnull (tst);
  g_assert (ADW_IS_TOAST (ADW_TOAST ((void *)tst)));

  toast = ADW_TOAST (tst);
  adw_toast_dismiss (toast);
}

static void
gtui_toast_set_button (uint64_t toast, const char *title)
{
  g_assert_nonnull (toast);
  g_assert_nonnull (title);
  g_assert (ADW_IS_TOAST (ADW_TOAST ((void *)toast)));

  adw_toast_set_button_label (toast, strdup (title));
}

static uint64_t
gtui_create_toastoverlay (uint64_t child)
{
  g_assert_nonnull (child);
  g_assert (GTK_IS_WIDGET (GTK_WIDGET ((void *)child)));
  AdwToastOverlay *toastoverlay = ADW_TOAST_OVERLAY (adw_toast_overlay_new ());
  adw_toast_overlay_set_child (toastoverlay, child);
  return toastoverlay;
}

static void
gtui_toastoverlay_add_toast (uint64_t toastoverlay, uint64_t toast)
{
  g_assert_nonnull (toastoverlay);
  g_assert_nonnull (toast);
  g_assert (ADW_IS_TOAST_OVERLAY (ADW_TOAST_OVERLAY ((void *)toastoverlay)));
  g_assert (ADW_IS_TOAST (ADW_TOAST ((void *)toast)));

  adw_toast_overlay_add_toast (toastoverlay, toast);
}

static uint64_t
gtui_create_banner (const char *title)
{
  g_assert_nonnull (title);
  return (uint64_t)adw_banner_new (strdup (title));
}

static void
gtui_banner_init_signals (uint64_t bnr, uint64_t data)
{
  AdwBanner *banner;

  g_assert_nonnull (bnr);
  g_assert_nonnull (data);
  g_assert (ADW_IS_BANNER (ADW_BANNER ((void *)bnr)));

  banner = ADW_BANNER (bnr);
  swift_retain (data);
  g_signal_connect (bnr, "button-clicked", G_CALLBACK (banner_on_click_cb), (void *)data);
}

static void
gtui_banner_set_button (uint64_t banner, const char *title)
{
  g_assert_nonnull (banner);
  g_assert_nonnull (title);
  g_assert (ADW_IS_BANNER (ADW_BANNER ((void *)banner)));

  adw_banner_set_button_label (banner, strdup (title));
}

static void
gtui_banner_set_revealed (uint64_t banner, gboolean revealed)
{
  g_assert_nonnull (banner);
  g_assert (ADW_IS_BANNER (ADW_BANNER ((void *)banner)));

  adw_banner_set_revealed (banner, revealed);
}

static gboolean
gtui_banner_is_revealed (uint64_t banner)
{
  g_assert_nonnull (banner);
  g_assert (ADW_IS_BANNER (ADW_BANNER ((void *)banner)));

  return adw_banner_get_revealed (banner);
}

static uint64_t
gtui_create_avatar (int size, const char *text, gboolean show_initials)
{
  return (uint64_t)adw_avatar_new (size, text, show_initials);
}

static void
gtui_avatar_set_icon_name (uint64_t avatar, const char *icon_name)
{
  g_assert_nonnull (avatar);
  g_assert_nonnull (icon_name);
  g_assert (ADW_IS_AVATAR (ADW_AVATAR ((void *)avatar)));

  adw_avatar_set_icon_name (avatar, icon_name);
}

static uint64_t
gtui_create_messagedialog (uint64_t parent, const char *heading, const char *body)
{
  return (uint64_t)adw_message_dialog_new (parent, heading, body);
}

static void
gtui_messagedialog_init_signals (uint64_t msg, uint64_t data)
{
  AdwMessageDialog *msgdialog;

  g_assert_nonnull (msg);
  g_assert_nonnull (data);
  g_assert (ADW_IS_MESSAGE_DIALOG (ADW_MESSAGE_DIALOG ((void *)msg)));

  msgdialog = ADW_MESSAGE_DIALOG (msg);
  swift_retain (data);
  g_signal_connect (msgdialog, "response", G_CALLBACK (messagedialog_on_click_cb), (void *)data);
}

static void
gtui_messagedialog_present (uint64_t messagedialog)
{
  g_assert_nonnull (messagedialog);
  g_assert (ADW_IS_MESSAGE_DIALOG (ADW_MESSAGE_DIALOG ((void *)messagedialog)));

  adw_message_dialog_set_heading_use_markup (messagedialog, TRUE);
  adw_message_dialog_set_body_use_markup (messagedialog, TRUE);
  gtk_window_present (GTK_WINDOW (messagedialog));
}

static void
gtui_messagedialog_add_response (uint64_t    messagedialog,
                                 const char *id,
                                 const char *label,
                                 int         appearance,
                                 gboolean    enabled,
                                 int         type)
{
  g_assert_nonnull (messagedialog);
  g_assert_nonnull (id);
  g_assert_nonnull (label);
  g_assert (ADW_IS_MESSAGE_DIALOG (ADW_MESSAGE_DIALOG ((void *)messagedialog)));

  AdwResponseAppearance adwAppearance = ADW_RESPONSE_DEFAULT;

  switch (appearance)
    {
    case 1:
      adwAppearance = ADW_RESPONSE_SUGGESTED;
      break;
    case 2:
      adwAppearance = ADW_RESPONSE_DESTRUCTIVE;
      break;
    }

  adw_message_dialog_add_response (messagedialog, id, label);
  adw_message_dialog_set_response_appearance (messagedialog, id, adwAppearance);
  adw_message_dialog_set_response_enabled (messagedialog, id, enabled);

  switch (type)
    {
    case 1:
      adw_message_dialog_set_close_response (messagedialog, id);
      break;
    case 2:
      adw_message_dialog_set_default_response (messagedialog, id);
    }
}

static void
gtui_messagedialog_set_extra_child (uint64_t messagedialog, uint64_t child)
{
  g_assert_nonnull (messagedialog);
  g_assert (ADW_IS_MESSAGE_DIALOG (ADW_MESSAGE_DIALOG ((void *)messagedialog)));

  adw_message_dialog_set_extra_child (messagedialog, child);
}

static uint64_t
gtui_create_preferenceswindow ()
{
  return (uint64_t)adw_preferences_window_new ();
}

static void
gtui_preferenceswindow_add (uint64_t window, uint64_t page)
{
  g_assert_nonnull (window);
  g_assert_nonnull (page);
  g_assert (ADW_IS_PREFERENCES_WINDOW (ADW_PREFERENCES_WINDOW ((void *)window)));
  g_assert (ADW_IS_PREFERENCES_PAGE (ADW_PREFERENCES_PAGE ((void *)page)));

  adw_preferences_window_add (window, page);
}

static void
gtui_preferenceswindow_add_toast (uint64_t window, uint64_t toast)
{
  g_assert_nonnull (window);
  g_assert_nonnull (toast);
  g_assert (ADW_IS_PREFERENCES_WINDOW (ADW_PREFERENCES_WINDOW ((void *)window)));
  g_assert (ADW_IS_TOAST (ADW_TOAST ((void *)toast)));

  adw_preferences_window_add_toast (window, toast);
}

static uint64_t
gtui_create_preferencespage (const char *name, const char *icon, const char *description)
{
  g_assert_nonnull (name);
  g_assert_nonnull (icon);
  g_assert_nonnull (description);

  AdwPreferencesPage *page = ADW_PREFERENCES_PAGE (adw_preferences_page_new ());
  adw_preferences_page_set_title (page, name);
  adw_preferences_page_set_name (page, name);
  adw_preferences_page_set_icon_name (page, icon);
  adw_preferences_page_set_description (page, description);

  return page;
}

static void
gtui_preferencespage_add (uint64_t page, uint64_t group)
{
  g_assert_nonnull (page);
  g_assert_nonnull (group);
  g_assert (ADW_IS_PREFERENCES_PAGE (ADW_PREFERENCES_PAGE ((void *)page)));
  g_assert (ADW_IS_PREFERENCES_GROUP (ADW_PREFERENCES_GROUP ((void *)group)));

  adw_preferences_page_add (page, group);
}

static uint64_t
gtui_create_preferencesgroup (const char *name, const char *description)
{
  g_assert_nonnull (name);
  g_assert_nonnull (description);

  AdwPreferencesGroup *group = ADW_PREFERENCES_GROUP (adw_preferences_group_new ());
  adw_preferences_group_set_title (group, name);
  adw_preferences_group_set_description (group, description);

  return group;
}

static void
gtui_preferencesgroup_add (uint64_t preferencesgroup, uint64_t child)
{
  g_assert_nonnull (preferencesgroup);
  g_assert_nonnull (child);
  g_assert (ADW_IS_PREFERENCES_GROUP (ADW_PREFERENCES_GROUP ((void *)preferencesgroup)));
  g_assert (GTK_IS_WIDGET (GTK_WIDGET ((void *)child)));

  adw_preferences_group_add (preferencesgroup, child);
}

static void
gtui_preferencesgroup_header_suffix (uint64_t preferencesgroup, uint64_t child)
{
  g_assert_nonnull (preferencesgroup);
  g_assert_nonnull (child);
  g_assert (ADW_IS_PREFERENCES_GROUP (ADW_PREFERENCES_GROUP ((void *)preferencesgroup)));
  g_assert (GTK_IS_WIDGET (GTK_WIDGET ((void *)child)));

  adw_preferences_group_set_header_suffix (preferencesgroup, child);
}

static void
gtui_preferencesrow_set_title (uint64_t preferencesrow, const char *title)
{
  g_assert_nonnull (preferencesrow);
  g_assert_nonnull (title);
  g_assert (ADW_IS_PREFERENCES_ROW (ADW_PREFERENCES_ROW ((void *)preferencesrow)));

  adw_preferences_row_set_title (preferencesrow, title);
}

static uint64_t
gtui_create_actionrow ()
{
  return (uint64_t)adw_action_row_new ();
}

static void
gtui_actionrow_set_subtitle (uint64_t actionrow, const char *subtitle)
{
  g_assert_nonnull (actionrow);
  g_assert_nonnull (subtitle);
  g_assert (ADW_IS_ACTION_ROW (ADW_ACTION_ROW ((void *)actionrow)));

  adw_action_row_set_subtitle (actionrow, subtitle);
}

static void
gtui_actionrow_add_prefix (uint64_t actionrow, uint64_t widget)
{
  g_assert_nonnull (actionrow);
  g_assert_nonnull (widget);
  g_assert (ADW_IS_ACTION_ROW (ADW_ACTION_ROW ((void *)actionrow)));
  g_assert (GTK_IS_WIDGET (GTK_WIDGET ((void *)widget)));

  adw_action_row_add_prefix (actionrow, widget);
}

static void
gtui_actionrow_add_suffix (uint64_t actionrow, uint64_t widget)
{
  g_assert_nonnull (actionrow);
  g_assert_nonnull (widget);
  g_assert (ADW_IS_ACTION_ROW (ADW_ACTION_ROW ((void *)actionrow)));
  g_assert (GTK_IS_WIDGET (GTK_WIDGET ((void *)widget)));

  adw_action_row_add_suffix (actionrow, widget);
}

static uint64_t
gtui_create_comborow (uint64_t list)
{
  g_assert (GTK_IS_STRING_LIST (list));

  AdwComboRow *row = ADW_COMBO_ROW (adw_combo_row_new ());
  adw_combo_row_set_model (row, list);
  return row;
}

static uint64_t
gtui_create_expanderrow ()
{
  return (uint64_t)adw_expander_row_new ();
}

static void
gtui_expanderrow_set_subtitle (uint64_t expanderrow, const char *subtitle)
{
  g_assert_nonnull (expanderrow);
  g_assert_nonnull (subtitle);
  g_assert (ADW_IS_EXPANDER_ROW (ADW_EXPANDER_ROW ((void *)expanderrow)));

  adw_expander_row_set_subtitle (expanderrow, subtitle);
}

static void
gtui_expanderrow_add_prefix (uint64_t expanderrow, uint64_t widget)
{
  g_assert_nonnull (expanderrow);
  g_assert_nonnull (widget);
  g_assert (ADW_IS_EXPANDER_ROW (ADW_EXPANDER_ROW ((void *)expanderrow)));
  g_assert (GTK_IS_WIDGET (GTK_WIDGET ((void *)widget)));

  adw_expander_row_add_prefix (expanderrow, widget);
}

static void
gtui_expanderrow_add_row (uint64_t expanderrow, uint64_t widget)
{
  g_assert_nonnull (expanderrow);
  g_assert_nonnull (widget);
  g_assert (ADW_IS_EXPANDER_ROW (ADW_EXPANDER_ROW ((void *)expanderrow)));
  g_assert (GTK_IS_WIDGET (GTK_WIDGET ((void *)widget)));

  adw_expander_row_add_row (expanderrow, widget);
}

static uint64_t
gtui_create_entryrow ()
{
  return (uint64_t)adw_entry_row_new ();
}

static uint64_t
gtui_entryrow_init_signals (uint64_t er, uint64_t data)
{
  GtkButton *entryrow;

  g_assert_nonnull (er);
  g_assert_nonnull (data);
  g_assert (ADW_IS_ENTRY_ROW (ADW_ENTRY_ROW ((void *)er)));

  entryrow = ADW_ENTRY_ROW (er);
  swift_retain (data);
  g_signal_connect (entryrow, "apply", G_CALLBACK (entryrow_on_submit_cb), (void *)data);
}

static void
gtui_entryrow_add_prefix (uint64_t entryrow, uint64_t widget)
{
  g_assert_nonnull (entryrow);
  g_assert_nonnull (widget);
  g_assert (ADW_IS_ENTRY_ROW (ADW_ENTRY_ROW ((void *)entryrow)));
  g_assert (GTK_IS_WIDGET (GTK_WIDGET ((void *)widget)));

  adw_entry_row_add_prefix (entryrow, widget);
}

static void
gtui_entryrow_add_suffix (uint64_t entryrow, uint64_t widget)
{
  g_assert_nonnull (entryrow);
  g_assert_nonnull (widget);
  g_assert (ADW_IS_ENTRY_ROW (ADW_ENTRY_ROW ((void *)entryrow)));
  g_assert (GTK_IS_WIDGET (GTK_WIDGET ((void *)widget)));

  adw_entry_row_add_suffix (entryrow, widget);
}

static void
gtui_entryrow_set_show_apply_button (uint64_t entryrow, gboolean visibility)
{
  g_assert_nonnull (entryrow);
  g_assert (ADW_IS_ENTRY_ROW (ADW_ENTRY_ROW ((void *)entryrow)));

  adw_entry_row_set_show_apply_button (entryrow, visibility);
}

static uint64_t
gtui_create_passwordentryrow ()
{
  return (uint64_t)adw_password_entry_row_new ();
}

static uint64_t
gtui_create_switchrow ()
{
  return (uint64_t)adw_switch_row_new ();
}

static gboolean
gtui_switchrow_get_active (uint64_t switchrow)
{
  g_assert_nonnull (switchrow);
  g_assert (ADW_IS_SWITCH_ROW (ADW_SWITCH_ROW ((void *)switchrow)));

  return adw_switch_row_get_active (switchrow);
}

static void
gtui_switchrow_set_active (uint64_t switchrow, gboolean active)
{
  g_assert_nonnull (switchrow);
  g_assert (ADW_IS_SWITCH_ROW (ADW_SWITCH_ROW ((void *)switchrow)));

  adw_switch_row_set_active (switchrow, active);
}

static uint64_t
gtui_create_spinrow (double min, double max, double step)
{
  return (uint64_t)adw_spin_row_new_with_range (min, max, step);
}

static void
gtui_spinrow_set_configuration (uint64_t spinrow, double min, double max, double step)
{
  g_assert_nonnull (spinrow);
  g_assert (ADW_IS_SPIN_ROW (ADW_SPIN_ROW ((void *)spinrow)));

  adw_spin_row_configure (spinrow, gtk_adjustment_new (0, min, max, step, step, 0), 0, 0);
}

static double
gtui_spinrow_get_value (uint64_t spinrow)
{
  g_assert_nonnull (spinrow);
  g_assert (ADW_IS_SPIN_ROW (ADW_SPIN_ROW ((void *)spinrow)));

  return adw_spin_row_get_value (spinrow);
}

static void
gtui_spinrow_set_value (uint64_t spinrow, double value)
{
  g_assert_nonnull (spinrow);
  g_assert (ADW_IS_SPIN_ROW (ADW_SPIN_ROW ((void *)spinrow)));

  adw_spin_row_set_value (spinrow, value);
}

static uint64_t
gtui_create_navigationview ()
{
  return (uint64_t)adw_navigation_view_new ();
}

static uint64_t
gtui_navigationview_add (uint64_t navigationview, uint64_t widget, const char *title)
{
  g_assert_nonnull (navigationview);
  g_assert_nonnull (widget);
  g_assert_nonnull (title);
  g_assert (ADW_IS_NAVIGATION_VIEW (ADW_NAVIGATION_VIEW ((void *)navigationview)));
  g_assert (GTK_IS_WIDGET (GTK_WIDGET ((void *)widget)));

  AdwNavigationPage *navigationpage = adw_navigation_page_new (widget, title);
  adw_navigation_view_push (navigationview, navigationpage);
  return (uint64_t)navigationpage;
}

static void
gtui_navigationview_remove (uint64_t navigationview, uint64_t widget, gboolean pop)
{
  g_assert_nonnull (navigationview);
  g_assert_nonnull (widget);
  g_assert (ADW_IS_NAVIGATION_VIEW (ADW_NAVIGATION_VIEW ((void *)navigationview)));
  g_assert (ADW_IS_NAVIGATION_PAGE (ADW_NAVIGATION_PAGE ((void *)widget)));

  adw_navigation_view_remove (navigationview, widget);

  if (pop)
    {
      adw_navigation_view_pop (navigationview);
    }
}

static uint64_t
gtui_create_navigationsplitview ()
{
  return (uint64_t)adw_navigation_split_view_new ();
}

static void
gtui_navigationsplitview_set_sidebar (uint64_t navigationsplitview, uint64_t sidebar, const char *title)
{
  g_assert_nonnull (navigationsplitview);
  g_assert_nonnull (sidebar);
  g_assert_nonnull (title);
  g_assert (ADW_IS_NAVIGATION_SPLIT_VIEW (ADW_NAVIGATION_SPLIT_VIEW ((void *)navigationsplitview)));
  g_assert (GTK_IS_WIDGET (GTK_WIDGET ((void *)sidebar)));

  AdwNavigationPage *navigationpage = adw_navigation_page_new (sidebar, title);
  adw_navigation_split_view_set_sidebar (navigationsplitview, navigationpage);
}

static void
gtui_navigationsplitview_set_content (uint64_t navigationsplitview, uint64_t content, const char *title)
{
  g_assert_nonnull (navigationsplitview);
  g_assert_nonnull (content);
  g_assert_nonnull (title);
  g_assert (ADW_IS_NAVIGATION_SPLIT_VIEW (ADW_NAVIGATION_SPLIT_VIEW ((void *)navigationsplitview)));
  g_assert (GTK_IS_WIDGET (GTK_WIDGET ((void *)content)));

  AdwNavigationPage *navigationpage = adw_navigation_page_new (content, title);
  adw_navigation_split_view_set_content (navigationsplitview, navigationpage);
}

static uint64_t
gtui_create_overlaysplitview ()
{
  return (uint64_t)adw_overlay_split_view_new ();
}

static void
gtui_overlaysplitview_set_sidebar (uint64_t overlaysplitview, uint64_t sidebar)
{
  g_assert_nonnull (overlaysplitview);
  g_assert_nonnull (sidebar);
  g_assert (ADW_IS_OVERLAY_SPLIT_VIEW (ADW_OVERLAY_SPLIT_VIEW ((void *)overlaysplitview)));
  g_assert (GTK_IS_WIDGET (GTK_WIDGET ((void *)sidebar)));

  adw_overlay_split_view_set_sidebar (overlaysplitview, sidebar);
}

static void
gtui_overlaysplitview_set_content (uint64_t overlaysplitview, uint64_t content)
{
  g_assert_nonnull (overlaysplitview);
  g_assert_nonnull (content);
  g_assert (ADW_IS_OVERLAY_SPLIT_VIEW (ADW_OVERLAY_SPLIT_VIEW ((void *)overlaysplitview)));
  g_assert (GTK_IS_WIDGET (GTK_WIDGET ((void *)content)));

  adw_overlay_split_view_set_content (overlaysplitview, content);
}

static uint64_t
gtui_create_toolbarview (uint64_t content)
{
  g_assert_nonnull (content);
  g_assert (GTK_IS_WIDGET (GTK_WIDGET ((void *)content)));

  AdwToolbarView *toolbarview = adw_toolbar_view_new ();
  adw_toolbar_view_set_content (toolbarview, content);

  return (uint64_t)toolbarview;
}

static void
gtui_toolbarview_add_bottom_bar (uint64_t toolbarview, uint64_t bottom_bar)
{
  g_assert_nonnull (toolbarview);
  g_assert_nonnull (bottom_bar);
  g_assert (ADW_IS_TOOLBAR_VIEW (ADW_TOOLBAR_VIEW ((void *)toolbarview)));
  g_assert (GTK_IS_WIDGET (GTK_WIDGET ((void *)bottom_bar)));

  adw_toolbar_view_add_bottom_bar (toolbarview, bottom_bar);
}

static void
gtui_toolbarview_add_top_bar (uint64_t toolbarview, uint64_t top_bar)
{
  g_assert_nonnull (toolbarview);
  g_assert_nonnull (top_bar);
  g_assert (ADW_IS_TOOLBAR_VIEW (ADW_TOOLBAR_VIEW ((void *)toolbarview)));
  g_assert (GTK_IS_WIDGET (GTK_WIDGET ((void *)top_bar)));

  adw_toolbar_view_add_top_bar (toolbarview, top_bar);
}

static void
gtui_toolbarview_set_reveal_bottom_bar (uint64_t toolbarview, gboolean revealed)
{
  g_assert_nonnull (toolbarview);
  g_assert (ADW_IS_TOOLBAR_VIEW (ADW_TOOLBAR_VIEW ((void *)toolbarview)));

  adw_toolbar_view_set_reveal_bottom_bars (toolbarview, revealed);
}

static void
gtui_toolbarview_set_reveal_top_bar (uint64_t toolbarview, gboolean revealed)
{
  g_assert_nonnull (toolbarview);
  g_assert (ADW_IS_TOOLBAR_VIEW (ADW_TOOLBAR_VIEW ((void *)toolbarview)));

  adw_toolbar_view_set_reveal_top_bars (toolbarview, revealed);
}

static AdwToolbarStyle
gtui_convert_number_to_toolbar_style (int number)
{
  AdwToolbarStyle style = ADW_TOOLBAR_FLAT;

  switch (number)
    {
    case 1:
      style = ADW_TOOLBAR_RAISED;
      break;
    case 2:
      style = ADW_TOOLBAR_RAISED_BORDER;
      break;
    }

  return style;
}

static void
gtui_toolbarview_set_top_bar_style (uint64_t toolbarview, int style)
{
  g_assert_nonnull (toolbarview);
  g_assert (ADW_IS_TOOLBAR_VIEW (ADW_TOOLBAR_VIEW ((void *)toolbarview)));

  adw_toolbar_view_set_top_bar_style (toolbarview, gtui_convert_number_to_toolbar_style (style));
}

static void
gtui_toolbarview_set_bottom_bar_style (uint64_t toolbarview, int style)
{
  g_assert_nonnull (toolbarview);
  g_assert (ADW_IS_TOOLBAR_VIEW (ADW_TOOLBAR_VIEW ((void *)toolbarview)));

  adw_toolbar_view_set_bottom_bar_style (toolbarview, gtui_convert_number_to_toolbar_style (style));
}

static char *
gtui_editable_contents (uint64_t editable)
{
  g_assert_nonnull (editable);
  g_assert (GTK_IS_EDITABLE (GTK_EDITABLE ((void *)editable)));

  return gtk_editable_get_text (editable);
}

static void
gtui_editable_set_contents (uint64_t editable, const char *contents)
{
  g_assert_nonnull (editable);
  g_assert_nonnull (contents);
  g_assert (GTK_IS_EDITABLE (GTK_EDITABLE ((void *)editable)));

  return gtk_editable_set_text (editable, contents);
}

static uint64_t
gtui_create_aboutwindow ()
{
  return (uint64_t)adw_about_window_new ();
}

static void
gtui_aboutwindow_set_general_data (uint64_t    aboutwindow,
                                   const char *title,
                                   const char *icon,
                                   const char *developer,
                                   const char *version)
{
  g_assert_nonnull (aboutwindow);
  g_assert_nonnull (title);
  g_assert_nonnull (icon);
  g_assert_nonnull (developer);
  g_assert_nonnull (version);
  g_assert (ADW_IS_ABOUT_WINDOW (ADW_ABOUT_WINDOW ((void *)aboutwindow)));

  adw_about_window_set_application_name (aboutwindow, title);
  adw_about_window_set_application_icon (aboutwindow, icon);
  adw_about_window_set_developer_name (aboutwindow, developer);
  adw_about_window_set_version (aboutwindow, version);
}

static void
gtui_aboutwindow_set_website (uint64_t aboutwindow, const char *website)
{
  g_assert_nonnull (aboutwindow);
  g_assert_nonnull (website);
  g_assert (ADW_IS_ABOUT_WINDOW (ADW_ABOUT_WINDOW ((void *)aboutwindow)));

  adw_about_window_set_website (aboutwindow, website);
}

static void
gtui_aboutwindow_set_support (uint64_t aboutwindow, const char *url)
{
  g_assert_nonnull (aboutwindow);
  g_assert_nonnull (url);
  g_assert (ADW_IS_ABOUT_WINDOW (ADW_ABOUT_WINDOW ((void *)aboutwindow)));

  adw_about_window_set_support_url (aboutwindow, url);
}

static void
gtui_aboutwindow_set_issue (uint64_t aboutwindow, const char *url)
{
  g_assert_nonnull (aboutwindow);
  g_assert_nonnull (url);
  g_assert (ADW_IS_ABOUT_WINDOW (ADW_ABOUT_WINDOW ((void *)aboutwindow)));

  adw_about_window_set_issue_url (aboutwindow, url);
}

static void
gtui_aboutwindow_add_link (uint64_t aboutwindow, const char *title, const char *url)
{
  g_assert_nonnull (aboutwindow);
  g_assert_nonnull (title);
  g_assert_nonnull (url);
  g_assert (ADW_IS_ABOUT_WINDOW (ADW_ABOUT_WINDOW ((void *)aboutwindow)));

  adw_about_window_add_link (aboutwindow, title, url);
}

static void
gtui_aboutwindow_set_artists (uint64_t aboutwindow, const char **artists)
{
  g_assert_nonnull (aboutwindow);
  g_assert_nonnull (artists);
  g_assert (ADW_IS_ABOUT_WINDOW (ADW_ABOUT_WINDOW ((void *)aboutwindow)));

  adw_about_window_set_artists (aboutwindow, artists);
}

static void
gtui_aboutwindow_set_designers (uint64_t aboutwindow, const char **designers)
{
  g_assert_nonnull (aboutwindow);
  g_assert_nonnull (designers);
  g_assert (ADW_IS_ABOUT_WINDOW (ADW_ABOUT_WINDOW ((void *)aboutwindow)));

  adw_about_window_set_designers (aboutwindow, designers);
}

static void
gtui_aboutwindow_set_developers (uint64_t aboutwindow, const char **developers)
{
  g_assert_nonnull (aboutwindow);
  g_assert_nonnull (developers);
  g_assert (ADW_IS_ABOUT_WINDOW (ADW_ABOUT_WINDOW ((void *)aboutwindow)));

  adw_about_window_set_developers (aboutwindow, developers);
}

static void
gtui_aboutwindow_set_documenters (uint64_t aboutwindow, const char **documenters)
{
  g_assert_nonnull (aboutwindow);
  g_assert_nonnull (documenters);
  g_assert (ADW_IS_ABOUT_WINDOW (ADW_ABOUT_WINDOW ((void *)aboutwindow)));

  adw_about_window_set_documenters (aboutwindow, documenters);
}

static void
gtui_aboutwindow_add_credit_section (uint64_t aboutwindow, const char *name, const char **people)
{
  g_assert_nonnull (aboutwindow);
  g_assert_nonnull (name);
  g_assert_nonnull (people);
  g_assert (ADW_IS_ABOUT_WINDOW (ADW_ABOUT_WINDOW ((void *)aboutwindow)));

  adw_about_window_add_credit_section (aboutwindow, name, people);
}

static void
gtui_aboutwindow_set_copyright (uint64_t aboutwindow, const char *copyright)
{
  g_assert_nonnull (aboutwindow);
  g_assert_nonnull (copyright);
  g_assert (ADW_IS_ABOUT_WINDOW (ADW_ABOUT_WINDOW ((void *)aboutwindow)));

  adw_about_window_set_copyright (aboutwindow, copyright);
}

static void
gtui_aboutwindow_set_license (uint64_t aboutwindow, int license)
{
  g_assert_nonnull (aboutwindow);
  g_assert (ADW_IS_ABOUT_WINDOW (ADW_ABOUT_WINDOW ((void *)aboutwindow)));

  GtkLicense license_type = GTK_LICENSE_UNKNOWN;

  switch (license)
    {
    case 1:
      license = GTK_LICENSE_GPL_2_0;
      break;
    case 2:
      license = GTK_LICENSE_GPL_3_0;
      break;
    case 3:
      license = GTK_LICENSE_LGPL_2_1;
      break;
    case 4:
      license = GTK_LICENSE_LGPL_3_0;
      break;
    case 5:
      license = GTK_LICENSE_BSD;
      break;
    case 6:
      license = GTK_LICENSE_MIT_X11;
      break;
    case 7:
      license = GTK_LICENSE_ARTISTIC;
      break;
    case 8:
      license = GTK_LICENSE_GPL_2_0_ONLY;
      break;
    case 9:
      license = GTK_LICENSE_GPL_3_0_ONLY;
      break;
    case 10:
      license = GTK_LICENSE_LGPL_2_1_ONLY;
      break;
    case 11:
      license = GTK_LICENSE_LGPL_3_0_ONLY;
      break;
    case 12:
      license = GTK_LICENSE_AGPL_3_0;
      break;
    case 13:
      license = GTK_LICENSE_AGPL_3_0_ONLY;
      break;
    case 14:
      license = GTK_LICENSE_BSD_3;
      break;
    case 15:
      license = GTK_LICENSE_APACHE_2_0;
      break;
    case 16:
      license = GTK_LICENSE_MPL_2_0;
    }

  adw_about_window_set_license_type (aboutwindow, license);
}

static uint64_t
gtui_create_carousel ()
{
  return (uint64_t)adw_carousel_new ();
}

static void
gtui_carousel_append (uint64_t carousel, uint64_t widget)
{
  g_assert_nonnull (carousel);
  g_assert_nonnull (widget);
  g_assert (ADW_IS_CAROUSEL (ADW_CAROUSEL ((void *)carousel)));
  g_assert (GTK_IS_WIDGET (GTK_WIDGET ((void *)widget)));

  adw_carousel_append (carousel, widget);
}

static void
gtui_carousel_prepend (uint64_t carousel, uint64_t widget)
{
  g_assert_nonnull (carousel);
  g_assert_nonnull (widget);
  g_assert (ADW_IS_CAROUSEL (ADW_CAROUSEL ((void *)carousel)));
  g_assert (GTK_IS_WIDGET (GTK_WIDGET ((void *)widget)));

  adw_carousel_prepend (carousel, widget);
}

static void
gtui_carousel_insert (uint64_t carousel, uint64_t widget, int position)
{
  g_assert_nonnull (carousel);
  g_assert_nonnull (widget);
  g_assert (ADW_IS_CAROUSEL (ADW_CAROUSEL ((void *)carousel)));
  g_assert (GTK_IS_WIDGET (GTK_WIDGET ((void *)widget)));

  adw_carousel_insert (carousel, widget, position);
}

static void
gtui_carousel_remove (uint64_t carousel, uint64_t widget)
{
  g_assert_nonnull (carousel);
  g_assert_nonnull (widget);
  g_assert (ADW_IS_CAROUSEL (ADW_CAROUSEL ((void *)carousel)));
  g_assert (GTK_IS_WIDGET (GTK_WIDGET ((void *)widget)));

  adw_carousel_remove (carousel, widget);
}

static uint64_t
gtui_create_carouselindicatordots (uint64_t carousel)
{
  g_assert_nonnull (carousel);
  g_assert (ADW_IS_CAROUSEL (ADW_CAROUSEL ((void *)carousel)));

  AdwCarouselIndicatorDots *dots = ADW_CAROUSEL_INDICATOR_DOTS (adw_carousel_indicator_dots_new ());
  adw_carousel_indicator_dots_set_carousel (dots, carousel);

  return dots;
}

static uint64_t
gtui_create_tabview ()
{
  return (uint64_t)adw_tab_view_new ();
}

static uint64_t
gtui_tabview_append (uint64_t tabview, uint64_t widget, const char *title)
{
  g_assert_nonnull (tabview);
  g_assert_nonnull (widget);
  g_assert (ADW_IS_TAB_VIEW (ADW_TAB_VIEW ((void *)tabview)));
  g_assert (GTK_IS_WIDGET (GTK_WIDGET ((void *)widget)));

  AdwTabPage *page = adw_tab_view_append (tabview, widget);
  adw_tab_page_set_title (page, title);

  return page;
}

static uint64_t
gtui_tabview_prepend (uint64_t tabview, uint64_t widget, const char *title)
{
  g_assert_nonnull (tabview);
  g_assert_nonnull (widget);
  g_assert (ADW_IS_TAB_VIEW (ADW_TAB_VIEW ((void *)tabview)));
  g_assert (GTK_IS_WIDGET (GTK_WIDGET ((void *)widget)));

  AdwTabPage *page = adw_tab_view_prepend (tabview, widget);
  adw_tab_page_set_title (page, title);

  return page;
}

static uint64_t
gtui_create_tabbutton (uint64_t tabview)
{
  g_assert_nonnull (tabview);
  g_assert (ADW_IS_TAB_VIEW (ADW_TAB_VIEW ((void *)tabview)));

  AdwTabButton *button = ADW_TAB_BUTTON (adw_tab_button_new ());
  adw_tab_button_set_view (button, tabview);

  return button;
}

static void
gtui_tabbutton_init_signals (uint64_t btn, uint64_t data)
{
  AdwTabButton *button;

  g_assert_nonnull (btn);
  g_assert_nonnull (data);
  g_assert (ADW_IS_TAB_BUTTON (ADW_TAB_BUTTON ((void *)btn)));

  button = ADW_TAB_BUTTON (btn);
  swift_retain (data);
  g_signal_connect (button, "clicked", G_CALLBACK (tabbutton_on_click_cb), (void *)data);
}

static uint64_t
gtui_create_taboverview ()
{
  return (uint64_t)adw_tab_overview_new ();
}

static void
gtui_taboverview_init_signals (uint64_t ovrw, uint64_t data)
{
  AdwTabOverview *overview;

  g_assert_nonnull (ovrw);
  g_assert_nonnull (data);
  g_assert (ADW_IS_TAB_OVERVIEW (ADW_TAB_OVERVIEW ((void *)ovrw)));

  overview = ADW_TAB_OVERVIEW (ovrw);
  swift_retain (data);
  g_signal_connect (overview, "create-tab", G_CALLBACK (taboverview_on_create_tab_cb), (void *)data);
}

static void
gtui_taboverview_add (uint64_t overview, uint64_t widget, uint64_t tabview)
{
  g_assert_nonnull (widget);
  g_assert_nonnull (tabview);
  g_assert_nonnull (overview);
  g_assert (GTK_IS_WIDGET (GTK_WIDGET ((void *)widget)));
  g_assert (ADW_IS_TAB_VIEW (ADW_TAB_VIEW ((void *)tabview)));
  g_assert (ADW_IS_TAB_OVERVIEW (ADW_TAB_OVERVIEW ((void *)overview)));

  adw_tab_overview_set_child (overview, widget);
  adw_tab_overview_set_view (overview, tabview);
}

static void
gtui_taboverview_show_create_tab (uint64_t overview)
{
  g_assert_nonnull (overview);
  g_assert (ADW_IS_TAB_OVERVIEW (ADW_TAB_OVERVIEW ((void *)overview)));

  adw_tab_overview_set_enable_new_tab (overview, TRUE);
}

static void
gtui_taboverview_set_open (uint64_t taboverview, gboolean open)
{
  g_assert_nonnull (taboverview);
  g_assert (ADW_IS_TAB_OVERVIEW (ADW_TAB_OVERVIEW ((void *)taboverview)));

  adw_tab_overview_set_open (taboverview, open);
}

static gboolean
gtui_taboverview_get_open (uint64_t taboverview)
{
  g_assert_nonnull (taboverview);
  g_assert (ADW_IS_TAB_OVERVIEW (ADW_TAB_OVERVIEW ((void *)taboverview)));

  return adw_tab_overview_get_open (taboverview);
}

static uint64_t
gtui_create_tabbar (uint64_t tabview)
{
  g_assert_nonnull (tabview);
  g_assert (ADW_IS_TAB_VIEW (ADW_TAB_VIEW ((void *)tabview)));

  AdwTabBar *bar = ADW_TAB_BAR (adw_tab_bar_new ());
  adw_tab_bar_set_view (bar, tabview);

  return bar;
}

static uint64_t
gtui_create_clamp (uint64_t widget)
{
  g_assert_nonnull (widget);
  g_assert (GTK_IS_WIDGET (GTK_WIDGET ((void *)widget)));

  AdwClamp *clamp = ADW_CLAMP (adw_clamp_new ());
  adw_clamp_set_child (clamp, widget);

  return clamp;
}

static void
gtui_clamp_set_maximum_size (uint64_t clamp, int maximum_size)
{
  g_assert_nonnull (clamp);
  g_assert (ADW_IS_CLAMP (ADW_CLAMP ((void *)clamp)));

  adw_clamp_set_maximum_size (clamp, maximum_size);
}

static uint64_t
gtui_create_buttoncontent ()
{
  return (uint64_t)adw_button_content_new ();
}

static void
gtui_buttoncontent_set_label (uint64_t button, const char *label)
{
  g_assert_nonnull (button);
  g_assert_nonnull (label);
  g_assert (ADW_IS_BUTTON_CONTENT (ADW_BUTTON_CONTENT (button)));

  adw_button_content_set_label (button, label);
}

static void
gtui_buttoncontent_set_icon (uint64_t button, const char *icon)
{
  g_assert_nonnull (button);
  g_assert_nonnull (icon);
  g_assert (ADW_IS_BUTTON_CONTENT (ADW_BUTTON_CONTENT (button)));

  adw_button_content_set_icon_name (button, icon);
}

static uint64_t
gtui_create_stack ()
{
  return (uint64_t)gtk_stack_new ();
}

static void
gtui_stack_add_child (uint64_t stack, uint64_t child)
{
  g_assert_nonnull (stack);
  g_assert_nonnull (child);
  g_assert (GTK_IS_STACK (GTK_STACK (stack)));
  g_assert (GTK_IS_WIDGET (GTK_WIDGET (child)));

  gtk_stack_add_child (stack, child);
}

static void
gtui_stack_set_visible_child (uint64_t stack, uint64_t child, int transition)
{
  g_assert_nonnull (stack);
  g_assert_nonnull (child);
  g_assert (GTK_IS_STACK (GTK_STACK (stack)));
  g_assert (GTK_IS_WIDGET (GTK_WIDGET (child)));

  GtkStackTransitionType gtk_transition = GTK_STACK_TRANSITION_TYPE_NONE;

  switch (transition)
    {
    case 1:
      gtk_transition = GTK_STACK_TRANSITION_TYPE_CROSSFADE;
      break;
    case 2:
      gtk_transition = GTK_STACK_TRANSITION_TYPE_SLIDE_RIGHT;
      break;
    case 3:
      gtk_transition = GTK_STACK_TRANSITION_TYPE_SLIDE_LEFT;
      break;
    case 4:
      gtk_transition = GTK_STACK_TRANSITION_TYPE_SLIDE_UP;
      break;
    case 5:
      gtk_transition = GTK_STACK_TRANSITION_TYPE_SLIDE_DOWN;
      break;
    case 6:
      gtk_transition = GTK_STACK_TRANSITION_TYPE_SLIDE_LEFT_RIGHT;
      break;
    case 7:
      gtk_transition = GTK_STACK_TRANSITION_TYPE_SLIDE_UP_DOWN;
      break;
    case 8:
      gtk_transition = GTK_STACK_TRANSITION_TYPE_OVER_UP;
      break;
    case 9:
      gtk_transition = GTK_STACK_TRANSITION_TYPE_OVER_DOWN;
      break;
    case 10:
      gtk_transition = GTK_STACK_TRANSITION_TYPE_OVER_LEFT;
      break;
    case 11:
      gtk_transition = GTK_STACK_TRANSITION_TYPE_OVER_RIGHT;
      break;
    case 12:
      gtk_transition = GTK_STACK_TRANSITION_TYPE_UNDER_UP;
      break;
    case 13:
      gtk_transition = GTK_STACK_TRANSITION_TYPE_UNDER_DOWN;
      break;
    case 14:
      gtk_transition = GTK_STACK_TRANSITION_TYPE_UNDER_LEFT;
      break;
    case 15:
      gtk_transition = GTK_STACK_TRANSITION_TYPE_UNDER_RIGHT;
      break;
    case 16:
      gtk_transition = GTK_STACK_TRANSITION_TYPE_OVER_UP_DOWN;
      break;
    case 17:
      gtk_transition = GTK_STACK_TRANSITION_TYPE_OVER_DOWN_UP;
      break;
    case 18:
      gtk_transition = GTK_STACK_TRANSITION_TYPE_OVER_LEFT_RIGHT;
      break;
    case 19:
      gtk_transition = GTK_STACK_TRANSITION_TYPE_OVER_RIGHT_LEFT;
      break;
    case 20:
      gtk_transition = GTK_STACK_TRANSITION_TYPE_ROTATE_LEFT;
      break;
    case 21:
      gtk_transition = GTK_STACK_TRANSITION_TYPE_ROTATE_RIGHT;
      break;
    case 22:
      gtk_transition = GTK_STACK_TRANSITION_TYPE_ROTATE_LEFT_RIGHT;
      break;
    }
  gtk_stack_set_transition_type (stack, gtk_transition);
  gtk_stack_set_visible_child (stack, child);
}

static void
gtui_stack_remove (uint64_t stack, uint64_t child)
{
  g_assert_nonnull (stack);
  g_assert_nonnull (child);
  g_assert (GTK_IS_STACK (GTK_STACK (stack)));
  g_assert (GTK_IS_WIDGET (GTK_WIDGET (child)));

  gtk_stack_remove (stack, child);
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

static void
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

static void
gtui_listbox_remove (uint64_t box, uint64_t widget)
{
  g_assert_nonnull (box);
  g_assert_nonnull (widget);
  g_assert (GTK_IS_LIST_BOX (GTK_LIST_BOX ((void *)box)));
  g_assert (GTK_IS_WIDGET (GTK_WIDGET ((void *)widget)));

  gtk_list_box_remove ((GtkListBox *)box, (GtkWidget *)widget);
}

static char *
gtui_stringlist_get_selected (uint64_t dropdown, uint64_t list)
{
  g_assert (GTK_IS_DROP_DOWN (GTK_DROP_DOWN ((void *)dropdown)));
  g_assert (GTK_IS_STRING_LIST (GTK_STRING_LIST ((void *)list)));

  return gtk_string_list_get_string (list, gtk_drop_down_get_selected (dropdown));
}

static char *
gtui_textview_contents (uint64_t textview)
{
  GtkTextIter    start, end;
  GtkTextBuffer *buffer;

  g_assert (GTK_IS_TEXT_VIEW (textview));

  buffer = gtk_text_view_get_buffer (textview);
  gtk_text_buffer_get_bounds (buffer, &start, &end);
  return gtk_text_buffer_get_text (buffer, &start, &end, FALSE);
}

static void
gtui_window_maximize (uint64_t ptr)
{
  g_assert_nonnull (ptr);
  GtkWindow *window = (void *)ptr;
  g_assert (GTK_IS_WINDOW (window));
  gtk_window_maximize (GTK_WINDOW (window));
}

static void
gtui_window_unmaximize (uint64_t ptr)
{
  g_assert_nonnull (ptr);
  GtkWindow *window = (void *)ptr;
  g_assert (GTK_IS_WINDOW (window));
  gtk_window_unmaximize (GTK_WINDOW (window));
}

static gboolean
gtui_window_is_maximized (uint64_t ptr)
{
  g_assert_nonnull (ptr);
  GtkWindow *window = (void *)ptr;
  g_assert (GTK_IS_WINDOW (window));
  return gtk_window_is_maximized (GTK_WINDOW (window));
}

static void
gtui_window_enter_fullscreen (uint64_t ptr)
{
  g_assert_nonnull (ptr);
  GtkWindow *window = (void *)ptr;
  g_assert (GTK_IS_WINDOW (window));
  gtk_window_fullscreen (GTK_WINDOW (window));
}

static void
gtui_window_leave_fullscreen (uint64_t ptr)
{
  g_assert_nonnull (ptr);
  GtkWindow *window = (void *)ptr;
  g_assert (GTK_IS_WINDOW (window));
  gtk_window_unfullscreen (GTK_WINDOW (window));
}

static void
gtui_window_minimize (uint64_t ptr)
{
  g_assert_nonnull (ptr);
  GtkWindow *window = (void *)ptr;
  g_assert (GTK_IS_WINDOW (window));
  gtk_window_minimize (GTK_WINDOW (window));
}

static void
gtui_window_close (uint64_t ptr)
{
  g_assert_nonnull (ptr);
  GtkWindow *window = (void *)ptr;
  g_assert (GTK_IS_WINDOW (window));
  gtk_window_close (GTK_WINDOW (window));
}

static void
gtui_window_set_default_size (uint64_t ptr, int width, int height)
{
  g_assert_nonnull (ptr);
  GtkWindow *window = (void *)ptr;
  g_assert (GTK_IS_WINDOW (window));
  gtk_window_set_default_size (GTK_WINDOW (window), width, height);
}

static void
gtui_window_set_resizability (uint64_t ptr, gboolean setting)
{
  g_assert_nonnull (ptr);
  GtkWindow *window = (void *)ptr;
  g_assert (GTK_IS_WINDOW (window));
  gtk_window_set_resizable (GTK_WINDOW (window), setting);
}

static void
gtui_window_set_deletability (uint64_t ptr, gboolean setting)
{
  g_assert_nonnull (ptr);
  GtkWindow *window = (void *)ptr;
  g_assert (GTK_IS_WINDOW (window));
  gtk_window_set_deletable (GTK_WINDOW (window), setting);
}

static void
gtui_set_hexpand (uint64_t widget, gboolean enabled)
{
  g_assert (GTK_IS_WIDGET (widget));

  gtk_widget_set_hexpand (GTK_WIDGET (widget), enabled);
}

static void
gtui_set_vexpand (uint64_t widget, gboolean enabled)
{
  g_assert (GTK_IS_WIDGET (widget));

  gtk_widget_set_vexpand (GTK_WIDGET (widget), enabled);
}

static GtkAlign
gtui_get_align (int number)
{
  GtkAlign align = GTK_ALIGN_FILL;
  switch (number)
    {
    case 1:
      align = GTK_ALIGN_START;
      break;
    case 2:
      align = GTK_ALIGN_END;
      break;
    case 3:
      align = GTK_ALIGN_CENTER;
      break;
    case 4:
      align = GTK_ALIGN_BASELINE_FILL;
      break;
    case 5:
      align = GTK_ALIGN_BASELINE_CENTER;
      break;
    }
  return align;
}

static void
gtui_set_halign (uint64_t widget, int align)
{
  g_assert_nonnull (widget);
  g_assert (GTK_IS_WIDGET (GTK_WIDGET (widget)));
  gtk_widget_set_halign (widget, gtui_get_align (align));
}

static void
gtui_set_valign (uint64_t widget, int align)
{
  g_assert_nonnull (widget);
  g_assert (GTK_IS_WIDGET (GTK_WIDGET (widget)));
  gtk_widget_set_valign (widget, gtui_get_align (align));
}

static void
gtui_set_margin_start (uint64_t widget, int margin)
{
  g_assert (GTK_IS_WIDGET (widget));

  gtk_widget_set_margin_start (GTK_WIDGET (widget), margin);
}

static void
gtui_set_margin_end (uint64_t widget, int margin)
{
  g_assert (GTK_IS_WIDGET (widget));

  gtk_widget_set_margin_end (GTK_WIDGET (widget), margin);
}

static void
gtui_set_margin_top (uint64_t widget, int margin)
{
  g_assert (GTK_IS_WIDGET (widget));

  gtk_widget_set_margin_top (GTK_WIDGET (widget), margin);
}

static void
gtui_set_margin_bottom (uint64_t widget, int margin)
{
  g_assert (GTK_IS_WIDGET (widget));

  gtk_widget_set_margin_bottom (GTK_WIDGET (widget), margin);
}

static void
gtui_set_size_request (uint64_t widget, int width, int height)
{
  g_assert (GTK_IS_WIDGET (widget));

  gtk_widget_set_size_request (GTK_WIDGET (widget), width, height);
}

static int
gtui_get_width (uint64_t widget)
{
  g_assert (GTK_IS_WIDGET (widget));

  return gtk_widget_get_width (widget);
}

static int
gtui_get_height (uint64_t widget)
{
  g_assert (GTK_IS_WIDGET (widget));

  return gtk_widget_get_height (widget);
}

static void
gtui_add_css_class (uint64_t widget, const char *css_class)
{
  g_assert (GTK_IS_WIDGET (widget));
  gtk_widget_add_css_class (widget, css_class);
}

static void
gtui_label_set_text (uint64_t widget, const char *text)
{
  g_assert (GTK_IS_LABEL (widget));

  gtk_label_set_text (widget, text);
}
