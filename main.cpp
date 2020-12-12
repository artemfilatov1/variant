#include <iostream>

using namespace std;

union u{
    char c;
    short s;
    int i;
    double d;
    char* str;
    bool b;
};

enum t{
    Char, Short, Int, Double, String, Bool
};

class variant{
    u value;
    t type;
public:
    variant() = delete;
    variant(char c): type(Char), value{.c = c}{}
    variant(short s): type(Short), value{.s = s}{}
    variant(int i): type(Int), value{.i = i}{}
    variant(double d): type(Double), value{.d = d}{}
    variant(char* str): type(String), value{.str = strdup(str)}{}
    variant(bool b): type(Bool), value{.b = b}{}
    ~variant(){
        if (type == String){
            free(value.str);
        }
    }
    
    char asChar() throw(char*) {
        if (type == String){
            return value.c;
        } else {
            throw "incorect type";
        }
    }
    short asShort()throw(char*){
        if (type == Short){
            return value.s;
        } else {
            throw "incorect type";
        }
    }
    int asInt()throw(char*){
        if (type == Int){
            return value.i;
        } else {
            throw "incorect type";
        }
    }
    double asDouble()throw(char*){
        if (type == Double){
            return value.d;
        } else {
            throw "incorect type";
        }
    }
    char* asString()throw(char*){
        if (type == String){
            return value.str;
        } else {
            throw "incorect type";
        }
    }
    bool asBool()throw(char*){
        if (type == Bool){
            return value.b;
        } else {
            throw "incorect type";
        }
    }
    
    operator char() throw(char*) {
        return asChar();
    }
    operator short() throw(char*) {
        return asShort();
    }
    operator int() throw(char*) {
        return asInt();
    }
    operator double() throw(char*) {
        return asDouble();
    }
    operator char*() throw(char*) {
        return asString();
    }
    operator bool() throw(char*) {
        return asBool();
    }
    
    bool operator == (const variant& v){
        if (v.type != type) return false;
        switch(type){
            case Char: return v.value.c == value.c;
            case Short: return v.value.s == value.s;
            case Int: return v.value.i == value.i;
            case Double: return v.value.d == value.d;
            case String: return strcmp(v.value.str, value.str) == 0;
            case Bool: return v.value.b == value.b;
        }
    }
    bool operator == (const char& c){
        return operator == (variant(c));
    }
    bool operator == (const short& s){
        return operator == (variant(s));
    }
    bool operator == (const int& i){
        return operator == (variant(i));
    }
    bool operator == (const double& d){
        return operator == (variant(d));
    }
    bool operator == (const char*& str){
        return operator == (variant(str));
    }
    bool operator == (const bool& b){
        return operator == (variant(b));
    }
    
    void operator = (const variant& v){
        if(type == String) free(value.str);
        type = v.type;
        switch(type){
            case Char: value.c = v.value.c; break;
            case Short: value.s = v.value.s; break;
            case Int: value.i = v.value.i; break;
            case Double: value.d = v.value.d; break;
            case String: value.str = strdup(v.value.str); break;
            case Bool: value.b = v.value.b; break;
        }
        
    }
    void operator = (const char& c){
        operator = (variant(c));
    }
    void operator = (const short& s){
        operator = (variant(s));
    }
    void operator = (const int& i){
        operator = (variant(i));
    }
    void operator = (const double& d){
        operator = (variant(d));
    }
    void operator = (const char*& str){
        operator = (variant(str));
    }
    void operator = (const bool& b){
        operator = (variant(b));
    }
};

int main(int argc, const char * argv[]) {
    u un;
    variant v(5);
    if (v == 5) cout << "hello" << endl;
    cout << sizeof(un) << endl;
    cout << sizeof(v) << endl;
    return 0;
}
