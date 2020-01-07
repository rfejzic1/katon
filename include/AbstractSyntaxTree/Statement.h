#pragma once

class Environment;

struct Statement {
    virtual void execute(Environment& env) = 0;
};
