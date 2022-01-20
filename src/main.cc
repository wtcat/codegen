#include <string>
#include <iostream>

#include <google/protobuf/io/printer.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>



int main(int argc, char* argv[]) {
    std::string s;
    google::protobuf::io::StringOutputStream output(&s);
    google::protobuf::io::Printer printer(&output, '$');
    std::map<std::string, std::string> vars;
    vars["1"] = "hello";
    vars["2"] = "world";
    vars["3"] = "!";
    printer.Print(vars, "$1$ $2$ $3$");

    std::cout << s;
    return 0;
}

