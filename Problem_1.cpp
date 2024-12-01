#include <iostream>
#include <climits>
using namespace std;

class min_heap {
private:
    int* heap_array;
    int max_capacity;
    int current_size;

    int get_parent_index(int index) { return (index - 1) / 2; }
    int get_left_child_index(int index) { return 2 * index + 1; }
    int get_right_child_index(int index) { return 2 * index + 2; }

    void heapify_down(int index) {
        int smallest = index;
        int left_child = get_left_child_index(index);
        int right_child = get_right_child_index(index);

        if (left_child < current_size && heap_array[left_child] < heap_array[smallest])
            smallest = left_child;
        if (right_child < current_size && heap_array[right_child] < heap_array[smallest])
            smallest = right_child;

        if (smallest != index) {
            swap(heap_array[index], heap_array[smallest]);
            heapify_down(smallest);
        }
    }

    void heapify_up(int index) {
        while (index != 0 && heap_array[get_parent_index(index)] > heap_array[index]) {
            swap(heap_array[index], heap_array[get_parent_index(index)]);
            index = get_parent_index(index);
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

    void insert_task(int priority) {
        if (current_size == max_capacity) {
            cout << "Error: Heap Overflow! Cannot insert new task.\n";
            return;
        }

        current_size++;
        int index = current_size - 1;
        heap_array[index] = priority;
        heapify_up(index);
        cout << "Task with priority " << priority << " inserted successfully.\n";
    }

    int extract_min_task() {
        if (current_size <= 0)
            return INT_MAX;

        if (current_size == 1) {
            current_size--;
            return heap_array[0];
        }

        int root_priority = heap_array[0];
        heap_array[0] = heap_array[current_size - 1];
        current_size--;
        heapify_down(0);

        return root_priority;
    }

    void extract_top_three_tasks() {
        cout << "\nExtracting Top 3 Priority Tasks:\n";
        for (int i = 0; i < 3 && current_size > 0; ++i) {
            cout << "   Task with priority: " << extract_min_task() << endl;
        }
        cout << "-------------------------------------\n";
    }

    void display_heap() {
        cout << "Current Heap: ";
        for (int i = 0; i < current_size; i++) {
            cout << heap_array[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    const int max_capacity = 50;
    min_heap task_heap(max_capacity);

    int num_tasks;
    cout << "Enter the number of tasks: ";
    cin >> num_tasks;

    cout << "Enter the priorities of the tasks: ";
    for (int i = 0; i < num_tasks; i++) {
        int task_priority;
        cin >> task_priority;
        task_heap.insert_task(task_priority);
    }

    cout << "\nInitial Heap Constructed Successfully!\n";
    task_heap.display_heap();

    int choice;
    do {
        cout << "\n------------- Menu -------------\n";
        cout << "1. Insert a New Task\n";
        cout << "2. Extract the Highest-Priority Task\n";
        cout << "3. Extract the Top 3 Priority Tasks\n";
        cout << "4. Display the Heap\n";
        cout << "5. Exit\n";
        cout << "---------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int new_priority;
                cout << "Enter the priority of the new task: ";
                cin >> new_priority;
                task_heap.insert_task(new_priority);
                break;
            }
            case 2: {
                int min_priority = task_heap.extract_min_task();
                if (min_priority == INT_MAX)
                    cout << "The heap is empty. No tasks to extract.\n";
                else
                    cout << "Task extracted with priority: " << min_priority << endl;
                break;
            }
            case 3:
                task_heap.extract_top_three_tasks();
                break;
            case 4:
                task_heap.display_heap();
                break;
            case 5:
                cout << "Exiting program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
