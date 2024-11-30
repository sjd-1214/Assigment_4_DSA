#include <iostream>
#include <climits>
using namespace std;

class MinHeap {
private:
    int* heap_array;    // Array to store heap elements
    int max_capacity;   // Maximum capacity of the heap
    int current_size;   // Current size of the heap

    // Helpers
    int parent(int index) { return (index - 1) / 2; }
    int leftChild(int index) { return 2 * index + 1; }
    int rightChild(int index) { return 2 * index + 2; }

    void heapifyDown(int index) {
        int smallest = index;
        int left = leftChild(index);
        int right = rightChild(index);

        if (left < current_size && heap_array[left] < heap_array[smallest])
            smallest = left;
        if (right < current_size && heap_array[right] < heap_array[smallest])
            smallest = right;

        if (smallest != index) {
            swap(heap_array[index], heap_array[smallest]);
            heapifyDown(smallest);
        }
    }

    void heapifyUp(int index) {
        while (index != 0 && heap_array[parent(index)] > heap_array[index]) {
            swap(heap_array[index], heap_array[parent(index)]);
            index = parent(index);
        }
    }

public:
    MinHeap(int max_capacity) {
        this->max_capacity = max_capacity;
        heap_array = new int[max_capacity];
        current_size = 0;
    }

    ~MinHeap() {
        delete[] heap_array;
    }

    void insert(int key) {
        if (current_size == max_capacity) {
            cout << "Heap overflow!" << endl;
            return;
        }

        current_size++;
        int index = current_size - 1;
        heap_array[index] = key;
        heapifyUp(index);
    }

    int extractMin() {
        if (current_size <= 0)
            return INT_MAX;

        if (current_size == 1) {
            current_size--;
            return heap_array[0];
        }

        int root = heap_array[0];
        heap_array[0] = heap_array[current_size - 1];
        current_size--;
        heapifyDown(0);

        return root;
    }

    void extractTopThree() {
        cout << "\n=== Extracting Top 3 Priority Tasks ===" << endl;
        for (int i = 0; i < 3 && current_size > 0; ++i) {
            cout << "- Task with priority: " << extractMin() << endl;
        }
        cout << "=======================================" << endl;
    }

    void printHeap() {
        cout << "Heap Content: ";
        for (int i = 0; i < current_size; i++) {
            cout << heap_array[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    // Array
    int tasks[] = { 15, 10, 20, 8, 12, 25, 18 };
    int num_tasks = sizeof(tasks) / sizeof(tasks[0]);

    // MinHeap
    MinHeap min_heap(20);
    for (int i = 0; i < num_tasks; i++) {
        min_heap.insert(tasks[i]);
    }

    cout << "\n=== Initial Heap Construction ===" << endl;
    min_heap.printHeap();

    //Adding new task
    cout << "\n=== Inserting New Task with Priority 5 ===" << endl;
    min_heap.insert(5);
    min_heap.printHeap();

    // Extracting highest priority task
    cout << "\n=== Extracting the Highest-Priority Task ===" << endl;
    int min_task = min_heap.extractMin();
    cout << "Task extracted with priority: " << min_task << endl;
    min_heap.printHeap();

    // Removing top 3
    min_heap.extractTopThree();
    min_heap.printHeap();

    return 0;
}
