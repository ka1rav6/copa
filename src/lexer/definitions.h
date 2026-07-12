#ifndef FUNCTION_H
#define FUNCTION_H

#include <string>
#include <vector>
#include <cstdint>
#include <iostream>
#include <optional>

struct Parameter{
    std::string dataType;
    std::optional<std::string> param_name;
    Parameter(std::string type){
        this->dataType = type;
    }
    Parameter(std::string type, std::string name){
        this->dataType   = type;
        this->param_name = name;
    }
};

enum Flags{
    isStatic  = 1 << 0, // for functions
    isExtern  = 1 << 1, // for functions
    isTypedef = 1 << 2, // for enums/structs etc
};

struct Function{
    std::string name;
    std::vector<Parameter> params;
    std::string returnType;
    uint8_t flags;
    Function(std::string name, 
             std::vector<Parameter> params,
             std::string returnType
            ){
        this->name       = name;
        this->params     = std::move(params);
        this->returnType = returnType;
    }
};

struct EnumField{
    std::string name;
    std::optional<std::string> value;
    EnumField(std::string name, std::string value){
        this->name  = name;
        this->value = value;
    }
};

struct Enum{
    std::string name;
    std::vector<EnumField> fields;
    Enum(std::string name, std::vector<EnumField> fields){
        this->name   = name;
        this->fields = std::move(fields);
    }
};

struct ExternVariable{
    std::string type;
    std::string name;
    ExternVariable(std::string type,
                   std::string name
                  ){
        this->type = type;
        this->name = name;
    }
};

struct StructField{
    std::string type;
    std::string name;
    StructField(std::string type,
                std::string name                
               ){
        this->type = type;
        this->name = name;
    }
};

struct Struct{
    std::string name;
    std::vector<StructField> fields; // as C structs have no initalization
    Struct(std::string name,
           std::vector<StructField> fields
          ){
        this->name   = name;
        this->fields = std::move(fields);
    }
};



#endif // FUNCTION_H
