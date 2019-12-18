#pragma once

#include <memory>

template <typename T>
using ptr = std::shared_ptr<T>;

#include "Node.h"
#include "Symbol.h"
#include "Values/Value.h"
#include "Values/Integer.h"
#include "Values/Double.h"
#include "Values/Boolean.h"
#include "Values/String.h"
#include "Expression.h"
#include "Operators/BinaryOperator.h"
#include "AttributeDeclaration.h"
