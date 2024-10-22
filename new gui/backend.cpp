#include "ATMBackend.h"
#include <fstream>
#include <ctime>
#include <algorithm>

// Function for encrypting and decrypting PINs
std::string encryptDecrypt(const std::string& input, char key) {
    std::string output = input;
    for (size_t i = 0; i < input.length(); i++) {
        output[i] ^= key;  // XOR encryption
    }
    return output;
}

// Save account data to file
void save(const std::vector<ATMAccount>& accounts) {
    std::ofstream outFile("atmAccounts.txt", std::ios::trunc);
    if (outFile.is_open()) {
        for (const ATMAccount& account : accounts) {
            outFile << account.acctNum << std::endl;
            outFile << account.acctName << std::endl;
            outFile << account.midName << std::endl;
            outFile << account.surname << std::endl;
            outFile << account.suffix << std::endl;
            outFile << account.username << std::endl;
            outFile << account.bday << std::endl;
            outFile << account.contactNum << std::endl;
            outFile << account.emerContactNum << std::endl;
            outFile << account.balance << std::endl;
            outFile << account.pinCode << std::endl;
            outFile << account.acctType << std::endl;
        }
        outFile.close();
    }
}

// Change the PIN
bool changePIN(ATMAccount& account, const std::string& currentPIN, const std::string& newPIN1, const std::string& newPIN2, std::vector<ATMAccount>& accounts) {
    std::string encryptedCurrentPIN = encryptDecrypt(currentPIN);
    if (encryptedCurrentPIN == account.pinCode) {
        if (newPIN1 == newPIN2 && newPIN1.length() == 6 && std::all_of(newPIN1.begin(), newPIN1.end(), ::isdigit)) {
            account.pinCode = encryptDecrypt(newPIN1);  // Encrypt the new PIN
            save(accounts);  // Save the updated accounts list
            return true;
        }
        else {
            return false;  // New PINs don't match or are not valid
        }
    }
    else {
        return false;  // Current PIN is incorrect
    }
}

// Get the last N transactions from the account
std::vector<std::string> getTransactionStatement(const ATMAccount& account, int numberOfTransactions) {
    std::vector<std::string> transactions;
    if (account.transacHistory.empty()) {
        return transactions;  // Return an empty list if no transaction history
    }
    int numTransac = account.transacHistory.size();
    int showTransac = (numTransac < numberOfTransactions) ? numTransac : numberOfTransactions;

    for (int i = 0; i < showTransac; ++i) {
        transactions.push_back(account.transacHistory[numTransac - 1 - i]);
    }
    return transactions;
}

// Validate login
ATMAccount* login(std::vector<ATMAccount>& accounts, const std::string& username, const std::string& acctNum, const std::string& enteredPin) {
    ATMAccount* loggedInAccount = nullptr;

    for (ATMAccount& account : accounts) {
        if (account.username == username && account.acctNum == acctNum) {
            loggedInAccount = &account;
            break;
        }
    }

    if (loggedInAccount != nullptr) {
        std::string encryptedEnteredPin = encryptDecrypt(enteredPin);
        if (encryptedEnteredPin == loggedInAccount->pinCode) {
            return loggedInAccount;
        }
    }
    return nullptr;  // Login failed
}

// Check if a value (account number or username) is unique
bool isUnique(const std::vector<ATMAccount>& accounts, const std::string& value) {
    for (const ATMAccount& account : accounts) {
        if (account.acctNum == value || account.username == value) {
            return false;
        }
    }
    return true;
}

// Generate a unique account number
std::string uniqueAcctNum(const std::vector<ATMAccount>& accounts) {
    srand(time(0));
    std::string acctNum;
    bool unique = false;
    int attempts = 0;

    while (!unique && attempts < 100) {
        int ranNum = 10000 + rand() % 90000;
        acctNum = std::to_string(ranNum);
        unique = isUnique(accounts, acctNum);
        attempts++;
    }

    return acctNum;
}

// Enrollment function
ATMAccount enroll(std::vector<ATMAccount>& accounts, const std::string& acctName, const std::string& midName, const std::string& surname,
    const std::string& suffix, const std::string& username, const std::string& bday, const std::string& contactNum,
    const std::string& emerContactNum, const std::string& acctType, double initialDeposit, const std::string& pinCode) {

    ATMAccount newAccount;
    newAccount.acctNum = uniqueAcctNum(accounts);
    newAccount.acctName = acctName;
    newAccount.midName = midName;
    newAccount.surname = surname;
    newAccount.suffix = suffix;
    newAccount.username = username;
    newAccount.bday = bday;
    newAccount.contactNum = contactNum;
    newAccount.emerContactNum = emerContactNum;
    newAccount.acctType = acctType;
    newAccount.balance = initialDeposit;
    newAccount.pinCode = encryptDecrypt(pinCode);  // Encrypt the PIN

    accounts.push_back(newAccount);
    save(accounts);  // Save the new account to file

    return newAccount;
}

// Withdraw money from an account
bool withdraw(ATMAccount& currentAccount, double amount) {
    if (amount > currentAccount.balance) {
        return false;  // Insufficient funds
    }
    currentAccount.balance -= amount;
    return true;
}

// Deposit money into an account
void deposit(ATMAccount& currentAccount, double amount) {
    currentAccount.balance += amount;
}
