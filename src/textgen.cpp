// Copyright 2026 UNN-IASR
#include "textgen.h"

#include <fstream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

static std::mt19937 rng(std::random_device {}());

void buildTable(const std::string& filename, statetab& table) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open the file: " + filename);
    }
    std::vector<std::string> words;
    std::string word;
    while (file >> word) {
        words.push_back(word);
    }
    file.close();
    if (words.size() < static_cast<size_t>(NPREF + 1)) {
        throw std::runtime_error("Your file is too small");
    }
    prefix currentPrefix;
    for (int i = 0; i < NPREF; i++) {
        currentPrefix.push_back(words[i]);
    }
    for (size_t i = NPREF; i < words.size(); i++) {
        const std::string& suffix = words[i];
        table[currentPrefix].push_back(suffix);
        currentPrefix.pop_front();
        currentPrefix.push_back(suffix);
    }
}

std::string randomSuffix(const statetab& table, const prefix& p) {
    auto it = table.find(p);
    if (it == table.end()) {
        return "";
    }
    const std::vector<std::string>& suffixes = it->second;
    if (suffixes.empty()) {
        return"";
    }
    std::uniform_int_distribution<size_t> dist(0, suffixes.size() - 1);
    return suffixes[dist(rng)];
}
std::string generate(statetab& table) {
    if (table.empty()) {
        return "";
    }
    prefix current = table.begin()->first;
    std::vector<std::string> result;
    for (const auto& w : current) {
        result.push_back(w);
    }
    for (int i = NPREF; i < MAXGEN; i++) {
        std::string nextWord = randomSuffix(table, current);
        if (nextWord.empty()) {
            break;
        }
        result.push_back(nextWord);
        current.pop_front();
        current.push_back(nextWord);
    }
    std::stringstream ss;
    for (size_t i = 0; i < result.size(); i++) {
        if (i != 0) ss << " ";
        ss << result[i];
    }
    return ss.str();
}
void saveToFile(const std::string& text, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to create a file " + filename);
    }
    file << text;
    file.close();
}
