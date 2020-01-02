#pragma once

#include <memory>

template <typename T>
using ptr = std::shared_ptr<T>;

#include "Node.h"
#include "Symbol.h"
#include "Values/Value.h"
#include "Values/Primitives/Primitive.h"
#include "Values/Primitives/Integer.h"
#include "Values/Primitives/Double.h"
#include "Values/Primitives/Boolean.h"
#include "Values/Primitives/String.h"
#include "Expression.h"
#include "Operators/BinaryOperator.h"
#include "AttributeDeclaration.h"
