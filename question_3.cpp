#include <iostream>
using namespace std;

const int max_cap = 10;

class Queue
{
private:
    int queue[max_cap];
    int front, rear;

public:
    Queue()
    {
        front = -1;
        rear = -1;
    }
    bool empty()
    {
        return front == -1;
    }

    void enqueue(int val)
    {
        if (rear == max_cap - 1)
        {
            cout << "Queue is full!" << endl;
            return;
        }
        if (front == -1)
            front = 0;
        queue[++rear] = val;
    }

    // Remove and return an element from the queue
    int dequeue()
    {
        if (empty())
        {
            cout << "Queue is empty!" << endl;
            return -1;
        }
        int val = queue[front++];
        if (front > rear)
            front = rear = -1;
        return val;
    }
};

class Stack
{
private:
    int stack[max_cap];
    int top;

public:
    Stack()
    {
        top = -1;
    }

    bool empty()
    {
        return top == -1;
    }

    void push(int val)
    {
        if (top == max_cap - 1)
        {
            cout << "Stack is full!" << endl;
            return;
        }
        stack[++top] = val;
    }

    int pop()
    {
        if (empty())
        {
            cout << "Stack is empty!" << endl;
            return -1;
        }
        return stack[top--];
    }
};

class Graph
{
private:
    int matrix[max_cap][max_cap];
    char users[max_cap];
    int usr_count;

    int get_user_num(char user)
    {
        for (int i = 0; i < usr_count; ++i)
        {
            if (users[i] == user)
                return i;
        }
        return -1;
    }

public:
    Graph()
    {
        usr_count = 0;
        for (int i = 0; i < max_cap; ++i)
        {
            for (int j = 0; j < max_cap; ++j)
            {
                matrix[i][j] = 0;
            }
        }
    }

    void add_new_user(char user)
    {
        if (usr_count < max_cap)
        {
            users[usr_count++] = user;
        }
    }

    void add_new_edge(char u, char v)
    {
        int x = get_user_num(u);
        int y = get_user_num(v);

        if (x != -1 && y != -1)
        {
            matrix[x][y] = 1;
            matrix[y][x] = 1;
        }
    }

    void BFS(char start)
    {
        int starting = get_user_num(start);
        if (starting == -1)
            return;

        bool visited_arr[max_cap] = {false};
        Queue q;
        char bfsOrder[max_cap];
        int bfsIndex = 0;

        q.enqueue(starting);
        visited_arr[starting] = true;

        while (!q.empty())
        {
            int temp = q.dequeue();
            bfsOrder[bfsIndex++] = users[temp];

            for (int i = 0; i < usr_count; ++i)
            {
                if (matrix[temp][i] == 1 && !visited_arr[i])
                {
                    q.enqueue(i);
                    visited_arr[i] = true;
                }
            }
        }

        cout << "BFS Traversal: ";
        for (int i = 0; i < bfsIndex; ++i)
        {
            cout << bfsOrder[i] << " ";
        }
        cout << endl;
    }

    void DFS(char start)
    {
        int starting = get_user_num(start);
        if (starting == -1)
            return;

        bool visited_arr[max_cap] = {false};
        Stack s;
        char dfsOrder[max_cap];
        int dfsIndex = 0;

        s.push(starting);

        while (!s.empty())
        {
            int temp = s.pop();

            if (!visited_arr[temp])
            {
                dfsOrder[dfsIndex++] = users[temp];
                visited_arr[temp] = true;

                for (int i = usr_count - 1; i >= 0; --i)
                {
                    if (matrix[temp][i] == 1 && !visited_arr[i])
                    {
                        s.push(i);
                    }
                }
            }
        }

        cout << "DFS Traversal: ";
        for (int i = 0; i < dfsIndex; ++i)
        {
            cout << dfsOrder[i] << " ";
        }
        cout << endl;
    }

    void shortestPath(char start, char end)
    {
        int starting = get_user_num(start);
        int endIndex = get_user_num(end);
        if (starting == -1 || endIndex == -1)
            return;
        bool visited_arr[max_cap] = {false};
        Queue q;
        int parent[max_cap];
        for (int i = 0; i < max_cap; ++i)
            parent[i] = -1;

        q.enqueue(starting);
        visited_arr[starting] = true;

        while (!q.empty())
        {
            int temp = q.dequeue();

            for (int i = 0; i < usr_count; ++i)
            {
                if (matrix[temp][i] == 1 && !visited_arr[i])
                {
                    q.enqueue(i);
                    visited_arr[i] = true;
                    parent[i] = temp;

                    if (i == endIndex)
                        break;
                }
            }
        }

        int path[max_cap], pathIndex = 0;
        for (int at = endIndex; at != -1; at = parent[at])
        {
            path[pathIndex++] = at;
        }

        cout << "Shortest Path from " << start << " to " << end << ": ";
        for (int i = pathIndex - 1; i >= 0; --i)
        {
            cout << users[path[i]] << " ";
        }
        cout << endl;
    }
};

int main()
{
    Graph g;

    g.add_new_user('A');
    g.add_new_user('B');
    g.add_new_user('C');
    g.add_new_user('D');
    g.add_new_user('E');
    g.add_new_user('F');

    g.add_new_edge('A', 'B');
    g.add_new_edge('A', 'C');
    g.add_new_edge('B', 'D');
    g.add_new_edge('B', 'E');
    g.add_new_edge('C', 'F');

    g.BFS('A');
    g.DFS('A');

    g.shortestPath('A', 'E');

    return 0;
}
