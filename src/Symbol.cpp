#include "../include/AbstractSyntaxTree/Symbol.h"

#include "../include/AbstractSyntaxTree/Environment.h"

ptr <Value> Symbol::evaluate(Environment *env) {
    return env -> getValue(name);
}

bool Symbol::operator==(const Symbol &symbol) const {
    return false;
}
