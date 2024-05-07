/*-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.*/
#ifndef SENECA_TIME_H
#define SENECA_TIME_H
#include <ctime>
#include <iostream>

namespace seneca {
    class Time {
    private:
        unsigned int minutes;

    public:
        Time(unsigned int min = 0u);

        Time& reset();

        void write(std::ostream& os) const;

        void read(std::istream& is);

        operator unsigned int() const;

        Time& operator*=(int val);

        Time& operator-=(const Time& D);

        Time operator-(const Time& T) const;
    };

    std::ostream& operator<<(std::ostream& os, const Time& time);

    std::istream& operator>>(std::istream& is, Time& time);
}

#endif //SENECA_TIME_H
