#include "args_test.hpp"

bool cargs_test::test_register_switch_arg()
{
    cargs args;

    const std::string abbreviation = "t";
    const std::string name = "test";
    const std::string description = "test description";
    args.register_switch_arg(abbreviation, name, description);

    for (const auto &arg : args.args_)
    {
        if (arg.abbreviation == abbreviation &&
            arg.name == name &&
            arg.description == description &&
            arg.type == cargs::arg_type_def::kSwitch)
        {
            return true;
        }
    }

    return false;
}

bool cargs_test::test_register_number_arg()
{
    cargs args;

    const std::string abbreviation = "t";
    const std::string name = "test";
    const std::string description = "test description";
    args.register_number_arg(abbreviation, name, description);

    for (const auto &arg : args.args_)
    {
        if (arg.abbreviation == abbreviation &&
            arg.name == name &&
            arg.description == description &&
            arg.type == cargs::arg_type_def::kNumber)
        {
            return true;
        }
    }

    return false;
}

bool cargs_test::test_register_float_arg()
{
    cargs args;

    const std::string abbreviation = "t";
    const std::string name = "test";
    const std::string description = "test description";
    args.register_float_arg(abbreviation, name, description);

    for (const auto &arg : args.args_)
    {
        if (arg.abbreviation == abbreviation &&
            arg.name == name &&
            arg.description == description &&
            arg.type == cargs::arg_type_def::kFloat)
        {
            return true;
        }
    }

    return false;
}

bool cargs_test::test_register_string_arg()
{
    cargs args;

    const std::string abbreviation = "t";
    const std::string name = "test";
    const std::string description = "test description";
    args.register_string_arg(abbreviation, name, description);

    for (const auto &arg : args.args_)
    {
        if (arg.abbreviation == abbreviation &&
            arg.name == name &&
            arg.description == description &&
            arg.type == cargs::arg_type_def::kString)
        {
            return true;
        }
    }

    return false;
}

bool cargs_test::test_parse()
{
    return test_valid_parse_args() && test_invalid_parse_args();
}

bool cargs_test::test_contains()
{
    cargs args;

    const std::string switch_abbreviation = "s";
    const std::string switch_name = "switch";
    const std::string switch_description = "switch description";

    args.args_.push_back({switch_abbreviation,
                          switch_name,
                          switch_description,
                          cargs::arg_type::kSwitch,
                          true});

    return args.contains(switch_abbreviation) && args.contains(switch_name);
}

bool cargs_test::test_count()
{
    cargs args;

    // Switch arg
    const std::string switch_abbreviation = "s";
    const std::string switch_name = "switch";
    const std::string switch_description = "switch description";
    args.args_.push_back({switch_abbreviation,
                          switch_name,
                          switch_description,
                          cargs::arg_type::kSwitch});

    // Number arg
    const std::string number_abbreviation = "n";
    const std::string number_name = "number";
    const std::string number_description = "number description";
    args.args_.push_back({number_abbreviation,
                          number_name,
                          number_description,
                          cargs::arg_type::kNumber});

    // Double arg
    const std::string double_abbreviation = "d";
    const std::string double_name = "double";
    const std::string double_description = "double description";
    args.args_.push_back({double_abbreviation,
                          double_name,
                          double_description,
                          cargs::arg_type::kFloat});

    // String arg
    const std::string string_abbreviation = "t";
    const std::string string_name = "text";
    const std::string string_description = "text description";
    args.args_.push_back({string_abbreviation,
                          string_name,
                          string_description,
                          cargs::arg_type::kString});

    return args.count() == 4;
}

bool cargs_test::get_bool_value()
{
    cargs args;

    const std::string switch_abbreviation = "s";
    const std::string switch_name = "switch";
    const std::string switch_description = "switch description";
    const bool switch_value = true;

    args.args_.push_back({switch_abbreviation,
                          switch_name,
                          switch_description,
                          cargs::arg_type::kSwitch,
                          switch_value});

    bool value;
    return args.get_value(switch_name, value) && value;
}

bool cargs_test::get_number_value()
{
    cargs args;

    const std::string number_abbreviation = "n";
    const std::string number_name = "number";
    const std::string number_description = "number description";
    const int number_value = 5;

    args.args_.push_back({number_abbreviation,
                          number_name,
                          number_description,
                          cargs::arg_type::kNumber,
                          number_value});

    int value;
    return args.get_value(number_name, value) && value == number_value;
}

