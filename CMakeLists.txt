cmake_minimum_required(VERSION 3.29)
project(HotelSystem C)

set(CMAKE_C_STANDARD 11)

add_executable(HotelSystem src/main.c
        src/DateProcessing.c
        src/DateProcessing.h
        src/Utility.c
        src/Utility.h
        src/FileIO.c
        src/FileIO.h
        src/Query.c
        src/Query.h
        src/CheckInOut.c
        src/CheckInOut.h
        src/ReservationProcessMenus.c
        src/ReservationProcessMenus.h
        src/DataValidation.c
        src/DataValidation.h
        src/AdditionalMenus.c
        src/AdditionalMenus.h
        src/Includes.h
        src/Structures.h)
