#pragma once

#include <string>
#include <vector>
#include <memory>
#include <regex>

#include <expressions/result.hpp>

namespace expressions {
    struct container {
        std::string regex_;
        std::vector<std::string> arguments_{};

        /**
         * Get the regex
         *
         * @return std::string
         */
        std::string
        get_regex() const;

        /**
         * Get the arguments
         *
         * @return std::vector<std::string>
         */
        std::vector<std::string>
        get_arguments() const;

        /**
         * Query the expression
         *
         * @param input
         * @return
         */
        result
        query(const std::string &input) const;

        /**
         * Creates a expression from strings
         *
         * @param input
         * @return std::shared_ptr<expression>
         */
        static container
        from_string(const std::string &input);
    };
}
