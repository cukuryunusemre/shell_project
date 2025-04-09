#ifndef VIEW_H
#define VIEW_H

#include <gtk/gtk.h>

typedef struct {
    GtkWidget *window;
    GtkWidget *text_view;
    GtkWidget *entry;
} AppWidgets;

void view_init(int argc, char *argv[]);
void append_text_to_view(const char *text);

#endif

