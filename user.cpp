#include <cstdio>
#include <memory>
#include <string>
#include <vector>
#include <utility>
#include <gtk/gtk.h>
#include "internal.hpp"

extern window_param win_param;

extern "C" int define_window(int x, int y, int width, int height) {
    //--> std::vector<std::unique_ptr<std::vector<std::unique_ptr<operation> >& ops = get_op_list();

    return _define_window(x, y, width, height);
}

extern "C" void draw_line( double x1, double y1, double x2, double y2 ) {
    plist_type plist { std::make_unique<std::vector<param>>() };
    
    add_parameter<double,DoubleParam>(*plist, x1);
    add_parameter<double,DoubleParam>(*plist, y1);
    add_parameter<double,DoubleParam>(*plist, x2);
    add_parameter<double,DoubleParam>(*plist, y2);
    
    add_operation(
        operation {new Operation {std::move(plist), OperationType::draw}}
    );
}

extern "C" void set_line_color( const char *col ) {
    //plist_type plist { new std::vector<param> {} };
    plist_type plist { std::make_unique<std::vector<param>>() };
    
    add_parameter<std::string,StringParam>(*plist, col);
    add_operation(
        operation {new Operation {std::move(plist), OperationType::set_line_color}}
    );
}

extern "C" void set_line_width( double w ) {
    //plist_type plist { new std::vector<param> {} };
    plist_type plist { std::make_unique<std::vector<param>>() };
    
    add_parameter<double,DoubleParam>(*plist, w);
    add_operation(
        operation {new Operation {std::move(plist), OperationType::set_line_width}}
    );
}

extern "C" void set_title( const char *title ) {
    _set_title(title);
}

extern "C" void show_window() {
    const char *argv[1] = { "prog" };
    int argc = 1;
    GtkApplication *app = gtk_application_new (
        "org.gtk.example", G_APPLICATION_FLAGS_NONE
    );
    g_signal_connect( app, "activate", G_CALLBACK(activate), NULL);
    int status = g_application_run(G_APPLICATION(app), argc, const_cast<char **>(argv));
    g_object_unref (app);
}


