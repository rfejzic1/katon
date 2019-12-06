# Katon Language

## Introduction

Katon is an interpreted language and it's interpreter is built in C++. The Katon interpreter is built for educational
purposes as a part of a project assignment. The language itself is simple and is intended to be an object-based scripting 
language inspired by elements of other languages like JavaScript, C++, Java, Python, PHP etc. 

## Example code
The code below is just a simple example. More of the language features will be documented in this README file.
```
# Module level variable
let name = 'John';

# Only a source file with a main() method
# can be executed by the interpreter!
main() {
    # A string is wrapped in single quotes
    let greeting = 'Hello';
    
    # An interpolated string is wrapped in double quotes
    print("${greeting}, ${name}!");
}

```

