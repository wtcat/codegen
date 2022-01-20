#include <cstdio>
#include <system.h>
#include "gtest/gtest.h"

int main(int argc, char* argv[]) {
    int ret;
    testing::InitGoogleTest(&argc, argv);
    ret = RUN_ALL_TESTS();
    system("pause");
    return ret;
}
