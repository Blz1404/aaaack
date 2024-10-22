#ifndef ATM_BACKEND_H
#define ATM_BACKEND_H

#include <string>
#include <vector>

// Function for encrypting and decrypting PINs
std::string encryptDecrypt(const std::string& input, char key = 'K');

// Struct for ATMAccount
struct ATMAccount {
    std::string acctNum;
    std::string acctName;
    std::string midName;
    std::string surname;
    std::string suffix;
    std::string username;
    std::string bday;
    std::string contactNum;
    std::string emerContactNum;
    std::string acctType;
    double balance;
    std::string pinCode;
    std::vector<std::string> transacHistory;
};

// Function to save account data to file
void save(const std::vector<ATMAccount>& accounts);

// Function to change the PIN
bool changePIN(ATMAccount& account, const std::string& currentPIN, const std::string& newPIN1, const std::string& newPIN2, std::vector<ATMAccount>& accounts);

// Function to get the last N transactions from the account
std::vector<std::string> getTransactionStatement(const ATMAccount& account, int numberOfTransactions = 10);

// Function to validate login
ATMAccount* login(std::vector<ATMAccount>& accounts, const std::string& username, const std::string& acctNum, const std::string& enteredPin);

// Function to check if a value (account number or username) is unique
bool isUnique(const std::vector<ATMAccount>& accounts, const std::string& value);

// Generate a unique account number
std::string uniqueAcctNum(const std::vector<ATMAccount>& accounts);

// Backend enrollment function
ATMAccount enroll(std::vector<ATMAccount>& accounts, const std::string& acctName, const std::string& midName, const std::string& surname,
    const std::string& suffix, const std::string& username, const std::string& bday, const std::string& contactNum,
    const std::string& emerContactNum, const std::string& acctType, double initialDeposit, const std::string& pinCode);

// Function to withdraw money from an account
bool withdraw(ATMAccount& currentAccount, double amount);

// Function to deposit money into an account
void deposit(ATMAccount& currentAccount, double amount);

#endif // ATM_BACKEND_H
#pragma once
