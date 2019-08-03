# lazy_initializer

A small, header-only C++ class for a lazy initializer.

[![GitHub license](https://img.shields.io/badge/license-MIT-blue.svg)](https://raw.githubusercontent.com/jmitchell1982/lazy_initializer/master/LICENSE)

## Features

- Initialization deferred until first usage or direct value assignment
- Determination of initialization status
- Determination of initialization via deferred or direct initialization
- Resetable to uninitialized state

## Common Usage Scenarios

- Defer initialization of objects that are expensive to initialize until and if they are needed
- Defer initialization of objects that depend on other objects which may not be immediately available
- Initializations of objects which can be derived from each other using complex chains of initialization

## Lazy Initialization Drawbacks

- Increased performance overhead
  - Initialization and access of the value requires extra function calls
- Increased memory overhead
  - The object is made from two std::optional objects and a std::function. Each std::optional likely contains both an instance of the underlying type as well as a flag.
