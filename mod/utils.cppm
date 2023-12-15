module;
#include <span>
#include <string_view>

export module utils;

export {
    std::span<const char * const> main_args_as_span(int argc, char *argv[]); // NOLINT(*-avoid-c-arrays)
    [[noreturn]] void error(std::string_view error_message);
}
