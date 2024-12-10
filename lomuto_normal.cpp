#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>

// Lomuto's Partition Scheme
int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high]; // Pivot element
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Recursive Quicksort using Lomuto's Partition
void quickSortLomuto(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);  // Partition the array
        quickSortLomuto(arr, low, pi - 1);   // Recursively sort the left part
        quickSortLomuto(arr, pi + 1, high);  // Recursively sort the right part
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

    // Start measuring time
    auto start_time = std::chrono::high_resolution_clock::now();

    // Call Lomuto's QuickSort
    quickSortLomuto(arr, 0, array_size - 1);

    // End measuring time
    auto end_time = std::chrono::high_resolution_clock::now();

    // Calculate duration
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

    // Print the time taken to complete sorting
    std::cout << "Lomuto's QuickSort completed in " << duration.count() << " milliseconds." << std::endl;

    return 0;
}
