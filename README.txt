MergeSort README.
By: Mathew Shimko
Student ID: 801273652

How To Use:
In order to run this program in VSCode, the user must have C++ installed on said software, as well as a compiler, such as g++.
The Merge Sort program I have written only requires one user input, which is the size of the array to be sorted. 
The maximum size of the array possible is 10^9 (or 1,000,000,000), if you input a size greater than this, it will result in a error, most likely a segmentation fault.
While you may enter a number lower than 1, this will result in the program not printing anything out, or sorting anything.
You may change the value of the Boolean 'viewArray' to true if you wish to see the values of the array before and after sorting (would not recommend on array sizes greater than 1000), or false to hide the array values before and after sorting.

Upon entering the size of the array, the program will set each value of the array to a random number, after which it will sort the array via merge sort.
Upon completion, the program will declare the array has been sorted, and will output the time (in seconds) in took to sort the array.
