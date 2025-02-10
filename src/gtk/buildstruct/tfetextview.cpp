#include <glib.h>
#include <gtk/gtk.h>
#include <gtk/gtkshortcut.h>
#include "tfetextview.h"

/*
--------------------------------------------------------------------------------------
这段代码是对之前声明的 `TfeTextView` 类型的具体实现。加下划线表明是私有对象
它定义了 `_TfeTextView` 类型的结构体
*/
struct _TfeTextView
{
  GtkTextView parent;
  GFile *file;
};

/*
--------------------------------------------------------------------------------------
这个宏主要用于向类型系统注册新类
*/
// 参数列表：子对象名称(驼峰大小写)，带有下划线的小写，父对象类型(prefix)TYPE(object)
G_DEFINE_TYPE (TfeTextView, tfe_text_view, GTK_TYPE_TEXT_VIEW);


/* ---------------------------------------------------------------------------------- */
/* 类方法，主要是定义类生命周期函数 或者 自定义初始化函数 */
/* 类初始化函数，可进行生命周期函数的绑定 和 自定义信号的注册 */
// 自定义信号
enum{
    CHANGE_FILE,
    OPEN_RESPONSE,
    NUMBER_OF_SIGNALS
};
// 信号数组
static guint tfe_text_view_signals[NUMBER_OF_SIGNALS];
// 定义生命周期函数，这里用销毁函数为例
static void tfe_text_view_dispose(GObject *gobject){
    TfeTextView *tv = TFE_TEXT_VIEW(gobject);
    // 判断tv->file是否释放
    if (G_IS_FILE(tv->file)){
        // 释放tv->file
        g_clear_object(&tv->file);
    }
    // 调用父类的dispose函数
    G_OBJECT_CLASS(tfe_text_view_parent_class)->dispose(gobject);
}
// 类初始化函数
static void tfe_text_view_class_init(_TfeTextViewClass *class){
    GObjectClass *object_class = G_OBJECT_CLASS(class);
    // 绑定dispose函数
    object_class->dispose = tfe_text_view_dispose;
    // 注册自定义信号
    tfe_text_view_signals[CHANGE_FILE] = g_signal_new("change-file",
        G_TYPE_FROM_CLASS(class), // 类型
        G_SIGNAL_RUN_LAST | G_SIGNAL_NO_RECURSE | G_SIGNAL_NO_HOOKS, // 信号标志
        0, // 类偏移量
        NULL, // 累加器
        NULL, // 累加器数据
        NULL, // C调用函数
        G_TYPE_NONE, // 返回类型
        0); // 参数个数
    tfe_text_view_signals[OPEN_RESPONSE] = g_signal_new("open_response",
        G_TYPE_FROM_CLASS(class),// 类型
        G_SIGNAL_RUN_LAST | G_SIGNAL_NO_RECURSE | G_SIGNAL_NO_HOOKS, // 信号标志
        0, // 类偏移量
        NULL, // 累加器
        NULL, // 累加器数据
        NULL, // C调用函数
        G_TYPE_NONE, // 返回类型
        1, // 参数个数
        G_TYPE_INT); // 参数类型
}
// 初始化函数
static void tfe_text_view_init(TfeTextView *tv){
    tv->file = NULL;
}


