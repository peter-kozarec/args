#ifndef ARGS_TEST_HPP
#define ARGS_TEST_HPP

#include <gtest/gtest.h>
#include "args.hpp"


class cargs_test final
{
public:
    cargs_test() = default;
    cargs_test(const cargs_test &other) = delete;
    cargs_test(cargs_test &&other) noexcept = delete;
    cargs_test& operator=(const cargs_test &other) = delete;
    cargs_test& operator=(cargs_test &&other) noexcept = delete;
    ~cargs_test() = default;

    static bool test_register_switch_arg();
    static bool test_register_number_arg();
    static bool test_register_float_arg();
    static bool test_register_string_arg();
    static bool test_parse();
    static bool test_contains();
    static bool test_count();
    static bool get_bool_value();
    static bool get_number_value();
    static bool get_float_value();
    static bool get_string_value();

private:
    static bool test_valid_parse_args();
    static bool test_invalid_parse_args();
};

TEST(Args_Test, test_register_switch_arg)
{
    ASSERT_TRUE(cargs_test::test_register_switch_arg());
}

TEST(Args_Test, test_register_number_arg)
{
    ASSERT_TRUE(cargs_test::test_register_number_arg());
}

TEST(Args_Test, test_register_float_arg)
{
    ASSERT_TRUE(cargs_test::test_register_float_arg());
}

TEST(Args_Test, test_register_string_arg)
{
    ASSERT_TRUE(cargs_test::test_register_string_arg());
}

TEST(Args_Test, test_parse)
{
    ASSERT_TRUE(cargs_test::test_parse());
}

TEST(Args_Test, test_contains)
{
    ASSERT_TRUE(cargs_test::test_contains());
}

TEST(Args_Test, test_count)
{
    ASSERT_TRUE(cargs_test::test_count());
}

TEST(Args_Test, get_bool_value)
{
    ASSERT_TRUE(cargs_test::get_bool_value());
}

TEST(Args_Test, get_number_value)
{
    ASSERT_TRUE(cargs_test::get_number_value());
}

TEST(Args_Test, get_float_value)
{
    ASSERT_TRUE(cargs_test::get_float_value());
}

TEST(Args_Test, get_string_value)
{
    ASSERT_TRUE(cargs_test::get_string_value());
}

#endif // ARGS_TEST_HPP