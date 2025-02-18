#include <gtk/gtk.h>
#include <gtk/gtkcssprovider.h>
#include "tfetextview.h"
#include "tfenotebook.h"
#define APPLICATION_ID "org.gtk.example" // 定义应用程序ID

/*
--------------------------------------------------------------------------------------
1.应用程序支持，主要是处理命令行参数。
2.使用UI文件构建小部件。
3.连接按钮信号及其处理程序。
4.管理CSS。
--------------------------------------------------------------------------------------
*/

/*
程序销毁时，销毁css provider
*/
static void
before_destroy (GtkWidget *win, GtkCssProvider *provider) {
  GdkDisplay *display = gdk_display_get_default ();
  gtk_style_context_remove_provider_for_display (display, GTK_STYLE_PROVIDER (provider));
}
/*
点击打开按钮时调用的函数
*/
static void open_cb(GtkNotebook *nb){
    g_print("open_cb");
    notebook_page_open (GTK_NOTEBOOK (nb));
}
static void save_cb(GtkNotebook *nb){
    g_print("save_cb");
    notebook_page_save (GTK_NOTEBOOK (nb));
}
static void new_cb(GtkNotebook *nb){
    g_print("new_cb");
    notebook_page_new (GTK_NOTEBOOK (nb));
}
static void close_cb(GtkNotebook *nb){
    g_print("close_cb");
    notebook_page_close (GTK_NOTEBOOK (nb));
}
/*
程序启动时调用的函数
*/
static void on_startup(GApplication *application){
    GtkApplication *app = GTK_APPLICATION(application);

    // build an window from a resource
    GtkBuilder *builder = gtk_builder_new_from_file("/home/mr-kechen/Documents/cpp/src/gtk/selfdefinewidget/tfe.ui");
    // get item from builder
    GtkApplicationWindow *win = GTK_APPLICATION_WINDOW(gtk_builder_get_object(builder, "win"));
    GtkNotebook *nb = GTK_NOTEBOOK(gtk_builder_get_object(builder, "nb"));
    GtkButton *btn_open = GTK_BUTTON(gtk_builder_get_object(builder, "btnopen"));
    GtkButton *btn_save = GTK_BUTTON(gtk_builder_get_object(builder, "btnsave"));
    GtkButton *btn_new = GTK_BUTTON(gtk_builder_get_object(builder, "btnnew"));
    GtkButton *btn_close = GTK_BUTTON(gtk_builder_get_object(builder, "btnclose"));
    // set window to application
    gtk_window_set_application(GTK_WINDOW(win), app);
    // button connect signal
    g_signal_connect(btn_open, "clicked", G_CALLBACK(open_cb), nb);
    g_signal_connect(btn_save, "clicked", G_CALLBACK(save_cb), nb);
    g_signal_connect(btn_new, "clicked", G_CALLBACK(new_cb), nb);
    g_signal_connect(btn_close, "clicked", G_CALLBACK(close_cb), nb);
    // cancel ref builder
    g_object_unref(builder);

    // set css style
    GdkDisplay *display = gdk_display_get_default(); // 很奇怪，不是gtk，而是gdk
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_file(provider, g_file_new_for_path("/home/mr-kechen/Documents/cpp/src/gtk/selfdefinewidget/style.css"));
    gtk_style_context_add_provider_for_display(display, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    g_signal_connect (win, "destroy", G_CALLBACK (before_destroy), provider);
    g_object_unref (provider);
}
/*
程序激活时调用的函数
*/
void static on_activate(GApplication *app, gpointer user_data){
    GtkApplication *application = GTK_APPLICATION(app);
    // get activate window
    GtkWindow *win = gtk_application_get_active_window(application);
    // not know the code meaning
    // GtkWidget *boxv = gtk_window_get_child (GTK_WINDOW (win));
    // GtkNotebook *nb = GTK_NOTEBOOK (gtk_widget_get_last_child (boxv));
    // notebook_page_new (nb);

    // show window
    gtk_window_present(GTK_WINDOW(win));
}
/*
open信号处理函数
*/
void static on_open(GApplication *app, GFile **files, gint n_files,gchar *hint){
    GtkApplication *application = GTK_APPLICATION(app);
    // get activate window
    GtkWindow *win = gtk_application_get_active_window(application);
    // define variables
    int i;
    char *contents;
    gsize length;
    char *filename;
    GError *err = NULL;
    GtkWidget *scr;
    GtkWidget *tv;
    GtkTextBuffer *tb;
    GtkWidget *lab;
    GtkNotebookPage *nbp;
    // 创建notebook
    GtkWidget *nb = gtk_notebook_new();
    gtk_window_set_child(GTK_WINDOW(win), nb);

    // 循环文件列表，读取文件内容
    for (i = 0; i < n_files; i++) {
      // 参数：文件、编码、内容、长度、取消、错误
      if (g_file_load_contents(files[i], NULL, &contents, &length, NULL, &err)) {
        // 创建滚动窗格
        scr = gtk_scrolled_window_new();
        // 创建文本视图
        tv = tfe_text_view_new();
        tb = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tv));
        gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(tv), GTK_WRAP_WORD_CHAR);
        gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scr), tv);

        // 将文件内容加载到文本视图
        tfe_text_view_set_file(TFE_TEXT_VIEW(tv), g_file_dup(files[i]));
        gtk_text_buffer_set_text(tb, contents, length);
        g_free(contents);

        // 添加到notebook
        filename = g_file_get_basename(files[i]);
        lab = gtk_label_new(filename);
        gtk_notebook_append_page(GTK_NOTEBOOK(nb), scr, lab);
        // 设置标签页可扩展
        nbp = gtk_notebook_get_page(GTK_NOTEBOOK(nb), scr);
        g_object_set(nbp, "tab-expand", TRUE, NULL);
        g_free(filename);
      } else {
        g_printerr("%s.\n", err->message);
        g_clear_error(&err);
      }
    }
}

int main(int argc, char *argv[]) {
    // 创建一个新的应用程序
    GtkApplication *app = gtk_application_new(APPLICATION_ID,G_APPLICATION_HANDLES_OPEN);
    // 连接信号
    g_signal_connect(app, "open", G_CALLBACK(on_open), NULL);
    g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);
    g_signal_connect(app, "startup", G_CALLBACK(on_startup), NULL);
    // 运行应用程序
    int status = g_application_run(G_APPLICATION(app),argc,argv);
    // 释放资源
    g_object_unref(app);
    return status;
}
