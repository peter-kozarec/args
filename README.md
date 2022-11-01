[![ci](https://github.com/peter-kozarec/args/actions/workflows/ci.yml/badge.svg)](https://github.com/peter-kozarec/args/actions/workflows/ci.yml)

# ARGS
Argument parsing library

## Requirement
You'll need:

* "CMake >= 3.19".

## Build
To build the C++ project, as usual:
```sh
cmake -S. -Bbuild -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

## Tests
To run the tests:
```sh
ctest -C Release
```

## Usage
Add to your CMakeLists.txt:
```
find_package(args REQUIRED)
target_include_libraries(${TARGET} PRIVATE args)
```

## Example
```
#include <iostream>
#include "args.hpp"

int main(int argc, char **argv)
{
    cargs args;
    args.register_number_arg("n", "number", "test number");
    
    if (args.parse(argc, argv))
    {
        int value;
        if (args.get_value("number", value))
        {
            std::cout << "Number argument with value: " << value << std::endl;
        } 
    }
   
    return 0;
}
```

## License
Apache 2. See the LICENSE file for details.