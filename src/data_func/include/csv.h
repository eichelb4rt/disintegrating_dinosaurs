#ifndef CSV_H_
#define CSV_H_
#include <string>
#include "dataframe.h"

dataframe read_csv(std::string file_path, int* error);
void write_csv(std::string file_path, const dataframe& df);

#endif  // CSV_H_