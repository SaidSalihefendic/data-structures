#include <iostream>
#include "polinom.h"

using namespace std;

int main() {
    while(true) {
        cout << "Unesite polinom: ";
        try {
            Polinom p;
            cin >> p;
            cout << endl;
            cout << "Uneseni polinom: " << p << endl;
        } catch(const char* err) {
            cout << err << endl;
        }
        cout << "-------------------------------------" << endl << endl;
    }

    return 0;
}

