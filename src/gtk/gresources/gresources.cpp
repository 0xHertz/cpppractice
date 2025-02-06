#include <gtk/gtk.h>
#include "resources.c"

void static
on_activate(GtkApplication *app, gpointer user_data){
    g_printerr("You need filename arguments.\n");
}
void static
on_open(GtkApplication *app, GFile ** files, gint n_files, gchar *hint){
    int i;
    char *contents;
    char *filename;
    gsize length;
    GtkWidget *scr;
    GtkWidget *tv;
    GtkWidget *lab;
    GtkTextBuffer *tb;
    GtkNotebookPage *nbp;
    GError *err = NULL;
    // 从资源文件中加载UI
    GtkBuilder *build = gtk_builder_new_from_resource("/home/mr-kechen/Documents/cpp/src/gtk/gresources/ftkbuilder_ui.ui");
    GtkWidget *win = GTK_WIDGET (gtk_builder_get_object (build, "win"));
    gtk_window_set_application (GTK_WINDOW (win), GTK_APPLICATION (app));
    GtkWidget *nb = GTK_WIDGET (gtk_builder_get_object (build, "nb"));
    g_object_unref(build);

    for (i = 0; i < n_files; i++) {
        if (g_file_load_contents (files[i], NULL, &contents, &length, NULL, &err)) {
          scr = gtk_scrolled_window_new ();
          tv = gtk_text_view_new ();
          tb = gtk_text_view_get_buffer (GTK_TEXT_VIEW (tv));
          gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW (tv), GTK_WRAP_WORD_CHAR);
          gtk_scrolled_window_set_child (GTK_SCROLLED_WINDOW (scr), tv);
          // gtk_text_view_set_file (GTK_TEXT_VIEW (tv),  g_file_dup (files[i]));
          gtk_text_buffer_set_text (tb, contents, length);
          g_free (contents);
          filename = g_file_get_basename (files[i]);
          lab = gtk_label_new (filename);
          gtk_notebook_append_page (GTK_NOTEBOOK (nb), scr, lab);
          nbp = gtk_notebook_get_page (GTK_NOTEBOOK (nb), scr);
          g_object_set (nbp, "tab-expand", TRUE, NULL);
          g_free (filename);
        } else {
          g_printerr ("%s.\n", err->message);
          g_clear_error (&err);
        }
      }
      if (gtk_notebook_get_n_pages (GTK_NOTEBOOK (nb)) > 0) {
        gtk_window_present (GTK_WINDOW (win));
      } else
        gtk_window_destroy (GTK_WINDOW (win));
}
int main(int argc, char *argv[]){
    // create a new application
    GtkApplication *app = gtk_application_new("org.gtk.example", G_APPLICATION_HANDLES_OPEN);
    // connect activate signal
    g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);
    // connect open signal
    g_signal_connect(app, "open", G_CALLBACK(on_open), NULL);
    // run the application
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    // release the application
    g_object_unref(app);
    // return status
    return status;
}
