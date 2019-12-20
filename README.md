# Katon Language

## Introduction

Katon is an interpreted language and its interpreter is built in C++. The Katon interpreter is built for educational
purposes as a part of a project assignment. The language itself is simple and is intended to be an object-based scripting 
language inspired by languages like JavaScript, C++, Java, Python etc. 

## Example code
The code below is just a simple example. More of the language features will be documented in this README file.
```
# Object level variable; let is optional; default scope is public
name = 'John';

# Only a source file with a main() method
# can be executed by the interpreter
fun main() {
    # let is mandatory; type is inferred
    let greeting = 'Hello';
    
    # if statement
    if greeting == 'Hello' {
        # The curly braces are mandatory
    }
}

```

