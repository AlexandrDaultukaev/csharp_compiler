#include "parser/parser.hpp"
#include <string>
#include <vector>
#include <gtest/gtest.h>

const std::string path = "../../tests/lexer-tests-cs/";

TEST(LexerSuite, PositionTest) {
    const std::string testfile = "test1.cs";
    cs_lang::tokens_array tkn_arr = cs_lang::dump_tokens(path+testfile, 0);
    EXPECT_EQ(1, tkn_arr[0].get_x());
    EXPECT_EQ(0, tkn_arr[0].get_y());
    EXPECT_EQ(1, tkn_arr[1].get_x());
    EXPECT_EQ(7, tkn_arr[1].get_y());
    EXPECT_EQ(1, tkn_arr[2].get_x());
    EXPECT_EQ(12, tkn_arr[2].get_y());
    EXPECT_EQ(1, tkn_arr[3].get_x());
    EXPECT_EQ(16, tkn_arr[3].get_y());
    EXPECT_EQ(1, tkn_arr[4].get_x());
    EXPECT_EQ(17, tkn_arr[4].get_y());
    EXPECT_EQ(1, tkn_arr[5].get_x());
    EXPECT_EQ(23, tkn_arr[5].get_y());
    EXPECT_EQ(1, tkn_arr[6].get_x());
    EXPECT_EQ(24, tkn_arr[6].get_y());
    EXPECT_EQ(1, tkn_arr[7].get_x());
    EXPECT_EQ(26, tkn_arr[7].get_y());
    EXPECT_EQ(3, tkn_arr[19].get_x());
    EXPECT_EQ(35, tkn_arr[19].get_y());
}

TEST(LexerSuite, TokenTest)
{
    const std::string testfile = "test1.cs";
    cs_lang::tokens_array tkn_arr = cs_lang::dump_tokens(path+testfile, 0);
    std::vector<std::string> token_strs = {"static", "void", "Main", "(", "string", "[", "]", "args", ")", "{", "int", "[", ",", "]", "array", "=", "new", "int", "[", "5", ",", "5", "]", ";", "InitializeArray", "(", "array", ")", ";", "Console.WriteLine", "(", ")", ";", "Console.WriteLine", "(", "\"", "Min", "Element", "in", "array", ":", "{", "0", "}", "\"", ",", "MinElement", "(", "array", ")", ")", ";", "Console.ReadLine", "(", ")", ";", "}"};
    std::vector<std::string> token_names = {"KEYWORD", "KEYWORD", "ID", "RLP", "VAR", "SLP", "SRP", "ID", "RRP", "CLB", "VAR", "SLP", "COMMA", "SRP", "ID", "ASSIGN", "KEYWORD", "VAR", "SLP", "NUMBER", "COMMA", "NUMBER", "SRP", "SEMICOLON", "ID", "RLP", "ID", "RRP", "SEMICOLON", "ID", "RLP", "RRP", "SEMICOLON", "ID", "RLP", "DQUOTES", "ID", "ID", "KEYWORD", "ID", "COLON", "CLB", "NUMBER", "CRB", "DQUOTES", "COMMA", "ID", "RLP", "ID", "RRP", "RRP", "SEMICOLON", "ID", "RLP", "RRP", "SEMICOLON", "CRB"};
    for(std::size_t i = 0; i < token_names.size(); i++)
    {
        EXPECT_EQ(token_strs[i], tkn_arr[i].get_token_str());
        EXPECT_EQ(token_names[i], tkn_arr[i].get_token_name());
    }
}