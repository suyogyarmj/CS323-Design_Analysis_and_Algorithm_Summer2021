/*
CSCI 323-2021-Summer
Assignment 1
Suyogya Rayamajhi
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;
 
// Total number of sorting runs
#define NUM 10

int ncomp; // global 'ncomp' variable

// Function to perform insertion sort on `arr[]`
void insertionSort(int arr[], int low, int n)
{
    // Start from the second element (the element at index 0
    // is already sorted)
    for (int i = low + 1; i <= n; i++)
    {
        int value = arr[i];
        int j = i;
 
        // find index `j` within the sorted subset `arr[0…i-1]`
        // where element `arr[i]` belongs
        while (j > low && arr[j - 1] > value)
        {
            arr[j] = arr[j - 1];
            j--;
        }
 
        // note that subarray `arr[j…i-1]` is shifted to
        // the right by one position, i.e., `arr[j+1…i]`
 
        arr[j] = value;
        ncomp ++;
    }
}
 
int partition(int a[], int low, int high)
{
    // Pick the rightmost element as a pivot from the array
    int pivot = a[high];
 
    // elements less than the pivot will be pushed to the left of `pIndex`
    // elements more than the pivot will be pushed to the right of `pIndex`
    // equal elements can go either way
    int pIndex = low;
 
    // each time we find an element less than or equal to the pivot, `pIndex`
    // is incremented, and that element would be placed before the pivot.
    for (int i = low; i < high; i++)
    {
        if (a[i] <= pivot)
        {   
            swap(a[i], a[pIndex]);
            pIndex++;
            //ncomp ++;
        }
    }
    // swap `pIndex` with pivot
    swap (a[pIndex], a[high]);
 
    // return `pIndex` (index of the pivot element)
    return pIndex;
}


 // Generates Random Pivot, swaps pivot with
// end element and calls the partition function
int partition_r(int a[], int low, int high)
{
    // Generate a random number in between
    // low .. high
    srand(time(NULL));
    int random = low + rand() % (high - low);
 
    // Swap A[random] with A[high]
    swap(a[random], a[high]);
 
    return partition(a, low, high);
}

void quickSort_random(int a[], int low, int high)
{
    if (low < high) {
 
        /* pi is partitioning index,
        arr[p] is now
        at right place */
        int pi = partition_r(a, low, high);
 
        // Separately sort elements before
        // partition and after partition
        quickSort_random(a, low, pi - 1);
        quickSort_random(a, pi + 1, high);
    }
        ncomp ++;

}

void quicksort(int a[], int low, int high)
{
    // base condition
    if (low >= high) {
        return;
    }
 
    // rearrange elements across pivot
    int pivot = partition(a, low, high);
 
    // recur on subarray containing elements that are less than the pivot
    quicksort(a, low, pivot - 1);
 
    // recur on subarray containing elements that are more than the pivot
    quicksort(a, pivot + 1, high);
    ncomp ++;

}
 
void optimizedQuicksort(int A[], int low, int high)
{
    while (low < high)
    {
        if (high - low < 10) // we choose the threshold as 10
        {
            insertionSort(A, low, high);
            break;
        }
        else {
            int pivot = partition(A, low, high);
 
            // tail call optimizations – recur on the smaller subarray
            if (pivot - low < high - pivot)
            {
                optimizedQuicksort(A, low, pivot - 1);
                low = pivot + 1;
            }
            else {
                optimizedQuicksort(A, pivot + 1, high);
                high = pivot - 1;
            }
        }
    }
    ncomp ++;

}
 
int main()
{
    int N;
    cout <<"Enter the number of elements to QuickSort. (i.e. N): ";
    cin >> N;
    cout <<"\n";
    int arr[N], dup[N];
 
    // seed for random input
    srand(time(NULL));
 
    // to measure the time taken by optimized and non-optimized Quicksort
    clock_t begin, end;
    double t1 = 0.0, t2 = 0.0, t3 = 0.0;

     int comp_quick = 0;
     int comp_opt = 0;
     int comp_rand = 0;
 
    // perform Quicksort NUM times and take an average
    for (int i = 0; i < NUM; i++)
    {
        // generate random input
        for (int i = 0; i < N; i++) {
            dup[i] = arr[i] = rand() % 100000;
            //cout << dup[i]<<endl;
        }
 
        // Perform non-optimized Quicksort on the array
        begin = clock();
        quicksort(arr, 0, N - 1);
        end = clock();
        

        // calculate the time taken by non-optimized Quicksort
        t1 += (double)(end - begin) / CLOCKS_PER_SEC;
        comp_quick = ncomp;

        // Perform optimized Quicksort on the duplicate array
        begin = clock();
        optimizedQuicksort(dup, 0, N - 1);
        end = clock();
        // calculate the time taken by optimized Quicksort
        t2 += (double)(end - begin) / CLOCKS_PER_SEC;
        comp_opt = ncomp - comp_quick;

        begin = clock();
        quickSort_random(arr, 0, N - 1);
        end = clock();
        t3 += (double)(end - begin) / CLOCKS_PER_SEC;
        comp_rand = ncomp - comp_opt - comp_quick;
    }
 
    cout << "The average time taken by non-optimized Quicksort: " << t1/NUM;
    cout << "\nThe average time taken by optimized Quicksort: " << t2/NUM;
    cout<<"\nThe average time taken by randomized Quicksort: " << t3/NUM;
    cout <<"\n";  
    cout <<"\nNon-Optimized Quicksort no. of comparisons: "<<comp_quick;
    cout <<"\nOptimized QuickSort no. of comparisons: "<<comp_opt;
    cout <<"\nRandom QuickSort no. of comparisons: "<<comp_rand;
    return 0;
}