#pragma once

#include <string>
#include <vector>
#include <memory>
#include <regex>

#include <expressions/result.hpp>

namespace expressions {
    class container : public std::enable_shared_from_this<container> {
        std::string regex_;
        std::vector<std::string> arguments_{};

    public:
        /**
         * Expression constructor
         *
         * @param regex
         * @param arguments
         */
        container(
            std::string regex,
            std::vector<std::string> arguments
        );

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
        std::shared_ptr<result>
        query(const std::string &input);

        /**
         * Creates a expression from strings
         *
         * @param input
         * @return std::shared_ptr<expression>
         */
        static std::shared_ptr<container>
        from_string(const std::string &input);
    };
}
