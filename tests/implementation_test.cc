#include <gtest/gtest.h>
#include <expressions/container.hpp>

TEST(Expressions, Assertions) {
    using namespace expressions;

    const auto _non_empty_expression = container::from_string("/users/{user}/details");
    ASSERT_FALSE(_non_empty_expression->get_arguments().empty());
    ASSERT_EQ(_non_empty_expression->get_arguments().size(), 1);
    ASSERT_EQ(_non_empty_expression->get_arguments().at(0), "user");

    const auto _empty_expression = container::from_string("/ping");
    ASSERT_TRUE(_empty_expression->get_arguments().empty());
    ASSERT_EQ(_empty_expression->get_regex(), "/ping");

    const auto _non_empty_string_expression_result = _non_empty_expression->query("/users/80bdc6d1-524e-411a-b316-976a65a3ed3c/details");
    ASSERT_TRUE(_non_empty_string_expression_result->matches());
    ASSERT_FALSE(_non_empty_string_expression_result->bindings().empty());
    ASSERT_EQ(_non_empty_string_expression_result->bindings().at("user"), "80bdc6d1-524e-411a-b316-976a65a3ed3c");

    const auto _non_empty_integer_expression_result = _non_empty_expression->query("/users/1337/details");
    ASSERT_TRUE(_non_empty_integer_expression_result->matches());
    ASSERT_FALSE(_non_empty_integer_expression_result->bindings().empty());
    ASSERT_EQ(_non_empty_integer_expression_result->bindings().at("user"), "1337");
}
