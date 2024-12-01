#include <iostream>
using namespace std;

const int max_cap = 10;

class queue_ds
{
private:
    int queue[max_cap];
    int front, rear;

public:
    queue_ds()
    {
        front = -1;
        rear = -1;
    }

    bool is_empty()
    {
        return front == -1;
    }

    void enqueue(int val)
    {
        if (rear == max_cap - 1)
        {
            cout << "queue is full!" << endl;
            return;
        }
        if (front == -1)
            front = 0;
        queue[++rear] = val;
    }

    int dequeue()
    {
        if (is_empty())
        {
            cout << "queue is empty!" << endl;
            return -1;
        }
        int val = queue[front++];
        if (front > rear)
            front = rear = -1;
        return val;
    }
};

class stack_ds
{
private:
    int stack[max_cap];
    int top;

public:
    stack_ds()
    {
        top = -1;
    }

    bool is_empty()
    {
        return top == -1;
    }

    void push(int val)
    {
        if (top == max_cap - 1)
        {
            cout << "stack is full!" << endl;
            return;
        }
        stack[++top] = val;
    }

    int pop()
    {
        if (is_empty())
        {
            cout << "stack is empty!" << endl;
            return -1;
        }
        return stack[top--];
    }
};

class graph_ds
{
private:
    int matrix[max_cap][max_cap];
    char users[max_cap];
    int user_count;

    int get_user_index(char user)
    {
        for (int i = 0; i < user_count; ++i)
        {
            if (users[i] == user)
                return i;
        }
        return -1;
    }

public:
    graph_ds()
    {
        user_count = 0;
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
        if (user_count < max_cap)
        {
            users[user_count++] = user;
        }
    }

    void add_new_edge(char u, char v)
    {
        int x = get_user_index(u);
        int y = get_user_index(v);

        if (x != -1 && y != -1)
        {
            matrix[x][y] = 1;
            matrix[y][x] = 1;
        }
    }

    void bfs(char start)
    {
        int starting = get_user_index(start);
        if (starting == -1)
            return;

        bool visited[max_cap] = {false};
        queue_ds q;
        char bfs_order[max_cap];
        int bfs_index = 0;

        q.enqueue(starting);
        visited[starting] = true;

        while (!q.is_empty())
        {
            int temp = q.dequeue();
            bfs_order[bfs_index++] = users[temp];

            for (int i = 0; i < user_count; ++i)
            {
                if (matrix[temp][i] == 1 && !visited[i])
                {
                    q.enqueue(i);
                    visited[i] = true;
                }
            }
        }

        cout << "bfs traversal: ";
        for (int i = 0; i < bfs_index; ++i)
        {
            cout << bfs_order[i] << " ";
        }
        cout << endl;
    }

    void dfs(char start)
    {
        int starting = get_user_index(start);
        if (starting == -1)
            return;

        bool visited[max_cap] = {false};
        stack_ds s;
        char dfs_order[max_cap];
        int dfs_index = 0;

        s.push(starting);

        while (!s.is_empty())
        {
            int temp = s.pop();

            if (!visited[temp])
            {
                dfs_order[dfs_index++] = users[temp];
                visited[temp] = true;

                for (int i = user_count - 1; i >= 0; --i)
                {
                    if (matrix[temp][i] == 1 && !visited[i])
                    {
                        s.push(i);
                    }
                }
            }
        }

        cout << "dfs traversal: ";
        for (int i = 0; i < dfs_index; ++i)
        {
            cout << dfs_order[i] << " ";
        }
        cout << endl;
    }

    void shortest_path(char start, char end)
    {
        int starting = get_user_index(start);
        int end_index = get_user_index(end);
        if (starting == -1 || end_index == -1)
            return;

        bool visited[max_cap] = {false};
        queue_ds q;
        int parent[max_cap];
        for (int i = 0; i < max_cap; ++i)
            parent[i] = -1;

        q.enqueue(starting);
        visited[starting] = true;

        while (!q.is_empty())
        {
            int temp = q.dequeue();

            for (int i = 0; i < user_count; ++i)
            {
                if (matrix[temp][i] == 1 && !visited[i])
                {
                    q.enqueue(i);
                    visited[i] = true;
                    parent[i] = temp;

                    if (i == end_index)
                        break;
                }
            }
        }

        int path[max_cap], path_index = 0;
        for (int at = end_index; at != -1; at = parent[at])
        {
            path[path_index++] = at;
        }

        cout << "shortest path from " << start << " to " << end << ": ";
        for (int i = path_index - 1; i >= 0; --i)
        {
            cout << users[path[i]] << " ";
        }
        cout << endl;
    }
};

int main()
{
    graph_ds g;

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

    g.bfs('A');
    g.dfs('A');
    g.shortest_path('A', 'F');

    return 0;
}
