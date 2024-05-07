#ifndef TRIAGEPATIENT_H
#define TRIAGEPATIENT_H

#include "Patient.h"

class TriagePatient : public Patient {
private:
    char* symptoms;
public:
    TriagePatient();
    TriagePatient(const TriagePatient& other);
    TriagePatient& operator=(const TriagePatient& other);
    ~TriagePatient();
    char type() const;
    std::ostream& write(std::ostream& os) const override;
    std::istream& read(std::istream& is) override;
};

#endif // TRIAGEPATIENT_H
