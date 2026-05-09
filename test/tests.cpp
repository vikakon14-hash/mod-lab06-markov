// Copyright 2021 GHA Test Team
#include "textgen.h"

#include <gtest/gtest.h>
#include <fstream>
#include <string>

TEST(MarkovTest, test1) {
    statetab emptyTable;
    std::string result = generate(emptyTable);
    EXPECT_TRUE(result.empty());
}

TEST(MarkovTest, test2) {
    statetab table;
    std::ofstream testFile("test2.txt");
    testFile << "words for the test";
    testFile.close();
    buildTable("test2.txt", table);
    prefix p1 = {"words", "for"};
    prefix p2 = {"for", "the"};
    EXPECT_EQ(table.count(p1), 1);
    EXPECT_EQ(table[p1][0], "the");
    EXPECT_EQ(table.count(p2), 1);
    EXPECT_EQ(table[p2][0], "test");
    remove("test2.txt");
}
TEST(MarkovTest, test3) {
    statetab table;
    std::ofstream testFile("test3.txt");
    testFile << "a b c b c d";
    testFile.close();
    buildTable("test3.txt", table);
    prefix p1 = { "a", "b" };
    prefix p2 = { "b", "c" };
    prefix p3 = { "c", "b" };
    EXPECT_EQ(table[p1].size(), 1);
    EXPECT_EQ(table[p2].size(), 2);
    EXPECT_EQ(table[p3].size(), 1);
    EXPECT_EQ(table[p2][0], "b");
    EXPECT_EQ(table[p2][1], "d");
    remove("test3.txt");
}

TEST(MarkovTest, test4) {
    statetab table;
    std::ofstream testFile("test4.txt");
    testFile << "a b c b c d";
    testFile.close();
    buildTable("test4.txt", table);
    prefix p = { "b", "c" };
    bool suf1 = false, suf2 = false;
    for (int i = 0; i < 50; i++) {
        std::string s = randomSuffix(table, p);
        if (s == "b") suf1 = true;
        if (s == "d") suf2 = true;
    }
    EXPECT_TRUE(suf1 && suf2);
    remove("test4.txt");
}

TEST(MarkovTest, test5) {
    statetab table;
    std::ofstream testFile("test5.txt");
    testFile << "a b c b c d";
    testFile.close();
    buildTable("test5.txt", table);
    for (const auto& entry : table) {
        EXPECT_EQ(entry.first.size(), NPREF);
    }
    remove("test5.txt");
}

TEST(MarkovTest, test6) {
    statetab table;
    std::ofstream testFile("test6.txt");
    testFile << "a a a a a a a";
    testFile.close();
    buildTable("test6.txt", table);
    prefix p = {"a", "a"};
    EXPECT_EQ(table[p].size(), 5);
    EXPECT_EQ(table.count(p), 1);
    remove("test6.txt");
}

TEST(MarkovTest, test7) {
    statetab table;
    std::ofstream testFile("test7.txt");
    testFile << "a b c";
    testFile.close();
    buildTable("test7.txt", table);
    prefix p = { "a", "b" };
    for (int i = 0; i < 50; i++) {
        std::string result = randomSuffix(table, p);
        EXPECT_EQ(result, "c");
    }
    EXPECT_EQ(table.size(), 1);
    remove("test7.txt");
}

TEST(MarkovTest, test8) {
    statetab table;
    std::ofstream testFile("test8.txt");
    testFile << "a b c";
    testFile.close();
    buildTable("test8.txt", table);
    prefix p = { "e", "f" };
    std::string result = randomSuffix(table, p);
    EXPECT_TRUE(result.empty());
    remove("test8.txt");
}

TEST(MarkovTest, test9) {
    statetab table;
    std::ofstream testFile("test9.txt");
    testFile << "a b a b a b a b a b a b a b a b a b a b";
    testFile.close();
    buildTable("test9.txt", table);
    std::string result = generate(table);
    int wordCount = 1;
    for (char c : result) {
        if (c == ' ') wordCount++;
    }
    EXPECT_EQ(wordCount, MAXGEN);
    remove("test9.txt");
}

TEST(MarkovTest, test10) {
    statetab table;
    prefix p = {"a", "b"};
    table[p];
    std::string result = randomSuffix(table, p);
    EXPECT_TRUE(result.empty());
}
TEST(MarkovTest, test11) {
    statetab table;
    std::ofstream testFile("test11.txt");
    testFile << "a b c";
    testFile.close();
    buildTable("test11.txt", table);
    std::string result = generate(table);
    int wordCount = 1;
    for (char c : result) {
        if (c == ' ') wordCount++;
    }
    EXPECT_EQ(wordCount, 3);
    remove("test11.txt");
}
