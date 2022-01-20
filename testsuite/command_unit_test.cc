#include "base/command.h"
#include "gtest/gtest.h"

#include <vector>


struct cmdtest_class {
    struct cmd_class cmd;
    const char* str;
};

static int cmdtest_execute(struct cmd_class* cd) {
    struct cmdtest_class* cts = (struct cmdtest_class*)cd;
    printf("Command name: %s\n", cts->str);
    return 0;
}


#if 0
class CmdTest : public ::testing::TestWithParam<const char*> {
public:
    CmdTest() : cmdset_test() {
        cmdset_test.list = nullptr;
    }
    struct cmdset_class* get_instance() {
        return &cmdset_test;
    }
protected:
    void SetUp() override {
        printf("Set up\n");
    }
    void TearDown() override {
        printf("Tear down\n");
        //cmdset_del(&cmdset_test);
    }
private:
    struct cmdset_class cmdset_test;
};

INSTANTIATE_TEST_CASE_P(Command,
    CmdTest,
    ::testing::Values("1", "2", "3", "4", "5")
);

TEST_P(CmdTest, cmdset_add) {
    struct cmd_list** plist = &(get_instance()->list);
    const char* name = GetParam();

    ASSERT_TRUE(*plist == NULL);
    cmdset_add(get_instance(), CmdCreate(name, cmdtest_execute));
    ASSERT_TRUE(*plist != NULL);
    ASSERT_TRUE((*plist)->idx == 1);
}
#else

class CmdTest : public ::testing::Test {
public:
    CmdTest() : cmdset_test() {
        cmdset_test.list = nullptr;
        vector.reserve(100);
    }
    ~CmdTest() {}
    cmdset_class* get_instance() {
        return &cmdset_test;
    }
    cmd_class* CmdCreate(const char* cmd,
        int (*fn)(struct cmd_class*)) {
        struct cmdtest_class* ctest = new cmdtest_class();
        ctest->cmd.execute = fn;
        ctest->str = cmd;
        vector.push_back(ctest);
        return (cmd_class*)ctest;
    }
protected:
    void SetUp() override {
        printf("Set up\n");
    }
    void TearDown() override {
        printf("Tear down\n");
        cmdset_destory(get_instance());
        for (auto iter : vector)
            delete iter;
    }
private:
    struct cmdset_class cmdset_test;
    std::vector<cmdtest_class*> vector;
};

static struct cmdset_class cmdset_test;

TEST_F(CmdTest, cmdset_add) {
    struct cmd_list** plist = &(get_instance()->list);

    ASSERT_TRUE(*plist == NULL);

    cmdset_add(get_instance(), CmdCreate("1", cmdtest_execute));
    ASSERT_TRUE(*plist != NULL);
    ASSERT_TRUE((*plist)->idx == 1);

    cmdset_add(get_instance(), CmdCreate("2", cmdtest_execute));
    ASSERT_TRUE(*plist != NULL);
    ASSERT_TRUE((*plist)->idx == 2);

    cmdset_add(get_instance(), CmdCreate("3", cmdtest_execute));
    ASSERT_TRUE(*plist != NULL);
    ASSERT_TRUE((*plist)->idx == 3);

    cmdset_add(get_instance(), CmdCreate("4", cmdtest_execute));
    ASSERT_TRUE(*plist != NULL);
    ASSERT_TRUE((*plist)->idx == 4);

    cmdset_add(get_instance(), CmdCreate("5", cmdtest_execute));
    ASSERT_TRUE(*plist != NULL);
    ASSERT_TRUE((*plist)->idx == 5);

    ASSERT_TRUE(cmd_execute(&(get_instance()->cmd)) == 0);
}
#endif

