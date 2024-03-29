#include <iostream>
#include <list>
#include <chrono>

// 1: test the result and the function of insertion sort are working (both stl version and normal)
// 2: timing test for both the stl version and the normal with 4 types of experiement

// timing test resuults summary
// sorted order and all duplicate elements will be the fastest, then its random. reverse sorted order is the slowest
// also `insertionSortSTL` using the std library, all the other tests are similar, but found that `sorted order` takes a bit longer than others
// I think its because of the inner working functionlaity of the `upper_bound` and `rotate` function

// helper function to print list
template<typename Iter>
void print(const Iter& begin, const Iter& end, bool new_line = true)
{
    std::for_each(begin, end, [](auto& i) { std::cout << i << " "; });
    if (new_line) {
        std::cout << std::endl;
    }
}

// insertion sort using standard libraries, just to make comparison
template<typename Iter, typename Comparator>
void insertionSortSTL(Iter begin, Iter end, Comparator compare) {
    for (auto iter = begin; iter != end; iter++) {
        auto const insertion = std::upper_bound(begin, iter, *iter, compare);
        std::rotate(insertion, iter, std::next(iter));
    }
}

template<typename Iter, typename Comparator>
void insertionSort(Iter begin, Iter end, Comparator compare) {
    // if the container is empty
    if (begin == end) {
        return;
    }

    // loop through the list
    for (Iter j = begin; j != end; j++) {
        // move the value to be inserted
        auto key = std::move(*j); 
        Iter i = j;
        while (i != begin && compare(key, *(std::prev(i)))) {
            *i = std::move(*(std::prev(i)));
            i--;
        }
        // insert the key into it's correct position
        *i = std::move(key);
    }
}

// test sort results
template<typename Comparator>
void testSortedResultSTL(Comparator compare) {
    std::list<int> l = {5,2,1,8,9,3};
    std::cout << "Before sort: ";
    print(l.begin(), l.end());
    insertionSortSTL(l.begin(), l.end(), compare);
    std::cout << "After sort: ";
    print(l.begin(), l.end());
}

template<typename Comparator>
void testSortedResult(Comparator compare) {
    std::list<int> l = {5,2,1,8,9,3};
    std::cout << "Before sort: ";
    print(l.begin(), l.end());
    insertionSort(l.begin(), l.end(), compare);
    std::cout << "After sort: ";
    print(l.begin(), l.end());
}


// timing test
// ----------------- Sorted Order -----------------
void testSortedSTL() {
    std::list<int> l;
    std::cout << "Experiment 1 (STL): Sorted Order\n";
    for (int i = 1; i <= 10000; ++i) {
        l.push_back(i);
    }
    auto start = std::chrono::high_resolution_clock::now();
    insertionSortSTL(l.begin(), l.end(), std::less<int>());
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n\n";
}

void testSorted() {
    std::list<int> l;
    std::cout << "Experiment 1: Sorted Order\n";
    for (int i = 1; i <= 10000; ++i) {
        l.push_back(i);
    }
    auto start = std::chrono::high_resolution_clock::now();
    insertionSort(l.begin(), l.end(), std::less<int>());
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n\n";
}


// ----------------- Reverse Sorted Order -----------------
void testReverseSortedSTL() {
    std::list<int> l;
    std::cout << "Experiment 2 (STL): Reverse Sorted Order\n";
    for (int i = 10000; i >= 1; --i) {
        l.push_back(i);
    }
    auto start = std::chrono::high_resolution_clock::now();
    insertionSortSTL(l.begin(), l.end(), std::less<int>());
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n\n";
}

void testReverseSorted() {
    std::list<int> l;
    std::cout << "Experiment 2: Reverse Sorted Order\n";
    for (int i = 10000; i >= 1; --i) {
        l.push_back(i);
    }
    auto start = std::chrono::high_resolution_clock::now();
    insertionSort(l.begin(), l.end(), std::less<int>());
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n\n";
}

// ----------------- Random Order -----------------
void testRandomSTL() {
    std::list<int> l;
    std::cout << "Experiment 3 (STL): Random Order\n";
    for (int i = 0; i < 10000; ++i) {
        l.push_back(rand() % 10000);
    }
    auto start = std::chrono::high_resolution_clock::now();
    insertionSortSTL(l.begin(), l.end(), std::less<int>());
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n\n";
}

void testRandom() {
    std::list<int> l;
    std::cout << "Experiment 3: Random Order\n";
    for (int i = 0; i < 10000; ++i) {
        l.push_back(rand() % 10000);
    }
    auto start = std::chrono::high_resolution_clock::now();
    insertionSort(l.begin(), l.end(), std::less<int>());
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n\n";
}

// ----------------- All Duplicates Elements -----------------
void testAllDuplicatesSTL() {
    std::list<int> l;
    std::cout << "Experiment 4 (STL): All Duplicate Elements\n";
    for (int i = 0; i < 10000; ++i) {
        l.push_back(42);
    }
    auto start = std::chrono::high_resolution_clock::now();
    insertionSortSTL(l.begin(), l.end(), std::less<int>());
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n\n";
}

void testAllDuplicates() {
    std::list<int> l;
    std::cout << "Experiment 4: All Duplicate Elements\n";
    for (int i = 0; i < 10000; ++i) {
        l.push_back(42);
    }
    auto start = std::chrono::high_resolution_clock::now();
    insertionSort(l.begin(), l.end(), std::less<int>());
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n\n";
}

int main() {
    // test result
    std::cout << "Test Result: " << std::endl;

    std::cout << "Type -> insertionSortSTL -> Ascending Order:\n";
    testSortedResultSTL(std::less<int>());

    std::cout << "Type -> insertionSortSTL -> Descending Order:\n";
    testSortedResultSTL(std::greater<int>());

    std::cout << "Type -> insertionSort -> Ascending Order:\n";
    testSortedResult(std::less<int>());

    std::cout << "Type -> insertionSort -> Descending Order:\n";
    testSortedResult(std::greater<int>());

    std::cout << std::endl;

    // timing
    std::cout << "TIMING TESTS: " << std::endl;
    testSortedSTL();
    testSorted();

    testReverseSortedSTL();
    testReverseSorted();

    testRandomSTL();
    testRandom();

    testAllDuplicatesSTL();
    testAllDuplicates();
    return 0;
}
