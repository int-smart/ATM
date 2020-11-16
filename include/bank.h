#ifndef _BANK_H
#include <iostream>
#include <map>
#include <stdlib.h>
#include <string>
#include <vector>

/*
  Transaction class
*/
class Transaction {
private:
  uint64_t amount;
  bool type; // 0-deposit, 1-withdraw
  uint64_t atm_id;
  uint64_t time_created;

public:
  Transaction(uint64_t amount, bool type, uint64_t atm_id = 5)
    : amount(amount), type(type), atm_id(atm_id){};

  /*
  This function gets transaction amount
  */
  uint64_t getAmount() {
    return amount;
  }

  /*
  This function gets transaction type
  */
  bool getType() {
    return type;
  }
};

class BankAccount {
private:
  // Data
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

  /*
  This function gets balance amount
  */
  uint64_t getBalance() {
    return balance;
  };
  /*
  Given a transaction this function applies the transaction and updates balance
  amount
  */
  bool updateTransaction(Transaction* transaction) {
    if (transaction->getType()) {
      if (balance >= transaction->getAmount()) {
        balance = balance - transaction->getAmount();
      } else {
        std::cout << "Not enough Balance for this withdrawal." << std::endl;
        return false;
      }
    } else {
      balance = balance + transaction->getAmount();
    }
    transactions.push_back(transaction);
    return true;
  };

  /*
  This function checks if pin is valid
  */
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

  /*
  This function adds customers
  */
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

  /*
  This function applies transaction to a particular bank account
  */
  void updateBalance(BankAccount* indiv, Transaction* trans) {
    indiv->updateTransaction(trans);
  };

  /*
  This function checks validity of bank account
  */
  BankAccount* isValidBankAccount(uint64_t read_account) {
    if (customers.find(read_account) != customers.end()) {
      return customers[read_account];
    } else {
      return NULL;
    }
  };

  /*
  This function checks if given pin is the pin of given account
  */
  bool isValidPin(uint64_t pin, BankAccount* account) {
    return account->validPin(pin);
  }
};
#endif // !_BANK_H