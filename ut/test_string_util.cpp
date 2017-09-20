#include <gtest/gtest.h>

#include "ralph/common/string_util.h"

TEST(string_util, ToUpper)
{
    ASSERT_EQ(ralph::Str::ToUpper("hello"), "HELLO");
    ASSERT_EQ(ralph::Str::ToUpper("hello world"), "HELLO WORLD");
}

TEST(string_util, ToLower)
{
    ASSERT_EQ(ralph::Str::ToLower("HELLO"), "hello");
    ASSERT_EQ(ralph::Str::ToLower("HELLO WORLD"), "hello world");
}

TEST(string_util, StartsWith)
{
    ASSERT_TRUE(ralph::Str::StartsWith("hello world", "he"));
    ASSERT_TRUE(ralph::Str::StartsWith("hello world", "hello"));
    ASSERT_TRUE(ralph::Str::StartsWith("hello world", "hello "));
    ASSERT_TRUE(ralph::Str::StartsWith("hello world", "hello world"));

    ASSERT_FALSE(ralph::Str::StartsWith("hello world", "hello-"));
    ASSERT_FALSE(ralph::Str::StartsWith("hello world", "hello h"));
    ASSERT_FALSE(ralph::Str::StartsWith("hello world", "hello world!"));
}

TEST(string_util, EndsWith)
{
    ASSERT_TRUE(ralph::Str::EndsWith("hello world", "d"));
    ASSERT_TRUE(ralph::Str::EndsWith("hello world", "ld"));
    ASSERT_TRUE(ralph::Str::EndsWith("hello world", "world"));
    ASSERT_TRUE(ralph::Str::EndsWith("hello world", "hello world"));

    ASSERT_FALSE(ralph::Str::EndsWith("hello world", "-"));
    ASSERT_FALSE(ralph::Str::EndsWith("hello world", "-d"));
    ASSERT_FALSE(ralph::Str::EndsWith("hello world", "-world"));
    ASSERT_FALSE(ralph::Str::EndsWith("hello world", "hello world!"));
}

TEST(string_util, Replace)
{
    ASSERT_EQ(ralph::Str::Replace("a waiter entered with a tray bearing a glass", "test", ""),
                                  "a waiter entered with a tray bearing a glass");

    ASSERT_EQ(ralph::Str::Replace("a waiter entered with a tray bearing a glass", "a", "e"),
                                  "e waiter entered with a tray bearing a glass");

    ASSERT_EQ(ralph::Str::Replace("a waiter entered with a tray bearing a glass", "waiter", "person"),
                                  "a person entered with a tray bearing a glass");

    ASSERT_EQ(ralph::Str::Replace("a waiter entered with a tray bearing a glass", "glass", "apple"),
                                  "a waiter entered with a tray bearing a apple");
}

TEST(string_util, ReplaceAll)
{
    ASSERT_EQ(ralph::Str::ReplaceAll("a waiter entered with a tray bearing a glass", "test", ""),
                                  "a waiter entered with a tray bearing a glass");

    ASSERT_EQ(ralph::Str::ReplaceAll("a waiter entered with a tray bearing a glass", "a", "e"),
                                     "e weiter entered with e trey beering e gless");

    ASSERT_EQ(ralph::Str::ReplaceAll("a waiter entered with a tray bearing a glass", "waiter", "person"),
                                  "a person entered with a tray bearing a glass");

    ASSERT_EQ(ralph::Str::ReplaceAll("a waiter entered with a tray bearing a glass", "glass", "apple"),
                                  "a waiter entered with a tray bearing a apple");

    ASSERT_EQ(ralph::Str::ReplaceAll("a waiter entered with a tray bearing a glass", " ", ","),
                                     "a,waiter,entered,with,a,tray,bearing,a,glass");
}

TEST(string_util, Ltrim)
{
    ASSERT_EQ(ralph::Str::Ltrim(" \r\t\n\v\a\b"), "");
    ASSERT_EQ(ralph::Str::Ltrim("hello world"), "hello world");
    ASSERT_EQ(ralph::Str::Ltrim("  hello world"), "hello world");
    ASSERT_EQ(ralph::Str::Ltrim("\r\n\t\v\b\a  hello world"), "hello world");
    ASSERT_EQ(ralph::Str::Ltrim("  hello world   "), "hello world   ");

    ASSERT_EQ(ralph::Str::Ltrim("hello world", "held"), "o world");
    ASSERT_EQ(ralph::Str::Ltrim("hello world", "hed"), "llo world");
    ASSERT_EQ(ralph::Str::Ltrim("hello world", "h"), "ello world");
    ASSERT_EQ(ralph::Str::Ltrim("hello \n\t\rworld", "hello"), " \n\t\rworld");
    ASSERT_EQ(ralph::Str::Ltrim("hello \n\t\rworld", "hello\n "), "\t\rworld");
    ASSERT_EQ(ralph::Str::Ltrim("   \n\t\rhello world   ", "held"), "   \n\t\rhello world   ");
}

