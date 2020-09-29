#include <iostream>
#include "Histogram.h"

int main()
{
    std::cout << "Enter text, followed by QUIT on its own line" << std::endl;

    // Read lines of text, appending them to a string
    std::string text;
    bool done = false;
    while (!done) {
        std::string line;
        std::getline(std::cin, line);

        if (line == std::string("QUIT")) {
            done = true;
        } else {
            text.append(line);
        }
    }

    // Use the histogram to analyze the letter counts
    Histogram h(26);
    for (unsigned i = 0; i < text.length(); i++) {
        char c = text[i];
        int bucket = -1;
        if (c >= 'a' && c <= 'z') {
            bucket = c - 'a';
        } else if (c >= 'A' && c <= 'Z') {
            bucket = c - 'A';
        }

        if (bucket >= 0) {
            h.increaseCount(bucket);
        }
    }

    // Print a bar graph
    for (int i = 0; i < 26; i++) {
        std::cout << char(i + 'A') << ": ";
        std::cout << std::string(h.getCount(i), '=') << std::endl;
    }

    return 0;
}
