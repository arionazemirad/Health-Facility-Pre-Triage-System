/*-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.*/
#include "Time.h"
#include "Utils.h" // For Utils module
#include <iomanip>
#include <sstream>

namespace seneca {
    Time::Time(unsigned int min) : minutes(min) {}

    Time& Time::reset() {
        if (seneca::debug) {
            minutes = U.getTime(); // Call getTime() on the Utils instance
        }
        else {
            minutes = 0;
        }
        return *this;
    }


    void Time::write(std::ostream& os) const {
        unsigned int hours = minutes / 60;
        unsigned int mins = minutes % 60;
        os  << std::setfill('0') << std::setw(2) << hours << ":" << std::setw(2) << mins;
    }



    void Time::read(std::istream& is) {
        unsigned int hours = 0, mins = 0;
        char colon;

        // Read hours
        is >> hours;

        // Check for the presence of colon
        if (is.peek() != ':') {
            is.setstate(std::ios::failbit);
            return;
        }
        is >> colon;

        // Check if colon is followed by minutes
        if (!(is >> mins) || colon != ':') {
            is.setstate(std::ios::failbit);
            return;
        }

        // Check if the minutes are greater than or equal to 60
        if (mins >= 60) {
            hours += mins / 60; // Add the extra hours
            mins %= 60; // Adjust the minutes
        }

        // Convert hours and mins to minutes
        minutes = hours * 60 + mins;

    }













    Time::operator unsigned int() const {
        return minutes;
    }

    Time& Time::operator*=(int val) {
        minutes *= val;
        return *this;
    }

    Time& Time::operator-=(const Time& D) {
        int diff = minutes - D.minutes;
        if (diff < 0) {
            diff += 24 * 60; // add 24 hours in minutes
        }
        minutes = diff;
        return *this;
    }

    Time Time::operator-(const Time& T) const {
        int diff = minutes - T.minutes;
        if (diff < 0) {
            diff += 24 * 60; // add 24 hours in minutes
        }
        return Time(diff);
    }

    std::ostream& operator<<(std::ostream& os, const Time& time) {
        time.write(os);
        return os;
    }

    std::istream& operator>>(std::istream& is, Time& time) {
        time.read(is);
        return is;
    }
}
