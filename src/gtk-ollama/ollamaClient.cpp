#include <cstddef>
#include <gtk/gtk.h>

// 配置对话框响应的回调函数
static void on_config_response(GtkDialog *dialog, gint response_id, gpointer user_data) {
    GtkWidget *ip_entry = GTK_WIDGET(g_object_get_data(G_OBJECT(dialog), "ip_entry"));
    GtkWidget *combo_box = GTK_WIDGET(g_object_get_data(G_OBJECT(dialog), "combo_box"));

    if (response_id == GTK_RESPONSE_OK) {
        // const gchar *ip_address = gtk_entry_get_text(GTK_ENTRY(ip_entry));
        // const gchar *selected_option = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(combo_box));
        // g_print("IP Address: %s\n", ip_address);
        // g_print("Selected Option: %s\n", selected_option);
    }

    gtk_window_destroy(GTK_WINDOW(dialog));
}
// 配置按钮的点击事件处理函数
static void on_config_button_clicked(GtkButton *button, gpointer user_data) {
    // 创建配置对话框
    GtkWidget *dialog;
    GtkWidget *content_area;
    GtkWidget *ip_entry;
    GtkWidget *combo_box;
    GtkWidget *label;
    GtkDialogFlags flags = (GtkDialogFlags)(GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT);

    dialog = gtk_dialog_new_with_buttons("Configure Settings",
                                            GTK_WINDOW(user_data),
                                            flags,
                                            "_OK",
                                            GTK_RESPONSE_OK,
                                            "_Cancel",
                                            GTK_RESPONSE_CANCEL,
                                            NULL);

    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    // 添加 IP 地址输入框
    label = gtk_label_new("IP Address:");
    gtk_box_append(GTK_BOX(content_area), label);
    ip_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(ip_entry), "Enter IP address");
    gtk_box_append(GTK_BOX(content_area), ip_entry);

    // 添加下拉选择框
    label = gtk_label_new("Select Option:");
    gtk_box_append(GTK_BOX(content_area), label);
    combo_box = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_box), "Option 1");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_box), "Option 2");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_box), "Option 3");
    gtk_combo_box_set_active(GTK_COMBO_BOX(combo_box), 0); // 默认选择第一个选项
    gtk_box_append(GTK_BOX(content_area), combo_box);

    // 将控件指针存储在对话框的数据中以便稍后使用
    g_object_set_data(G_OBJECT(dialog), "ip_entry", ip_entry);
    g_object_set_data(G_OBJECT(dialog), "combo_box", combo_box);

    // 连接响应信号以处理对话框响应
    g_signal_connect(dialog, "response", G_CALLBACK(on_config_response), NULL);

    gtk_widget_show(dialog);

    gtk_window_destroy(GTK_WINDOW(dialog));
}

// 发送按钮的点击事件处理函数
static void on_send_button_clicked(GtkButton *button, gpointer user_data) {
    g_print("Send button clicked!\n");
}


// 激活函数，创建窗口和布局
static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *box;
    GtkWidget *session_list;
    GtkWidget *session_view;
    GtkWidget *header_bar;
    GtkWidget *config_button;
    GtkWidget *entry_box;
    GtkWidget *input_entry;
    GtkWidget *send_button;

    // 创建窗口
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Ollama Client");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

    // 创建水平盒子布局
    box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_window_set_child(GTK_WINDOW(window), box);

    // 创建左侧会话列表
    session_list = gtk_list_box_new();
    gtk_box_append(GTK_BOX(box), session_list);

    // 创建右侧会话窗口
    session_view = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_append(GTK_BOX(box), session_view);

    // 向会话列表中添加元素
    for (int i = 0; i < 5; i++) {
        GtkWidget *row = gtk_list_box_row_new(); // 创建新的 GtkListBoxRow
        GtkWidget *label = gtk_label_new(g_strdup_printf("Session %d", i + 1)); // 创建标签
        gtk_list_box_row_set_child(GTK_LIST_BOX_ROW(row), label); // 设置行的子组件
        gtk_list_box_append(GTK_LIST_BOX(session_list), row); // 将行添加到列表中
    }
    // 创建输入框和发送按钮的容器
    entry_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_append(GTK_BOX(session_view), entry_box);

    // 创建输入框
    input_entry = gtk_entry_new();
    gtk_box_append(GTK_BOX(entry_box), input_entry);

    // 创建发送按钮
    send_button = gtk_button_new_with_label("Send");
    g_signal_connect(send_button, "clicked", G_CALLBACK(on_send_button_clicked), NULL);
    gtk_box_append(GTK_BOX(entry_box), send_button);

    // 创建标题栏
    header_bar = gtk_header_bar_new();
    gtk_window_set_titlebar(GTK_WINDOW(window), header_bar);

    // 创建配置按钮
    config_button = gtk_button_new_from_icon_name("preferences-system-symbolic");
    gtk_button_set_label(GTK_BUTTON(config_button), "Config");
    g_signal_connect(config_button, "clicked", G_CALLBACK(on_config_button_clicked), window);
    gtk_header_bar_pack_end(GTK_HEADER_BAR(header_bar), config_button);

    // 显示所有部件
    gtk_widget_show(window);
}

int main(int argc, char **argv) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("com.example.ollama_client", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
