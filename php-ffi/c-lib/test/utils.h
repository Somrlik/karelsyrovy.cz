#ifndef MEDDLE_UTILS_H
#define MEDDLE_UTILS_H

#include <string>
#include <gtest/gtest.h>

/**
 * Reads binary contents from file and compares them against expected
 *
 * @param filename name of file located in "./resources"
 * @param expected the expected bytes
 * @return corresponding AssertionResult
 */
testing::AssertionResult FileContentsEqual(const std::string &filename, char* expected);

#endif
