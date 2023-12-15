#include <cctype>
#include <fstream>
#include <print>
#include <string>
#include <string_view>

import utils;

using namespace std;

int extract_calibration_value(const string &line);

int main(int argc, char *argv[]) noexcept(false) {
    auto args = main_args_as_span(argc, argv);

    if (args.size() < 2) error("Input filename expected");
    const string_view input_filename{args[1]};

    ifstream input{input_filename};
    if (!input) error("Invalid input file");

    int calibration_sum = 0;
    for (string line; getline(input, line);) {
        calibration_sum += extract_calibration_value(line);
    }

    println("Calibration sum: {}", calibration_sum);
}

int extract_calibration_value(const string &line) {
    const char unset = '\0';
    char first_digit = unset;
    char last_digit = unset;
    for (const char c : line) {
        if (first_digit == unset && isdigit(c) != 0) first_digit = c;
        if (isdigit(c) != 0) last_digit = c;
    }
    if (first_digit == unset || last_digit == unset) error("Invalid input line (no digits)");

    auto as_int = [](char c) -> int { return c - '0'; };

    return as_int(first_digit) * 10 + as_int(last_digit);
}
