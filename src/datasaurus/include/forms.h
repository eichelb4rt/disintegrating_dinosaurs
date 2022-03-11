#ifndef FORMS_H_
#define FORMS_H_

#include <string>
#include <algorithm>
#include <fstream>
#include <vector>
#include <omp.h>
#include "json.hpp"
#include "math_helper.h"
#include "images.h"

using json = nlohmann::json;


// abstract mathematical form has a name and a distance measure
class mathematical_form {
public:
    // here we define forms mathematically by defining the distance between a point in 2d-space and the form
    virtual double distance(double x, double y) const = 0;
};

// read form from file
mathematical_form& read_json_form(const std::string& form_path, int* error);

#endif // FORMS_H_