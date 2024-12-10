#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>  // for system("cls")
#include <conio.h>  // for getch()
using namespace std;

class Account 
{
public:
    string name, address, username, password, mobile;
    long balance, account;
        
    void registerUser() 
    {
        ofstream myfile("data.txt", ios::app);
        
        cout << "\n------------------------------" << endl;
        cin.ignore();  // clear the newline character from the buffer
        cout << "Enter Your Name: ";
        getline(cin, name);
        cout << "Enter Your Address: ";
        getline(cin, address);
        cout << "Enter Your Mobile no.: "; 
        cin >> mobile;
        cout << "Enter Account No.: "; 
        cin >> account;
        cout << "Enter Initial Funding Amount: Rs."; 
        cin >> balance;
        cout << "\nEnter User-Name: ";
        cin >> username;
        cout << "Enter Password: ";
        cin >> password;
        cout<<"Press Enter!!";

        myfile << username << " " << password << " " << name << " " << address << " " << mobile << " " << account << " " << balance << endl;
        myfile.close();
        getch();
    }

    bool login() 
    {
        system("cls");
        cout<<"\nLogin Your Account-"<<endl;
        cout<<"---------------------------";
        cout << "\nEnter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        ifstream myfile("data.txt");
        bool found = false;
        string user, pwd;
        string n, addr, mob;
        long long acc, bal;
        
        while (myfile >> user >> pwd >> n >> addr >> mob >> acc >> bal) 
        {
            if (username == user && password == pwd) 
            {
                name = n;
                address = addr;
                mobile = mob;
                account = acc;
                balance = bal;
                found = true;
                cout << "\t\t\t************* Login Successfully!! ***********" << endl;
                myfile.close();
                return true;
                getch();
            }
        }
        
        if (!found) 
        {
            cout << "Invalid username or password" << endl;
        }
        myfile.close();
        return false;
    }

    void deposit() 
    {
        long amount;
        cout << "Enter amount to deposit: Rs.";
        cin >> amount;

        balance += amount;
        updateBalance();
        logTransaction("deposited", amount);
    }

    void withdrawal() 
    {
        long amount;
        cout << "Enter amount to withdraw: Rs.";
        cin >> amount;

        if (amount <= balance) 
        {
            balance -= amount;
            updateBalance();
            logTransaction("withdrew", amount);
        } else 
        {
            cout << "Insufficient funds!" << endl;
        }
    }

    void checkBalance() 
    {
        cout << "Your Balance: Rs." << balance << endl;
    }

    void transactionHistory() 
    {
        ifstream myfile("transaction.txt");
        string info;
        while (getline(myfile, info)) 
        {
            if (info.find(username) != string::npos) 
            {
                cout << info << endl;
            }
        }
        myfile.close();
    }

private:
    void updateBalance() 
    {
        ifstream myfile("data.txt");
        ofstream temp("temp.txt");
        string user, pwd, n, addr, mob;
        long acc, bal;

        while (myfile >> user >> pwd >> n >> addr >> mob >> acc >> bal) 
        {
            if (username == user) {
                bal = balance;
            }
            temp << user << " " << pwd << " " << n << " " << addr << " " << mob << " " << acc << " " << bal << endl;
        }
        myfile.close();
        temp.close();

        remove("data.txt");
        rename("temp.txt", "data.txt");
    }

    void logTransaction(const string& type, long amount) 
    {
        ofstream myfile("transaction.txt", ios::app);
        myfile << username << " " << type << " " << amount << endl;
        myfile.close();
    }
};

int main() 
{
    system("cls");
    Account atm;
    int choice;

    while (true) 
    {
        cout << "\n\t\t\t\t\t\t\t\t*****************************************" << endl;
        cout << "\t\t\t\t\t\t\t\t************* |ATM Machine| *************" << endl;
        cout << "\t\t\t\t\t\t\t\t*****************************************" << endl << endl;
        cout << "------------------------------" << endl;
        cout << "1. Registration" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;
        cout << "------------------------------" << endl;
        cout << "\nChoose an option: ";
        cin >> choice;

        switch (choice) 
        {
            case 1:
                atm.registerUser();
                break;
            case 2:
                if (atm.login()) 
                {
                    system("cls");
                    while (true) 
                    {
                        cout << "\n1. My Profile" << endl;
                        cout << "2. Deposit" << endl;
                        cout << "3. Withdrawal" << endl;
                        cout << "4. Check Balance" << endl;
                        cout << "5. Transaction History" << endl;
                        cout << "6. Exit" << endl;
                        cout << "\nChoose an option: ";
                        cin >> choice;

                        switch (choice) 
                        {
                            case 1:
                                cout << "\n***************************************" << endl;
                                cout << "Name: " << atm.name << endl;
                                cout << "Address: " << atm.address << endl;
                                cout << "Mobile No.: " << atm.mobile << endl;
                                cout << "Account No.: " << atm.account << endl;
                                break;
                            case 2:
                                atm.deposit();
                                break;
                            case 3:
                                atm.withdrawal();
                                break;
                            case 4:
                                atm.checkBalance();
                                break;
                            case 5:
                                atm.transactionHistory();
                                break;
                            case 6:
                                goto end_login;
                            default:
                                cout << "Invalid choice" << endl;
                        }
                    }
                }
                end_login:
                break;
            case 3:
                return 0;
            default:
                cout << "Invalid choice" << endl;
        }
    }
    getch();
    return 0;
}
