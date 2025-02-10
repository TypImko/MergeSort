#include <iostream>
#include <vector>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;
void merge(int arr[], int left, int right, int mid){
    //Code commented out is for debugging purposes, used the video linked in assignment as a reference.
    int * arrB = new int[right + 1];
    int i = left;
    int k = left;
    int j = mid + 1;
    //cout << "While Loop 1 Running...." << endl;
    while(i <= mid && j <= right){
        if(arr[i] < arr[j]){
            arrB[k] = arr[i];
            i++;
            k++;
        }
        else{
            arrB[k] = arr[j];
            j++;
            k++;
        }
    }
    //cout << "While Loop 1 Ended." << endl;
    //cout << "While Loop 2 Running...." << endl;
    while(i<=mid){
        arrB[k] = arr[i];
        i++;
        k++;
    }
    //cout << "While Loop 2 Ended." << endl;
    //cout << "While Loop 3 Running...." << endl;
    while(j <= right){
        arrB[k] = arr[j];
        j++;
        k++;
    }
    //cout << "While Loop 3 Ended." << endl;
    for(int i = left; i <= right; i++ ){
        arr[i] = arrB[i];
    }
    delete [] arrB;

}

//alternate input: vector<int>&arr
void mergesort(int arr[], int left, int right){
    //cout << right << endl;
    if(left < right){
        //This checks to ensure the left and right values are valid.
        int mid = (left + right) / 2;
        mergesort(arr,left,mid);
        mergesort(arr,mid+1,right);
        merge(arr,left,right,mid);
    }
}

int main(int argc, char* argv[])
{
    //You can change this variable to either true to see the array when sorted and unsorted.
    bool viewArray = false;
    //I set the array to a pointer array of size 10^9, and allocate the memory in the same line.
    int * array = new int[1000000000];
    cout << "Set Array Size: " << stoi(argv[argc-1]) << endl;
    cout << "\nArray Size has been set" << endl;
    //Sets each value of the array to a random value.
    srand(time(0));
    array[0] = 1 + (rand() % 10000);
    for(int i = 0; i < stoi(argv[argc-1]) ; i++){
        array[i] = 1 + (rand() % 10000);
        //Uncomment line below to test if each value is being set as intended.
        //cout << " " << array[i];
    }
    cout << "\nFinnished setting every value of array to a random number." << endl;
    if(viewArray){
        cout << "Array (Unsorted): " << endl;
        for(int i = 0; i < stoi(argv[argc-1]) ; i++){
            cout << array[i] << " ";
        }
    }
    //cout << aSize << endl;
    //vector<int> arrTest = {3,12,4,2,64,9,43,10,23,5,8,24};
    double sTime = time(NULL);
    mergesort(array,0, stoi(argv[argc-1]) -1);
    double eTime = time(NULL);
    if(viewArray){
        cout << "Array (Sorted): " << endl;
        for(int i = 0; i < stoi(argv[argc-1]) ; i++){
            cout << array[i] << " ";
        }
    }
    cout << "\nArray has been sorted." << endl;
    cout << "\nTime taken to sort array: " << eTime - sTime << " seconds." << endl;
    delete [] array;

    return 0;
}