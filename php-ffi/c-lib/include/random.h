#ifndef MEDDLE_RANDOM_H
#define MEDDLE_RANDOM_H

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * Generates a deterministic int
 * @return int between 0 and 256
 */
int randomInt();

/**
 * Generates a deterministic int between two values
 *
 * @param min minimum > 0
 * @param max maximum
 * @return int between min and max
 */
int randomIntBetween(int min, int max);

/**
 * Resets deterministic int generator
 */
void randomIntReset();

#ifdef __cplusplus
}
#endif

#endif
