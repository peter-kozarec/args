#include "args.hpp"
#include <cstring>
#include <stdexcept>

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
            err_text.append("Reason is invalid length \n");
            return false;
        }

        for (auto &arg : args_)
        {
            std::string input_arg(&argv[i][pos], len);

            if (arg.abbreviation == input_arg ||
                arg.name == input_arg)
            {
                switch (arg.type)
                {
                    case arg_type_def::kSwitch:arg.value = true;
                        break;
                    case arg_type_def::kNumber:
                        try
                        {
                            ++i;
                            arg.value = std::stoi(argv[i]);
                        }
                        catch (std::invalid_argument const &e)
                        {
                            err_text.append(
                                "Unable to parse application arguments\n");
                            err_text.append(e.what());
                            return false;
                        }
                        catch (std::out_of_range const &e)
                        {
                            err_text.append(
                                "Unable to parse application arguments\n");
                            err_text.append(e.what());
                            return false;
                        }
                        break;
                    case arg_type_def::kFloat:
                        try
                        {
                            ++i;
                            arg.value = std::stof(argv[i]);
                        }
                        catch (std::invalid_argument const &e)
                        {
                            err_text.append(
                                "Unable to parse application arguments\n");
                            err_text.append(e.what());
                            return false;
                        }
                        catch (std::out_of_range const &e)
                        {
                            err_text.append(
                                "Unable to parse application arguments\n");
                            err_text.append(e.what());
                            return false;
                        }
                        break;
                    case arg_type_def::kString:++i;
                        arg.value = std::string(argv[i]);
                        break;

                    default:
                        err_text.append(
                            "Unable to parse application arguments\n");
                        err_text.append("Reason is invalid argument type \n");
                        return false;
                }
            }
        }
    }

    return true;
}

bool cargs::register_switch_arg(const std::string &abbreviation,
                                const std::string &name,
                                const std::string &description)
{
    for (const auto &arg : args_)
    {
        if (arg.abbreviation == abbreviation || arg.name == name)
        {
            return false;
        }
    }

    args_.emplace_back(arg{abbreviation, name, description, arg_type::kSwitch,
                           {}});
    return true;
}

bool cargs::register_number_arg(const std::string &abbreviation,
                                const std::string &name,
                                const std::string &description)
{
    for (const auto &arg : args_)
    {
        if (arg.abbreviation == abbreviation || arg.name == name)
        {
            return false;
        }
    }

    args_.emplace_back(arg{abbreviation, name, description, arg_type::kNumber,
                           {}});
    return true;
}

bool cargs::register_float_arg(const std::string &abbreviation,
                               const std::string &name,
                               const std::string &description)
{
    for (const auto &arg : args_)
    {
        if (arg.abbreviation == abbreviation || arg.name == name)
        {
            return false;
        }
    }

    args_.emplace_back(arg{abbreviation, name, description, arg_type::kFloat,
                           {}});
    return true;
}

bool cargs::register_string_arg(const std::string &abbreviation,
                                const std::string &name,
                                const std::string &description)
{
    for (const auto &arg : args_)
    {
        if (arg.abbreviation == abbreviation || arg.name == name)
        {
            return false;
        }
    }

    args_.emplace_back(arg{abbreviation, name, description, arg_type::kString,
                           {}});
    return true;
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
    const auto it = find(name);

    if (it != args_.end() && it->type == arg_type_def::kSwitch)
    {
        val = it->value.has_value();
        return val;
    }

    return false;
}

bool cargs::get_value(const std::string &name, int &val) const
{
    const auto it = find(name);

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
    const auto it = find(name);

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
    const auto it = find(name);

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

std::list<cargs::arg>::const_iterator cargs::find(const std::string &name) const
{
    auto it = args_.begin();

    while (it != args_.end())
    {
        if (it->abbreviation == name ||
            it->name == name)
        {
            return it;
        }

        ++it;
    }

    return it;
}
