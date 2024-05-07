#ifndef PATIENT_H
#define PATIENT_H

#include <iostream>
#include <string>
#include "IOAble.h" // Include IOAble.h
#include "Ticket.h" // Include Ticket.h
#include "Time.h"
#include <string>

class Patient : public seneca::IOAble {
private:
    char* name;
    int ohip;
    seneca::Ticket ticket;
    char patientType; // Add a member variable to represent patient type
    std::string symptoms;

public:
    Patient(int ticketNumber, char type); // Update constructor to include patient type
    Patient(const Patient& other);
    Patient& operator=(const Patient& other);
    ~Patient();

    char type() const; // Modify type() function to return patient type
    bool operator==(char type) const;
    bool operator==(const Patient& other) const;
    void setSymptoms(const std::string& newSymptoms);
    std::string getSymptoms() const;
    void setArrivalTime();
    int ticketTime() const;
    int number() const;
    std::string time() const;
    long getOHIP() const; // Method to retrieve OHIP number

    operator bool() const;
    operator const char*() const;

    std::ostream& write(std::ostream& os) const override;
    std::istream& read(std::istream& is) override;
};

#endif // PATIENT_H
