#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>

using namespace std;

int main(){
    int a, b ,c;

    cout << "Enter 3 integers: ";
    cin >> a >> b >> c;

    int smallest = a, largest = a;

    if(b > largest) {
        largest = b;
    }

    if(c > largest) {
        largest = c;
    }

    if (b < smallest) {
        smallest = b;
    }

    if (c < smallest) {
        smallest = c;
    }
    
    cout << "Largest number: " << largest << endl;

    cout << "Smallest number: " << smallest << endl;

    return 0;


}
