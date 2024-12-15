#include "../include/airline_system.h"
#include <fstream>
#include <iomanip>
#include <limits>

// Screen utilities
void AirlineSystem::clearScreen() const {
    #ifdef _WIN32
        std::system("cls");
    #else
        std::system("clear");
    #endif
}

// Helper functions implementation
std::string AirlineSystem::getAirlineName(Airline airline) const {
    switch(airline) {
        case Airline::AIR_INDIA: return "Air India";
        case Airline::BRITISH_AIRWAYS: return "British Airways";
        case Airline::GULF_AIRWAYS: return "Gulf Airways";
        case Airline::UNITED_AIRLINES: return "United Airlines";
        case Airline::LUFTHANSA: return "Lufthansa";
        default: return "Unknown Airline";
    }
}

std::string AirlineSystem::getDestinationName(Route route) const {
    switch(route) {
        case Route::LONDON: return "LONDON";
        case Route::NEWYORK: return "NEW YORK";
        case Route::PARIS: return "PARIS";
        case Route::SWITZERLAND: return "SWITZERLAND";
        default: return "Unknown Destination";
    }
}

std::string AirlineSystem::getFileName(Airline airline) const {
    switch(airline) {
        case Airline::AIR_INDIA: return "Ind.dat";
        case Airline::BRITISH_AIRWAYS: return "Brit.dat";
        case Airline::GULF_AIRWAYS: return "Gulf.dat";
        case Airline::UNITED_AIRLINES: return "Unit.dat";
        case Airline::LUFTHANSA: return "Luf.dat";
        default: throw AirlineException("Invalid airline selected");
    }
}

void AirlineSystem::displayMenu() const {
    clearScreen();
    Visual::printWithDelay(LINE('*'));
    Visual::printWithDelay(Visual::center("AIRLINE RESERVATION SYSTEM"));
    Visual::printWithDelay(LINE('*'));
    
    std::cout << "\n\n" << std::setw(40) << "MAIN MENU\n"
              << "\n\t1. New Reservation"
              << "\n\t2. Passenger Info"
              << "\n\t3. Modify Record"
              << "\n\t4. Display Information Of Passengers"
              << "\n\t5. Cancellation"
              << "\n\t0. Exit\n"
              << "\n\t" << LINE('-') << "\n"
              << "\n\tEnter choice: ";
}

std::optional<AirlineSystem::Airline> AirlineSystem::selectAirline() const {
    clearScreen();
    Visual::printWithDelay(Visual::center("SELECT A FLIGHT"));
    Visual::printWithDelay(LINE('='));

    for (int i = 1; i <= 5; ++i) {
        std::cout << "\n\t" << i << ". " 
                 << getAirlineName(static_cast<Airline>(i));
    }
    std::cout << "\n\tR. Return to Main Menu"
              << "\n\n\tEnter choice: ";

    char choice;
    std::cin >> choice;
    choice = std::toupper(choice);

    if (choice == 'R') return std::nullopt;
    return static_cast<Airline>(choice - '0');
}

