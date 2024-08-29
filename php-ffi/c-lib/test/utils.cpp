#include "./utils.h"
#include <fstream>
#include <gtest/gtest.h>

testing::AssertionResult FileContentsEqual(const std::string &filename, char* expected) {
    std::ifstream in("./resources/" + filename, std::ios::in | std::ios::binary);
    if (!in) {
        return testing::AssertionFailure() << "Failed to open test resource '" << filename << "'";
    }
    std::string contents;
    in.seekg(0, std::ios::end);
    contents.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&contents[0], (long)contents.size());
    in.close();

    EXPECT_STREQ(expected, contents.c_str()) << "The contents of file " << filename << " are not equal";
    return testing::AssertionSuccess();
}
