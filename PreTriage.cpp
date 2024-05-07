#include <iostream>
#include <fstream>
#include <cstring>
#include "PreTriage.h"
#include "Patient.h"
#include "Time.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
using namespace std;

PreTriage::PreTriage(const char* dataFilename) {
    m_dataFilename = new char[strlen(dataFilename) + 1];
    strcpy(m_dataFilename, dataFilename);
    m_averCovidWait = seneca::Time(15);
    m_averTriageWait = seneca::Time(5);
    m_lineupSize = 0;
    load();
}

PreTriage::~PreTriage() {
    save();
    delete[] m_dataFilename;
    for (int i = 0; i < m_lineupSize; ++i) {
        if (m_lineup[i] != nullptr) { // Check if the pointer is valid
            delete m_lineup[i];
            m_lineup[i] = nullptr; // Reset the pointer after deletion
        }
    }
}


void PreTriage::run() {
    int selection;
    while (true) {
        cout << "\nGeneral Healthcare Facility Pre-Triage Application\n"
             << "1- Register\n"
             << "2- Admit\n"
             << "3- View Lineup\n"
             << "0- Exit\n"
             << "> ";
        cin >> selection;
        cin.ignore(1000, '\n');

        switch (selection) {
            case 1:
                reg();
                break;
            case 2:
                admit();
                break;
            case 3:
                lineup();
                break;
            case 0:
                return;
            default:
                cout << "Invalid selection, please try again." << endl;
                break;
        }
    }
}

void PreTriage::reg() {
    if (m_lineupSize >= maxNoOfPatients) {
        cout << "Line up full!" << endl;
        return;
    }

    int selection;
    Patient* newPatient = nullptr;

    cout << "   Select Type of Registration:\n"
         << "   1- Covid Test\n"
         << "   2- Triage\n"
         << "   0- Exit\n"
         << "   > ";
    cin >> selection;
    cin.ignore(1000, '\n');

    switch (selection) {
        case 0:
            return;
        case 1:
            newPatient = new Patient(m_lineupSize + 1, 'C');
            break;
        case 2:
            newPatient = new Patient(m_lineupSize + 1, 'T');
            break;
        default:
            cout << "Invalid selection, please try again." << endl;
            return;
    }

    newPatient->setArrivalTime();
    cout << "Please enter patient information: " << endl;
    newPatient->read(cin);
    cout << "\n******************************************\n";
    newPatient->write(cout);
    cout << "\nEstimated Wait Time: " << getWaitTime(*newPatient) << endl;
    cout << "******************************************\n\n";

    m_lineup[m_lineupSize++] = newPatient;
}

void PreTriage::admit() {
    int selection;
    char type;

    cout << "   Select Type of Admittance:\n"
         << "   1- Covid Test\n"
         << "   2- Triage\n"
         << "   0- Exit\n"
         << "   > ";
    cin >> selection;
    cin.ignore(1000, '\n');

    switch (selection) {
        case 0:
            return;
        case 1:
            type = 'C';
            break;
        case 2:
            type = 'T';
            break;
        default:
            cout << "Invalid selection, please try again." << endl;
            return;
    }

    int index = indexOfFirstInLine(type);

    if (index == -1) {
        cout << "Lineup is empty!" << endl;
        return;
    }

    std::string callTime = m_lineup[index]->time(); // Declaration and initialization of callTime

    cout << "******************************************\n"
         << "Call time: [" << callTime << "]\n"  // Display the call time
         << "Calling at for Contagion TEST\n";
    m_lineup[index]->write(cout);
    cout << "******************************************\n\n";

    setAverageWaitTime(*m_lineup[index]);
    removeDynamicElement(m_lineup, index, m_lineupSize);
}

