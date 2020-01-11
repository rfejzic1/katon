#pragma once

#include <vector>
#include <memory>

struct Value;

template <typename T>
using ptr = std::shared_ptr<T>;

typedef std::string Identifier;
typedef std::vector<ptr<Value>> ValueList;
typedef std::vector<Identifier> IdentifierList;
