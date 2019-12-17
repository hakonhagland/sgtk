#include <string>
#include <memory>
#include <vector>

typedef struct {
    int x;
    int y;
    int height;
    int width;
    std::unique_ptr<std::string> title;
} window_param;

//extern window_param *win_param;

class Parameter {
public:
    Parameter() {
    }
    virtual ~Parameter() {}
};

using param = std::unique_ptr<Parameter>;
using plist_type = std::unique_ptr<std::vector<param>>;

enum class OperationType {
    set_line_width, draw, set_line_color
};


class Operation {
public:
    Operation(plist_type plist, OperationType ot) 
        : plist(std::move(plist)), op_name(ot) { }

    OperationType get_name() {
        return op_name;
    }

    plist_type& get_plist() {
        return plist;
    }
    
private:
    plist_type plist;
    OperationType op_name;
};

using operation = std::unique_ptr<Operation>;
using oplist_type = std::unique_ptr<std::vector<operation>>;

class StringParam : public Parameter {
public:
    StringParam(const std::string &s) : s_(s) { }
    std::string get_value() {return s_; }
private:
    const std::string s_;
};

class DoubleParam : public Parameter {
public:
    DoubleParam(double a) : a(a) { }
    double get_value() {return a; }
private:
    double a;
};

class IntParam : public Parameter {
public:
    IntParam(int a) : a(a) { }
private:
    int a;
};

template <class T, class R, class U>
void add_parameter(U &plist, T x1) {
    R *param1 {new R {x1}};
    auto *pparam1 = dynamic_cast<Parameter *>(param1);
    auto up1 = std::unique_ptr<Parameter>(pparam1);
    plist.emplace_back(std::move(up1));
}


void add_operation (operation o);
void activate (GtkApplication* app, gpointer user_data);
int _define_window(int x, int y, int width, int height);
void _set_title( const char *title );
