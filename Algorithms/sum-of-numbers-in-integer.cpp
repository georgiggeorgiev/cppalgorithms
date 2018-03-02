#include <iostream>

using namespace std;

int main()
{
    int num, div = 1, sum = 0;
    cout << "Enter number: " << endl;
    cin >> num;

    while(num/div!=1){
        div*=10;
    }

    while(num>0){
        sum+=num%10;
        num/=10;
    }

    cout << sum << endl;

    return 0;
}
