#include <iostream>
#include "json.hpp"
#include <fstream>

using json = nlohmann::json;

// with path
int main() {
    std::string json_path;
    std::cin >> json_path;
    std::ifstream f(json_path);
    if (f.is_open()) {
        json data = json::parse(f);
        std::cout << data;
    }
    else {
        std::cerr << "Json reading error: json file with " << json_path << " path can't be open.\n";
    }
}


// with cin
/*
int main() {
    // json reader
    std::string json_string;
    char a;
    while (std::cin) {
        std::cin >> a;
        json_string += a;
    }
    json_string.pop_back();
    json data = json::parse(json_string);
    std::cout << data;
}
*/