#include "Patient.h"
#include "IOAble.h"
#include "Ticket.h"
#include <iomanip>
#include <limits>
#include <sstream>
#include <cstring>
#include <string>

Patient::Patient(int ticketNumber, char type) : name(nullptr), ohip(0), ticket(ticketNumber), patientType(type) {}

Patient::Patient(const Patient& other) : name(nullptr), ohip(0), ticket(other.ticket), patientType(other.patientType), symptoms(other.symptoms) {
    if (other.name != nullptr) {
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);
    }
    ohip = other.ohip;
}

Patient& Patient::operator=(const Patient& other) {
    if (this != &other) {
        delete[] name;
        if (other.name != nullptr) {
            name = new char[strlen(other.name) + 1];
            strcpy(name, other.name);
        } else {
            name = nullptr;
        }
        ohip = other.ohip;
        ticket = other.ticket;
        patientType = other.patientType;
        symptoms = other.symptoms;
    }
    return *this;
}

Patient::~Patient() {
    delete[] name;
}

char Patient::type() const {
    return patientType;
}

bool Patient::operator==(const Patient& other) const {
    return patientType == other.patientType;
}

bool Patient::operator==(char type) const {
    return patientType == type;
}

void Patient::setArrivalTime() {
    ticket.resetTime();
}

int Patient::ticketTime() const {
    return ticket.time();
}

int Patient::number() const {
    return ticket.number();
}

Patient::operator bool() const {
    return name != nullptr && ohip >= 100000000 && ohip <= 999999999;
}

Patient::operator const char*() const {
    return name;
}

std::string Patient::time() const {
    int totalMinutes = ticket.time();
    int hours = totalMinutes / 60;
    int minutes = totalMinutes % 60;
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << hours << ":" << std::setw(2) << std::setfill('0') << minutes;
    return oss.str();
}

long Patient::getOHIP() const {
    return ohip;
}

std::ostream& Patient::write(std::ostream& os) const {
    if (!name) {
        os << "Invalid Patient Record" << std::endl;
    } else if (&os == &std::cout) {
        os << ticket << std::endl;
        os << name << ", OHIP: " << ohip << std::endl;
    } else if (&os == &std::clog) {
        os << std::setw(53) << std::left << std::setfill('.') << name << std::setw(0) << std::right << ohip << "    " << ticket.number()<< " " << std::setw(2) << std::setfill('0') << ticket.time() / 60 << ":" << std::setw(2) << std::setfill('0') << ticket.time() % 60;
    } else {
        os << patientType << ',' << name << ',' << ohip << ',';
        ticket.write(os);

        if (patientType == 'T') {
            // If patient type is 'T' (Triage), include symptoms
            os  << symptoms;
        }
    }
    return os;
}


void Patient::setSymptoms(const std::string& newSymptoms) {
    symptoms = newSymptoms;
}

std::string Patient::getSymptoms() const {
    return symptoms;
}

std::istream& Patient::read(std::istream& is) {
    delete[] name;
    name = nullptr;
    char tempName[51];

    if (&is == &std::cin) {
        std::cout << "Name: ";
        is.get(tempName, 51, '\n');
        is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } else {
        is.get(tempName, 51, ',');
        is.ignore(std::numeric_limits<std::streamsize>::max(), ',');
    }
    name = new char[strlen(tempName) + 1];
    strcpy(name, tempName);

    if (&is == &std::cin) {
        std::cout << "OHIP: ";
        while (!(is >> ohip) || ohip < 100000000 || ohip > 999999999) {
            if (is.fail()) {
                std::cout << "Bad integer value, try again: ";
                is.clear();
                is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            } else {
                std::cout << "Invalid value entered, retry [100000000 <= value <= 999999999]: ";
            }
        }
        is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } else {
        is >> ohip;
        is.ignore(std::numeric_limits<std::streamsize>::max(), ',');
    }

    if (&is != &std::cin) {
        is >> ticket;
        if (patientType == 'T') {
            // Read symptoms for triage patients
            std::getline(is, symptoms, '\n');
        }
    }

    return is;
}
