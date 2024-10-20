#pragma once

#include <memory>
#include <unordered_map>

namespace expressions {
    class result : public std::enable_shared_from_this<result> {
        bool _matches = false;
        std::unordered_map<std::string, std::string> _bindings;

    public:
        /**
         * Expression result constructor
         *
         * @param matches
         * @param bindings
         */
        result(
            bool matches,
            std::unordered_map<std::string, std::string> bindings
        );

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
    };
}
