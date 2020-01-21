#include "../include/AbstractSyntaxTree/Values/Array.h"

void Array::add(ptr<Value> &value) {
    values.push_back(value);
}

void Array::addAll(ValueList &newValues) {
    values.insert(values.end(), newValues.begin(), newValues.end());
}

void Array::remove(ptr<Value> &value) {
    // todo: After the equality operator is implemented, use it here to check which element to remove
}

void Array::clean() {
    values.clear();
}

ptr<Integer> Array::length() {
    return make<Integer>(values.size());
}

Type Array::getType() {
    return Type::Array;
}

std::string Array::asString() {
    std::string result = "[ ";

    for(ptr<Value>& value : values) {
        result += value -> asString() + ", ";
    }

    result.pop_back();
    result += " ]";

    return result;
}

long long int Array::asInteger() {
    return values.size();
}

double Array::asDouble() {
    return values.size();
}

bool Array::asBoolean() {
    return !values.empty();
}

ptr<Value> Array::getValue() {
    return nullptr;
}

ptr<ValueList> Array::getValues() {
    return make<ValueList>(values);
}

ptr<Array> Array::asArray() {
    return thisArray;
}
