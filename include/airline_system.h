#pragma once
#include <vector>
#include <optional>
#include <memory>
#include "passenger.h"
#include "exceptions.h"
#include "visual/effects.h"

class AirlineSystem {
private:
    std::vector<Passenger> passengers;
    static constexpr int MAX_PASSENGERS = 5;
    
    // Enum classes for improved type safety
    enum class Route {
        LONDON = 1,
        NEWYORK,
        PARIS,
        SWITZERLAND
    };

    enum class Airline {
        AIR_INDIA = 1,
        BRITISH_AIRWAYS,
        GULF_AIRWAYS,
        UNITED_AIRLINES,
        LUFTHANSA
    };

    std::string getAirlineName(Airline airline) const;
    std::string getDestinationName(Route route) const;
    std::string getFileName(Airline airline) const;
    void displayPassenger(const Passenger& p) const;
    void saveToFile(Airline airline) const;

public:
    void clearScreen() const;
    void displayMenu() const;
    std::optional<Airline> selectAirline() const;
    void addNewPassenger();
    void displayPassengerInfo();
    void modifyRecord();
    void cancelTicket();
    void run();
};