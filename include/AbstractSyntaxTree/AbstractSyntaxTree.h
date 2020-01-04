#pragma once

#include <memory>
#include <unordered_map>

#include "Symbol.h"

template <typename T>
using ptr = std::shared_ptr<T>;

typedef std::unordered_map<std::string, ptr<Symbol>> SymbolMap;

#include "Values/Value.h"
#include "Values/Object.h"
