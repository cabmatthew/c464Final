#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <iomanip> 
#include <omp.h>

int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
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

void quickSortLomutoParallel(std::vector<int>& arr, int low, int high, int depth = 0) {
    if (low < high) {
        int pi = partition(arr, low, high);  

        #pragma omp task shared(arr) if (depth < 4) 
        quickSortLomutoParallel(arr, low, pi - 1, depth + 1);

        #pragma omp task shared(arr) if (depth < 4) 
        quickSortLomutoParallel(arr, pi + 1, high, depth + 1);

        #pragma omp taskwait 
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

    omp_set_num_threads(num_threads);

    std::vector<int> arr(array_size);

    std::srand(std::time(nullptr));

    for (int i = 0; i < array_size; ++i) {
        arr[i] = std::rand() % 10000; 
    }

    std::cout << "Sorting an array of size: " << array_size << " with " << num_threads << " threads." << std::endl;

    auto start_time = std::chrono::high_resolution_clock::now();

    #pragma omp parallel
    {
        #pragma omp single
        quickSortLomutoParallel(arr, 0, array_size - 1);
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(end_time - start_time).count();

    std::cout << "Parallel Lomuto's QuickSort completed in " 
              << std::fixed << std::setprecision(4) 
              << duration << " milliseconds." << std::endl;

    return 0;
}
