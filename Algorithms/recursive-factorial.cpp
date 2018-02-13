#include <iostream>

using namespace std;

long long fact(int n)
{
    if(n==1||0){
        return 1;
    }
    return n*fact(n-1);
}

int main()
{
    cout << fact(10) << endl;
}