TEST(string_util, Rtrim)
{
    ASSERT_EQ(ralph::Str::Rtrim(" \r\t\n\v\a\b"), "");
    ASSERT_EQ(ralph::Str::Rtrim("hello world"), "hello world");
    ASSERT_EQ(ralph::Str::Rtrim("hello world    "), "hello world");
    ASSERT_EQ(ralph::Str::Rtrim("   hello world    "), "   hello world");
    ASSERT_EQ(ralph::Str::Rtrim("hello world \r\t\n\a\b\v   "), "hello world");

    ASSERT_EQ(ralph::Str::Rtrim("hello world", "world"), "hello ");
    ASSERT_EQ(ralph::Str::Rtrim("hello world", "world "), "he");
    ASSERT_EQ(ralph::Str::Rtrim("   hello world", "world "), "   he");
}

TEST(string_util, Trim)
{
    ASSERT_EQ(ralph::Str::Trim(" \r\t\n\v\a\b"), "");
    ASSERT_EQ(ralph::Str::Trim("hello world"), "hello world");
    ASSERT_EQ(ralph::Str::Trim("hello world    "), "hello world");
    ASSERT_EQ(ralph::Str::Trim("   hello world"), "hello world");
    ASSERT_EQ(ralph::Str::Trim("   hello world   "), "hello world");
    ASSERT_EQ(ralph::Str::Trim("hello world \r\t\n\a\b\v   "), "hello world");
    ASSERT_EQ(ralph::Str::Trim("   \n\t\r\a\b hello world \r\t\n\a\b\v   "), "hello world");

    ASSERT_EQ(ralph::Str::Trim("hello world", "world"), "hello ");
    ASSERT_EQ(ralph::Str::Trim("hello world", "world "), "he");
    ASSERT_EQ(ralph::Str::Trim("hello world", "hworld "), "e");
    ASSERT_EQ(ralph::Str::Trim("hello world  ", "world"), "hello world  ");
    ASSERT_EQ(ralph::Str::Trim("hello world  ", "world "), "he");
    ASSERT_EQ(ralph::Str::Trim("   hello world  ", "held"), "   hello world  ");
    ASSERT_EQ(ralph::Str::Trim("   hello world  ", "held "), "o wor");
}

TEST(string_util, Split)
{
    std::vector<std::string> res = ralph::Str::Split("this  is  a  test", " ");
    size_t i = 0;
    ASSERT_EQ(res[i++], "this");
    ASSERT_EQ(res[i++], "is");
    ASSERT_EQ(res[i++], "a");
    ASSERT_EQ(res[i++], "test");

    res = ralph::Str::Split("this  is  a  test", " ", true);
    i = 0;
    ASSERT_EQ(res[i++], "this");
    ASSERT_EQ(res[i++], "");
    ASSERT_EQ(res[i++], "is");
    ASSERT_EQ(res[i++], "");
    ASSERT_EQ(res[i++], "a");
    ASSERT_EQ(res[i++], "");
    ASSERT_EQ(res[i++], "test");

    res = ralph::Str::Split("  this  is  a  test. ", "  ");
    i = 0;
    ASSERT_EQ(res[i++], "this");
    ASSERT_EQ(res[i++], "is");
    ASSERT_EQ(res[i++], "a");
    ASSERT_EQ(res[i++], "test. ");
}

TEST(string_util, SplitAny)
{
    std::vector<std::string> res = ralph::Str::SplitAny("this is\ta\ntest", " \t\n");
    size_t i = 0;
    ASSERT_EQ(res[i++], "this");
    ASSERT_EQ(res[i++], "is");
    ASSERT_EQ(res[i++], "a");
    ASSERT_EQ(res[i++], "test");

    res = ralph::Str::SplitAny("this  is\ta\n\ntest", " \t\n", true);
    i = 0;
    ASSERT_EQ(res[i++], "this");
    ASSERT_EQ(res[i++], "");
    ASSERT_EQ(res[i++], "is");
    ASSERT_EQ(res[i++], "a");
    ASSERT_EQ(res[i++], "");
    ASSERT_EQ(res[i++], "test");
}

TEST(string_util, Join)
{
    std::vector<std::string> res = ralph::Str::SplitAny("this is\ta\ntest", " \t\n");
    size_t i = 0;
    ASSERT_EQ(res[i++], "this");
    ASSERT_EQ(res[i++], "is");
    ASSERT_EQ(res[i++], "a");
    ASSERT_EQ(res[i++], "test");

    ASSERT_EQ(ralph::Str::Join(res, " "), "this is a test");
}

TEST(string_util, Format)
{
    ASSERT_EQ(ralph::Str::Format(" "), " ");
    ASSERT_EQ(ralph::Str::Format("%s %s!", "hello", "world"), "hello world!");
    ASSERT_EQ(ralph::Str::Format("%d times, %s %s!", 10, "hello", "world"), "10 times, hello world!");
}

TEST(string_util, Random)
{
    ASSERT_EQ(ralph::Str::Random("a", 20), std::string(20, 'a');
    ASSERT_EQ(ralph::Str::Random("a-zA-Z0-9!@#", 20).length(), 20);
    ASSERT_EQ(ralph::Str::Random("a-zA-Z", 30).length(), 30);
    ASSERT_EQ(ralph::Str::Random("0-9", 40).length(), 40);
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
