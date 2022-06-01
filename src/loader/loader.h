


#ifndef LOADER_H_
#define LOADER_H_

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

class Loader
{
private:
    std::string file_name;
    std::string content;
public:
    Loader();
    void load_from_file(const std::string& name);

    std::string get_file_name();
    std::string get_content();


};






#endif  // LOADER_H_
