#include <iostream>
#include <climits>
using namespace std;

class min_heap {
private:
    int* heap_array;
    int max_capacity;
    int current_size;

    int parent(int index) { return (index - 1) / 2; }
    int left_child(int index) { return 2 * index + 1; }
    int right_child(int index) { return 2 * index + 2; }

    void heapify_down(int index) {
        int smallest = index;
        int left = left_child(index);
        int right = right_child(index);

        if (left < current_size && heap_array[left] < heap_array[smallest])
            smallest = left;
        if (right < current_size && heap_array[right] < heap_array[smallest])
            smallest = right;

        if (smallest != index) {
            swap(heap_array[index], heap_array[smallest]);
            heapify_down(smallest);
        }
    }

    void heapify_up(int index) {
        while (index != 0 && heap_array[parent(index)] > heap_array[index]) {
            swap(heap_array[index], heap_array[parent(index)]);
            index = parent(index);
        }
    }

public:
    min_heap(int max_capacity) {
        this->max_capacity = max_capacity;
        heap_array = new int[max_capacity];
        current_size = 0;
    }

    ~min_heap() {
        delete[] heap_array;
    }

    void insert(int key) {
        if (current_size == max_capacity) {
            cout << "heap overflow!" << endl;
            return;
        }

        current_size++;
        int index = current_size - 1;
        heap_array[index] = key;
        heapify_up(index);
    }

    int extract_min() {
        if (current_size <= 0)
            return INT_MAX;

        if (current_size == 1) {
            current_size--;
            return heap_array[0];
        }

        int root = heap_array[0];
        heap_array[0] = heap_array[current_size - 1];
        current_size--;
        heapify_down(0);

        return root;
    }

    void extract_top_three() {
        cout << "\n=== extracting top 3 priority tasks ===" << endl;
        for (int i = 0; i < 3 && current_size > 0; ++i) {
            cout << "- task with priority: " << extract_min() << endl;
        }
        cout << "=======================================" << endl;
    }

    void print_heap() {
        cout << "heap content: ";
        for (int i = 0; i < current_size; i++) {
            cout << heap_array[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    int max_capacity = 50;
    min_heap task_heap(max_capacity);

    int num_tasks;
    cout << "enter the number of tasks: ";
    cin >> num_tasks;

    cout << "enter the priorities of the tasks: ";
    for (int i = 0; i < num_tasks; i++) {
        int task_priority;
        cin >> task_priority;
        task_heap.insert(task_priority);
    }

    cout << "\n=== initial heap construction ===" << endl;
    task_heap.print_heap();

    int choice;
    do {
        cout << "\nmenu:\n";
        cout << "1. insert a new task\n";
        cout << "2. extract the highest-priority task\n";
        cout << "3. extract the top 3 priority tasks\n";
        cout << "4. display the heap\n";
        cout << "5. exit\n";
        cout << "enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            int new_priority;
            cout << "enter the priority of the new task: ";
            cin >> new_priority;
            task_heap.insert(new_priority);
            cout << "task inserted successfully.\n";
        } else if (choice == 2) {
            int min_task = task_heap.extract_min();
            if (min_task == INT_MAX)
                cout << "the heap is empty.\n";
            else
                cout << "task extracted with priority: " << min_task << endl;
        } else if (choice == 3) {
            task_heap.extract_top_three();
        } else if (choice == 4) {
            task_heap.print_heap();
        } else if (choice == 5) {
            cout << "exiting program. goodbye!\n";
        } else {
            cout << "invalid choice. please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
