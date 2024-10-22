#include <expressions/result.hpp>

namespace expressions {
    bool result::matches() const {
        return _matches;
    }

    std::unordered_map<std::string, std::string> result::bindings() const {
        return _bindings;
    }

    std::string
    result::get(const std::string &name) const {
        if (_bindings.contains(name))
            return _bindings.at(name);
        throw std::runtime_error("The provided argument doesn't exists");
    }
}
