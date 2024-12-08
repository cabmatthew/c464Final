#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <omp.h> // OpenMP header

int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[low]; // Pivot element
    int i = low - 1, j = high + 1;

    while (true) {
        do {
            i++;
        } while (arr[i] < pivot);

        do {
            j--;
        } while (arr[j] > pivot);

        if (i >= j)
            return j;

        std::swap(arr[i], arr[j]);
    }
}

void quickSortHoareParallel(std::vector<int>& arr, int low, int high, int depth = 0) {
    if (low < high) {
        int pi = partition(arr, low, high);

        #pragma omp task shared(arr) if (depth < 4)
        quickSortHoareParallel(arr, low, pi, depth + 1);

        #pragma omp task shared(arr) if (depth < 4)
        quickSortHoareParallel(arr, pi + 1, high, depth + 1);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <array_size> <num_threads>" << std::endl;
        return 1;
    }

    int array_size = std::atoi(argv[1]);
    int num_threads = std::atoi(argv[2]);

    if (array_size <= 0 || num_threads <= 0) {
        std::cerr << "Array size and number of threads must be positive integers." << std::endl;
        return 1;
    }

    std::vector<int> arr(array_size);
    std::srand(std::time(nullptr));

    for (int i = 0; i < array_size; ++i) {
        arr[i] = std::rand() % 10000;
    }

    // Set the desired number of threads for OpenMP
    omp_set_num_threads(num_threads);

    std::cout << "Sorting an array of size: " << array_size << " with " << num_threads << " threads." << std::endl;

    auto start_time = std::chrono::high_resolution_clock::now();

    #pragma omp parallel
    {
        #pragma omp single
        {
            quickSortHoareParallel(arr, 0, array_size - 1);
        }
    }

    auto end_time = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

    std::cout << "Parallelized Hoare QuickSort completed in " << duration.count() << " milliseconds." << std::endl;

    return 0;
}

