#ifndef TESTPATIENT_H
#define TESTPATIENT_H

#include "Patient.h"

class TestPatient : public Patient {
public:
    TestPatient();
    char type() const;
    std::ostream& write(std::ostream& os) const override;
    std::istream& read(std::istream& is) override;
};

#endif // TESTPATIENT_H
