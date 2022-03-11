#include <iostream>
#include <boost/program_options.hpp>
#include "parse_args.h"
#include "default_args.cpp"

namespace po = boost::program_options;
using namespace std;


int parse_args_ignore_exceptions(int argc, char const* argv[]) {
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message")
        ("iterations", po::value<double>(&ITERATIONS_OPTION_VALUE), "set number of iterations")
        ("out", po::value<string>(&FILE_PATH_OUT), "set output path")
        ("in", po::value<string>(&DATA_PATH_IN), "set input path")
        ("form", po::value<string>(&JSON_FORM_PATH), "choose target form")
        ("params", po::value<string>(&JSON_PARAMETERS_PATH), "path to parameters file")
        ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        cout << desc << endl;
        return 1;
    }
    return 0;
}

int parse_args(int argc, char const* argv[]) {
    try {
        return parse_args_ignore_exceptions(argc, argv);
    } catch (exception& e) {
        cerr << "error: " << e.what() << endl;
        return 1;
    } catch (...) {
        return 1;
        cerr << "Exception of unknown type!" << endl;
    }

    return 0;
}