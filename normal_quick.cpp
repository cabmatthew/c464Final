#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <algorithm> // For std::copy

// Normal Quicksort Implementation
std::vector<int> quickSortNormal(const std::vector<int>& arr) {
    if (arr.size() <= 1)
        return arr;

    int pivot = arr[arr.size() / 2];
    std::vector<int> left, right, equal;

    for (const auto& num : arr) {
        if (num < pivot) left.push_back(num);
        else if (num > pivot) right.push_back(num);
        else equal.push_back(num);
    }

    left = quickSortNormal(left);
    right = quickSortNormal(right);

    left.insert(left.end(), equal.begin(), equal.end());
    left.insert(left.end(), right.begin(), right.end());

    return left;
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

    // Seed for random number generation
    std::srand(std::time(nullptr));

    // Fill the array with random integers
    for (int i = 0; i < array_size; ++i) {
        arr[i] = std::rand() % 10000; // Random numbers in the range [0, 9999]
    }

    std::cout << "Sorting an array of size: " << array_size << std::endl;

    auto start_time = std::chrono::high_resolution_clock::now();

    std::vector<int> sorted_arr = quickSortNormal(arr);

    auto end_time = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

    std::cout << "Normal Quick Sort completed in " << duration.count() << " milliseconds." << std::endl;

    return 0;
}