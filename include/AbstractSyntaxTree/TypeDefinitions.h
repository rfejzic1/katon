#pragma once

#include <vector>
#include <memory>
#include <unordered_map>

struct Value;
class Symbol;

template <typename T>
using ptr = std::shared_ptr<T>;

typedef std::unordered_map<std::string, ptr<Symbol>> SymbolMap;
typedef std::vector<ptr<Value>> ValueList;
typedef std::vector<std::string> IdentifierList;

