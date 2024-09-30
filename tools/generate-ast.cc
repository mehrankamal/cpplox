
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>

void ltrim(std::string &s, unsigned char c)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [c](unsigned char ch)
                                    { return ch != c; }));
}

void rtrim(std::string &s, unsigned char c)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), [c](unsigned char ch)
                         { return ch != c; })
                .base(),
            s.end());
}

void trim(std::string &s, unsigned char c)
{
    ltrim(s, c);
    rtrim(s, c);
}

void ltrim(std::string &s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch)
                                    { return !std::isspace(ch); }));
}

void rtrim(std::string &s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch)
                         { return !std::isspace(ch); })
                .base(),
            s.end());
}

void trim(std::string &s)
{
    ltrim(s);
    rtrim(s);
}

std::string convert_to_lowercase(const std::string& str) {
    std::string result;
    for (char ch : str) {
        result += std::tolower(ch);
    }
    return result;
}


void define_includes(std::filesystem::path output_dir, std::string base_name, std::vector<std::string> types)
{
    std::ofstream file(output_dir / (base_name + ".hh"));

    file << "#pragma once" << std::endl;
    file << std::endl;
    file << "#include \"Token.hh\"" << std::endl;
    file << std::endl;
    file << "namespace Lox" << std::endl;
    file << "{" << std::endl;
    file << std::endl;


    file << "    template <typename R>" << std::endl;
    file << "    class " << base_name << "Visitor;" << std::endl;
    file << std::endl;

    file << "    class Expr" << std::endl;
    file << "    {" << std::endl;
    file << "    public:" << std::endl;
    file << "        virtual std::any visit(ExprVisitor<std::any> &visitor) = 0;" << std::endl;
    file << "        virtual ~Expr() = default;" << std::endl;
    file << "    };" << std::endl;
    file << std::endl;

    for (const auto &type : types)
    {
        auto pos = type.find(":");
        auto class_name = type.substr(0, pos);
        trim(class_name);
        auto type_params = type.substr(pos + 1);
        trim(type_params);

        file << "    class " << class_name << " : public Expr" << std::endl;
        file << "    {" << std::endl;
        file << "    public:" << std::endl;
        file << "        " << class_name << "(" << type_params << ");" << std::endl;
        file << "        template <typename R>" << std::endl;
        file << "        R visit(ExprVisitor<R> *visitor);" << std::endl;
        file << "        ~" << class_name << "();" << std::endl;
        file << std::endl;
        std::vector<std::string> fields;

        while (type_params.find(",") != std::string::npos)
        {
            auto field = type_params.substr(0, type_params.find(","));
            trim(field);
            fields.push_back(field);
            type_params = type_params.substr(type_params.find(",") + 1);
        }

        trim(type_params);
        fields.push_back(type_params);

        for (const auto &field : fields)
        {
            file << "        " << field << ";" << std::endl;
        }

        file << "    };" << std::endl;
        file << std::endl;
    }

    file << "    template <typename R>" << std::endl;
    file << "    class " << base_name << "Visitor" << std::endl;
    file << "    {" << std::endl;
    file << "    public:" << std::endl;

    for (const auto &type : types)
    {
        auto pos = type.find(":");
        auto class_name = type
                              .substr(0, pos);
        trim(class_name);

        file << "        virtual R visit_" << convert_to_lowercase(class_name) << "("
             << class_name << " *expr) = 0;" << std::endl;
    }
    file << "    };" << std::endl;

    file << "}" << std::endl;

    file.close();
}

void define_implementations(std::filesystem::path output_dir, std::string base_name, std::vector<std::string> types)
{
    std::ofstream file(output_dir / (base_name + ".cc"));

    file << "#include \"" << base_name << ".hh\"" << std::endl;
    file << std::endl;
    file << "namespace Lox" << std::endl;
    file << "{" << std::endl;
    file << std::endl;

    for (const auto &type : types)
    {
        auto pos = type.find(":");
        auto class_name = type.substr(0, pos);
        trim(class_name);
        auto type_params = type.substr(pos + 1);
        trim(type_params);

        file << "    " << class_name << "::" << class_name << "(" << type_params << ")" << " : ";

        std::vector<std::string> fields;

        while (type_params.find(",") != std::string::npos)
        {
            auto field = type_params.substr(0, type_params.find(","));
            trim(field);
            field = field.substr(field.find(" ") + 1);
            trim(field);
            trim(field, '*');
            fields.push_back(field);
            type_params = type_params.substr(type_params.find(",") + 1);
        }

        type_params = type_params.substr(type_params.find(" ") + 1);
        trim(type_params);
        type_params = type_params.substr(type_params.find(" ") + 1);
        trim(type_params);
        trim(type_params, '*');
        fields.push_back(type_params);

        for (size_t i = 0; i < fields.size(); i++)
        {
            file << fields[i] << "(" << fields[i] << ")";
            if (i < fields.size() - 1)
            {
                file << ", ";
            }
        }

        file << std::endl;
        file << "    {" << std::endl;
        file << "    }" << std::endl;

        file << "    template <typename R>" << std::endl;
        file << "    R " << class_name << "::visit(ExprVisitor<R> *visitor)" << std::endl;
        file << "    {" << std::endl;
        file << "        return visitor->visit" << class_name << "(this);" << std::endl;
        file << "    }" << std::endl;

        file << "    " << class_name << "::~" << class_name << "()" << std::endl;
        file << "    {" << std::endl;
        file << "    }" << std::endl;
        file << std::endl;
    }

    file << "}" << std::endl;
}

void define_ast(std::string output_dir, std::string base_name, std::vector<std::string> types)
{
    define_includes(std::filesystem::path(output_dir + "/include"), base_name, types);
    define_implementations(std::filesystem::path(output_dir + "/src"), base_name, types);
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <output_directory>" << std::endl;
        return 1;
    }

    std::string output_dir = argv[1];

    define_ast(output_dir, "Expr", {"Binary: Expr *left, Token op, Expr *right", "Grouping: Expr *expression", "Literal: std::any value", "Unary    : Token op, Expr *right"});

    return 0;
}