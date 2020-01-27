#include "../include/AbstractSyntaxTree/Values/Object.h"

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

ptr<Object> Object::asObject() {
    return make<Object>(members);
}

ptr<Array> Object::asArray() {
    return nullptr;
}

ptr<Member> Object::getMember(const Identifier &ident) {
    return members.getMember(ident);
}

ptr<Value> Object::getAttribute(const Identifier &ident) {
    return members.getValue(ident);
}

ptr<Function> Object::getFunction(const Identifier &ident) {
    return members.getFunction(ident);
}

Environment* Object::getEnvironment() {
    return &members;
}
