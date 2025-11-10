#define EXPECT_EXCEPTION_MSG(stmt, exception, msg)                                                                                                   \
    try {                                                                                                                                            \
        stmt;                                                                                                                                        \
        FAIL() << "Expected " << #exception;                                                                                                         \
    } catch (const exception &e) {                                                                                                                   \
        EXPECT_STREQ(e.what(), msg);                                                                                                                 \
    } catch (...) {                                                                                                                                  \
        FAIL() << "Expected " << #exception;                                                                                                         \
    }