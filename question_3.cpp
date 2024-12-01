#include <iostream>
using namespace std;

const int max_capacity = 10;

class queue_ds {
private:
    int queue[max_capacity];
    int front_index, rear_index;

public:
    queue_ds() {
        front_index = -1;
        rear_index = -1;
    }

    bool is_empty() {
        return front_index == -1;
    }

    void enqueue(int value) {
        if (rear_index == max_capacity - 1) {
            cout << "Error: Queue is full!" << endl;
            return;
        }
        if (front_index == -1)
            front_index = 0;
        queue[++rear_index] = value;
    }

    int dequeue() {
        if (is_empty()) {
            cout << "Error: Queue is empty!" << endl;
            return -1;
        }
        int value = queue[front_index++];
        if (front_index > rear_index)
            front_index = rear_index = -1;
        return value;
    }
};

class stack_ds {
private:
    int stack[max_capacity];
    int top_index;

public:
    stack_ds() {
        top_index = -1;
    }

    bool is_empty() {
        return top_index == -1;
    }

    void push(int value) {
        if (top_index == max_capacity - 1) {
            cout << "Error: Stack is full!" << endl;
            return;
        }
        stack[++top_index] = value;
    }

    int pop() {
        if (is_empty()) {
            cout << "Error: Stack is empty!" << endl;
            return -1;
        }
        return stack[top_index--];
    }
};

class graph_ds {
private:
    int adjacency_matrix[max_capacity][max_capacity];
    char user_labels[max_capacity];
    int user_count;

    int get_user_index(char user_label) {
        for (int i = 0; i < user_count; ++i) {
            if (user_labels[i] == user_label)
                return i;
        }
        return -1;
    }

public:
    graph_ds() {
        user_count = 0;
        for (int i = 0; i < max_capacity; ++i) {
            for (int j = 0; j < max_capacity; ++j) {
                adjacency_matrix[i][j] = 0;
            }
        }
    }

    void add_new_user(char user_label) {
        if (user_count < max_capacity) {
            user_labels[user_count++] = user_label;
        }
    }

    void add_new_edge(char user_a, char user_b) {
        int index_a = get_user_index(user_a);
        int index_b = get_user_index(user_b);

        if (index_a != -1 && index_b != -1) {
            adjacency_matrix[index_a][index_b] = 1;
            adjacency_matrix[index_b][index_a] = 1;
        }
    }

    void bfs(char start_user) {
        int start_index = get_user_index(start_user);
        if (start_index == -1)
            return;

        bool visited[max_capacity] = {false};
        queue_ds queue;
        char bfs_traversal[max_capacity];
        int traversal_index = 0;

        queue.enqueue(start_index);
        visited[start_index] = true;

        while (!queue.is_empty()) {
            int current_index = queue.dequeue();
            bfs_traversal[traversal_index++] = user_labels[current_index];

            for (int i = 0; i < user_count; ++i) {
                if (adjacency_matrix[current_index][i] == 1 && !visited[i]) {
                    queue.enqueue(i);
                    visited[i] = true;
                }
            }
        }

        cout << "\nBreadth-First Search (BFS) Traversal:\n";
        for (int i = 0; i < traversal_index; ++i) {
            cout << " -> " << bfs_traversal[i];
        }
        cout << endl;
    }

    void dfs(char start_user) {
        int start_index = get_user_index(start_user);
        if (start_index == -1)
            return;

        bool visited[max_capacity] = {false};
        stack_ds stack;
        char dfs_traversal[max_capacity];
        int traversal_index = 0;

        stack.push(start_index);

        while (!stack.is_empty()) {
            int current_index = stack.pop();

            if (!visited[current_index]) {
                dfs_traversal[traversal_index++] = user_labels[current_index];
                visited[current_index] = true;

                for (int i = user_count - 1; i >= 0; --i) {
                    if (adjacency_matrix[current_index][i] == 1 && !visited[i]) {
                        stack.push(i);
                    }
                }
            }
        }

        cout << "\nDepth-First Search (DFS) Traversal:\n";
        for (int i = 0; i < traversal_index; ++i) {
            cout << " -> " << dfs_traversal[i];
        }
        cout << endl;
    }

    void shortest_path(char start_user, char end_user) {
        int start_index = get_user_index(start_user);
        int end_index = get_user_index(end_user);
        if (start_index == -1 || end_index == -1)
            return;

        bool visited[max_capacity] = {false};
        queue_ds queue;
        int parent[max_capacity];
        for (int i = 0; i < max_capacity; ++i)
            parent[i] = -1;

        queue.enqueue(start_index);
        visited[start_index] = true;

        while (!queue.is_empty()) {
            int current_index = queue.dequeue();

            for (int i = 0; i < user_count; ++i) {
                if (adjacency_matrix[current_index][i] == 1 && !visited[i]) {
                    queue.enqueue(i);
                    visited[i] = true;
                    parent[i] = current_index;

                    if (i == end_index)
                        break;
                }
            }
        }

        int path[max_capacity], path_length = 0;
        for (int at = end_index; at != -1; at = parent[at]) {
            path[path_length++] = at;
        }

        cout << "\nShortest Path from " << start_user << " to " << end_user << ":\n";
        for (int i = path_length - 1; i >= 0; --i) {
            cout << " -> " << user_labels[path[i]];
        }
        cout << endl;
    }
};

int main() {
    graph_ds graph;

    graph.add_new_user('A');
    graph.add_new_user('B');
    graph.add_new_user('C');
    graph.add_new_user('D');
    graph.add_new_user('E');
    graph.add_new_user('F');

    graph.add_new_edge('A', 'B');
    graph.add_new_edge('A', 'C');
    graph.add_new_edge('B', 'D');
    graph.add_new_edge('B', 'E');
    graph.add_new_edge('C', 'F');

    graph.bfs('A');
    graph.dfs('A');
    graph.shortest_path('A', 'E');

    return 0;
}
