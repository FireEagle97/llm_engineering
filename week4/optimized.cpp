#include <iostream>
#include <vector>
#include <limits>
#include <ctime>

// Linear Congruential Generator function
std::vector<int> lcg(int64_t seed, int64_t n, int min_val, int max_val) {
    constexpr int64_t a = 1664525;
    constexpr int64_t c = 1013904223;
    constexpr int64_t m = 1ULL << 32;
    std::vector<int> random_numbers;
    random_numbers.reserve(n);
    int64_t value = seed;
    for (int64_t i = 0; i < n; ++i) {
        value = (a * value + c) % m;
        random_numbers.push_back(value % (max_val - min_val + 1) + min_val);
    }
    return random_numbers;
}

// Function to find the maximum subarray sum using Kadane's algorithm
int max_subarray_sum(const std::vector<int>& random_numbers) {
    int max_sum = std::numeric_limits<int>::min();
    int current_sum = 0;
    for (int number : random_numbers) {
        current_sum = std::max(number, current_sum + number);
        max_sum = std::max(max_sum, current_sum);
    }
    return max_sum;
}

// Compute total maximum subarray sum for 20 runs
int64_t total_max_subarray_sum(int64_t n, int64_t initial_seed, int min_val, int max_val) {
    int64_t total_sum = 0;
    int64_t seed = initial_seed;
    for (int i = 0; i < 20; ++i) {
        seed = (1664525 * seed + 1013904223) % (1ULL << 32);
        auto random_numbers = lcg(seed, n, min_val, max_val);
        total_sum += max_subarray_sum(random_numbers);
    }
    return total_sum;
}

int main() {
    int64_t n = 10000;           // Number of random numbers
    int64_t initial_seed = 42;   // Initial seed for the LCG
    int min_val = -10;           // Minimum value of random numbers
    int max_val = 10;            // Maximum value of random numbers

    std::clock_t start_time = std::clock();
    int64_t result = total_max_subarray_sum(n, initial_seed, min_val, max_val);
    std::clock_t end_time = std::clock();
    
    std::cout << "Total Maximum Subarray Sum (20 runs): " << result << std::endl;
    std::cout << "Execution Time: " << static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC << " seconds" << std::endl;

    return 0;
}
