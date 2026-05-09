// Copyright 2026 UNN-IASR
#include "main.h"
#include "textgen.h"
#include <iostream>
#include <string>

int main() {
    std::string input = "frost.txt";
    std::string output = "gen.txt";
    try {
        std::cout << "Downloading data from a file:" << input << std::endl;
        statetab table;
        buildTable(input, table);
        std::cout << "The table is formed. "
            << "Starting text generation" << std::endl;
        std::string generated = generate(table);
        saveToFile(generated, output);
        std::cout << "The generated text is saved to a file "
            << output << std::endl;
    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }
    return 0;
}
