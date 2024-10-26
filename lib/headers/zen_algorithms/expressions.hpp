#pragma once

#include <string>
#include <utility>
#include <vector>
#include <memory>
#include <unordered_map>
#include <regex>

namespace zen_algorithms::expressions {

    class expression_result : public std::enable_shared_from_this<expression_result> {
        bool matches_;
        std::unordered_map<std::string, std::string> bindings_;

        public:
        expression_result(const bool matches, const std::unordered_map<std::string, std::string> & bindings) : matches_(matches), bindings_(bindings) {}

        bool matches() const { return matches_; }
        std::unordered_map<std::string, std::string> get_bindings() const { return bindings_; }

        std::string get(const std::string &name) const {
            if (bindings_.contains(name))
                return bindings_.at(name);
            throw std::runtime_error("The provided argument doesn't exists");
        }
    };

    class expression : public std::enable_shared_from_this<expression> {
        std::string regex_;
        std::vector<std::string> arguments_;

        public:

        expression(std::string regex, const std::vector<std::string> & arguments) : regex_(std::move(regex)), arguments_(arguments) {}

        std::vector<std::string> get_arguments() const { return arguments_; }
        std::string get_regex() const { return regex_; }

        std::shared_ptr<expression_result> query(const std::string &input) const {
            std::unordered_map<std::string, std::string> _bindings;
            const std::regex _pattern(regex_);
            bool _matches = false;
            if (std::smatch _match; std::regex_match(input, _match, _pattern)) {
                _matches = true;
                auto _iterator = _match.begin();
                ++_iterator;
                for (auto &_key: arguments_) {
                    _bindings[_key] = *_iterator;
                    ++_iterator;
                }
            }
            return std::make_shared<expression_result>(_matches, _bindings);
        }
    };

    static std::shared_ptr<expression> from_string(const std::string &input) {
        std::size_t _open = input.find('{');
        std::size_t _close = input.find('}');
        std::size_t _position = 0;

        std::vector<std::string> _arguments;
        std::string _regex;

        if (_open == std::string::npos && _close == std::string::npos)
            return std::make_shared<expression>(input, _arguments);

        while (_open != std::string::npos && _close != std::string::npos) {
            _regex.append(input.substr(_position, _open - _position));
            std::string _value{input.substr(_open + 1, _close - _open - 1)};

            if (std::find(_arguments.begin(), _arguments.end(), _value) != _arguments.end())
                throw std::runtime_error("The provided input contains repeated arguments.");

            _regex.append(R"(([a-zA-Z0-9\-_]+))");
            _arguments.emplace_back(_value);

            _position = _close + 1;
            _open = input.find('{', _close);
            _close = input.find('}', _open);
        }

        if (_position != input.size())
            _regex.append(input.substr(_position, input.size() - _position));


        return std::make_shared<expression>(_regex, _arguments);
    }

}