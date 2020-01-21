#pragma once

#include <vector>
#include <memory>
#include <functional>

struct Value;
struct Expression;

template <typename T>
using ptr = std::shared_ptr<T>;

template <class T, class... Args>
ptr<T> make(Args&&... args) {
    return std::make_shared<T>(args...);
}

typedef std::string Identifier;
typedef std::vector<ptr<Value>> ValueList;
typedef std::vector<Identifier> IdentifierList;
typedef std::vector<ptr<Expression>> ExpressionList;
