#include "../include/AbstractSyntaxTree/Values/Value.h"

#include "../include/AbstractSyntaxTree/ExceptionObjects.h"
#include "../include/AbstractSyntaxTree/Packets.h"

std::string Value::asString() {
    throw ThrowPacket(ExceptionObjects::bad_cast("Could not cast value to String"));
}

long long int Value::asInteger() {
    throw ThrowPacket(ExceptionObjects::bad_cast("Could not cast value to Integer"));
}

double Value::asDouble() {
    throw ThrowPacket(ExceptionObjects::bad_cast("Could not cast value to Double"));
}

bool Value::asBoolean() {
    throw ThrowPacket(ExceptionObjects::bad_cast("Could not cast value to Boolean"));
}

ptr<Object> Value::asObject() {
    throw ThrowPacket(ExceptionObjects::bad_cast("Could not cast value to Object"));
}

ptr<Array> Value::asArray() {
    throw ThrowPacket(ExceptionObjects::bad_cast("Could not cast value to Array"));
}