/*
--------------------------------------------------------------------------------------
构造函数
*/
// 无参数构造函数
GtkWidget *tfe_text_view_new(void){
    return GTK_WIDGET(g_object_new(TFE_TYPE_TEXT_VIEW, NULL));
}
// 有参数构造函数
GtkWidget *tfe_text_view_new_with_file(GFile *f){
    g_return_val_if_fail(G_IS_FILE(f), NULL);

    char *contents;
    int length;

    // 打开文件
    if (! g_file_load_contents(f, NULL, &contents, &length, NULL,NULL)){
        return NULL;
    }

    GtkWidget *tv = tfe_text_view_new();
    GtkTextBuffer *tb = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tv));
    TFE_TEXT_VIEW(tv)->file = g_file_dup(f);
    gtk_text_buffer_set_modified(tb, FALSE); // 设置为未修改
    g_free(contents);
    return tv;
}
/*
--------------------------------------------------------------------------------------
实例方法，主要是定义对象的操作方法
需要用到很多普通辅助函数
*/
// 设置文件
void tfe_text_view_set_file(TfeTextView *tv, GFile *f){
    tv->file = f;
}
// 获取文件
GFile *tfe_text_view_get_file(TfeTextView *tv){
    g_return_val_if_fail(TFE_IS_TEXT_VIEW(tv), NULL);
    if (G_IS_FILE(tv->file)){
        return g_file_dup(tv->file);
    }else{
        return NULL;
    }
}
static void open_dialog_cb (GObject *source_object, GAsyncResult *res, gpointer data); // 声明打开文件对话框回调函数
// 打开文件
void tfe_text_view_open(TfeTextView *tv, GtkWindow *win){
    g_return_if_fail(TFE_IS_TEXT_VIEW(tv));
    g_return_if_fail(GTK_IS_WINDOW(win) || win == NULL);

    GtkFileDialog *dialog;
    dialog = gtk_file_dialog_new();
    // 打开文件对话框，参数：对话框、窗口、父对象、回调函数、数据(将tv作为data传递给回调函数)
    gtk_file_dialog_open(dialog, win, NULL, open_dialog_cb, tv);
    g_object_unref(dialog);
}
static gboolean save_file(GFile *file, GtkTextBuffer *tb, GtkWindow *win); // 声明保存文件函数
// 保存文件
void tfe_text_view_save(TfeTextView *tv){
    g_return_if_fail(TFE_IS_TEXT_VIEW(tv));

    GtkTextBuffer *tb = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tv));
    GtkWidget *win = gtk_widget_get_ancestor(GTK_WIDGET(tv), GTK_TYPE_WINDOW);

    if (! gtk_text_buffer_get_modified(tb)){
        return;
    }else if (tv->file == NULL){
        tfe_text_view_saveas(tv);
    }else{
        save_file(tv->file, tb, GTK_WINDOW(win));
    }
}
static void save_dialog_cb(GObject *source_object, GAsyncResult *res, gpointer data); // 声明保存对话框回调函数
// 另存为
void tfe_text_view_saveas(TfeTextView *tv){
    g_return_if_fail(TFE_IS_TEXT_VIEW(tv));

    GtkWidget *win = gtk_widget_get_ancestor(GTK_WIDGET(tv), GTK_TYPE_WINDOW);
    GtkFileDialog *dialog;

    dialog = gtk_file_dialog_new();
    gtk_file_dialog_save(dialog, GTK_WINDOW(win), NULL, save_dialog_cb, tv);
    g_object_unref(dialog);
}


