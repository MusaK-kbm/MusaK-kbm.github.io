#include <iostream>

using namespace std;

int main() {

    string input, reversedString;
    cout << "Enter a string: ";
    getline(cin, input);

    for(int i = input.length()-1; i >= 0 ; i--) {
        reversedString += input[i];
    }
    
    cout << endl;

    cout << "Original String: " << input << endl;
    cout << "Reversed String: " << reversedString << endl;

    cout << endl;

    bool palindrome = (input == reversedString) ? true : false;
    cout << "Is Palindrome (yes : 1/ / no : 0)?: " << palindrome <<endl;

    return 0;
}