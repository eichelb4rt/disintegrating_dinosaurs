#include "datasaurus.h"

using namespace std;

int perturb(dataframe& df, double temperature, random_seeds& seeds, const mathematical_form& form) {
    bool do_bad = random_normal(seeds) < temperature;
    bool in_bounds = true;
    int index;
    double x_old, y_old, x_new, y_new, dist_new, dist_old;
    do {
        // choose a random point
        index = random_index(seeds, df.n_points);
        // get its coords and distance to the target form
        x_old = df.x[index];
        y_old = df.y[index];
        dist_old = df.distances[index];
        // shake it, get new coords and distance
        x_new = x_old + random_normal(seeds) * SHAKE;
        y_new = y_old + random_normal(seeds) * SHAKE;
        dist_new = form.distance(x_new, y_new);
        // do until:
        // everything is in bounds and ((new is better) or (new is allowed) or (we are do_bad))
    } while (!((dist_new < dist_old || dist_new < ALLOWED_DIST || do_bad) && in_bounds));

    df.x[index] = x_new;
    df.y[index] = y_new;
    df.distances[index] = dist_new;
    return index;
}

dataframe run_pattern(const dataframe& initial_df, const mathematical_form& form, long iterations, const vector<long> saved_iterations) {
    // initialize random stuff
    random_seeds seeds;
    seed(seeds);
    // current index of the next iteration to be saved
    int next_saved_iteration_index = 0;
    int n_saved_iterations = saved_iterations.size();
    // index that is changed by perturb
    int changed_index;
    // simulated annealing temperature
    double temperature;
    // df changed by perturb
    dataframe new_df = initial_df.copy();
    new_df.cache_distances(form);
    // df that is compared to new df
    dataframe current_df = initial_df.copy();
    current_df.cache_distances(form);
    // initial stats
    const standard_stats initial_stats = get_standard_stats(initial_df);
    // stats of the new (changing) dataframe
    standard_stats new_stats;

    for (int i = 1; i <= iterations; ++i) {
        // adjust the temperature
        temperature = (MAX_TEMPERATURE - MIN_TEMPERATURE) * s_curve(((iterations - i) / iterations)) + MIN_TEMPERATURE;
        // move a point towards the target form
        changed_index = perturb(new_df, temperature, seeds, form);
        // and see if it's actually better
        new_stats = get_standard_stats(new_df);
        if (stats_equal_in_shown_digits(initial_stats, new_stats)) {
            // if it's better, change the dataframe
            current_df.x[changed_index] = new_df.x[changed_index];
            current_df.y[changed_index] = new_df.y[changed_index];
            current_df.distances[changed_index] = new_df.distances[changed_index];
        } else {
            // if it's worse, reset the new dataframe
            new_df.x[changed_index] = current_df.x[changed_index];
            new_df.y[changed_index] = current_df.y[changed_index];
            new_df.distances[changed_index] = current_df.distances[changed_index];
        }

        // save iteration stuff
        if (n_saved_iterations > 0 && i == saved_iterations[next_saved_iteration_index]) {
            // construct filename where iteration is saved
            size_t lastindex = FILE_PATH_OUT.find_last_of(".");
            string rawname = FILE_PATH_OUT.substr(0, lastindex);
            string extension = FILE_PATH_OUT.substr(lastindex, FILE_PATH_OUT.length());
            stringstream save_name;
            save_name << rawname << "_iteration_" << i << extension;
            // save iteration
            write_csv(save_name.str(), new_df);
            // go to the next iteration if there is a next one
            if (next_saved_iteration_index < n_saved_iterations - 1) {
                ++next_saved_iteration_index;
            }
        }
    }
    return current_df;
}