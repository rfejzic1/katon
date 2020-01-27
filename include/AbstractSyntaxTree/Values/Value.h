#pragma once

#include "../Expression.h"
#include "../Type.h"
#include "../ExceptionObjects.h"
#include "../Packets.h"
#include "../Member.h"

class Object;
class Array;

class Value : public Member, public Expression {
public:
    ptr<Value> evaluate(Environment* env) override {
        // TODO: FIX THIS
        return std::shared_ptr<Value>(this);
    }

    virtual std::string asString() {
        throw ThrowPacket(ExceptionObjects::bad_cast("Could not cast value to String"));
    };

    virtual long long int asInteger() {
        throw ThrowPacket(ExceptionObjects::bad_cast("Could not cast value to Integer"));
    };

    virtual double asDouble() {
        throw ThrowPacket(ExceptionObjects::bad_cast("Could not cast value to Double"));
    };

    virtual bool asBoolean() {
        throw ThrowPacket(ExceptionObjects::bad_cast("Could not cast value to Boolean"));
    };

    virtual ptr<Object> asObject() {
        throw ThrowPacket(ExceptionObjects::bad_cast("Could not cast value to Object"));
    };

    virtual ptr<Array> asArray() {
        throw ThrowPacket(ExceptionObjects::bad_cast("Could not cast value to Array"));
    };

    virtual Type getType() = 0;
    virtual ~Value() { }
};