void AirlineSystem::addNewPassenger() {
    if (passengers.size() >= MAX_PASSENGERS) {
        throw AirlineException("Flight is full. Cannot add more passengers.");
    }

    auto airline = selectAirline();
    if (!airline) return;

    auto passenger = std::make_unique<Passenger>();
    
    clearScreen();
    Visual::printWithDelay(Visual::center("NEW PASSENGER REGISTRATION"));
    Visual::printWithDelay(LINE('='));

    std::cout << "\nEnter passenger details:\n";
    std::cout << "Name: ";
    std::cin.ignore();
    std::getline(std::cin, passenger->name);

    do {
        std::cout << "Sex (M/F): ";
        std::cin >> passenger->sex;
        passenger->sex = std::toupper(passenger->sex);
    } while (passenger->sex != 'M' && passenger->sex != 'F');

    do {
        std::cout << "Age (4-100): ";
        std::cin >> passenger->age;
    } while (passenger->age < 4 || passenger->age > 100);

    std::cout << "Nationality: ";
    std::cin.ignore();
    std::getline(std::cin, passenger->nationality);

    Visual::printWithDelay("\nAvailable Routes:");
    Visual::printWithDelay(LINE('-'));
    for (int i = 1; i <= 4; ++i) {
        std::cout << i << ". DELHI - " 
                 << getDestinationName(static_cast<Route>(i)) 
                 << " - DELHI\n";
    }
    std::cout << "Select route: ";
    std::cin >> passenger->destination;

    passenger->passNo = passengers.size() + 1;
    passenger->status = passengers.size() < 5 ? "C" : "W";

    passengers.push_back(*passenger);
    saveToFile(*airline);

    Visual::printWithDelay(LINE('*'));
    std::cout << "\nReservation completed! Ticket number: " 
              << passenger->passNo << "\n"
              << "Status: " << passenger->status << "\n";
    Visual::printWithDelay(LINE('*'));
    
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

void AirlineSystem::saveToFile(Airline airline) const {
    auto filename = getFileName(airline);
    std::ofstream file{filename, std::ios::binary | std::ios::app};
        
    if (!file) {
        throw AirlineException("Error opening file!");
    }

    for (const auto& passenger : passengers) {
        file.write(reinterpret_cast<const char*>(&passenger), 
            sizeof(Passenger));
    }
}

void AirlineSystem::displayPassenger(const Passenger& p) const {
    Visual::printWithDelay(LINE('='));
    Visual::printWithDelay(Visual::center("PASSENGER INFORMATION"));
    Visual::printWithDelay(LINE('='));

    std::cout << "\n\tTicket No    : " << p.passNo
              << "\n\tName         : " << p.name
              << "\n\tSex          : " << p.sex
              << "\n\tAge          : " << p.age
              << "\n\tNationality  : " << p.nationality
              << "\n\tDestination  : " << getDestinationName(static_cast<Route>(p.destination))
              << "\n\tStatus       : " << p.status << "\n";
    
    Visual::printWithDelay(LINE('-'));
}

void AirlineSystem::displayPassengerInfo() {
    if (passengers.empty()) {
        Visual::printWithDelay("\nNo passengers in the system.");
        return;
    }

    int ticketNo;
    std::cout << "\nEnter ticket number: ";
    std::cin >> ticketNo;

    auto it = std::find_if(passengers.begin(), passengers.end(),
        [ticketNo](const Passenger& p) { return p.passNo == ticketNo; });

    if (it != passengers.end()) {
        clearScreen();
        displayPassenger(*it);
    } else {
        Visual::printWithDelay("\nPassenger not found!");
    }
    
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore();
    std::cin.get();
}

void AirlineSystem::modifyRecord() {
    clearScreen();
    Visual::printWithDelay(Visual::center("MODIFY PASSENGER RECORD"));
    Visual::printWithDelay(LINE('='));

    int ticketNo;
    std::cout << "\nEnter ticket number to modify: ";
    std::cin >> ticketNo;

    auto it = std::find_if(passengers.begin(), passengers.end(),
        [ticketNo](const Passenger& p) { return p.passNo == ticketNo; });

    if (it != passengers.end()) {
        std::cout << "\nCurrent details:\n";
        displayPassenger(*it);
        
        Visual::printWithDelay("\nEnter new details:");
        Visual::printWithDelay(LINE('-'));
        
        std::cout << "Name: ";
        std::cin.ignore();
        std::getline(std::cin, it->name);
        
        std::cout << "Age: ";
        std::cin >> it->age;
        
        Visual::printWithDelay("\nRecord modified successfully!");
    } else {
        Visual::printWithDelay("\nPassenger not found!");
    }

    std::cout << "\nPress Enter to continue...";
    std::cin.ignore();
    std::cin.get();
}
void AirlineSystem::cancelTicket() {
    clearScreen();
    Visual::printWithDelay(Visual::center("TICKET CANCELLATION"));
    Visual::printWithDelay(LINE('='));

    int ticketNo;
    std::cout << "\nEnter ticket number to cancel: ";
    std::cin >> ticketNo;

    auto it = std::find_if(passengers.begin(), passengers.end(),
        [ticketNo](const Passenger& p) { return p.passNo == ticketNo; });

    if (it != passengers.end()) {
        passengers.erase(it);
        Visual::printWithDelay("\nTicket cancelled successfully!");
        
        // Update waiting list status
        for (size_t i = 0; i < std::min(passengers.size(), 
            static_cast<size_t>(MAX_PASSENGERS)); ++i) {
            passengers[i].status = "C";
        }
    } else {
        Visual::printWithDelay("\nTicket not found!");
    }

    std::cout << "\nPress Enter to continue...";
    std::cin.ignore();
    std::cin.get();
}

void AirlineSystem::run() {
    try {
        char choice;
        do {
            displayMenu();
            std::cin >> choice;

            switch (choice) {
                case '1': addNewPassenger(); break;
                case '2': displayPassengerInfo(); break;
                case '3': modifyRecord(); break;
                case '4': 
                    if (passengers.empty()) {
                        clearScreen();
                        Visual::printWithDelay(Visual::center("PASSENGER LIST"));
                        Visual::printWithDelay(LINE('='));
                        Visual::printWithDelay("\nNo passengers in the system.");
                    } else {
                        clearScreen();
                        Visual::printWithDelay(Visual::center("PASSENGER LIST"));
                        Visual::printWithDelay(LINE('='));
                        
                        for (const auto& passenger : passengers) {
                            displayPassenger(passenger);
                            std::cout << '\n';
                        }
                        
                        Visual::printWithDelay(LINE('-'));
                        std::cout << "\nTotal Passengers: " << passengers.size() 
                                << " / " << MAX_PASSENGERS << "\n";
                        Visual::printWithDelay(LINE('='));
                    }
                    std::cout << "\nPress Enter to continue...";
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cin.get();
                    break;
                case '5': 
                    cancelTicket(); 
                    break;
                case '0': 
                    clearScreen();
                    Visual::printWithDelay(LINE('*'));
                    Visual::printWithDelay(Visual::center("THANK YOU FOR USING OUR SYSTEM"));
                    Visual::printWithDelay(Visual::center("Have a great journey!"));
                    Visual::printWithDelay(LINE('*'));
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                    break;
                default: 
                    std::cout << "\nInvalid choice! Please try again...";
                    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
            }
        } while (choice != '0');
    }
    catch (const AirlineException& e) {
        clearScreen();
        Visual::printWithDelay(LINE('!'));
        Visual::printWithDelay(Visual::center("ERROR"));
        Visual::printWithDelay(Visual::center(e.what()));
        Visual::printWithDelay(LINE('!'));
        std::cout << "\nPress Enter to continue...";
        std::cin.ignore();
        std::cin.get();
    }
    catch (const std::exception& e) {
        clearScreen();
        Visual::printWithDelay(LINE('!'));
        Visual::printWithDelay(Visual::center("SYSTEM ERROR"));
        Visual::printWithDelay(Visual::center(e.what()));
        Visual::printWithDelay(LINE('!'));
        std::cout << "\nPress Enter to continue...";
        std::cin.ignore();
        std::cin.get();
    }
}