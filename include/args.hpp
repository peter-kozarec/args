#ifndef ARGS_HPP
#define ARGS_HPP

#include <string>
#include <any>
#include <list>
#include <optional>


class cargs final
{
    friend class cargs_test;

    typedef enum class arg_type_def
    {
        kInvalid,
        kSwitch,
        kNumber,
        kFloat,
        kString,
    } arg_type;

    typedef struct arg_def
    {
        std::string abbreviation{};
        std::string name{};
        std::string description{};
        arg_type type{arg_type::kInvalid};
        std::optional<std::any> value;
    } arg;

    std::list<arg> args_;

public:
    cargs() = default;
    cargs(const cargs &other);
    cargs(cargs &&other) noexcept;
    cargs& operator=(const cargs &other);
    cargs& operator=(cargs &&other) noexcept;
    ~cargs() = default;

    bool register_switch_arg(const std::string &abbreviation,
                             const std::string &name,
                             const std::string &description);

    bool register_number_arg(const std::string &abbreviation,
                             const std::string &name,
                             const std::string &description);

    bool register_float_arg(const std::string &abbreviation,
                            const std::string &name,
                            const std::string &description);

    bool register_string_arg(const std::string &abbreviation,
                             const std::string &name,
                             const std::string &description);

    bool parse(int argc, char **argv, std::string &err_text);

    [[nodiscard]] bool contains(const std::string &name) const;
    [[nodiscard]] size_t count() const;

    [[nodiscard]] bool get_value(const std::string &name, bool &val) const;
    [[nodiscard]] bool get_value(const std::string &name, int &val) const;
    [[nodiscard]] bool get_value(const std::string &name, float &val) const;
    [[nodiscard]] bool get_value(const std::string &name, std::string &val) const;

private:
    [[nodiscard]] bool register_arg(const std::string &abbreviation,
                                    const std::string &name,
                                    const std::string &description,
                                    arg_type type);

    [[nodiscard]] static bool char_conv(const char *str, size_t len, int &out);
    [[nodiscard]] static bool char_conv(const char *str, size_t len, float &out);
};

#endif // ARGS_HPP