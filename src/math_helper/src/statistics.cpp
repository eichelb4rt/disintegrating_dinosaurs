#include "statistics.h"

using namespace std;

string stats_string(standard_stats stats) {
    stringstream ss;
    ss << "mean x:\t" << stats.mean_x << endl;
    ss << "mean y:\t" << stats.mean_y << endl;
    ss << "sd x:\t" << stats.standard_deviation_x << endl;
    ss << "sd y:\t" << stats.standard_deviation_y << endl;
    ss << "correlation:\t" << stats.correlation;
    return ss.str();
}