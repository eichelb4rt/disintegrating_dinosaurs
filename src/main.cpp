#include <iostream>
#include "parse_args.h"
#include "dataframe.h"
#include "csv.h"
#include "datasaurus.h"
#include "forms.h"
#include "math_helper.h"
#include "images.h"
#include "parameters.h"
#include "read_parameters.h"

#define N_SAVED_ITERATIONS 50

using namespace std;

int main(int argc, char const* argv[]) {
    int err;
    // parse arguments
    err = parse_args(argc, argv);
    if (err) {
        return EXIT_FAILURE;
    }

    // read parameters
    err = read_parameters(JSON_PARAMETERS_PATH);
    if (err) {
        cout << "Something went wrong reading parameter file " << JSON_PARAMETERS_PATH << endl;
        return EXIT_FAILURE;
    }

    // confirm shake
    cout << "Shake was set to " << SHAKE << "." << endl;

    // confirm iteration count
    cout << "Iteration count was set to " << ITERATIONS_OPTION_VALUE << "." << endl;
    // construct how many iterations we want to save
    vector<long> saved_iterations;
    saved_iterations.reserve(N_SAVED_ITERATIONS);
for (int i = 0; i < N_SAVED_ITERATIONS; ++i) {
        saved_iterations.push_back(1 + round((ITERATIONS_OPTION_VALUE - 1) * ease_in_sine((double) i / N_SAVED_ITERATIONS)));
    }

    // read the form
    mathematical_form& form = read_json_form(JSON_FORM_PATH, &err);
    if (err) {
        cout << "Something went wrong reading form file " << JSON_FORM_PATH << endl;
        return EXIT_FAILURE;
    }

    // read the data
    const dataframe df = read_csv(DATA_PATH_IN, &err);
    if (err) {
        cout << "Something went wrong reading data file " << DATA_PATH_IN << endl;
        return EXIT_FAILURE;
    }

    // do the stuff
    dataframe new_df = run_pattern(df, form, ITERATIONS_OPTION_VALUE, saved_iterations);
    write_csv(FILE_PATH_OUT, new_df);
    cout << "initial stats:" << endl << stats_string(get_standard_stats(df)) << endl << endl << "new stats:" << endl << stats_string(get_standard_stats(new_df)) << endl;

    return EXIT_SUCCESS;
}

