#include <gtk/gtk.h>

/*
############################################################################################################
# C并不支持面向对象编程，但是可以通过结构体和函数指针来模拟面向对象编程。
# #include <stdio.h>
# #include <stdlib.h>
# #include <string.h>
#
# // 定义一个结构体，类似于 Java 类
# typedef struct {
#     char text[100];  // 相当于 Java 的成员变量
#    void (*setText)(struct TextView*, const char*);  // 方法指针
# } TextView;
#
# // setText 方法
# void setTextFunc(TextView* self, const char* t) {
#     strcpy(self->text, t);
# }
#
# // 创建实例
# int main() {
#     TextView view;  // 相当于 Java 的 `new`
#     view.setText = setTextFunc;
#     view.setText(&view, "Hello, World!");
#
#     printf("%s\n", view.text);
#     return 0;
# }
############################################################################################################
# GTK 的 GObject 类型系统在 C 语言里实现了 OOP 机制，主要依靠：
#
# 结构体（struct）来模拟类
# 指针和函数表来模拟继承和多态
# GObject 类型系统来管理对象
#
# 在 GTK 中：
# GtkTextView 是实例，类似于 Java 的 new TextView()。
# GtkTextViewClass 是类结构体，存储类的行为（类似于 Java 的 Class<?>）。
# ------------------------------------------------------------------
# typedef struct {
#     GtkWidget parent_instance;  // 继承自 GtkWidget
# } GtkTextView;
#
# typedef struct {
#     GtkWidgetClass parent_class;  // 存储类方法
# } GtkTextViewClass;
# ------------------------------------------------------------------
# 两者如何关联？
# 在 GObject 体系中，每个实例(GtkTextView)继承Gobject,Gobject有一个g_type_instance指针，指向其类
# 因此每个实例(GtkTextView)都有一个指向其类(GtkTextViewClass)的指针。这个指针存储在 parent_instance 里
# ------------------------------------------------------------------
# typedef struct {
#     GTypeInstance g_type_instance;  // 这里存储指向类结构体的指针
# } GObject;
#
# typedef struct {
#     GObject parent_instance;
# } GtkWidget;
#
# typedef struct {
#     GtkWidget parent_instance;  // GtkTextView 继承 GtkWidget
# } GtkTextView;
# ------------------------------------------------------------------
# 当我们有 GtkTextView 实例时，可以通过 GTK_TEXT_VIEW_GET_CLASS() 获取它的类信息
# GtkTextViewClass *klass = GTK_TEXT_VIEW_GET_CLASS(view); // 获取类指针
# 当 GtkTextView 需要调用类的方法时
# 先通过 GTK_TEXT_VIEW_GET_CLASS(view) 获取 GtkTextViewClass。
# 然后调用 GtkTextViewClass 里的方法指针。
############################################################################################################
*/


/* Define TfeTextView Widget which is the child class of GtkTextView */

/*
这行代码定义了一个宏 `TFE_TYPE_TEXT_VIEW`，它的值是 `tfe_text_view_get_type()`。
这个宏用于获取 `TfeTextView` 类型的GType（GTK类型系统中的类型）。
*/

// TfeTextView分为两部分。Tfe和TextView。Tfe称为前缀（prefix）或命名空间（namespace）。TextView被称为object
// 首先，定义TFE_TYPE_TEXT_VIEW宏为tfe_text_view_get_type()。
// 名称总是(prefix)TYPE(object)，并且字母都是大写。
// 替换文本总是(prefix)_(object)_get_type()，字母都是小写。
// 该定义放在G_DECLARE_FINAL_TYPE宏之前。
#define TFE_TYPE_TEXT_VIEW tfe_text_view_get_type()
/*
这行代码使用了一个宏 `G_DECLARE_FINAL_TYPE` 来声明一个新的最终类型
`TfeTextView`。 这个宏会生成一些必要的函数和类型定义，使得 `TfeTextView`
成为一个GTK对象。具体来说，它会生成以下内容：
- `tfe_text_view_get_type()` 函数，用于获取 `TfeTextView` 类型的GType。
- `TfeTextView` 结构体，表示这个新的类型。typedef struct _TfeTextView
- `TfeTextViewClass` 结构体，表示这个新的类型的类。typedef struct {GtkTextView parent_class;} TfeTextViewClass;
TfeTextView
- 一些其他的辅助函数和宏。
*/
// 参数列表：子类名、小写带下划线、前缀(大写)、对象(大写带下划线)和父类名(驼峰式)
G_DECLARE_FINAL_TYPE(TfeTextView, tfe_text_view, TFE, TEXT_VIEW, GtkTextView)

