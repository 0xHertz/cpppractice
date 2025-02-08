#include <gtk/gtk.h>
#include "tfetextview.h"

/*
这段代码是对之前声明的 `TfeTextView` 类型的具体实现。加下划线表明是私有对象
它定义了 `_TfeTextView` 类型的结构体
*/
struct _TfeTextView
{
  GtkTextView parent;
  GFile *file;
};

/*
这个宏主要用于向类型系统注册新类
*/
// 参数列表：子对象名称(驼峰大小写)，带有下划线的小写，父对象类型(prefix)TYPE(object)
G_DEFINE_TYPE (TfeTextView, tfe_text_view, GTK_TYPE_TEXT_VIEW);

static void
tfe_text_view_init (TfeTextView *tv) {
}

static void
tfe_text_view_class_init (TfeTextViewClass *class) {
}

void
tfe_text_view_set_file (TfeTextView *tv, GFile *f) {
  tv->file = f;
}

GFile *
tfe_text_view_get_file (TfeTextView *tv) {
  return tv->file;
}

GtkWidget *
tfe_text_view_new (void) {
  return GTK_WIDGET (g_object_new (TFE_TYPE_TEXT_VIEW, NULL));
}
