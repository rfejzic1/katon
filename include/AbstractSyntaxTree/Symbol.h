#pragma once

struct Symbol {
    const std::string& name;
    bool constant;
public:
    Symbol(const std::string& name, bool constant) : name(name), constant(constant) {}
};
