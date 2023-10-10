#include <iostream>
#include <fstream>
#include <string>
#include "json.hpp"

using json = nlohmann::json;

using namespace std;
using dbl = double;


json read_json(const std::string& path) {
    std::ifstream f(path);
    if (f.is_open()) {
        json json_data = json::parse(f);
        return json_data;
    }
    else {
        throw ("Json reading error: json file with \"" + path + "\" path can't be open.\n");
    }
}

void change_datapath(nlohmann::json& json, const std::string datapath) {
    json["parameters"]["datapath"] = datapath;
    std::ofstream json_file(json["parameters"]["jsonpath"].get<std::string>());
    if (json_file.is_open()) json_file << json.dump(2, ' ', false);
    else std::cerr << "Error: json reading error file";
    json_file.close();
}


int main(int argc, char* argv[]) {
    // path to json file
    std::string path = argv[1];

    json json_data;
    try {
        json_data = read_json(path);
    }
    catch (std::string error) {
        std::cout << error;
    }

    // json const
    const string name = json_data["name"].get<std::string>();
    const dbl omega = json_data["omega"].get<double>();
    const dbl end_time = json_data["end_time"].get<double>();
    const dbl dt = json_data["dt"].get<double>();
    const dbl x_0 = json_data["x_0"].get<double>();
    const dbl v_0 = json_data["v_0"].get<double>();

    // changeable paramerts
    dbl t = 0;

    // data making
    ofstream datafile ("datafiles/" + name + ".txt");
    if (datafile.is_open()) {
        dbl x_i = x_0, v_i = v_0;
        datafile << 0 << "\t" << x_0 << "\t" << v_0 << "\n"; 
        dbl x_j, v_j;
        while (t < end_time) {
            x_j =  x_i + dt * v_i;
            v_j = v_i + dt * (- omega * omega) * x_i;
            t += dt;
            datafile << t << "\t" << x_j << "\t" << v_j << "\n";
            x_i = x_j;
            v_i = v_j;
            
        }

        change_datapath(json_data, "datafiles/" + name + ".txt");

        datafile.close();
    }
    else {cerr << "File opening error\n";}
    
}