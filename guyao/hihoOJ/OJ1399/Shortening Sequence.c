#include <iostream>
#include <math.h>

using namespace std;

int main(){
    long long int x;
    long odd = 0;
    long even = 0;
    int length = 0;
    cin >> length;
    for(int i = 0;i<length;i++){
        cin >> x;
        if(x % 2 == 0) even ++;
        else odd++;
    }

    cout<< abs(odd-even);




    return 0;
}