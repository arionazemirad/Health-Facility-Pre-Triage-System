cmake_minimum_required(VERSION 3.26)
project(ms5_1_new)

set(CMAKE_CXX_STANDARD 17)

add_executable(ms5_1_new main.cpp
        IOAble.cpp
        Patient.cpp
        PreTriage.cpp
        TestPatient.cpp
        Ticket.cpp
        Time.cpp
        TriagePatient.cpp
        Utils.cpp
        Menu.cpp)
