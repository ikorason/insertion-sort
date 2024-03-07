#include <iostream>
#include <list>
#include <chrono>

template<typename Iter, typename Comparator>
void insertionSortSTL(const Iter begin, const Iter end, Comparator compare) {
    for (auto iter = begin; iter != end; iter++) {
        auto const insertion = std::upper_bound(begin, iter, *iter, compare);
        std::rotate(insertion, iter, std::next(iter));
    }
}

template<typename Iter, typename Comparator>
void insertionSort(const Iter begin, const Iter end, Comparator compare) {
    // if the container is empty
    if (begin == end) {
        return;
    }

    for (Iter j = begin; j != end; j++) {
        auto key = std::move(*j); // move the value to be inserted
        Iter i = j;
        while (i != begin && compare(key, *(std::prev(i)))) {
            *i = std::move(*(std::prev(i)));
            i--;
        }
        // insert the key into it's correct position
        *i = std::move(key);
    }
}

// --------------------------------------------------------------------------------------------------------
// the blow versions is from the c++ text book
// --------------------------------------------------------------------------------------------------------
// inner for loop version from the c++ text book in insertionSort chapter
template<typename Iter, typename Comparator>
void insertionSortInnerForLoop(const Iter begin, const Iter end, Comparator compare) {
    if (begin == end) {
        return;
    }

    Iter i;

    for (Iter j = begin; j != end; j++) {
        auto key = std::move(*j); // move the value to be inserted
        for (i = j; i != begin && compare(key, *(prev(i))); i--) {
            *i = std::move(*(std::prev(j)));
        }
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

// timing test
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

int main() {
    std::list<int> l = {5,2,1,8,9,3};
    testRandom();
    return 0;
}
