#include <iostream>

using namespace std;

int main()
{
    int arr[] = {66,44,75,88,2,10,0,420};
    int size = sizeof(arr)/sizeof(int);
    int temp;

    for(int i=0; i<size-1; i++){
        for(int j=0; j<size-i-1; j++){
            if(arr[j] > arr[j+1]){
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                //swap(arr[j],arr[j+1]);
            }
        }
    }

    for(int i=0;i<size;i++){
        cout << arr[i] << "\t";
    }

    return 0;
}
