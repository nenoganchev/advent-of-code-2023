module;
#include <cstddef>
#include <cstdlib>
#include <print>
#include <span>
#include <string_view>

module utils;

using namespace std;

span<const char * const> main_args_as_span(int argc, char *argv[]) { // NOLINT(*-avoid-c-arrays)
    return span<const char * const>{argv, static_cast<size_t>(argc)};
}

void error(string_view error_message) {
    println("ERROR: {}", error_message);
    exit(1); // NOLINT(concurrency-mt-unsafe)
}
