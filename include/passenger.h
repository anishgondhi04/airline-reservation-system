#pragma once
#include <string>

/********************************************************
 * Passenger Structure
 * Contains all relevant information about a passenger
 * including personal details and booking status
 ********************************************************/
struct Passenger {
    std::string name;        // Passenger's full name
    char sex;               // M or F
    std::string from;       // Default departure city (DELHI)
    std::string status;     // Booking status (C: Confirmed, W: Waiting)
    std::string nationality;// Passenger's nationality
    int passNo;            // Unique ticket number
    int age;               // Passenger's age
    int destination;       // Destination route number

    // Constructor with modern initialization
    Passenger() : 
        sex{'X'},
        from{"DELHI"},
        status{"W"},
        passNo{0},
        age{0},
        destination{0} {}
};