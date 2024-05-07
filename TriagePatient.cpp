#include "TriagePatient.h"
#include <cstring>
#include <limits>


int nextTriageTicket = 1;

TriagePatient::TriagePatient() : Patient(nextTriageTicket++, 'T'), symptoms(nullptr) {}

TriagePatient::TriagePatient(const TriagePatient& other) : Patient(other), symptoms(nullptr) {
    if (other.symptoms) {
        symptoms = new char[strlen(other.symptoms) + 1];
        strcpy(symptoms, other.symptoms);
    }
}

TriagePatient& TriagePatient::operator=(const TriagePatient& other) {
    if (this != &other) {
        Patient::operator=(other);
        delete[] symptoms;
        symptoms = nullptr;
        if (other.symptoms) {
            symptoms = new char[strlen(other.symptoms) + 1];
            strcpy(symptoms, other.symptoms);
        }
    }
    return *this;
}

TriagePatient::~TriagePatient() {
    delete[] symptoms;
}

char TriagePatient::type() const {
    return 'T';
}

std::ostream& TriagePatient::write(std::ostream& os) const {
    if (&os == &std::cout) {
        os << "TRIAGE" << std::endl;
        Patient::write(os);
        if (symptoms) {
            os << "Symptoms: " << symptoms << std::endl;
        }
    } else if (&os == &std::clog) {
        Patient::write(os);
    } else {
        Patient::write(os);
        if (symptoms) {
            os << "," << symptoms;
        }
    }
    return os;
}

std::istream& TriagePatient::read(std::istream& is) {
    Patient::read(is);
    delete[] symptoms;
    symptoms = nullptr;
    if (&is == &std::cin) {
        std::cout << "Symptoms: ";
        char tempSymptoms[512];
        is.get(tempSymptoms, 512, '\n');
        is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        symptoms = new char[strlen(tempSymptoms) + 1];
        strcpy(symptoms, tempSymptoms);
    } else {
        char tempSymptoms[512];
        is.ignore();
        is.get(tempSymptoms, 512, '\n');
        is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        symptoms = new char[strlen(tempSymptoms) + 1];
        strcpy(symptoms, tempSymptoms);
        nextTriageTicket = this->number() + 1;
    }
    return is;
}
