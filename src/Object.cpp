#include "../include/AbstractSyntaxTree/Values/Object.h"

Environment *Object::getEnvironment() {
    return &members;
}

Type Object::getType() {
    return Type::Object;
}
