#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
class table_cipher{
    private:
    uint key;
    double rows;
    std::string i_value;
    std::string t;
    std::vector<std::vector<std::string>> st_to_vec;
    void write_str_to_v(std::string st,std::vector<std::vector<std::string>> &v);
    void write_str_to_v(std::vector<std::vector<std::string>> &v);
    public:
    std::string encrypt();
    std::string decrypt();
    void text_validation(std::string &text);
    void key_validation(uint &key,std::string &text);
    table_cipher(std::string text,double k,std::string& initial_value);
    
};
class table_error: public std::invalid_argument
{
public:
    explicit table_error (const std::string& what_arg):
        std::invalid_argument(what_arg) {}
    explicit table_error (const char* what_arg):
        std::invalid_argument(what_arg) {}
};
