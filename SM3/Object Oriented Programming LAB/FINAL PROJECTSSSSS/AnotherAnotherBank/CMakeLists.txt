cmake_minimum_required(VERSION 3.29)
project(AnotherAnotherBank)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories("Header Files")
include_directories("Main File")
include_directories("Source Files")

add_executable(AnotherAnotherBank
        "Header Files/AccountType.h"
        "Header Files/BankingEmployee.h"
        "Header Files/Bronze.h"
        "Header Files/Business.h"
        "Header Files/Card.h"
        "Header Files/CompanyClient.h"
        "Header Files/Gold.h"
        "Header Files/Transaction.h"
        "Header Files/User.h"
        "Header Files/UserClient.h"
        "Header Files/UserManager.h"
        "Main File/main.cpp"
        "Source Files/AccountType.cpp"
        "Source Files/BankingEmployee.cpp"
        "Source Files/Bronze.cpp"
        "Source Files/Business.cpp"
        "Source Files/Card.cpp"
        "Source Files/CompanyClient.cpp"
        "Source Files/Gold.cpp"
        "Source Files/Transaction.cpp"
        "Source Files/User.cpp"
        "Source Files/UserClient.cpp")
