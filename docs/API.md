# Airline Reservation System API Documentation

## Core Classes

### Passenger
```cpp
struct Passenger {
    std::string name;        // Passenger's full name
    char sex;               // M or F
    std::string from;       // Default departure city
    std::string status;     // Booking status (C/W)
    std::string nationality;// Nationality
    int passNo;            // Ticket number
    int age;               // Age
    int destination;       // Route number
};
```

### AirlineSystem
Main system class managing all airline operations.

#### Public Methods

##### `void run()`
Starts the airline reservation system.

##### `void addNewPassenger()`
Handles new passenger registration.

##### `void displayPassengerInfo()`
Shows information for a specific passenger.

##### `void modifyRecord()`
Modifies existing passenger records.

##### `void cancelTicket()`
Handles ticket cancellation.

#### Private Methods

##### `std::string getAirlineName(Airline airline) const`
Returns airline name from enum.

##### `std::string getDestinationName(Route route) const`
Returns destination name from enum.

##### `std::string getFileName(Airline airline) const`
Returns data file name for specified airline.

### Visual Namespace
Provides visual effects and formatting utilities.

#### Methods

##### `void printWithDelay(const std::string& text, int delay_ms = 50)`
Prints text with animation effect.

##### `std::string center(const std::string& text, int width = 50)`
Centers text in given width.

## Data Storage

Data is stored in airline-specific binary files:
- Ind.dat (Air India)
- Brit.dat (British Airways)
- Gulf.dat (Gulf Airways)
- Unit.dat (United Airlines)
- Luf.dat (Lufthansa)

