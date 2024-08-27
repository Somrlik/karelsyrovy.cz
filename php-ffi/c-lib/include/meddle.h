#ifndef LIB_MEDDLE
#define LIB_MEDDLE

#if __cplusplus
extern "C" {
#endif

/**
 * Increments the given int by
 * - 1  if called using C
 * - 10 if called using CPP
 */
int meddle(int);

#if __cplusplus
}
#endif

#endif
