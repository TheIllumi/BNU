//bank.h
#pragma once
#ifndef BANK_H
#define BANK_H

#include <string>

bool login(const std::string& username, const std::string& password);
void signUp(const std::string& username, const std::string& password);

#endif // BANK_H