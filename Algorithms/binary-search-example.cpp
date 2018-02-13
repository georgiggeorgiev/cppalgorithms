#include <iostream>

using namespace std;

int binary_search(int arr[], int size, int search)
{
    int low = 0, high = size-1, mid;

    while(low<=high){
        mid = (low+high)/2;
        if(arr[mid]==search){
            return mid;
        }
        else if(search>arr[mid]){
            low = mid+1;
        }
        else{
            high = mid-1;
        }
    }

    return -1;
}

int main()
{
    int arr[] = {69,333,420,690,444};

    cout << binary_search(arr,5,420) << endl;

    return 0;
}
