#include "read_parameters.h"

using namespace std;

int read_parameters(const string& parameters_file) {
    // read the json file
    ifstream f(parameters_file);
    // check if it actually exists
    if (!f.good()) {
        f.close();
        return 1;
    }
    json json_params = json::parse(f);
    f.close();

    // read parameters
    SHAKE = json_params["shake"].get<double>();
    ALLOWED_DIST = json_params["allowed_dist"].get<double>();
    ACCEPTED_DECIMAL_DIGITS = json_params["digits"].get<int>();
    MIN_TEMPERATURE = json_params["min_temp"].get<double>();
    MAX_TEMPERATURE = json_params["max_temp"].get<double>();
    return 0;
}