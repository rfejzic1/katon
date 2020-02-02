#include "../include/AbstractSyntaxTree/Environment.h"

#include "../include/AbstractSyntaxTree/Symbol.h"
#include "../include/AbstractSyntaxTree/Values/Value.h"
#include "../include/AbstractSyntaxTree/Function.h"

bool Environment::hasSymbol(const Identifier& ident) {
    for(auto& it : symbols) {
        if(it.first.name == ident)
            return true;
    }
    return false;
}

void Environment::putValue(const Identifier &ident, Scope scope, ptr<Value> value, bool constant) {
    Symbol symbol(ident, constant, scope);
    symbols[symbol] = std::dynamic_pointer_cast<Member>(value);
}

void Environment::putFunction(const Identifier &ident, Scope scope, ptr<Function> function) {
    Symbol symbol(ident, true, scope);
    symbols[symbol] = std::dynamic_pointer_cast<Member>(function);
}

ptr<Member> Environment::getMember(const Identifier &ident) {
    return symbols[ident];
}

ptr<Value> Environment::getValue(const Identifier &ident) {
    return std::dynamic_pointer_cast<Value>(getMember(ident));
}

ptr<Function> Environment::getFunction(const Identifier &ident) {
    return std::dynamic_pointer_cast<Function>(getMember(ident));
}

void Environment::merge(Environment *other) {
    for(auto& it : other -> symbols) {
        symbols[it.first] = it.second;
    }
}

void Environment::setFunctionsOwner(Object *object) {
    for(auto& it : symbols) {
        ptr<Function> function = std::dynamic_pointer_cast<Function>(it.second);
        if(function)
            function->setOwner(object);
    }
}

Environment::Environment(const Environment &other) {
    for(const auto& it : other.symbols) {
        ptr<Member> member = it.second;
        ptr<Function> function = std::dynamic_pointer_cast<Function>(member);
        if(function) {
            symbols[it.first] = make<Function>(*function);
        } else {
            symbols[it.first] = member;
        }
    }
}

Environment& Environment::operator=(const Environment &other) {
    if(this == &other)
        return *this;

    symbols.clear();

    for(const auto& it : other.symbols) {
        ptr<Member> member = it.second;
        ptr<Function> function = std::dynamic_pointer_cast<Function>(member);
        if(function) {
            symbols[it.first] = make<Function>(*function);
        } else {
            symbols[it.first] = member;
        }
    }

    return *this;
}

std::string Environment::toString(bool pretty = false) {
    std::string result;
    for(const auto& it : symbols) {
        ptr<Value> value = std::dynamic_pointer_cast<Value>(it.second);
        if(value) {
            if(pretty) result += '\t';
            result += it.first.name + " = " + value->asString() + "";
            if(!pretty) result += ";";
            if(pretty) result += '\n';
        }
    }
    return result;
}
