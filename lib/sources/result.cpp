#include <expressions/result.hpp>

namespace expressions {
    result::result(const bool matches, std::unordered_map<std::string, std::string> bindings)
    : _matches(matches), _bindings(std::move(bindings)) {
    }

    bool result::matches() const {
        return _matches;
    }

    std::unordered_map<std::string, std::string> result::bindings() const {
        return _bindings;
    }
}
