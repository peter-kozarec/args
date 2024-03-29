#include "args.hpp"
#include <cstring>
#include <stdexcept>
#include <algorithm>

cargs::cargs(const cargs &other)
{
    if (this != &other)
    {
        args_ = other.args_;
    }
}

cargs::cargs(cargs &&other) noexcept
{
    if (this != &other)
    {
        args_ = std::move(other.args_);
    }
}

cargs &cargs::operator=(const cargs &other)
{
    if (this != &other)
    {
        args_ = other.args_;
    }
    return *this;
}

cargs &cargs::operator=(cargs &&other) noexcept
{
    if (this != &other)
    {
        args_ = std::move(other.args_);
    }
    return *this;
}

bool cargs::parse(int argc, char **argv, std::string &err_text)
{
    err_text.clear();

    for (int i = 1; i < argc; ++i)
    {
        auto pos = 0;

        if (argv[i][pos] != '-')
        {
            err_text.append("Unable to parse application arguments\n");
            err_text.append("Reason - invalid character \n");
            return false;
        }

        ++pos;
        const auto len = strlen(&argv[i][pos]);

        if (!len)
        {
            err_text.append("Unable to parse application arguments\n");
            err_text.append("Reason - invalid length \n");
            return false;
        }

        for (auto &arg : args_)
        {
            std::string input_arg(&argv[i][pos], len);

            if (arg.abbreviation != input_arg &&
                arg.name != input_arg)
            {
                continue;
            }

            switch (arg.type)
            {
                case arg_type_def::kSwitch:arg.value = true;
                    break;
                case arg_type_def::kNumber:
                    ++i;
                    int number_val;
                    if (!char_conv(argv[i],
                                   strlen(argv[i]),
                                   number_val))
                    {
                        err_text.append("Unable to parse argument.\n");
                        return false;
                    }
                    arg.value = number_val;
                    break;
                case arg_type_def::kFloat:
                    ++i;
                    float float_val;
                    if (!char_conv(argv[i],
                                   strlen(argv[i]),
                                   float_val))
                    {
                        err_text.append("Unable to parse argument.\n");
                        return false;
                    }
                    arg.value = float_val;
                    break;
                case arg_type_def::kString:
                    ++i;
                    arg.value = std::string(argv[i]);
                    break;

                default:
                    err_text.append("Unable to parse application arguments\n");
                    return false;
            }
        }
    }

    return true;
}

bool cargs::register_switch_arg(const std::string &abbreviation,
                                const std::string &name,
                                const std::string &description)
{
    return register_arg(abbreviation,
                        name,
                        description,
                        arg_type_def::kSwitch);
}

bool cargs::register_number_arg(const std::string &abbreviation,
                                const std::string &name,
                                const std::string &description)
{
    return register_arg(abbreviation,
                        name,
                        description,
                        arg_type_def::kNumber);
}

bool cargs::register_float_arg(const std::string &abbreviation,
                               const std::string &name,
                               const std::string &description)
{
    return register_arg(abbreviation,
                        name,
                        description,
                        arg_type_def::kFloat);
}

bool cargs::register_string_arg(const std::string &abbreviation,
                                const std::string &name,
                                const std::string &description)
{
    return register_arg(abbreviation,
                        name,
                        description,
                        arg_type_def::kString);
}

size_t cargs::count() const
{
    return args_.size();
}

bool cargs::contains(const std::string &name) const
{
    for (const auto &arg : args_)
    {
        if (name == arg.name || name == arg.abbreviation)
        {
            return arg.value.has_value();
        }
    }

    return false;
}

bool cargs::get_value(const std::string &name, bool &val) const
{
    const auto it = std::find_if(args_.begin(), args_.end(),
                                 [&](const arg_def &arg)
                                 {
                                     return arg.abbreviation == name ||
                                         arg.name == name;
                                 });

    if (it != args_.end() && it->type == arg_type_def::kSwitch)
    {
        val = it->value.has_value();
        return val;
    }

    return false;
}

bool cargs::get_value(const std::string &name, int &val) const
{
    const auto it = std::find_if(args_.begin(), args_.end(),
                                 [&](const arg_def &arg)
                                 {
                                     return arg.abbreviation == name ||
                                         arg.name == name;
                                 });

    if (it != args_.end() && it->type == arg_type_def::kNumber)
    {
        if (it->value.has_value())
        {
            val = std::any_cast<int>(it->value.value());
            return true;
        }
    }

    return false;
}

bool cargs::get_value(const std::string &name, float &val) const
{
    const auto it = std::find_if(args_.begin(), args_.end(),
                                 [&](const arg_def &arg)
                                 {
                                     return arg.abbreviation == name ||
                                         arg.name == name;
                                 });

    if (it != args_.end() && it->type == arg_type_def::kFloat)
    {
        if (it->value.has_value())
        {
            val = std::any_cast<float>(it->value.value());
            return true;
        }
    }

    return false;
}

bool cargs::get_value(const std::string &name, std::string &val) const
{
    const auto it = std::find_if(args_.begin(), args_.end(),
                                 [&](const arg_def &arg)
                                 {
                                    return arg.abbreviation == name ||
                                           arg.name == name;
                                 });

    if (it != args_.end() && it->type == arg_type_def::kString)
    {
        if (it->value.has_value())
        {
            val = std::any_cast<std::string>(it->value.value());
            return true;
        }
    }

    return false;
}

bool cargs::register_arg(const std::string &abbreviation,
                         const std::string &name,
                         const std::string &description,
                         cargs::arg_type type)
{
    for (const auto &arg : args_)
    {
        if (arg.abbreviation == abbreviation || arg.name == name)
        {
            return false;
        }
    }

    args_.emplace_back(arg{abbreviation,
                           name,
                           description,
                           type,
                           {}});
    return true;
}

bool cargs::char_conv(const char *str, size_t len, int &out)
{
    if (!str || !len)
    {
        return false;
    }

    try
    {
        out = std::stoi(std::string(str, len));
        return true;
    }
    catch(...)
    {
        return false;
    }
}

bool cargs::char_conv(const char *str, size_t len, float &out)
{
    if (!str || !len)
    {
        return false;
    }

    try
    {
        out = std::stof(std::string(str, len));
        return true;
    }
    catch(...)
    {
        return false;
    }
}
