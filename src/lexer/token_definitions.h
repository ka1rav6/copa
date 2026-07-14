#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

struct Parameter {
    std::string dataType;
    std::optional<std::string> param_name;

    explicit Parameter(
        std::string type,
        std::optional<std::string> name = std::nullopt)
        : dataType(std::move(type)),
          param_name(std::move(name)) {}
};

enum Flags : uint8_t {
    isStatic  = 1 << 0, // for functions
    isExtern  = 1 << 1, // for functions and variables
    isTypedef = 1 << 2, // for structs, types etc.
};

struct Function {
    std::string name;
    std::vector<Parameter> params;
    std::string returnType;
    uint8_t flags = 0;

    Function(
        std::string name,
        std::vector<Parameter> params,
        std::string returnType)
        : name(std::move(name)),
          params(std::move(params)),
          returnType(std::move(returnType)) {}
};

struct EnumField {
    std::string name;
    std::optional<std::string> value;

    explicit EnumField(
        std::string name,
        std::optional<std::string> value = std::nullopt)
        : name(std::move(name)),
          value(std::move(value)) {}
};

struct Enum {
    std::string name;
    std::vector<EnumField> fields;

    Enum(
        std::string name,
        std::vector<EnumField> fields)
        : name(std::move(name)),
          fields(std::move(fields)) {}
};

struct ExternVariable {
    std::string type;
    std::string name;

    ExternVariable(
        std::string type,
        std::string name)
        : type(std::move(type)),
          name(std::move(name)) {}
};

struct StructField {
    std::string type;
    std::string name;
    StructField(
        std::string type,
        std::string name)
        : type(std::move(type)),
          name(std::move(name)) {}
};

struct Struct {
    std::string name;
    std::vector<StructField> fields;

    Struct(
        std::string name,
        std::vector<StructField> fields)
        : name(std::move(name)),
          fields(std::move(fields)) {}
};

struct VariableDefinition {
    std::string dataType;
    std::string name;
    std::optional<std::string> value;
    VariableDefinition(
        std::string dataType,
        std::string name,
        std::optional<std::string> value = std::nullopt)
        : dataType(std::move(dataType)),
          name(std::move(name)),
          value(std::move(value)) {}
};



struct Typedef{
    std::string underlyingType;
    std::string alias;
    
    Typedef(   std::string underlyingType,
               std::string alias
            ): underlyingType(std::move(underlyingType)),
               alias(std::move(alias)){}
};
struct UnionField{
    std::string name;
    std::string type;
    UnionField(  std::string name,
                 std::string type
              ): name(std::move(name)),
                 type(std::move(type))
    {}
};

struct Union{
    std::string name;
    std::vector<UnionField> fields;
    Union(  std::string name,
            std::vector<UnionField> fields
         ): name(std::move(name)),
            fields(std::move(fields)){}
};

struct Macro {
    std::string name;
    std::optional<std::string> parameters;
    std::string body;

    Macro(
            std::string name,
            std::string body,
            std::optional<std::string> parameters = std::nullopt
        ) : name(std::move(name)),
            body(std::move(body)),
            parameters(std::move(parameters))
    {}
};

struct IncludeStatements{
    bool system;
    std::string path;
};

enum class ForwardKind {
    Struct,
    Union,
    Enum
};

struct ForwardDeclaration {
    ForwardKind kind;
    std::string name;
};


#endif // DEFINITIONS_H
