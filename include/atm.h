#ifndef _ATM_H_
#include <bank.h>
#include <iostream>
class ATM {
private:
  Bank* my_bank;
  BankAccount* customer_acc;
  uint16_t atm_id;

public:
  ATM() {
    my_bank = new Bank();
    customer_acc = NULL;
    atm_id = 123;
    // Add dummy customers to test
    addCustomersTest();
  };
  ~ATM() {
    delete customer_acc;
    delete my_bank;
  }

  /*
  This function runs the ATM software
  */
  void run();

  /*
  The below function emulate different user input
  */
  int readAccountNumber() {
    // API given by ATM
    return 1;
  }
  bool isCardInserted() {
    return true;
  };
  uint16_t getPin() {
    uint16_t pin;
    std::cout << "Insert Pin: ";
    std::cin >> pin;
    return pin;
  };
  bool getSavings() {
    bool isSavings;
    std::cout << "Insert Account type (0 or 1) : Checkings:0, Savings:1"
              << std::endl;
    std::cin >> isSavings;
    return isSavings;
  }
  int getAction() {
    int action = -1;
    std::cout << "Enter 1 for Balance, 2 for Deposit, 3 for Withdraw."
              << std::endl;
    std::cin >> action;
    return action;
  }
  uint64_t getAmount() {
    uint64_t amount = 0;
    std::cout << "Insert Amount: ";
    std::cin >> amount;
    return amount;
  }
  void addCustomersTest() {
    my_bank->addCustomer("Adam");
    my_bank->addCustomer("Mary");
    my_bank->addCustomer("Abe");
  }
};

/*
  This function runs the ATM software
*/
void ATM::run() {
  while (true) {
    // Poll card tray for a card
    if (isCardInserted()) {
      // Get the bank account number from the card
      int account_number = readAccountNumber();

      // Query the bank if the bank account number exists or not
      customer_acc = my_bank->isValidBankAccount(account_number);

      if (customer_acc != NULL) {
        uint16_t pin;
        // If yes ask for pin
        pin = getPin();

        if (my_bank->isValidPin(pin, customer_acc)) {
          bool isSavings = false;
          // Select Account type as in Savings or Checkings
          isSavings = getSavings();

          // Implementing just for checkings account. Other can be factored in
          // in a similar way. If the savings account has significantly
          // different attributes and methods BankAccount can be used as
          // a base class and customer to bank account map can have multiple
          // accounts for the customer key

          switch (getAction()) {
          case 1: {
            std::cout << customer_acc->getBalance() << std::endl;
            break;
          }
          case 2: {
            std::cout << "Amount: ";
            int amount = getAmount();
            Transaction trans(amount, 0, atm_id);
            if (customer_acc->updateTransaction(&trans)) {
              std::cout << "Money deposited" << std::endl;
            }
            break;
          }
          case 3: {
            std::cout << "Amount: ";
            int amount = getAmount();
            Transaction trans(amount, 1, atm_id);
            if (customer_acc->updateTransaction(&trans)) {
              std::cout << "Money withdrew" << std::endl;
            }
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