#include <iostream>
#include <climits>
using namespace std;

class MinHeap {
private:
    int* heap;      // Array to store heap elements
    int capacity;   // Maximum capacity of the heap
    int size;       // Current size of the heap

    // Helper functions
    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }

    void heapifyDown(int i) {
        int smallest = i;
        int left = leftChild(i);
        int right = rightChild(i);

        if (left < size && heap[left] < heap[smallest])
            smallest = left;
        if (right < size && heap[right] < heap[smallest])
            smallest = right;

        if (smallest != i) {
            swap(heap[i], heap[smallest]);
            heapifyDown(smallest);
        }
    }

    void heapifyUp(int i) {
        while (i != 0 && heap[parent(i)] > heap[i]) {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

public:
    MinHeap(int capacity) {
        this->capacity = capacity;
        heap = new int[capacity];
        size = 0;
    }

    ~MinHeap() {
        delete[] heap;
    }

    void insert(int key) {
        if (size == capacity) {
            cout << "Heap overflow!" << endl;
            return;
        }

        size++;
        int i = size - 1;
        heap[i] = key;
        heapifyUp(i);
    }

    int extractMin() {
        if (size <= 0)
            return INT_MAX;

        if (size == 1) {
            size--;
            return heap[0];
        }

        int root = heap[0];
        heap[0] = heap[size - 1];
        size--;
        heapifyDown(0);

        return root;
    }

    void extractTopThree() {
        cout << "Top 3 priority tasks: ";
        for (int i = 0; i < 3 && size > 0; ++i) {
            cout << extractMin() << " ";
        }
        cout << endl;
    }

    void printHeap() {
        cout << "Heap: ";
        for (int i = 0; i < size; i++) {
            cout << heap[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    // Input array
    int tasks[] = { 15, 10, 20, 8, 12, 25, 18 };
    int n = sizeof(tasks) / sizeof(tasks[0]);

    // Build the MinHeap
    MinHeap minHeap(20);
    for (int i = 0; i < n; i++) {
        minHeap.insert(tasks[i]);
    }

    cout << "Heap after building: ";
    minHeap.printHeap();

    // Insert new task with priority 5
    minHeap.insert(5);
    cout << "Heap after inserting 5: ";
    minHeap.printHeap();

    // Extract the highest-priority task
    int minTask = minHeap.extractMin();
    cout << "Extracted highest-priority task: " << minTask << endl;
    cout << "Heap after extracting the minimum: ";
    minHeap.printHeap();

    // Extract the top 3 priority tasks
    minHeap.extractTopThree();
    cout << "Heap after extracting top 3 tasks: ";
    minHeap.printHeap();

    return 0;
}
