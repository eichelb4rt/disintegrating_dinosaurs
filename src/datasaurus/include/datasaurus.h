#ifndef DATASAURUS_H_
#define DATASAURUS_H_

#include <math.h>
#include <string>
#include <sstream>
#include <iterator>
#include "csv.h"
#include "forms.h"
#include "my_rng.h"
#include "dataframe.h"
#include "parse_args.h"
#include "math_helper.h"
#include "parameters.h"

int perturb(dataframe& df, double temperature, random_seeds& seeds, const mathematical_form& form);

bool is_error_still_ok(const dataframe& df1, const dataframe& df2);

dataframe run_pattern(const dataframe& df, const mathematical_form& form, long iterations, const std::vector<long> saved_iterations = {});

#endif // DATASAURUS_H_
