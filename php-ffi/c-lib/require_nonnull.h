#ifndef MEDDLE_REQUIRE_NONNULL_H
#define MEDDLE_REQUIRE_NONNULL_H

#ifdef NDEBUG
#define require_nonnull(x)((void)((x) ? 1 : abort(), 0))
#else
#include <assert.h>
#define require_nonnull assert
#endif

#endif
