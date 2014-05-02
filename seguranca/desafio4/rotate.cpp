#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;


int main() {

    string s;
    char c;   
    int ascii; 

    while (cin >> c) {
        s.push_back(c);
    }
    
    for (int i=0; i<26; i++) {
        for (int j=0; j<s.size(); j++) {
            ascii = s[j]+i;
            if (ascii <= 90) {
                printf("%c",ascii);
            }
            else {
                printf("%c",'A'+ascii-'Z'-1);
            }
        }
        cout << "\n";
    }
}
