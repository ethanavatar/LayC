#ifndef LAYC_H
#define LAYC_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#define LAYC_ALLOCS_CAP 1024

typedef struct Entry Entry;
struct Entry {
    uintptr_t ptr;
    bool free;
};

static Entry LAYC_ALLOCS[LAYC_ALLOCS_CAP] = {0};
static size_t LAYC_ALLOCS_COUNT = 0;

static Entry* _get_next_empty_entry() {
    for (size_t i = 0; i < LAYC_ALLOCS_COUNT; i++) {
        if (LAYC_ALLOCS[i].free) {
            return &LAYC_ALLOCS[i];
        }
    }
    return NULL;
}

static void _save_entry(void* ptr) {
    Entry* entry = _get_next_empty_entry();
    if (entry == NULL) {
        return;
    }
    entry->ptr = (uintptr_t)ptr;
    entry->free = false;
}

static void* layc_alloc(size_t size) {
    void* ptr = malloc(size);
    if (ptr == NULL) {
        return NULL;
    }
    _save_entry(ptr);
    return ptr;
}

static void* layc_calloc(size_t n, size_t size) {
    void* ptr = calloc(n, size);
    if (ptr == NULL) {
        return NULL;
    }
    _save_entry(ptr);
    return ptr;
}

void layc_collect() {
    for (size_t i = 0; i < LAYC_ALLOCS_COUNT; i++) {
        Entry* current = &LAYC_ALLOCS[i];
        if (current->free) {
            continue;
        }
        free((void*)current->ptr);
        current->free = true;
    }
}

#endif // LAYC_H