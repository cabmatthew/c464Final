#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>

// Hoare's Partition Scheme
int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[low]; // Pivot element
    int i = low - 1, j = high + 1;

    while (true) {
        // Move left pointer to the right
        do {
            i++;
        } while (arr[i] < pivot);

        // Move right pointer to the left
        do {
            j--;
        } while (arr[j] > pivot);

        if (i >= j)
            return j;

        // Swap elements
        std::swap(arr[i], arr[j]);
    }
}

// Recursive Quicksort using Hoare's Partition
void quickSortHoare(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        // Partition the array
        int pi = partition(arr, low, high);

        // Recursively sort the two halves
        quickSortHoare(arr, low, pi);
        quickSortHoare(arr, pi + 1, high);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <array_size>" << std::endl;
        return 1;
    }

    int array_size = std::atoi(argv[1]);

    if (array_size <= 0) {
        std::cerr << "Array size must be a positive integer." << std::endl;
        return 1;
    }

    std::vector<int> arr(array_size);

    // Seed random number generator
    std::srand(std::time(nullptr));

    // Fill the array with random integers
    for (int i = 0; i < array_size; ++i) {
        arr[i] = std::rand() % 10000; // Random numbers in the range [0, 9999]
    }

    std::cout << "Sorting an array of size: " << array_size << std::endl;

    auto start_time = std::chrono::high_resolution_clock::now();

    // Call Hoare's QuickSort
    quickSortHoare(arr, 0, array_size - 1);

    auto end_time = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

    std::cout << "Hoare's QuickSort completed in " << duration.count() << " milliseconds." << std::endl;

    return 0;
}
