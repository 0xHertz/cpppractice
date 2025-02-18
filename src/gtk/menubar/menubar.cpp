#include <gtk/gtk.h>

/*
########################################################################################
1.当应用程序第一次运行时，该实例称为主实例。
2.主实例将自身注册到系统。如果成功，它会发出“startup”信号。
3.当实例被激活时，会发出“activate”或“open”信号。
4.如果应用程序第二次或以后运行并且存在主实例，则该实例称为远程实例。
5.远程实例不会发出“startup”信号。
6.如果它尝试发出“activate”或“open”信号，则信号不会在远程实例上发出，而是在主实例上发出。
7.远程实例退出。
因此，“activate”或“open”处理程序可以被调用两次或更多次。另一方面，“startup”处理程序被调用一次。因此，菜单栏应该在“startup”处理程序中设置。

static void
quit_activated(GSimpleAction *action, GVariant *parameter, gpointer app) { ... ... ...}

// 新建无状态的简单动作act_quit，名称为"quit"，无参数
GSimpleAction *act_quit = g_simple_action_new ("quit", NULL);

// 将act_quit添加到app的动作映射中
g_action_map_add_action (G_ACTION_MAP (app), G_ACTION (act_quit));

// 连接act_quit的activate信号到quit_activated回调函数
g_signal_connect (act_quit, "activate", G_CALLBACK (quit_activated), app);

// 创建一个菜单项menu_item_quit，名称为"Quit"，关联的动作为"app.quit"，此处quit和第一步的act_quit名称一致
GMenuItem *menu_item_quit = g_menu_item_new ("Quit", "app.quit");
########################################################################################
*/

static void
quit_activated(GSimpleAction *action, GVariant *parameter, GApplication *application) {
  g_application_quit (application);
}
// only called once
void static app_startup(GApplication *application){
    GtkApplication *app = GTK_APPLICATION (application);

    GSimpleAction *act_quit = g_simple_action_new ("quit",NULL);
    g_action_map_add_action(G_ACTION_MAP(app),G_ACTION(act_quit));
    g_signal_connect(act_quit,"activate",G_CALLBACK(quit_activated),app);

    GMenu *menubar = g_menu_new();
    GMenuItem *menu_item_menu = g_menu_item_new("Menu",NULL);
    GMenu *submenu = g_menu_new();
    GMenuItem *menu_item_quit = g_menu_item_new("Quit","app.quit");
    g_menu_append_item(submenu,menu_item_quit);
    g_menu_item_set_submenu(menu_item_menu,G_MENU_MODEL(submenu));
    g_menu_append_item(menubar,menu_item_menu);
    g_object_unref(menu_item_quit);
    g_object_unref(submenu);
    g_object_unref(menu_item_menu);

    gtk_application_set_menubar(app,G_MENU_MODEL(menubar));
}

void static app_activate(GApplication *application){
    GtkApplication *app = GTK_APPLICATION (application);
    GtkWidget *win = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (win), "menu1");
    gtk_window_set_default_size (GTK_WINDOW (win), 400, 300);

    gtk_application_window_set_show_menubar (GTK_APPLICATION_WINDOW (win), TRUE);
    gtk_window_present (GTK_WINDOW (win));
}

int main(int argc, char *argv[]){
    GtkApplication *app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "startup", G_CALLBACK(app_startup), NULL);
    g_signal_connect(app, "activate", G_CALLBACK(app_activate), NULL);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}
