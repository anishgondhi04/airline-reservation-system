#pragma once
#include <stdexcept>

/********************************************************
 * Custom Exception Class
 * Handles airline-specific exceptions with meaningful
 * error messages
 ********************************************************/
class AirlineException : public std::runtime_error {
    using std::runtime_error::runtime_error;
};