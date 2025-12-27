#include "AccountType.h"

// Base class constructor
AccountType::AccountType(string name, double limit) : typeName(name), dailyWithdrawalLimit(limit) {}

// Virtual destructor
AccountType::~AccountType() {}

// Bronze Account constructor
Bronze::Bronze() : AccountType("Bronze", 100000) {}

// Gold Account constructor
Gold::Gold() : AccountType("Gold", 500000) {}

// Business Account constructor
Business::Business() : AccountType("Business", 20000000) {}