/*
这段代码是对之前声明的 `TfeTextView` 类型的具体实现。加下划线表明是私有对象
它定义了 `_TfeTextView` 类型的结构体
*/
struct _TfeTextView {
  GtkTextView parent;
  GFile *file;
};
/*
这个宏主要用于向类型系统注册新类
*/
// 参数列表：子对象名称(驼峰大小写)，带有下划线的小写，父对象类型(prefix)TYPE(object)
G_DEFINE_FINAL_TYPE(TfeTextView, tfe_text_view, GTK_TYPE_TEXT_VIEW);

static void tfe_text_view_init(TfeTextView *tv) { tv->file = NULL; }

static void tfe_text_view_class_init(TfeTextViewClass *class) {}

void tfe_text_view_set_file(TfeTextView *tv, GFile *f) { tv->file = f; }

GFile *tfe_text_view_get_file(TfeTextView *tv) { return tv->file; }

GtkWidget *tfe_text_view_new(void) {
  return GTK_WIDGET(g_object_new(TFE_TYPE_TEXT_VIEW, NULL));
}

/* ---------- end of the definition of TfeTextView ---------- */

// 关闭窗口前保存文件
static gboolean before_close(GtkWindow *win, GtkWidget *nb) {
  GtkWidget *scr;
  GtkWidget *tv;
  GFile *file;
  char *pathname;
  GtkTextBuffer *tb;
  GtkTextIter start_iter;
  GtkTextIter end_iter;
  char *contents;
  unsigned int n;
  unsigned int i;
  GError *err = NULL;

  n = gtk_notebook_get_n_pages(GTK_NOTEBOOK(nb));
  for (i = 0; i < n; ++i) {
    scr = gtk_notebook_get_nth_page(GTK_NOTEBOOK(nb), i);
    tv = gtk_scrolled_window_get_child(GTK_SCROLLED_WINDOW(scr));
    file = tfe_text_view_get_file(TFE_TEXT_VIEW(tv));
    tb = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tv));
    gtk_text_buffer_get_bounds(tb, &start_iter, &end_iter);
    contents = gtk_text_buffer_get_text(tb, &start_iter, &end_iter, FALSE);
    if (!g_file_replace_contents(file, contents, strlen(contents), NULL, TRUE,
                                 G_FILE_CREATE_NONE, NULL, NULL, &err)) {
      g_printerr("%s.\n", err->message);
      g_clear_error(&err);
    }
    g_free(contents);
    g_object_unref(file);
  }
  return FALSE;
}

static void app_activate(GApplication *app) {
  g_print("You need to give filenames as arguments.\n");
}

static void app_open(GApplication *app, GFile **files, gint n_files,
                     gchar *hint) {
  GtkWidget *win;
  GtkWidget *nb;
  GtkWidget *lab;
  GtkNotebookPage *nbp;
  GtkWidget *scr;
  GtkWidget *tv;
  GtkTextBuffer *tb;
  char *contents;
  gsize length;
  char *filename;
  int i;
  GError *err = NULL;

  // 创建窗口
  win = gtk_application_window_new(GTK_APPLICATION(app));
  gtk_window_set_title(GTK_WINDOW(win), "file editor");
  gtk_window_set_default_size(GTK_WINDOW(win), 600, 400);

  // 创建notebook
  nb = gtk_notebook_new();
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
  // 如果notebook中有页面，显示窗口，否则销毁窗口
  if (gtk_notebook_get_n_pages(GTK_NOTEBOOK(nb)) > 0) {
    // 关闭窗口时触发close-request保存文件
    g_signal_connect(win, "close-request", G_CALLBACK(before_close), nb);
    gtk_window_present(GTK_WINDOW(win));
  } else
    gtk_window_destroy(GTK_WINDOW(win));
}

int main(int argc, char **argv) {
  GtkApplication *app;
  int status;

  app = gtk_application_new("com.github.ToshioCP.tfe1",
                            G_APPLICATION_HANDLES_OPEN);
  g_signal_connect(app, "activate", G_CALLBACK(app_activate), NULL);
  g_signal_connect(app, "open", G_CALLBACK(app_open), NULL);
  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);
  return status;
}
