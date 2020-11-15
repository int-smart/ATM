#ifndef _BANK_H
#include <iostream>
#include <map>
#include <stdlib.h>
#include <string>
#include <vector>
class Transaction {
private:
  uint64_t amount;
  bool type; // 0-deposit, 1-withdraw
  uint64_t atm_id;
  uint64_t time_created;

public:
  Transaction(uint64_t amount, bool type, uint64_t atm_id = 5)
    : amount(amount), type(type), atm_id(atm_id){};
  uint64_t getAmount() {
    return amount;
  }
  bool getType() {
    return type;
  }
};

class BankAccount {
private:
  uint64_t account_no;
  uint16_t pin_no;
  uint64_t balance;

  std::string name;
  std::string address;
  uint64_t time_created;
  std::vector<Transaction*> transactions;

public:
  BankAccount(uint64_t new_account_no, uint64_t new_pin)
    : balance(0.0), time_created(0.0) {
    account_no = new_account_no;
    pin_no = new_pin;
  };
  BankAccount(uint64_t new_account_no) : balance(0.0), time_created(0.0) {
    account_no = new_account_no;
    pin_no = 1234;
  };
  uint64_t getBalance() {
    return balance;
  };
  void updateTransaction(Transaction* transaction) {
    if (transaction->getType()) {
      balance = balance - transaction->getAmount();
    } else {
      balance = balance + transaction->getAmount();
    }
    transactions.push_back(transaction);
  };

  bool validPin(uint16_t pin) {
    return (pin == pin_no);
  }
};

class Bank {
private:
  std::map<uint64_t, BankAccount*> customers;
  std::string name;
  uint64_t total_customers;
  uint64_t reserve;
  std::string address;

public:
  Bank() : total_customers(0), name("ABCD"), address(""){};
  void addCustomer(std::string name) {
    // Generate Unique account no
    uint64_t new_account = total_customers;
    total_customers = total_customers + 1;

    // Generate a Bank account instance
    BankAccount* acc = new BankAccount(new_account);

    // Add to customers
    if (customers.find(new_account) == customers.end()) {
      customers[new_account] = acc;
    } else {
      // Try with different unique id as this has been taken
    }
  };

  void removeCustomer(){};

  void updateBalance(BankAccount* indiv, Transaction* trans) {
    indiv->updateTransaction(trans);
  };

  BankAccount* isValidBankAccount(uint64_t read_account) {
    if (customers.find(read_account) != customers.end()) {
      return customers[read_account];
    } else {
      return NULL;
    }
  };

  bool isValidPin(uint64_t pin, BankAccount* account) {
    return account->validPin(pin);
  }
};
#endif // !_BANK_H