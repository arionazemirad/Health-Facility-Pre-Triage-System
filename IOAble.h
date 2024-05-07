/*-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.*/
#ifndef IOABLE_H
#define IOABLE_H

#include <iostream>

namespace seneca {

    class IOAble {
    public:
        // Pure virtual functions
        virtual std::ostream& write(std::ostream& os) const = 0;
        virtual std::istream& read(std::istream& is) = 0;

        // Virtual destructor
        virtual ~IOAble() {}

        // Insertion and Extraction helper operator overloads
        friend std::ostream& operator<<(std::ostream& os, const IOAble& obj) {
            return obj.write(os);
        }

        friend std::istream& operator>>(std::istream& is, IOAble& obj) {
            return obj.read(is);
        }
    };
}

#endif // IOABLE_H
