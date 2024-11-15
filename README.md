# Credit Card Management System

This repository contains a project focused on building a simple Credit Card Management System in C++. The project aims to simulate some of the basic features of a credit card system, such as managing user accounts, tracking transactions, and handling credit limits. The goal is to gain a deeper understanding of financial application concepts and C++ programming.

## Overview

### Features

1. **Account Creation**:
   - Users can create a credit card account with basic information, such as **Name**, **Card Number**, **Credit Limit**, and **Balance**.

2. **Transaction Handling**:
   - Users can make **purchases** using the credit card, and the system will track the balance and verify if the transaction can be processed based on the available credit limit.
   - **Payments** can also be made to reduce the outstanding balance.

3. **Credit Limit Management**:
   - The system ensures that transactions do not exceed the credit limit.
   - Users can request an **increase** or **decrease** in their credit limit.

4. **Transaction History**:
   - A log of transactions is maintained, including **purchases** and **payments**, allowing users to review their transaction history.

## Requirements

- **Software**:
  - C++ Compiler (e.g., GCC)
  - Text editor or IDE for writing C++ code

## Setup Instructions

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/aalexanderfc/CCARD.git
   cd CCARD
   ```

2. **Compile the Code**:
   - Use a C++ compiler to compile the project:
   ```bash
   g++ credit_card_system.cpp -o credit_card_system
   ```

3. **Run the Program**:
   - Execute the compiled program:
   ```bash
   ./credit_card_system
   ```

## How It Works

- **Account Creation**: Users can create an account by providing details such as name, card number, and credit limit. The details are stored for future transactions.
- **Purchases and Payments**: Users can make purchases as long as they do not exceed their credit limit. Payments can also be made to reduce the balance.
- **Credit Management**: The system allows users to request a change in their credit limit, which is subject to certain conditions.

## Example Code

Here is an example snippet of the C++ code for handling transactions:

```cpp
#include <iostream>
#include <string>
#include <vector>

class CreditCard {
    std::string cardNumber;
    double creditLimit;
    double balance;
    // Constructor and other methods
};

void makePurchase(CreditCard& card, double amount) {
    if (card.getAvailableCredit() >= amount) {
        card.updateBalance(amount);
        std::cout << "Purchase approved." << std::endl;
    } else {
        std::cout << "Purchase declined. Not enough credit." << std::endl;
    }
}
```

For detailed code, please refer to the `credit_card_system.cpp` file in the repository.

## Limitations

- The project is a simple simulation of a credit card system and may lack the robustness needed for a real-world financial application.
- More advanced features, such as interest calculation or fraud detection, are not implemented in this version.

## Author

Developed by Alexander. Feel free to reach out for more information or collaboration opportunities.

