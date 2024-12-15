#pragma once
#include <string>
#include <iostream>
#include <chrono>
#include <thread>

// Function to create visual separator lines
#define LINE(ch) std::string(50, ch)

// Visual effects functions
namespace Visual {
    // Function to print text with delay for animation effect
    void printWithDelay(const std::string& text, int delay_ms = 50) {
        for (char c : text) {
            std::cout << c << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
        }
        std::cout << '\n';
    }

    // Function to create centered text
    std::string center(const std::string& text, int width = 50) {
        int spaces = (width - text.length()) / 2;
        return std::string(spaces, ' ') + text;
    }
}