#ifndef _ATM_H_
#include <bank.h>
#include <iostream>
class ATM {
private:
  Bank* my_bank;

public:
  ATM() {
    my_bank = new Bank();
  };
  ~ATM() {
    delete my_bank;
  }
  void run();
  int readAccountNumber() {
    // API given by ATM
    return 0;
  }
  bool isCardInserted() {
    return true;
  };
  uint16_t getPin() {
    return 1234;
  };
  bool getSavings() {
    return false;
  }
  int getAction() {
    return 2;
  }
  int getAmount() {
    return 10;
  }
};

void ATM::run() {
  while (true) {
    // Poll card tray for a card
    if (isCardInserted()) {
      // Get the bank account number from the card
      int account_number = readAccountNumber();

      // Query the bank if the bank account number exists or not
      BankAccount* customer_acc = my_bank->isValidBankAccount(account_number);
      if (customer_acc != NULL) {
        uint16_t pin;
        // If yes ask for pin
        pin = getPin();

        if (my_bank->isValidPin(pin, customer_acc)) {
          bool isSavings = false;
          // Select Account type as in Savings or Checkings
          std::cout << "Insert Account type (0 or 1) : Checkings:0, Savings:1";
          isSavings = getSavings();

          // Implementing just for checkings account. Other can be factored in
          // in a similar way. If the savings account has significantly
          // different attributes and methods BankAccount can be used as
          // a base class and customer to bank account map can have multiple
          // accounts for the customer key
          std::cout << "Enter 1 for Balance, 2 for Deposit, 3 for Withdraw.";

          switch (getAction()) {
          case 1: {
            std::cout << customer_acc->getBalance();
            break;
          }
          case 2: {
            std::cout << "Amount: ";
            int amount = getAmount();
            Transaction trans(amount, 0, 123);
            customer_acc->updateTransaction(&trans);
            break;
          }
          case 3: {
            std::cout << "Amount: ";
            int amount = getAmount();
            Transaction trans(amount, 1, 123);
            customer_acc->updateTransaction(&trans);
            break;
          }
          default:
            break;
          }
        }
      } else {
        // Show account not found
        break;
      }
      // If no tell not applicable and break
    }
  }
}
#endif // !_ATM_H_