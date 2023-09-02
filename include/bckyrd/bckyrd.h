#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct bckyrd_Pool {
  void *current_ptr;
  void *last_ptr;
  void *orig_ptr;
} bckyrd_Pool;

static inline bool bckyrd_Pool_alloc(bckyrd_Pool pool, size_t size) {
  void *next_ptr = ((char *)pool.current_ptr) + size;

  if (next_ptr > pool.last_ptr)
    return false;

  pool.current_ptr = next_ptr;

  return true;
}

static inline bckyrd_Pool bckyrd_Pool_create(size_t size) {
  void *p = malloc(size);

  return (bckyrd_Pool){
      .current_ptr = p,
      .last_ptr = ((char *)p) + size,
      .orig_ptr = p,
  };
}

static inline void bckyrd_Pool_free(bckyrd_Pool pool) {
  free(pool.orig_ptr);
}

static inline void bckyrd_Pool_reset(bckyrd_Pool *pool) {
  pool->current_ptr = pool->last_ptr;
}

static inline void bckyrd_Pool_reset_to(bckyrd_Pool *pool, void *ptr) {
  pool->current_ptr = ptr;
}
