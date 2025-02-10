#include <gio/gio.h>
#include <gtk/gtk.h>
#include <gtk/gtkshortcut.h>

// 自定义新的GTK组件流程，就是该文件和tfetextview.cpp文件

/*
这行代码定义了一个宏 `TFE_TYPE_TEXT_VIEW`，它的值是 `tfe_text_view_get_type()`。
这个宏用于获取 `TfeTextView` 类型的GType（GTK类型系统中的类型）。
*/

// TfeTextView分为两部分。Tfe和TextView。Tfe称为前缀（prefix）或命名空间（namespace）。TextView被称为object
// 首先，定义TFE_TYPE_TEXT_VIEW宏为tfe_text_view_get_type()。
// 名称总是(prefix)TYPE(object)，并且字母都是大写。
// 替换文本总是(prefix)_(object)_get_type()，字母都是小写。
// 该定义放在G_DECLARE_FINAL_TYPE宏之前。
#define TFE_TYPE_TEXT_VIEW tfe_text_view_get_type ()

/*
这行代码使用了一个宏 `G_DECLARE_FINAL_TYPE` 来声明一个新的最终类型 `TfeTextView`。
这个宏会生成一些必要的函数和类型定义，使得 `TfeTextView` 成为一个GTK对象。具体来说，它会生成以下内容：
- `tfe_text_view_get_type()` 函数，用于获取 `TfeTextView` 类型的GType。
- `TfeTextView` 结构体，表示这个新的类型。typedef struct _TfeTextView TfeTextView
- `TfeTextViewClass` 结构体，表示这个新的类型的类。typedef struct {GtkTextView parent_class;} TfeTextViewClass;
- 一些其他的辅助函数和宏。
*/
// 参数列表：子类名、小写带下划线、前缀(大写)、对象(大写带下划线)和父类名(驼峰式)
G_DECLARE_FINAL_TYPE (TfeTextView, tfe_text_view, TFE, TEXT_VIEW, GtkTextView)

/*
声明构造函数
*/
// 无参数构造函数
GtkWidget *tfe_text_view_new(void);
// 有参数构造函数
GtkWidget *tfe_text_view_new_with_file(GFile *f);

/*
声明实例方法
*/
// 设置文件
void tfe_text_view_set_file(TfeTextView *tv, GFile *f);
// 获取文件
GFile *tfe_text_view_get_file(TfeTextView *tv);
// 打开文件
void tfe_text_view_open(TfeTextView *tv, GtkWindow *win);
// 保存文件
void tfe_text_view_save(TfeTextView *tv);
// 另存为
void tfe_text_view_saveas(TfeTextView *tv);


/* 全局变量 */
// open-response信号的常数
enum TfeTextViewOpenResponseType {
    TFE_OPEN_RESPONSE_SUCCESS, // 0
    TFE_OPEN_RESPONSE_CANCEL,  // 1
    TFE_OPEN_RESPONSE_ERROR    // 2
};