void PreTriage::lineup() const {
    int selection;
    cout << "   Select The Lineup:\n"
         << "   1- Contagion Test\n"
         << "   2- Triage\n"
         << "   0- Exit\n"
         << "   > ";
    cin >> selection;
    cin.ignore(1000, '\n');


    if (selection == 1 || selection == 2) {
        char lineupType = (selection == 1) ? 'C' : 'T';
        int row = 1; // Initialize row counter
        std::cout << "Row - Patient name                                          OHIP     Tk #  Time" << std::endl
                  << "-------------------------------------------------------------------------------" << std::endl;

        for (int i = 0; i < m_lineupSize; ++i) {
            if (m_lineup[i]->type() == lineupType) {
                std::string name = m_lineup[i]->operator const char*();
                long ohip_long = m_lineup[i]->getOHIP(); // Assuming getOHIP() returns a long
                std::string ohip = std::to_string(ohip_long); // Convert long to string
                if (ohip.length() > 9)
                    ohip = ohip.substr(0, 9); // Trim to 9 characters
                else if (ohip.length() < 9)
                    ohip = ohip + std::string(9 - ohip.length(), ' '); // Pad with spaces if less than 9 characters
                int number = m_lineup[i]->number();
                std::string time = m_lineup[i]->time();

                cout << setw(1) << row << "   - "
                     << setw(48) << left << name // Adjusted setw() value
                     << setw(14)  << right << ohip // Fill between name and OHIP with '.'
                     << setw(5) << right << number // Adjusted setw() value
                     << setw(6) << time << endl; // Adjusted setw() value
                row++;
            }
        }
    } else if (selection == 0) {
        return;
    } else {
        cout << "Invalid selection, please try again." << endl;
    }

    cout << "-------------------------------------------------------------------------------" << endl;
}


void PreTriage::load() {
    cout << "Loading data..." << endl;

    ifstream file(m_dataFilename);
    if (!file) {
        //cout << "Loading data..." << endl;
        cout << "No data or bad data file!" << endl;
        return;
    }

    // Read the average wait times
    file >> m_averCovidWait;
    file.ignore();
    file >> m_averTriageWait;
    file.ignore();

    Patient* newPatient = nullptr;
    int recordsRead = 0;

    // Read patient records
    while (m_lineupSize < maxNoOfPatients && file >> std::ws && !file.eof()) {
        char type;
        file >> type;
        file.ignore();

        if (type == 'C' || type == 'T') {
            if (type == 'C')
                newPatient = new Patient(0, 'C');
            else if (type == 'T')
                newPatient = new Patient(0, 'T');

            if (newPatient) {
                file >> *newPatient;
                m_lineup[m_lineupSize++] = newPatient;
                ++recordsRead;
            }
        }
    }

    file.close();

    // Print dynamic count of records imported
    if (recordsRead > 0) {
        cout << recordsRead << " Records imported..." << endl;
    } else{
        cout << "No data or bad data file!" << endl;
    }
}








void PreTriage::save() const {
    int contagionTestsSaved = 0;
    int triageRecordsSaved = 0;

    cout << "Saving lineup..." << endl;

    ofstream file(m_dataFilename);
    if (!file) {
        cout << "Failed to create data file!" << endl;
        return;
    }

    file << m_averCovidWait << ',' << m_averTriageWait << endl;
    for (int i = 0; i < m_lineupSize; ++i) {
        m_lineup[i]->write(file);
        file << endl;

        if (m_lineup[i]->type() == 'C') {
            contagionTestsSaved++;
        } else if (m_lineup[i]->type() == 'T') {
            triageRecordsSaved++;
        }
    }

    cout << contagionTestsSaved << " Contagion Tests and " << triageRecordsSaved << " Triage records were saved!" << endl;
}

const seneca::Time PreTriage::getWaitTime(const Patient& p) const {
    return p.type() == 'C' ? m_averCovidWait * (p.number() - 1) : m_averTriageWait * (p.number() - 1);
}

void PreTriage::setAverageWaitTime(Patient& p) {
    seneca::Time currentTime;
    int ticketTime = p.ticketTime();
    seneca::Time ticketTimeObj(ticketTime);
    if (p.type() == 'C') {
        m_averCovidWait = ((currentTime - ticketTimeObj) + (m_averCovidWait * (p.number() - 1))) / p.number();
    } else {
        m_averTriageWait = ((currentTime - ticketTimeObj) + (m_averTriageWait * (p.number() - 1))) / p.number();
    }
}

void PreTriage::removeDynamicElement(Patient* array[], int index, int& size) {
    delete array[index];
    for (int i = index; i < size - 1; ++i) {
        array[i] = array[i + 1];
    }
    --size;
}

int PreTriage::indexOfFirstInLine(char type) const {
    for (int i = 0; i < m_lineupSize; ++i) {
        if (m_lineup[i]->type() == type)
            return i;
    }
    return -1;
}




