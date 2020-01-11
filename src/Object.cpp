#include "../include/AbstractSyntaxTree/Values/Object.h"

Environment *Object::getEnvironment() {
    return &members;
}

Type Object::getType() {
    return Type::Object;
}

std::string Object::asString() {
    return "";
}

long long int Object::asInteger() {
    return 0;
}

double Object::asDouble() {
    return 0;
}

bool Object::asBoolean() {
    return false;
}

