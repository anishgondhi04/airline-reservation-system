#include "../include/airline_system.h"

int main() {
    try {
        // Display welcome screen
        std::system("clear");  // or cls for Windows
        Visual::printWithDelay(LINE('*'), 20);
        Visual::printWithDelay(Visual::center("WELCOME TO"), 50);
        Visual::printWithDelay(Visual::center("AIRLINE RESERVATION SYSTEM"), 50);
        Visual::printWithDelay(Visual::center("Version 2.0"), 50);
        Visual::printWithDelay(LINE('*'), 20);
        Visual::printWithDelay(Visual::center("Loading..."), 100);
        std::this_thread::sleep_for(std::chrono::seconds(1));

        // Start the system
        AirlineSystem system;
        system.run();
    }
    catch (const std::exception& e) {
        std::cerr << "\nFATAL ERROR\n";
        Visual::printWithDelay(LINE('!'));
        Visual::printWithDelay(e.what());
        Visual::printWithDelay(LINE('!'));
        std::cout << "\nPress Enter to exit...";
        std::cin.get();
        return 1;
    }
    return 0;
}