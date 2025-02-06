#include <curses.h>
#include <gtk/gtk.h>

// 处理按钮点击事件
static void on_send_clicked(GtkWidget *widget, gpointer user_data) {
    GtkTextBuffer *buffer = GTK_TEXT_BUFFER(user_data);
    GtkTextIter end;
    gtk_text_buffer_get_end_iter(buffer, &end);
    gtk_text_buffer_insert(buffer, &end, "用户: 你好！\n", -1);
}

// 激活应用
static void on_activate(GtkApplication *app, gpointer user_data) {
    // 创建窗口
    // 有一个gtkwindow类，也可以作为一个顶级窗口使用，使用gtk_window_new()函数创建，但是不建议这样使用
    // 通常使用gtkapplicationwindowl类，使用gtk_application_window_new()函数创建一个窗口，这个函数会自动设置窗口的一些属性
    GtkWidget *window = gtk_application_window_new(app);
    // 设置窗口标题和大小
    gtk_window_set_title(GTK_WINDOW(window), "Ollama Client");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);

    // 主布局 - 分割窗格（左：聊天记录，右：当前聊天）
    GtkWidget *paned = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
    // 将分割窗格添加到窗口
    gtk_window_set_child(GTK_WINDOW(window), paned);

    // =======================================聊天记录（左侧）===========================================
    GtkWidget *chat_history = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(chat_history), FALSE);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(chat_history), GTK_WRAP_WORD);
    GtkWidget *scroll_history = gtk_scrolled_window_new();
    // 将文本视图添加到滚动窗格子控件
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scroll_history), chat_history);
    gtk_paned_set_start_child(GTK_PANED(paned), scroll_history);

    // =======================================右侧聊天窗口===============================================
    /*
        ----------------------
        | ------------------ |
        | |                | |
        | |    chatbox     | |
        | |                | |
        | |                | |
        | | -------------- | |
        | | |   inputbox | | |
        | | -------------- | |
        | ------------------ |
        ----------------------
    */
    // 创建一个垂直布局容器
    // 5表示容器中控件之间的间距
    GtkWidget *chat_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    // fills the box with the children, giving them the same space
    gtk_box_set_homogeneous(GTK_BOX(chat_box), TRUE);
    gtk_paned_set_end_child(GTK_PANED(paned), chat_box);

    // 当前对话内容（右上侧）
    GtkWidget *chat_view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(chat_view), FALSE);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(chat_view), GTK_WRAP_WORD);
    GtkWidget *scroll_chat = gtk_scrolled_window_new();
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scroll_chat), chat_view);
    gtk_box_append(GTK_BOX(chat_box), scroll_chat);

    // 底部输入框和按钮(右下侧)
    // 输入框和按钮放在一个水平布局容器中
    GtkWidget *input_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_append(GTK_BOX(chat_box), input_box);

    // 输入框
    GtkWidget *entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "输入你的问题...");
    gtk_box_append(GTK_BOX(input_box), entry);

    // 发送按钮
    GtkWidget *send_button = gtk_button_new_with_label("发送");
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(chat_history));
    g_signal_connect(send_button, "clicked", G_CALLBACK(on_send_clicked), buffer);
    gtk_box_append(GTK_BOX(input_box), send_button);

    // 显示窗口
    gtk_window_present (GTK_WINDOW (window));
}

int main(int argc, char *argv[]) {
    // 创建应用
    GtkApplication *app = gtk_application_new("com.example.OllamaClient", G_APPLICATION_FLAGS_NONE);
    // 连接激活信号,连接到函数on_activate
    g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);
    // 运行应用
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    // 释放资源
    g_object_unref(app);
    // 返回状态
    return status;
}
