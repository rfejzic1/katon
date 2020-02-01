#include "../include/AbstractSyntaxTree/Values/Object.h"
#include "../include/AbstractSyntaxTree/Packets.h"
#include "../include/AbstractSyntaxTree/ExceptionObjects.h"
#include "../include/AbstractSyntaxTree/Function.h"

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
    ptr<Object> object = make<Object>(members);
    object -> getEnvironment() -> setFunctionsOwner(object.get());
    return object;
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

ptr<Value> Object::call(ValueList &arguments) {
    ptr<Function> callFunction = getFunction("call");
    if(!callFunction)
        throw ThrowPacket(ExceptionObjects::undefined("'call' method not defined!"));

    return callFunction -> call(arguments);
}

Object *Object::getCaller() {
    return this;
}

void Object::setEnvironment(Environment *env) {
    members = *env;
}

void Object::merge(ptr<Object> other) {
    members.merge(other -> getEnvironment());
    members.setFunctionsOwner(this);
}
