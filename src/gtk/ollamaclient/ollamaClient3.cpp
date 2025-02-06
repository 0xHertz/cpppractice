#include <gtk/gtk.h>


/*
    事件处理函数
*/
// 处理按钮点击事件的回调函数
static void on_send_clicked(GtkWidget *widget, gpointer data) {
    g_print("Send button clicked!\n");
}

int main(int argc, char* argv[]){
    // 初始化GTK
    gtk_init();
    // 创建主窗口
    GtkWidget *window = gtk_window_new();
    // 设置窗口标题
    gtk_window_set_title(GTK_WINDOW(window), "Ollama Client");
    // 设置窗口大小
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);

    // 创建垂直布局容器
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    // 设置容器属性
    gtk_widget_set_margin_top(vbox, 10);
    gtk_widget_set_margin_start(vbox, 10);
    gtk_widget_set_margin_end(vbox, 10);
    gtk_widget_set_margin_bottom(vbox, 10);

    // 创建文本输入框
    GtkWidget *entry = gtk_entry_new();
    // 设置文本输入框属性
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Enter your message here");

    // 创建发送按钮
    GtkWidget *button = gtk_button_new_with_label("Send");
    // 设置按钮点击事件
    g_signal_connect(button, "clicked", G_CALLBACK(on_send_clicked), NULL);

    // 创建文本显示区域
    GtkWidget *text_view = gtk_text_view_new();
    // 设置文本显示区域属性
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE); // 设置为不可编辑
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text_view), GTK_WRAP_WORD);// 设置自动换行

    // 创建滚动条
    GtkWidget *scroll = gtk_scrolled_window_new();
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scroll), text_view); // 设置滚动条子控件

    // 将控件添加到垂直布局容器
    gtk_box_append(GTK_BOX(vbox), entry);
    gtk_box_append(GTK_BOX(vbox), button);
    gtk_box_append(GTK_BOX(vbox), scroll);
    // 将垂直布局容器添加到主窗口
    gtk_window_set_child(GTK_WINDOW(window), vbox);

    // 设置窗口关闭事件
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // 显示窗口
    gtk_widget_show(window);
    gtk_main();

    return 0;
}
