# entservices-apis local build failure: include paths root-cause (L1)

## Failure signal
- Many warnings of the form:
  - `cc1plus: warning: <path>: not a directory`
- Fatal header resolution failures:
  - `fatal error: interfaces/IAppManager.h: No such file or directory`
  - `fatal error: interfaces/entservices_errorcodes.h: No such file or directory`

## Where the broken include flags come from
File inspected:

- `build/entservices-apis/CMakeFiles/WPEFrameworkMarshalling.dir/flags.make`

The `CXX_INCLUDES` list contains multiple **file paths** incorrectly passed as include directories (`-I`), e.g.:

- `.../entservices-apis/apis/Ids.h`
- `.../entservices-apis/apis/Module.cpp`
- `.../entservices-apis/apis/Module.h`
- `.../entservices-apis/apis/common.json`
- `.../entservices-apis/apis/definitions.h`
- `.../entservices-apis/apis/entservices_errorcodes.h`

These directly explain the `not a directory` warnings.

## Why `<interfaces/*.h>` cannot be found
`entservices-apis/apis/Module.h` contains:

- `#include <interfaces/entservices_errorcodes.h>`

Therefore, the compiler must have an include directory `<include-root>` such that:

- `<include-root>/interfaces/entservices_errorcodes.h` exists.

In this workspace, the interfaces headers are present under:

- `install/usr/include/WPEFramework/interfaces/...`

So the include root that must be added is:

- `install/usr/include/WPEFramework`

Without it, `<interfaces/...>` cannot resolve.

## CMake cache evidence (current configuration)
File inspected:

- `build/entservices-apis/CMakeCache.txt`

It shows:

- `CMAKE_INCLUDE_PATH=/.../install_thunder/usr/include/WPEFramework;/.../install_thunder/usr/include`

This points to the Thunder-only prefix but does not provide a working `<include-root>/interfaces/...` layout in this environment.

## Concrete change needed
1. **Remove file paths from include directory lists**
   - Ensure any CMake variable used for include directories contains directories only, not header/cpp/json file paths.

2. **Add the correct interfaces include root**
   - Ensure entservices-apis compilation gets:
     - `-I<workspace>/install/usr/include/WPEFramework`
   - (or ensure the chosen Thunder prefix actually contains `include/WPEFramework/interfaces`, then add `-I<prefix>/include/WPEFramework`).

This is the minimal change required to make `<interfaces/*.h>` resolve and to eliminate `not a directory` warnings.
