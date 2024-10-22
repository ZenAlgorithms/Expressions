#pragma once

#include <memory>
#include <unordered_map>
#include <optional>

namespace expressions {
    struct result {
        bool _matches = false;
        std::unordered_map<std::string, std::string> _bindings;

        /**
         * Get matches
         *
         * @return
         */
        bool
        matches() const;

        /**
         * Get bindings
         *
         * @return
         */
        std::unordered_map<std::string, std::string>
        bindings() const;

        /**
         * Get parameter
         *
         * @param name
         * @return
         */
        std::string
        get(const std::string & name) const;
    };
}
