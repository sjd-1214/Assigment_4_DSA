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
    int max_capacity = 50;
    MinHeap min_heap(max_capacity);

    int num_tasks;
    cout << "Enter the number of tasks: ";
    cin >> num_tasks;

    cout << "Enter the priorities of the tasks: ";
    for (int i = 0; i < num_tasks; i++) {
        int task_priority;
        cin >> task_priority;
        min_heap.insert(task_priority);
    }

    cout << "\n=== Initial Heap Construction ===" << endl;
    min_heap.printHeap();

    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Insert a new task\n";
        cout << "2. Extract the highest-priority task\n";
        cout << "3. Extract the top 3 priority tasks\n";
        cout << "4. Display the heap\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            int new_priority;
            cout << "Enter the priority of the new task: ";
            cin >> new_priority;
            min_heap.insert(new_priority);
            cout << "Task inserted successfully.\n";
        } else if (choice == 2) {
            int min_task = min_heap.extractMin();
            if (min_task == INT_MAX)
                cout << "The heap is empty.\n";
            else
                cout << "Task extracted with priority: " << min_task << endl;
        } else if (choice == 3) {
            min_heap.extractTopThree();
        } else if (choice == 4) {
            min_heap.printHeap();
        } else if (choice == 5) {
            cout << "Exiting program. Goodbye!\n";
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
