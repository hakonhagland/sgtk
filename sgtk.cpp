#include <cstdio>
#include <exception>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <utility>
#include <gtk/gtk.h>
#include "internal.hpp"


static oplist_type oplist;

static window_param win_param;

int _define_window(int x, int y, int width, int height) {
    win_param.x = x;
    win_param.y = y;
    win_param.height = height;
    win_param.width = width;
    return 1;
}

void _set_title( const char *title ) {
    win_param.title = std::unique_ptr<std::string> { new std::string {title}};
}

void add_operation (operation o) {
    if (oplist == nullptr ) {
        oplist = std::unique_ptr<std::vector<operation>> {new std::vector<operation>};
    }
    oplist->push_back(std::move(o));
}

template <class T, class R, class U>
T get_operation_parameter(U op, std::size_t index)
{
    std::vector<std::unique_ptr<Parameter>> &plist = *((*op)->get_plist());
                
    T w = dynamic_cast<R *>(plist.at(index).get())->get_value();
    return w;
}


void do_operation(cairo_t *cr) {
    if (oplist != nullptr) {
        //std::cout << "Number of elements: " << oplist->size() << '\n';
        //std::cout << "Number of elements: " << '\n';
        for(auto op = oplist->begin(); op != oplist->end(); ++op) {
            //Operation& oper = *op;
            auto type = (*op)->get_name();
            switch(type) {
            case OperationType::set_line_width :
                {
                    auto w = get_operation_parameter<double, DoubleParam>( op, 0 );
                    cairo_set_line_width(cr, w);
                }
                break;
            case OperationType::draw :
                {
                    auto x1 = get_operation_parameter<double, DoubleParam>( op, 0 );
                    auto y1 = get_operation_parameter<double, DoubleParam>( op, 1 );
                    auto x2 = get_operation_parameter<double, DoubleParam>( op, 2 );
                    auto y2 = get_operation_parameter<double, DoubleParam>( op, 3 );
                    cairo_move_to(cr, x1, y1);
                    cairo_line_to(cr, x2, y2);
                    cairo_stroke(cr);
                }
                break;
            case OperationType::set_line_color :
                {
                    auto col =
                        get_operation_parameter<std::string, StringParam>( op, 0 );
                    GdkRGBA color;
                    gdk_rgba_parse(&color, col.c_str()); 
                    gdk_cairo_set_source_rgba(cr, &color);
                }
                break;
            default :
                throw std::runtime_error("Invalid operation");
            }
        }
    }
}


gboolean start_draw( GtkWidget *widget, cairo_t *cr, gpointer data) {

    GtkWidget *window = (GtkWidget *) data;
    GtkStyleContext *context = gtk_widget_get_style_context(widget);
    guint width = gtk_widget_get_allocated_width(widget);
    guint height = gtk_widget_get_allocated_height(widget);
    do_operation(cr);
    
    return FALSE;
}

static void init_draw(GtkWidget *gtkWindow) {
    GtkWidget *drawing_area = gtk_drawing_area_new();
    gtk_container_add(GTK_CONTAINER(gtkWindow), drawing_area);
    gtk_widget_set_size_request(drawing_area, win_param.width, win_param.height);
    g_signal_connect(
        G_OBJECT(drawing_area), "draw", G_CALLBACK(start_draw), gtkWindow
    );
}

void activate (GtkApplication* app, gpointer user_data)
{

    GtkWidget *gtkWindow = gtk_application_window_new(app);
    gtk_window_set_title (GTK_WINDOW (gtkWindow), win_param.title->c_str());
    
    gtk_window_set_default_size(
        GTK_WINDOW (gtkWindow), win_param.width, win_param.height
    );
    gtk_window_move(GTK_WINDOW(gtkWindow), win_param.x, win_param.y);
    gtk_window_set_resizable(GTK_WINDOW(gtkWindow), TRUE);
    //gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER_ALWAYS);
    init_draw(gtkWindow);
    gtk_widget_show_all (gtkWindow);
}

