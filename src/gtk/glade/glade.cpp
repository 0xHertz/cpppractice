#include <gtk/gtk.h>

void static
on_activate(GtkApplication *app, gpointer user_data){
    GtkBuilder *builder = gtk_builder_new_from_file("glade.ui");
    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "app"));
    gtk_window_set_application(GTK_WINDOW (window), GTK_APPLICATION (app));
    g_object_unref(builder);
    gtk_window_present (GTK_WINDOW (window));
}

int main(int argc, char *argv[]){
    GtkApplication *app = gtk_application_new("org.gtk.example",G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}
