#include "forms.h"
#include "forms/form_bullseye.h"
#include "forms/form_circle.h"
#include "forms/form_image.h"
#include "forms/form_cross.h"
#include "forms/form_rectangle.h"
#include "forms/form_star.h"
#include "forms/form_parallel_lines.h"

using namespace std;

mathematical_form& read_json_form(const string& form_path, int* error) {
    // read the json file
    ifstream f(form_path);
    // check if file actually exists
    *error = 0;
    if (!f.good()) {
        *error = 1;
        f.close();
        static form_circle returned_form(0, 0, 0);
        return returned_form;
    }
    json json_form = json::parse(f);
    f.close();

    // construct a form according to the json file
    string type = json_form["type"].get<string>();
    json parameters = json_form["parameters"];

    if (type == "circle") {
        double circle_center_x = parameters["circle_center_x"].get<double>();
        double circle_center_y = parameters["circle_center_y"].get<double>();
        double circle_radius = parameters["circle_radius"].get<double>();
        static form_circle returned_form(circle_center_x, circle_center_y, circle_radius);
        return returned_form;
    } else if (type == "rectangle") {
        double rectangle_start_x = parameters["rectangle_start_x"].get<double>();
        double rectangle_start_y = parameters["rectangle_start_y"].get<double>();
        double rectangle_width = parameters["rectangle_width"].get<double>();
        double rectangle_height = parameters["rectangle_height"].get<double>();
        static form_rectangle returned_form(rectangle_start_x, rectangle_start_y, rectangle_width, rectangle_height);
        return returned_form;
    } else if (type == "image") {
        double scale = parameters["scale"].get<double>();
        double offset_x = parameters["offset_x"].get<double>();
        double offset_y = parameters["offset_y"].get<double>();
        string image_path = parameters["image_path"].get<string>();
        static form_image returned_form(offset_x, offset_y, scale, image_path);
        return returned_form;
    } else if (type == "bullseye") {
        double center_x = parameters["center_x"].get<double>();
        double center_y = parameters["center_y"].get<double>();
        double inner_radius = parameters["inner_radius"].get<double>();
        double outer_radius = parameters["outer_radius"].get<double>();
        static form_bullseye returned_form(center_x, center_y, inner_radius, outer_radius);
        return returned_form;
    } else if (type == "cross") {
        double center_x = parameters["center_x"].get<double>();
        double center_y = parameters["center_y"].get<double>();
        double leg_length = parameters["leg_length"].get<double>();
        static form_cross returned_form(center_x, center_y, leg_length);
        return returned_form;
    } else if (type == "star") {
        int n_peaks = parameters["n_peaks"].get<int>();
        double center_x = parameters["center_x"].get<double>();
        double center_y = parameters["center_y"].get<double>();
        double size = parameters["size"].get<double>();
        double stretch = parameters["stretch"].get<double>();
        static form_star returned_form(n_peaks, center_x, center_y, size, stretch);
        return returned_form;
    } else if (type == "parallel_lines") {
        int n_lines = parameters["n_lines"].get<int>();
        double center_x = parameters["center_x"].get<double>();
        double center_y = parameters["center_y"].get<double>();
        double length = parameters["length"].get<double>();
        double distance = parameters["distance"].get<double>();
        double angle = parameters["angle"].get<double>();
        static form_parallel_lines returned_form(n_lines, center_x, center_y, length, distance, angle);
        return returned_form;
    }

    // else just use one of the example forms
    return read_json_form("example_forms/circle.json", error);
}