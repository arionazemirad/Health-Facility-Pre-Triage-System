/*-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.*/
#ifndef SENECA_MENU_H
#define SENECA_MENU_H

#include <iostream>

namespace seneca {
    class Menu {
        const char* m_text; // Content of the menu
        int m_numOptions; // Number of options in the menu
        int m_numTabs; // Number of indentation tabs

    public:
        // Constructor and Destructor
        Menu(const char* menuContent, int numberOfTabs = 0);
        ~Menu();

        // Copy and assignment - prevent copying and assignment
        Menu(const Menu& other) = delete;
        Menu& operator=(const Menu& other) = delete;

        // Display menu and receive selection
        int& operator>>(int& Selection);

        // Helper methods
        void display() const;
        int getInput() const;
    };
}

#endif //SENECA_MENU_H
