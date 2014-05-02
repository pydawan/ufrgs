#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <set>
#include <map>

using namespace std;

map< char, int > frequency;
typedef map< char, int>::const_iterator it;

int main() {

    char l;
    while(cin >> l) {
        frequency[l]++;
    }
    for (it iter = frequency.begin(); iter != frequency.end(); iter++) {
        printf("%c -> %d\n", iter->first, iter->second);
    }
}
