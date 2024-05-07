/*-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.*/
#include <iostream>
#include "Menu.h"
#include <cstring>
#include <sstream>
namespace seneca {
    Menu::Menu(const char* menuContent, int numberOfTabs)
            : m_text(nullptr), m_numOptions(0), m_numTabs(numberOfTabs) {
        if (menuContent) {
            m_text = new char[strlen(menuContent) + 1];
            strcpy(const_cast<char*>(m_text), menuContent);
            // Count number of options
            const char* ptr = m_text;
            while (*ptr) {
                if (*ptr == '\n') m_numOptions++;
                ptr++;
            }
        }
    }

    Menu::~Menu() {
        delete[] m_text;
    }

    int& Menu::operator>>(int& Selection) {
        display();
        Selection = getInput();
        return Selection;
    }

    void Menu::display() const {
        if (!m_text) return;

        // Split the menu content into lines
        std::istringstream iss(m_text);
        std::string line;
        while (std::getline(iss, line)) {
            for (int i = 0; i < m_numTabs; ++i) std::cout << "   "; // Print indentation tabs
            std::cout << line << std::endl;
        }

        for (int i = 0; i < m_numTabs; ++i) std::cout << "   "; // Print additional spaces for alignment
        std::cout << "0- Exit\n";
        for (int i = 0; i < m_numTabs; ++i) std::cout << "   "; // Print additional spaces for alignment
        std::cout << "> ";
    }



    int Menu::getInput() const {
        int input;
        while (true) {
            std::cin >> input;
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                std::cout << "Bad integer value, try again: ";
            } else if (input < 0 || input > m_numOptions) {
                std::cout << "Invalid value enterd, retry[0 <= value <= " << m_numOptions << "]: ";
            } else if (!std::cin.eof() && std::cin.peek() != '\n') {
                std::cout << "Only enter an integer, try again: ";
                std::cin.clear();
                std::cin.ignore(1000, '\n');
            } else {
                break;
            }
        }
        return input;
    }
}
