#include <iostream>
#include <list>
#include <chrono>

// if you run the program with 'g++ -std=c++11 main.cpp -o main' on your terminal or any other way with new c++ edition
// there will be series of printing happening
// 1: test the result and the function of insertion sort are working (both stl version and normal)
// 2: timing test for both the stl version and the normal with 4 types of experiement

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

// helper function to print list
template<typename Container>
void printList(Container& container) {
    for (const auto& element : container) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

// test sort results
template<typename Comparator>
void testSortedResultSTL(Comparator compare) {
    std::list<int> l = {5,2,1,8,9,3};
    std::cout << "Before sort: ";
    printList(l);
    insertionSortSTL(l.begin(), l.end(), compare);
    std::cout << "After sort: ";
    printList(l);
}

template<typename Comparator>
void testSortedResult(Comparator compare) {
    std::list<int> l = {5,2,1,8,9,3};
    std::cout << "Before sort: ";
    printList(l);
    insertionSort(l.begin(), l.end(), compare);
    std::cout << "After sort: ";
    printList(l);
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
