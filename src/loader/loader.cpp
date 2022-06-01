


#include "loader/loader.h"

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

Loader::Loader(){}

void
Loader::
load_from_file(const std::string& name)
{
    this->file_name = name;
    std::ifstream my_file;
    my_file.open(this->file_name);

    std::stringstream buffer;

    if (my_file.is_open()) {
        buffer << my_file.rdbuf();
        this->content = buffer.str();
    } else {
        std::cerr << "File: " << this->file_name << " open failed!" << std::endl;
    }
    my_file.close();
}

std::string
Loader::
get_file_name()
{
    return this->file_name;
}

std::string
Loader::
get_content()
{
    return this->content;
}

