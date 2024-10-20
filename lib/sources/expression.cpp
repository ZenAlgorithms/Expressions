#include <expression.hpp>

expression::expression(std::string regex, std::vector<std::string> arguments)
    : regex_(std::move(regex)), arguments_(std::move(arguments)) {
}

std::string expression::get_regex() const {
    return regex_;
}

std::vector<std::string> expression::get_arguments() const {
    return arguments_;
}

std::shared_ptr<expression_result> expression::query(const std::string &input) {
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

std::shared_ptr<expression> expression::from_string(const std::string &input) {
    std::size_t _open = input.find('{');
    std::size_t _close = input.find('}');
    std::size_t _position = 0;

    std::vector<std::string> _arguments;
    std::string _regex;

    if (_open == std::string::npos && _close == std::string::npos)
        return std::make_shared<expression>(std::string{input.data()}, _arguments);

    while (_open != std::string::npos && _close != std::string::npos) {
        _regex.append(input.substr(_position, _open - _position));
        std::string _value{input.substr(_open + 1, _close - _open - 1)};

        if (std::find(_arguments.begin(), _arguments.end(), _value) != _arguments.end())
            throw std::runtime_error("groups can't be repeated ... ");

        _regex.append(R"(([a-zA-Z0-9\-_]+))");
        _arguments.emplace_back(_value);

        _position = _close + 1;
        _open = input.find('{', _close);
        _close = input.find('}', _open);

        if (_open == std::string::npos && _close == std::string::npos && _position != input.size())
            _regex.append(input.substr(_position, input.size() - _position));
    }

    return std::make_shared<expression>(_regex, _arguments);
}
