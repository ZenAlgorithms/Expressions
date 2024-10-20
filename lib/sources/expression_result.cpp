#include <expression_result.hpp>

expression_result::expression_result(const bool matches, std::unordered_map<std::string, std::string> bindings)
    : _matches(matches), _bindings(std::move(bindings)) {
}

bool expression_result::matches() const {
    return _matches;
}

std::unordered_map<std::string, std::string> expression_result::bindings() const {
    return _bindings;
}
