// Zaidy Mae S. Sacayan, BSCS 2B
// Treasure Hunt with Priority: A Heap Adventure
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to display the heap
void displayHeap(const vector<int>& heap) {
    cout << "Current Treasure Hunt with Priority: A Heap Adventureies (Heap): ";
    for (int priority : heap) {
        cout << priority << " ";
    }
    cout << endl;
}

// Function to "heapify up" (for insertion)
void heapifyUp(vector<int>& heap, int index, bool isMaxHeap) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if ((isMaxHeap && heap[index] > heap[parent]) || (!isMaxHeap && heap[index] < heap[parent])) {
            swap(heap[index], heap[parent]);
            index = parent;
        } else {
            break;
        }
    }
}

// Function to "heapify down" (for removal)
void heapifyDown(vector<int>& heap, int index, bool isMaxHeap) {
    int size = heap.size();
    while (true) {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int target = index;

        if (leftChild < size && ((isMaxHeap && heap[leftChild] > heap[target]) || (!isMaxHeap && heap[leftChild] < heap[target]))) {
            target = leftChild;
        }
        if (rightChild < size && ((isMaxHeap && heap[rightChild] > heap[target]) || (!isMaxHeap && heap[rightChild] < heap[target]))) {
            target = rightChild;
        }
        if (target != index) {
            swap(heap[index], heap[target]);
            index = target;
        } else {
            break;
        }
    }
}

// Function to insert a treasure into the heap
void insertTreasure(vector<int>& heap, int priority, bool isMaxHeap) {
    heap.push_back(priority);
    heapifyUp(heap, heap.size() - 1, isMaxHeap);
    displayHeap(heap);
}

// Function to remove a specific treasure from the heap
void removeSpecificTreasure(vector<int>& heap, int priority, bool isMaxHeap) {
    auto it = find(heap.begin(), heap.end(), priority);
    if (it == heap.end()) {
        cout << "Treasure with priority " << priority << " not found!" << endl;
        return;
    }

    cout << "Removing treasure with priority " << priority << "." << endl;
    int index = distance(heap.begin(), it);
    heap[index] = heap.back(); // Replace with the last element
    heap.pop_back(); // Remove the last element

    if (index < heap.size()) {
        heapifyDown(heap, index, isMaxHeap);
        heapifyUp(heap, index, isMaxHeap);
    }

    displayHeap(heap);
}

// Function to convert between Max-Heap and Min-Heap
void toggleHeapType(vector<int>& heap, bool& isMaxHeap) {
    isMaxHeap = !isMaxHeap;
    if (isMaxHeap) {
        cout << "Converting to Max-Heap..." << endl;
        make_heap(heap.begin(), heap.end(), less<>());
    } else {
        cout << "Converting to Min-Heap..." << endl;
        make_heap(heap.begin(), heap.end(), greater<>());
    }
    displayHeap(heap);
}

// Main Treasure Hunt menu
void treasureHuntWithPriority() {
    cout << "\n===========================| Welcome to the Treasure Hunt with Priority! |===========================\n" << endl;
    cout << "In this adventure, treasures have priority levels, and you must manage their retrieval using heaps." << endl;

    vector<int> heap; // Vector to store the heap elements
    bool isMaxHeap = true; // Initial heap is a Max-Heap

    while (true) {
        cout << "\nChoose an action:" << endl;
        cout << "A. Add a treasure to the heap" << endl;
        cout << "B. Remove a specific priority treasure" << endl;
        cout << "C. Convert between Max-Heap and Min-Heap" << endl;
        cout << "D. Exit the hunt" << endl;

        char choice;
        cout << "Enter your choice (A/B/C/D): ";
        cin >> choice;

        if (choice == 'A' || choice == 'a') {
            int priority;
            cout << "Enter the priority of the treasure: ";
            cin >> priority;
            insertTreasure(heap, priority, isMaxHeap);

        } else if (choice == 'B' || choice == 'b') {
            if (heap.empty()) {
                cout << "No treasures to remove!" << endl;
                continue;
            }
            int priority;
            cout << "Enter the priority of the treasure to remove: ";
            cin >> priority;
            removeSpecificTreasure(heap, priority, isMaxHeap);

        } else if (choice == 'C' || choice == 'c') {
            if (heap.empty()) {
                cout << "Heap is empty! Cannot convert." << endl;
                continue;
            }
            toggleHeapType(heap, isMaxHeap);

        } else if (choice == 'D' || choice == 'd') {
            cout << "Thanks for participating in the Treasure Hunt with Priority!" << endl;
            break;

        } else {
            cout << "Invalid choice! Please try again." << endl;
        }
    }
}

// Main function
int main() {
    treasureHuntWithPriority();
    return 0;
}
