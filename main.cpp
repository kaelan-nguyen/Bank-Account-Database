/*
kaelan nguyen
*/
#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <iomanip>
#include <cmath>
using namespace std;

struct Person
    {
        string name;
        string address;
    }; // end of Person
    struct Account
    {
        int accountNumber;
        Person ownerInfo;
        double balance;
    }; // end of Account

void printMenu(int&);
void populateAccount(Account * accPtr, int maxAcc, int & populatedAccs);
bool validateBalance(string & input);
void printAccount(Account & acc);

int main()
{
    int maxAcc;
    int userChoice;
    int populatedAccs = 0;
    int numAttempts1 = 0;
    cout << "Enter max number of accounts: ";
    cin >> maxAcc;
    numAttempts1++;
    while ((maxAcc < 0) && (numAttempts1 < 5))
    {
        cout << "Invalid value, please reenter: ";
        cin >> maxAcc;
        numAttempts1++;
    } // end of while input validation
    if (numAttempts1 == 5)
    {
        cout << "Too many unsuccessful attempts, exiting";
        return -1;
    } // end of if input validation


    Account * accPtr = new Account[maxAcc];
    printMenu(userChoice);
    if ((userChoice <= 0) || (userChoice >= 5))
    {
        return -1;
    }

    int populateSuccess = populatedAccs;
    int searchAcc;
    int numAttempts2 = 0;
    bool searchSuccess;
    while (userChoice != 4)
    {
        switch (userChoice)
        {
            case 1:
                populateAccount(accPtr, maxAcc, populatedAccs);
                if (populateSuccess == populatedAccs)
                {
                    return -1;
                }
                break;
            case 2:
                searchSuccess = false;
                cout << "Enter account number: ";
                cin >> searchAcc;
                numAttempts2++;
                while ((searchAcc < 0) && (numAttempts2 < 5))
                {
                  cout << "Invalid value, please reenter: ";
                  cin >> searchAcc;
                  numAttempts2++;
                }
                if (numAttempts2 == 5)
                {
                    cout << "Too many unsuccessful attempts, exiting";
                    return -1;
                } // end of if input validation
                for (int i = 0; i < populatedAccs; i++)
                {
                    if (accPtr[i].accountNumber == searchAcc)
                    {
                        printAccount(accPtr[i]);
                        searchSuccess = true;
                    }
                }
                if (!searchSuccess)
                {
                    cout << "Account not found\n";
                }
                break;
            case 3:
                for (int i = 0; i < populatedAccs; i++)
                {
                    printAccount(accPtr[i]);
                }
                break;
        }
        userChoice = 0;
        printMenu(userChoice);
        if ((userChoice <= 0) || (userChoice >= 5))
        {
            return -1;
        }
    }
    if (userChoice == 4)
    {
        delete[] accPtr;
        return 0;
    }



    return 0;
} // end of main

void printMenu(int &choice)
{
    int numAttempts = 0;
    cout << endl;
    cout << "Menu:\n";
    cout << "1->Enter data to create account, 2->Display data for specific account\n" << "3->Display data for all accounts, 4->Quit:\n";
    cin >> choice;
    numAttempts++;
    while (((choice <= 0) || (choice >= 5)) && (numAttempts < 5)) // input validation
    {
        cout << "Invalid choice, please reenter: ";
        cin >> choice;
        numAttempts++;
    } // end of while input validation
    if (numAttempts == 5)
    {
        cout << "Too many unsuccessful attempts, exiting";
        return;
    } // end of if input validation
} // end of printMenu

void populateAccount(Account * accPtr, int maxAcc, int & populatedAccs)
{
    int numAttempts = 0;
    string balanceString;
    if (populatedAccs >= maxAcc)
    {
        cout << "Cannot execute, array is full\n";
        return;
    }
    cout << "Enter account number: ";
    cin >> accPtr[populatedAccs].accountNumber;
    numAttempts++;
    while ((accPtr[populatedAccs].accountNumber < 0) && (numAttempts < 5))
    {
        cout << "Invalid value, please reenter: ";
        cin >> accPtr[populatedAccs].accountNumber;
        numAttempts++;
    } // end of while input validation
    if (numAttempts == 5)
    {
        cout << "Too many unsuccessful attempts, exiting";
        return;
    } // end of if input validation

    numAttempts = 0;
    cin.ignore();
    cout << "Enter balance: ";
    getline(cin, balanceString);
    numAttempts++;

    if (validateBalance(balanceString))
    {
        accPtr[populatedAccs].balance = stod(balanceString);
    }
    else
    {
        while ((!validateBalance(balanceString)) && (numAttempts < 5))
        {
            cout << "Invalid value, please reenter: ";
            getline(cin, balanceString);
            numAttempts++;
        }
        if (numAttempts == 5)
        {
            cout << "Too many unsuccessful attempts, exiting";
            return;
        }
    }

    cout << "Enter owner's name: ";
    getline(cin, accPtr[populatedAccs].ownerInfo.name);
    cout << "Enter owner's address: ";
    getline (cin, accPtr[populatedAccs].ownerInfo.address);

    populatedAccs++;
}

bool validateBalance(string & input)
{
    int dotCount = 0;

    for (char c : input)
    {
        if (c == '.')
        {
            dotCount++;
            if (dotCount > 1)
            {
                return false;
            }
        }
        else if (!isdigit(c))
        {
            return false;
        }
    }

    if (dotCount == 1 && input.find('.') != std::string::npos && input.size() - input.find('.') > 3) {
      // If there is a dot, there should be at most two digits after it
      return false;
  }

    return true;
}

void printAccount(Account & acc)
{
    cout << "Account #: " << acc.accountNumber << endl;
    cout << "Owner's name: " << acc.ownerInfo.name << endl;
    cout << "Owner's address: " << acc.ownerInfo.address << endl;
    cout << "Balance: " << acc.balance << endl;
}
