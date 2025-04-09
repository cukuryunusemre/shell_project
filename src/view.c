#include "view.h"
#include "controller.h"
#include "model.h"
#include <string.h>

AppWidgets widgets;

void append_text_to_view(const char *text) {
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(widgets.text_view));
    GtkTextIter end;
    gtk_text_buffer_get_end_iter(buffer, &end);
    gtk_text_buffer_insert(buffer, &end, text, -1);
    gtk_text_buffer_insert(buffer, &end, "\n", -1);
}

gboolean poll_shared_message(gpointer data) {
    const char *msg = read_messages();

    if (strlen(msg) > 0) {
        static char last_msg[BUF_SIZE] = "";

        if (strcmp(msg, last_msg) != 0) {
            append_text_to_view(msg);
            strncpy(last_msg, msg, BUF_SIZE);
        }
    }
    return TRUE;
}

void on_entry_activate(GtkEntry *entry, gpointer data) {
    const char *input = gtk_entry_get_text(entry);
    handle_user_input(input);
    gtk_entry_set_text(entry, "");
}

void view_init(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    widgets.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(widgets.window), "Shell GUI");
    gtk_window_set_default_size(GTK_WINDOW(widgets.window), 600, 400);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(widgets.window), vbox);

    widgets.text_view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(widgets.text_view), FALSE);
    gtk_box_pack_start(GTK_BOX(vbox), widgets.text_view, TRUE, TRUE, 0);

    widgets.entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(vbox), widgets.entry, FALSE, FALSE, 0);

    g_signal_connect(widgets.window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(widgets.entry, "activate", G_CALLBACK(on_entry_activate), NULL);

    g_timeout_add(1000, poll_shared_message, NULL); // her saniye shared memory kontrolü

    gtk_widget_show_all(widgets.window);
    gtk_main();
}