bool cargs_test::get_float_value()
{
    cargs args;

    const std::string double_abbreviation = "d";
    const std::string double_name = "double";
    const std::string double_description = "double description";
    const float double_value = 3.9f;

    args.args_.push_back({double_abbreviation,
                          double_name,
                          double_description,
                          cargs::arg_type::kFloat,
                          double_value});

    float value;
    return args.get_value(double_name, value) && value == double_value;
}

bool cargs_test::get_string_value()
{
    cargs args;

    const std::string string_abbreviation = "t";
    const std::string string_name = "text";
    const std::string string_description = "text description";
    const std::string string_value = "test";

    args.args_.push_back({string_abbreviation,
                          string_name,
                          string_description,
                          cargs::arg_type::kString,
                          string_value});

    std::string value;
    return args.get_value(string_name, value) && value == string_value;
}

bool cargs_test::test_valid_parse_args()
{
    cargs args;

    // Switch arg
    const std::string switch_abbreviation = "s";
    const std::string switch_name = "switch";
    const std::string switch_description = "switch description";
    args.args_.push_back({switch_abbreviation,
                          switch_name,
                          switch_description,
                          cargs::arg_type::kSwitch});

    // Number arg
    const std::string number_abbreviation = "n";
    const std::string number_name = "number";
    const std::string number_description = "number description";
    args.args_.push_back({number_abbreviation,
                          number_name,
                          number_description,
                          cargs::arg_type::kNumber});

    // Float arg
    const std::string double_abbreviation = "d";
    const std::string double_name = "double";
    const std::string double_description = "double description";
    args.args_.push_back({double_abbreviation,
                          double_name,
                          double_description,
                          cargs::arg_type::kFloat});

    // String arg
    const std::string string_abbreviation = "t";
    const std::string string_name = "text";
    const std::string string_description = "text description";
    args.args_.push_back({string_abbreviation,
                          string_name,
                          string_description,
                          cargs::arg_type::kString});

    const int argc = 8;
    char **argv = new char *[argc];

    argv[0] = new char[1];
    strcpy(argv[0], "");
    argv[1] = new char[3];
    strcpy(argv[1], "-s");
    argv[2] = new char[3];
    strcpy(argv[2], "-n");
    argv[3] = new char[2];
    strcpy(argv[3], "5");
    argv[4] = new char[3];
    strcpy(argv[4], "-d");
    argv[5] = new char[4];
    strcpy(argv[5], "3.9");
    argv[6] = new char[3];
    strcpy(argv[6], "-t");
    argv[7] = new char[5];
    strcpy(argv[7], "test");

    std::string err_msg;
    bool result = args.parse(argc, argv, err_msg);

    result &= std::find_if(args.args_.begin(), args.args_.end(),
                           [&](const cargs::arg &arg)
                           {
                               return arg.abbreviation == switch_abbreviation &&
                                   arg.name == switch_name &&
                                   arg.description == switch_description &&
                                   arg.type == cargs::arg_type_def::kSwitch &&
                                   arg.value.has_value() &&
                                   arg.value;
                           }) != args.args_.end();

    result &= std::find_if(args.args_.begin(), args.args_.end(),
                           [&](const cargs::arg &arg)
                           {
                               return arg.abbreviation == number_abbreviation &&
                                   arg.name == number_name &&
                                   arg.description == number_description &&
                                   arg.type == cargs::arg_type_def::kNumber &&
                                   arg.value.has_value() &&
                                   std::any_cast<int>(arg.value.value()) == 5;
                           }) != args.args_.end();

    result &= std::find_if(args.args_.begin(), args.args_.end(),
                           [&](const cargs::arg &arg)
                           {
                               return arg.abbreviation == double_abbreviation &&
                                   arg.name == double_name &&
                                   arg.description == double_description &&
                                   arg.type == cargs::arg_type_def::kFloat &&
                                   arg.value.has_value() &&
                                   std::any_cast<float>(arg.value.value())
                                       == 3.9f;
                           }) != args.args_.end();

    result &= std::find_if(args.args_.begin(), args.args_.end(),
                           [&](const cargs::arg &arg)
                           {
                               return arg.abbreviation == string_abbreviation &&
                                   arg.name == string_name &&
                                   arg.description == string_description &&
                                   arg.type == cargs::arg_type_def::kString &&
                                   arg.value.has_value() &&
                                   std::any_cast<std::string>(arg.value.value())
                                       == "test";
                           }) != args.args_.end();

    for (auto i = 0; i < argc; i++)
    {
        delete[] argv[i];
    }
    delete[] argv;

    return result;
}

bool cargs_test::test_invalid_parse_args()
{
    // ToDo: Add test
    return true;
}
