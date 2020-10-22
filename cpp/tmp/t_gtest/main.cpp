#include "ddl.h"

TEST_F(ddl, run_test_ddl) {
    EXPECT_EQ(true, test_ddl());
}

int main(int argc, char *argv[]) {

    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

