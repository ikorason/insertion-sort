#include <iostream>
#include <list>

using namespace std;

template<typename Iterator, typename Comparator>
void insertionSort(const Iterator& begin, const Iterator& end, Comparator lessThan) {
    // if the container is empty
    if (begin == end) {
        return;
    }

    for (Iterator j = begin; j != end; j++) {
        auto key = move(*j); // move the value to be inserted
        Iterator i = j;
        while (i != begin && lessThan(key, *(prev(i)))) {
            *i = move(*(prev(i)));
            i--;
        }
        // insert the key into it's correct position
        *i = move(key);
    }
}

// template<typename Iterator, typename Comparator>
// void insertionSort(const Iterator& begin, const Iterator& end, Comparator lessThan) {
//     // if the container is empty
//     if (begin == end) {
//         return;
//     }

//     Iterator j;

//     for (Iterator p = begin; p != end; p++) {
//         auto key = move(*p); // move the value to be inserted
//         for (j = p; j != begin && lessThan(key, *(prev(j))); j--) {
//             *j = move(*(prev(j)));
//         }
//         *j = move(key);
//     }
// }

/**
 * Tthe two-parameter version calls the three-parameter version,
 * using C++11 decltype
*/
template<typename Iterator>
void insertionSort(const Iterator& begin, const Iterator& end) {
    insertionSort(begin, end, less<decltype(*begin)>{});
}

int main() {
    // list<int> l = {4,2,5,1,3};
    list<int> l = {5,2,9,1,5};

    cout << "Original list: ";

    for (const auto& l : l)
    {
        cout << l << " ";
    }
    cout << endl;

    insertionSort(l.begin(), l.end());

    cout << "Sorted list: ";
    for (const auto& l : l)
    {
        cout << l << " ";
    }
    cout << endl;

    return 0;
}
