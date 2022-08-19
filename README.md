# LayC

~~A garbage collection system for C~~

~~global arena allocation~~

Indiscriminately free everything

## Usage (Not Recommended)

```c
#include "LayC.h"
```

### `void* layc_alloc(size_t size)`

Just malloc, but keeps track of the pointer it returns in a global array

### `void* layc_calloc(size_t n, size_t size)`

Just calloc, but keeps track of the pointer it returns in a global array

### `void layc_collect(void* ptr)`

Frees everything that was allocated with `layc_alloc` or `layc_calloc`
