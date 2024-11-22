#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {

    string fname, lname, full_name, hobby;
    int age;

    cout << "First Name: ";
    cin >> fname;
    cout << "Last Name: ";
    cin >> lname;

    cout << "Age: ";
    cin >> age;

    cout << "Hobby: ";
    cin >> hobby;

    full_name = fname + " " + lname;
    cout << "Full Name: " << full_name;
    cout << endl;
    cout << "Length of Full Name: " << full_name.length();

    cout << endl;
    int spaceIndex = full_name.find(' ');
    cout << "Space Index" << spaceIndex << endl;

    cout << "Extracted Last Name: " << full_name.substr(4,full_name.length()-1);
}