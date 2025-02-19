#include <glib-object.h>
#include <gtk/gtk.h>
#include <gtk/gtkcssprovider.h>


GtkCssProvider *provider;
/*
################################################################################################################
// 第一个参数是发出“变更状态”信号的动作。第二个参数是新操作状态的值。第三个参数是在g_signal_connect中设置的用户数据
static void fullscreen_changed(GSimpleAction *action, GVariant *value, GtkWindow *win) {
  if (g_variant_get_boolean (value))
    gtk_window_maximize (win);
  else
    gtk_window_unmaximize (win);
  g_simple_action_set_state (action, value);
}

// 新建有状态的简单动作，参数为空，初始状态为FALSE
GSimpleAction *act_fullscreen = g_simple_action_new_stateful ("fullscreen",
                                NULL, g_variant_new_boolean (FALSE));

// 为动作关联change-state事件处理函数
g_signal_connect (act_fullscreen, "change-state", G_CALLBACK (fullscreen_changed), win);

// 将动作添加到app的动作映射中
g_action_map_add_action (G_ACTION_MAP (win), G_ACTION (act_fullscreen));
... ... ...

// 创建一个菜单项menu_item_fullscreen，名称为"Full Screen"，关联的动作为"app.fullscreen"，此处fullscreen和第一步的act_fullscreen名称一致
GMenuItem *menu_item_fullscreen = g_menu_item_new ("Full Screen", "win.fullscreen");
###############################################################################################################
*/
static void
fullscreen_changed(GSimpleAction *action, GVariant *value, GtkWindow *win) {
  if (g_variant_get_boolean (value))
    gtk_window_maximize (win);
  else
    gtk_window_unmaximize (win);
  g_simple_action_set_state (action, value);
}

static void
color_activated(GSimpleAction *action, GVariant *parameter) {
  char *color = g_strdup_printf ("label.lb {background-color: %s;}", g_variant_get_string (parameter, NULL));
  /* Change the CSS data in the provider. */
  /* Previous data is thrown away. */
  gtk_css_provider_load_from_data (provider, color, -1);
  g_free (color);
  g_action_change_state (G_ACTION (action), parameter);
}

static void
app_shutdown (GApplication *app, GtkCssProvider *provider) {
  gtk_style_context_remove_provider_for_display (gdk_display_get_default(), GTK_STYLE_PROVIDER (provider));
}

static void
my_app_activate (GApplication *app) {
  GtkWindow *win = GTK_WINDOW (gtk_application_window_new (GTK_APPLICATION (app)));
  gtk_window_set_title (win, "menu2");
  gtk_window_set_default_size (win, 400, 300);

  GtkWidget *lb = gtk_label_new (NULL);
  gtk_widget_add_css_class (lb, "lb"); /* the class is used by CSS Selector */
  gtk_window_set_child (win, lb);

  GSimpleAction *act_fullscreen
    = g_simple_action_new_stateful ("fullscreen", NULL, g_variant_new_boolean (FALSE));
  g_signal_connect (act_fullscreen, "change-state", G_CALLBACK (fullscreen_changed), win);
  g_action_map_add_action (G_ACTION_MAP (win), G_ACTION (act_fullscreen));

  gtk_application_window_set_show_menubar (GTK_APPLICATION_WINDOW (win), TRUE);

  gtk_window_present (win);
}

static void app_startup(GApplication *app){
    /*
    “b” means boolean type.
    “s” means string type.
    */
    GVariantType *type = g_variant_type_new("s");
    GSimpleAction *act_color = g_simple_action_new_stateful("color",type,g_variant_new_string("red"));
    GSimpleAction *act_quit = g_simple_action_new("quit",NULL);

    g_signal_connect(act_color, "activate", G_CALLBACK(color_activated), NULL);
    g_signal_connect_swapped(act_quit, "activate", G_CALLBACK (g_application_quit), NULL);

    g_action_map_add_action(G_ACTION_MAP(app), G_ACTION(act_color));
    g_action_map_add_action(G_ACTION_MAP(app), G_ACTION(act_quit));

    // 上方的菜单栏
    GMenu *menubar = g_menu_new();
    // 菜单栏的一个菜单
    GMenu *menu = g_menu_new();
    // 菜单里的菜单分组
    GMenu *section1 = g_menu_new ();
    GMenu *section2 = g_menu_new ();
    GMenu *section3 = g_menu_new ();
    // 菜单里的菜单项
    GMenuItem *menu_item_fullscreen = g_menu_item_new ("Full Screen", "win.fullscreen");
    GMenuItem *menu_item_red = g_menu_item_new ("Red","app.color::red");
    GMenuItem *menu_item_green = g_menu_item_new ("Green","app.color::green");
    GMenuItem *menu_item_blue = g_menu_item_new ("Blue","app.color::blue");
    GMenuItem *menu_item_quit = g_menu_item_new ("Quit", "app.quit");

    g_menu_append_item (section1, menu_item_fullscreen);
    g_menu_append_item (section2, menu_item_red);
    g_menu_append_item (section2, menu_item_green);
    g_menu_append_item (section2, menu_item_blue);
    g_menu_append_item (section3, menu_item_quit);

    g_menu_append_section (menu, NULL, G_MENU_MODEL (section1));
    g_menu_append_section (menu, "Color", G_MENU_MODEL (section2));
    g_menu_append_section (menu, NULL, G_MENU_MODEL (section3));

    g_menu_append_submenu (menubar, "Menu", G_MENU_MODEL (menu));

    // free memory
    g_variant_type_free (type);
    g_object_unref(menu_item_fullscreen);
    g_object_unref(menu_item_red);
    g_object_unref(menu_item_green);
    g_object_unref(menu_item_blue);
    g_object_unref(menu_item_quit);
    g_object_unref(section1);
    g_object_unref(section2);
    g_object_unref(section3);
    g_object_unref(menu);

    gtk_application_set_menubar (GTK_APPLICATION (app), G_MENU_MODEL (menubar));

    provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider,"label.lb {background-color: red;}",-1);
    gtk_style_context_add_provider_for_display (gdk_display_get_default (),GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    g_signal_connect (app, "shutdown", G_CALLBACK (app_shutdown), provider);
    g_object_unref (provider);
}
static void app_activate(GApplication *app, gpointer user_data){

}

int main(int argc, char * argv[]){
    GtkApplication *app = gtk_application_new("org.example.application",  G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app,"startup",G_CALLBACK(app_startup),NULL);
    g_signal_connect(app,"activate",G_CALLBACK(my_app_activate),NULL);
    int status = g_application_run(G_APPLICATION(app), argc,argv);
    g_object_unref(app);
    return status;
}
