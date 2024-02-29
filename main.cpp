#include <iostream>
#include <list>
#include <chrono>

template<typename Iter>
using value_type_t = typename std::iterator_traits<Iter>::value_type;

template<typename Iterator, typename Comparator = std::less<value_type_t<Iterator>>>
void insertionSortSTL(const Iterator& begin, const Iterator& end, Comparator lessThan = Comparator{}) {
    for (auto iter = begin; iter != end; iter++) {
        auto const insertion = std::upper_bound(begin, iter, *iter, lessThan);
        std::rotate(insertion, iter, std::next(iter));
    }
}

template<typename Iterator, typename Comparator = std::less<value_type_t<Iterator>>>
void insertionSort(const Iterator& begin, const Iterator& end, Comparator lessThan = Comparator{}) {
    // if the container is empty
    if (begin == end) {
        return;
    }

    for (Iterator j = begin; j != end; j++) {
        auto key = std::move(*j); // move the value to be inserted
        Iterator i = j;
        while (i != begin && lessThan(key, *(std::prev(i)))) {
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
template<typename Iterator, typename Comparator = std::less<value_type_t<Iterator>>>
void insertionSortInnerForLoop(const Iterator& begin, const Iterator& end, Comparator lessThan = Comparator{}) {
    if (begin == end) {
        return;
    }

    Iterator i;

    for (Iterator j = begin; j != end; j++) {
        auto key = std::move(*j); // move the value to be inserted
        for (i = j; i != begin && lessThan(key, *(prev(i))); i--) {
            *i = std::move(*(std::prev(j)));
        }
        *i = std::move(key);
    }
}

template<typename Container>
void printList(Container& container) {
    for (const auto& element : container) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

// timing test
void testRandom() {
    std::list<int> myList;
    std::cout << "Experiment 3: Random Order\n";
    for (int i = 0; i < 10000; ++i) {
        myList.push_back(rand() % 10000);
    }
    auto start = std::chrono::high_resolution_clock::now();
    insertionSortSTL(myList.begin(), myList.end());
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n\n";
}

int main() {
    testRandom();
    return 0;
}
