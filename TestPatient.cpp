#include "TestPatient.h"

static int nextTestTicket = 1;

TestPatient::TestPatient() : Patient(nextTestTicket++, 'C') {}

char TestPatient::type() const {
    return 'C';
}

std::ostream& TestPatient::write(std::ostream& os) const {
    if (&os == &std::cout)
        os << "Contagion TEST" << std::endl;
    return Patient::write(os);
}

std::istream& TestPatient::read(std::istream& is) {
    Patient::read(is);
    if (&is != &std::cin)
        nextTestTicket = this->number() + 1;
    return is;
}
