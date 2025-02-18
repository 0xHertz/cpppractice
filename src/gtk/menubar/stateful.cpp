#include <gtk/gtk.h>

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
