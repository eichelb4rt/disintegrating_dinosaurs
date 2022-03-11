#ifndef READ_PARAMETERS_H_
#define READ_PARAMETERS_H_

#include <string>
#include <fstream>
#include "parameters.h"
#include "json.hpp"

using json = nlohmann::json;

int read_parameters(const std::string& parameters_file);

#endif // READ_PARAMETERS_H_