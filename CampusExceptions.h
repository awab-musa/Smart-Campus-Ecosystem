#pragma once
#include <stdexcept>
#include <string>
using namespace std;

class CampusException : public runtime_error {
public:
    explicit CampusException(const string& msg) : runtime_error(msg) {}
};

class InsufficientStockException : public CampusException {
public:
    InsufficientStockException(const string& itemName, int available, int requested)
        : CampusException("Insufficient stock for '" + itemName +
                          "'. Available: " + to_string(available) +
                          ", Requested: " + to_string(requested)) {}
};

class InvalidCardException : public CampusException {
public:
    explicit InvalidCardException(const string& detail = "Card number must be 16 digits and contain only numeric characters.")
        : CampusException("Invalid card: " + detail) {}
};

class FileNotFoundException : public CampusException {
public:
    explicit FileNotFoundException(const string& filename)
        : CampusException("File not found: '" + filename + "'") {}
};

class FileWriteException : public CampusException {
public:
    explicit FileWriteException(const string& filename)
        : CampusException("Failed to write to file: '" + filename + "'") {}
};

class InvalidInputException : public CampusException {
public:
    explicit InvalidInputException(const string& msg)
        : CampusException("Invalid input: " + msg) {}
};

class ResourceNotFoundException : public CampusException {
public:
    explicit ResourceNotFoundException(const string& id)
        : CampusException("Resource with ID '" + id + "' not found.") {}
    explicit ResourceNotFoundException(int id)
        : CampusException("Resource with ID " + to_string(id) + " not found.") {}
};

class StockLimitException : public CampusException {
public:
    StockLimitException(const string& itemName, int stock, int qty)
        : CampusException("Stock limit exceeded for '" + itemName +
                          "'. In stock: " + to_string(stock) +
                          ", Requested: " + to_string(qty)) {}
};
