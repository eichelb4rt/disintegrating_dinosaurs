#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "csv.h"

using namespace std;

dataframe read_csv(string file_path, int* error) {
    // open file
    ifstream fs(file_path);
    // check if file actually exists
    *error = 0;
    if (!fs.good()) {
        *error = 1;
        fs.close();
        return dataframe(0);
    }
    string line;
    // read data line by line
    double read_value;
    vector<double> x, y;
    while (getline(fs, line)) {
        // read a line, column by column
        int column_id = 0;
        stringstream line_ss(line);
        while (line_ss >> read_value) {
            // save read column value in vector
            switch (column_id) {
            case 0: x.push_back(read_value); break;
            case 1: y.push_back(read_value); break;
            default: break;
            }
            // if next token is comma, move on
            if (line_ss.peek() == ',') line_ss.ignore();
            // move on to next column
            ++column_id;
        }
    }
    fs.close();

    // construct dataframe
    int n_points = x.size();
    dataframe df = dataframe(n_points);
    for (int i = 0; i < n_points; ++i) {
        df.x[i] = x[i];
        df.y[i] = y[i];
    }
    return df;
}

void write_csv(string file_path, const dataframe& df) {
    // prepare what is written to the file
    stringstream ss;
    for (int i = 0; i < df.n_points; ++i) {
        ss << df.x[i] << "," << df.y[i] << endl;
    }

    // write built string
    ofstream fs(file_path);
    fs << ss.str();
    fs.close();
}