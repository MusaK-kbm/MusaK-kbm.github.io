#include <iostream>

using namespace std;

int main() {
    
    int n;
    cout << "Enter an integer: ";
    cin >> n;
    
    int temp = n;
    
    cout << "Reversed integer: ";
    while(temp > 0) {
        int value = temp % 10;
        temp = temp / 10;
        cout << value;
    }
    
    return 0;
}
