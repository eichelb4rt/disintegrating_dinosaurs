#ifndef PARSE_ARGS_H_
#define PARSE_ARGS_H_
#include <string>

int parse_args(int argc, char const* argv[]);

extern double ITERATIONS_OPTION_VALUE;
extern std::string DATA_PATH_IN;
extern std::string FILE_PATH_OUT;
extern std::string JSON_FORM_PATH;
extern std::string JSON_PARAMETERS_PATH;

#endif // PARSE_ARGS_H_