/*
--------------------------------------------------------------------------------------
定义辅助函数
*/
// 保存文件
static gboolean save_file(GFile *file, GtkTextBuffer *tb, GtkWindow *win){
    // 定义开始和结束迭代器
    GtkTextIter start, end;
    // 定义错误
    GError *err = NULL;
    // 定义状态
    gboolean stat;
    // 定义弹窗
    GtkAlertDialog *alert_dialog;


    // 获取缓冲区的开始和结束位置
    gtk_text_buffer_get_bounds(tb, &start, &end);
    // 获取缓冲区的文本
    char *contents = gtk_text_buffer_get_text(tb, &start, &end, FALSE);
    // 保存文件
    stat = g_file_replace_contents (file, contents, strlen (contents), NULL, TRUE, G_FILE_CREATE_NONE, NULL, NULL, &err);
    if (stat)
      gtk_text_buffer_set_modified (tb, FALSE);
    else {
      alert_dialog = gtk_alert_dialog_new ("%s", err->message);
      gtk_alert_dialog_show (alert_dialog, win);
      g_object_unref (alert_dialog);
      g_error_free (err);
    }
    g_free (contents);
    return stat;
}
// 打开文件对话框回调函数
// 参数：source_object、res、data
// source_object：源对象
// res：结果
// data：数据
// 这里data是tv
static void
open_dialog_cb (GObject *source_object, GAsyncResult *res, gpointer data) {
  GtkFileDialog *dialog = GTK_FILE_DIALOG (source_object);
  TfeTextView *tv = TFE_TEXT_VIEW (data);
  GtkTextBuffer *tb = gtk_text_view_get_buffer (GTK_TEXT_VIEW (tv));
  GtkWidget *win = gtk_widget_get_ancestor (GTK_WIDGET (tv), GTK_TYPE_WINDOW);
  GFile *file;
  char *contents;
  gsize length;
  gboolean file_changed;
  GtkAlertDialog *alert_dialog;
  GError *err = NULL;
  // 打开文件，参数：对话框、结果、错误
  if ((file = gtk_file_dialog_open_finish (dialog, res, &err)) != NULL
      && g_file_load_contents (file, NULL, &contents, &length, NULL, &err)) {
    // 设置文本缓冲区的文本
    gtk_text_buffer_set_text (tb, contents, length);
    g_free (contents);
    gtk_text_buffer_set_modified (tb, FALSE);
    // G_IS_FILE(tv->file) && tv->file == file => unref(tv->file), tv->file=file, emit response with SUCCESS
    // G_IS_FILE(tv->file) && tv->file != file => unref(tv->file), tv->file=file, emit response with SUCCESS, emit change-file
    // tv->file==NULL =>                                           tv->file=file, emit response with SUCCESS, emit change-file
    // The order is important. If you unref tv->file first, you can't compare tv->file and file anymore.
    // And the signals are emitted after new tv->file is set. Or the handler can't catch the new file.
    // 判断文件是否改变
    file_changed = (G_IS_FILE (tv->file) && g_file_equal (tv->file, file)) ? FALSE : TRUE;
    // 判断tv->file是否释放
    if (G_IS_FILE (tv->file))
      g_object_unref (tv->file);
    // 设置文件
    tv->file = file; // The ownership of 'file' moves to TfeTextView
    // 发送信号
    if (file_changed)
      g_signal_emit (tv, tfe_text_view_signals[CHANGE_FILE], 0);
    g_signal_emit (tv, tfe_text_view_signals[OPEN_RESPONSE], 0, TFE_OPEN_RESPONSE_SUCCESS);
  } else {
    if (err->code == GTK_DIALOG_ERROR_DISMISSED) // The user canceled the file chooser dialog
      g_signal_emit (tv, tfe_text_view_signals[OPEN_RESPONSE], 0, TFE_OPEN_RESPONSE_CANCEL);
    else {
      alert_dialog = gtk_alert_dialog_new ("%s", err->message);
      gtk_alert_dialog_show (alert_dialog, GTK_WINDOW (win));
      g_object_unref (alert_dialog);
      g_signal_emit (tv, tfe_text_view_signals[OPEN_RESPONSE], 0, TFE_OPEN_RESPONSE_ERROR);
    }
    g_clear_error (&err);
  }
}
// 保存对话框回调函数
// 参数：source_object、res、data
// source_object：源对象
// res：结果
// data：数据
// 这里data是tv
static void
save_dialog_cb(GObject *source_object, GAsyncResult *res, gpointer data) {
  GtkFileDialog *dialog = GTK_FILE_DIALOG (source_object);
  TfeTextView *tv = TFE_TEXT_VIEW (data);
  GtkTextBuffer *tb = gtk_text_view_get_buffer (GTK_TEXT_VIEW (tv));
  GFile *file;
  GtkWidget *win = gtk_widget_get_ancestor (GTK_WIDGET (tv), GTK_TYPE_WINDOW);
  GError *err = NULL;
  GtkAlertDialog *alert_dialog;

  if (((file = gtk_file_dialog_save_finish (dialog, res, &err)) != NULL) && save_file(file, tb, GTK_WINDOW (win))) {
    // The following is complicated. The comments here will help your understanding
    // G_IS_FILE(tv->file) && tv->file == file  => nothing to do
    // G_IS_FILE(tv->file) && tv->file != file  => unref(tv->file), tv->file=file, emit change_file signal
    // tv->file==NULL                           =>                  tv->file=file, emit change_file signal
    if (! (G_IS_FILE (tv->file) && g_file_equal (tv->file, file))) {
      if (G_IS_FILE (tv->file))
        g_object_unref (tv->file);
      tv->file = file; // The ownership of 'file' moves to TfeTextView.
      g_signal_emit (tv, tfe_text_view_signals[CHANGE_FILE], 0);
    }
  }
  if (err) {
    alert_dialog = gtk_alert_dialog_new ("%s", err->message);
    gtk_alert_dialog_show (alert_dialog, GTK_WINDOW (win));
    g_object_unref (alert_dialog);
    g_clear_error (&err);
  }
}
