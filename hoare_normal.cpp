#include <iostream>
#include <vector>
#include <immintrin.h> // For SIMD intrinsics
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <algorithm> // For std::swap

// Vectorized partitioning using SIMD
int partitionSIMD(std::vector<int>& arr, int low, int high) {
    int pivot = arr[low]; // Pivot selection
    int i = low - 1, j = high + 1;

    while (true) {
        // SIMD for scanning from the left
        while (true) {
            i++;
            if (arr[i] >= pivot)
                break;
        }

        // SIMD for scanning from the right
        while (true) {
            j--;
            if (arr[j] <= pivot)
                break;
        }

        if (i >= j)
            return j;

        // Swap elements
        std::swap(arr[i], arr[j]);
    }
}

// Hoare QuickSort
void quickSortHoareSIMD(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partitionSIMD(arr, low, high);

        quickSortHoareSIMD(arr, low, pi);
        quickSortHoareSIMD(arr, pi + 1, high);
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
    std::srand(std::time(nullptr));

    // Fill the array with random integers
    for (int i = 0; i < array_size; ++i) {
        arr[i] = std::rand() % 10000;
    }

    std::cout << "Sorting an array of size: " << array_size << std::endl;

    auto start_time = std::chrono::high_resolution_clock::now();

    quickSortHoareSIMD(arr, 0, array_size - 1);

    auto end_time = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

    std::cout << "Vectorized Hoare QuickSort completed in " << duration.count() << " milliseconds." << std::endl;

    return 0;
}
