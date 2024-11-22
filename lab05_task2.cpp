#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

using namespace std;

int main(){

    string username, email, password, phone_number;
    unsigned int age;
    bool Flag = 1;

    cout << "Enter a username: ";
    cin >> username;

    cout << "Enter a Password: ";
    cin >> password;

    cout << "Enter an email: ";
    cin >> email;

    bool validEmail = email.find('@');

    cout << "Enter an age: ";
    cin >> age;

    cout << "Enter a phone number: ";
    cin >> phone_number;

    if (username.length() <= 5) {
        cout << "Error: Username must be 5 characters long." << endl;  
        Flag = 0;
    }
    
    if (password.length() <= 7) {
        cout << "Error: Password must be at least 8 characters long." << endl;
        Flag = 0;
    }

    if (validEmail != 1) { 
        cout << "Error: Inavlid Email." << endl;
        Flag = 0;
    }   

    if (age < 18 && age > 100) {
        cout << "Error: Age must be greater than 18 and less than 100." << endl;
        Flag = 0;
    }

    if (phone_number.length() != 10) {
        cout << "Error: Phone number must be exactly 10 digits long." << endl;
        Flag = 0;
    }

    if (Flag == 0) {
        cout << "Registration Failed!" << endl;
    } else {
        cout << "Registration Succesful!" << endl;
    }

    return 0;

}
