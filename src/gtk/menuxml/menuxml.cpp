#include <gio/gio.h>
#include <gtk/gtk.h>
#include <gtk/gtkshortcut.h>
#include "resources.c"

/*
############################################################################################################
有三个基本标签
1. menu
<interface>
  <menu id="menubar">
  </menu>
</interface>

2. submenu
<submenu>
  <attribute name="label">File</attribute>
    <item>
      <attribute name="label">New</attribute>
      <attribute name="action">win.new</attribute>
    </item>
</submenu>

3.item
<item>
  <attribute name="label">File</attribute>
    <link name="submenu">
      <item>
        <attribute name="label">New</attribute>
        <attribute name="action">win.new</attribute>
      </item>
    </link>
</item>
############################################################################################################
*/

GtkCssProvider *provider;

/*
动作处理函数的统一格式
*/
static void
new_activated (GSimpleAction *action, GVariant *parameter, gpointer user_data) {
}

static void
open_activated (GSimpleAction *action, GVariant *parameter, gpointer user_data) {
}

static void
save_activated (GSimpleAction *action, GVariant *parameter, gpointer user_data) {
}

static void
saveas_activated (GSimpleAction *action, GVariant *parameter, gpointer user_data) {
}

static void
close_activated (GSimpleAction *action, GVariant *parameter, gpointer user_data) {
  GtkWindow *win = GTK_WINDOW (user_data);

  gtk_window_destroy (win);
}

static void
cut_activated (GSimpleAction *action, GVariant *parameter, gpointer user_data) {
}

static void
copy_activated (GSimpleAction *action, GVariant *parameter, gpointer user_data) {
}

static void
paste_activated (GSimpleAction *action, GVariant *parameter, gpointer user_data) {
}

static void
selectall_activated (GSimpleAction *action, GVariant *parameter, gpointer user_data) {
}

static void
fullscreen_changed (GSimpleAction *action, GVariant *state, gpointer user_data) {
  GtkWindow *win = GTK_WINDOW (user_data);

  if (g_variant_get_boolean (state))
    gtk_window_maximize (win);
  else
    gtk_window_unmaximize (win);
  g_simple_action_set_state (action, state);
}
static void
app_shutdown (GApplication *app, GtkCssProvider *provider) {
  gtk_style_context_remove_provider_for_display (gdk_display_get_default(), GTK_STYLE_PROVIDER (provider));
}

static void
quit_activated (GSimpleAction *action, GVariant *parameter, gpointer user_data) {
  GApplication *app = G_APPLICATION (user_data);

  g_application_quit (app);
}

static void
color_activated(GSimpleAction *action, GVariant *parameter,gpointer user_data) {
  char *color = g_strdup_printf ("label.lb {background-color: %s;}", g_variant_get_string (parameter, NULL));
  /* Change the CSS data in the provider. */
  /* Previous data is thrown away. */
  gtk_css_provider_load_from_string (provider, color);
  g_free (color);
  g_action_change_state (G_ACTION (action), parameter);
}

static void
app_activate (GApplication *app) {
  GtkWindow *win = GTK_WINDOW(gtk_application_window_new (GTK_APPLICATION (app)));

  const GActionEntry win_entries[] = {
    { "save", save_activated, NULL, NULL, NULL },
    { "saveas", saveas_activated, NULL, NULL, NULL },
    { "close", close_activated, NULL, NULL, NULL },
    { "fullscreen", NULL, NULL, "false", fullscreen_changed }
  };
  g_action_map_add_action_entries (G_ACTION_MAP (win), win_entries, G_N_ELEMENTS (win_entries), win);

  gtk_application_window_set_show_menubar (GTK_APPLICATION_WINDOW (win), TRUE);

  gtk_window_set_title (GTK_WINDOW (win), "menu3");
  gtk_window_set_default_size (GTK_WINDOW (win), 400, 300);
  GtkWidget *lb = gtk_label_new (NULL);
  gtk_widget_add_css_class (lb, "lb"); /* the class is used by CSS Selector */
  gtk_window_set_child (win, lb);
  gtk_window_present (GTK_WINDOW (win));
}

static void
app_startup (GApplication *app) {
  GtkBuilder *builder = gtk_builder_new_from_resource ("/home/mr-kechen/Documents/cpp/src/gtk/menuxml/menu.ui");
  GMenuModel *menubar = G_MENU_MODEL (gtk_builder_get_object (builder, "menubar"));

  gtk_application_set_menubar (GTK_APPLICATION (app), menubar);
  g_object_unref (builder);

  /**
  ############################################################################################################
  可以通过一个结构体轻松完成action的定义、注册
  typedef struct _GActionEntry GActionEntry;
  struct _GActionEntry
  {
    /* action name
    const char *name;
    /* activate handler
    void (* activate) (GSimpleAction *action, GVariant *parameter, gpointer user_data);
    /* the type of the parameter given as a single GVariant type string
    const char *parameter_type;
    /* initial state given in GVariant text format
    const char *state;
    /* change-state handler
    void (* change_state) (GSimpleAction *action, GVariant *value, gpointer user_data);
    /* < private >
    gsize padding[3];
  };
  例如：
  { "fullscreen", NULL, NULL, "false", fullscreen_changed }
  { "color", color_activated, "s", "'red'", NULL }
  { "quit", quit_activated, NULL, NULL, NULL },
  ############################################################################################################
  **/
  const GActionEntry app_entries[] = {
    { "color", color_activated, "s", "'red'", NULL },
    { "new", new_activated, NULL, NULL, NULL },
    { "open", open_activated, NULL, NULL, NULL },
    { "cut", cut_activated, NULL, NULL, NULL },
    { "copy", copy_activated, NULL, NULL, NULL },
    { "paste", paste_activated, NULL, NULL, NULL },
    { "selectall", selectall_activated, NULL, NULL, NULL },
    { "quit", quit_activated, NULL, NULL, NULL }
  };
  g_action_map_add_action_entries (G_ACTION_MAP (app), app_entries, G_N_ELEMENTS (app_entries), app);
  provider = gtk_css_provider_new();
  gtk_css_provider_load_from_string(provider,"label.lb {background-color: red;}");
  gtk_style_context_add_provider_for_display (gdk_display_get_default (),GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
  g_signal_connect (app, "shutdown", G_CALLBACK (app_shutdown), provider);
  g_object_unref (provider);
}

#define APPLICATION_ID "com.github.ToshioCP.menu3"

int
main (int argc, char **argv) {
  GtkApplication *app;
  int stat;

  app = gtk_application_new (APPLICATION_ID, G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect (app, "startup", G_CALLBACK (app_startup), NULL);
  g_signal_connect (app, "activate", G_CALLBACK (app_activate), NULL);

  stat =g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);
  return stat;
}
