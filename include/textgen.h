// Copyright 2021 GHA Test Team
#ifndef INCLUDE_TEXTGEN_H_
#define INCLUDE_TEXTGEN_H_

#include <string>
#include <deque>
#include <map>
#include <vector>

typedef std::deque<std::string> prefix;
typedef std::map<prefix, std::vector<std::string>> statetab;

const int NPREF = 2;
const int MAXGEN = 1500;

void buildTable(const std::string& filename, statetab& table);
std::string generate(statetab& table);
void saveToFile(const std::string& text, const std::string& filename);
std::string randomSuffix(const statetab& table, const prefix& p);

#endif //INCLUDE_TEXTGEN_H_
