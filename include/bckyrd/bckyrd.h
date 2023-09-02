#ifndef BCKYRD_H
#define BCKYRD_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * A memory pool.
 */
typedef struct bckyrd_Pool {
  void *current_ptr;
  void *last_ptr;
  void *orig_ptr;
} bckyrd_Pool;

/*
 * Allocate memory from the pool. Returns the next pointer or null if the
 * allocation is too large.
 */
static inline void *bckyrd_Pool_alloc(bckyrd_Pool pool[static 1], size_t size) {
  void *next_ptr = ((char *)pool->current_ptr) + size;

  if (next_ptr > pool->last_ptr)
    return nullptr;

  pool->current_ptr = next_ptr;

  return next_ptr;
}

/*
 * Creates a new memory pool with the given size. The orig_ptr and current_ptr
 * fields are null if creation fails.
 */
static inline bckyrd_Pool bckyrd_Pool_create(size_t size) {
  void *p = malloc(size);

  return (bckyrd_Pool){
      .current_ptr = p,
      .last_ptr = ((char *)p) + size,
      .orig_ptr = p,
  };
}

/*
 * Frees the memory from the pool, which makes it unusable.
 */
static inline void bckyrd_Pool_free(bckyrd_Pool pool) {
  free(pool.orig_ptr);
}

/*
 * Resets the memory pool to its original state.
 */
static inline void bckyrd_Pool_reset(bckyrd_Pool pool[static 1]) {
  pool->current_ptr = pool->orig_ptr;
}

/*
 * Resets the memory pool to the pointer given. This pointer should be a
 * pointer given by the bckyrd_Pool_alloc function.
 */
static inline void bckyrd_Pool_reset_to(bckyrd_Pool pool[static 1], void *ptr) {
  pool->current_ptr = ptr;
}

#endif
