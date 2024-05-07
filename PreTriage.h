#ifndef PRETRIAGE_H
#define PRETRIAGE_H

#include "Patient.h"

const int maxNoOfPatients = 100;
class PreTriage {
    Patient* m_lineup[maxNoOfPatients]{};
    char* m_dataFilename = nullptr;
    int m_lineupSize = 0;
    seneca::Time m_averCovidWait;
    seneca::Time m_averTriageWait;

    const seneca::Time getWaitTime(const Patient& p) const;
    void setAverageWaitTime(Patient& p);
    void removeDynamicElement(Patient* array[], int index, int& size);
    int indexOfFirstInLine(char type) const;
    void load();
    void save() const;
    void reg();
    void admit();
    void validate();
    void sort();
    bool loadPatients();
    int indexOfFirstInLine(int type) const;
public:
    PreTriage(const char* dataFilename);
    ~PreTriage();
    void run(void);

    void lineup() const;
};

#endif // !PRETRIAGE_H
