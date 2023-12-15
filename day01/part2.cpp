#include <array>
#include <cstdlib>
#include <fstream>
#include <print>
#include <span>
#include <string>
#include <string_view>
#include <tuple>

using namespace std;

int extract_calibration_value(const string &line);
[[noreturn]] void error(string_view error_message);

int main(int argc, char *argv[]) noexcept(false) {
    const span args{argv, static_cast<size_t>(argc)};

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
    auto digit_patterns = to_array<const tuple<string_view, int>>({
        {"1", 1},
        {"one", 1},
        {"2", 2},
        {"two", 2},
        {"3", 3},
        {"three", 3},
        {"4", 4},
        {"four", 4},
        {"5", 5},
        {"five", 5},
        {"6", 6},
        {"six", 6},
        {"7", 7},
        {"seven", 7},
        {"8", 8},
        {"eight", 8},
        {"9", 9},
        {"nine", 9},
    });

    string::size_type curr_min_pos = string::npos;
    int first_digit; // NOLINT(*-init-variables)
    for (auto [pattern, digit] : digit_patterns) {
        auto pos = line.find(pattern);
        if (pos < curr_min_pos) {
            curr_min_pos = pos;
            first_digit = digit;
        }
    }

    string::size_type curr_max_pos = 0;
    int last_digit; // NOLINT(*-init-variables)
    for (auto [pattern, digit] : digit_patterns) {
        auto pos = line.rfind(pattern);
        if (pos != string::npos && pos >= curr_max_pos) {
            curr_max_pos = pos;
            last_digit = digit;
        }
    }

    return first_digit * 10 + last_digit; // NOLINT(*-magic-numbers)
}

void error(string_view error_message) {
    println("ERROR: {}", error_message);
    exit(1); // NOLINT(concurrency-mt-unsafe)
}
