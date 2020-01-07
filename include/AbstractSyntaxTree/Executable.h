#pragma once

class Interpreter;

struct Executable {
   virtual void execute(Interpreter* interpreter) = 0;
    virtual ~Executable() {}
};
