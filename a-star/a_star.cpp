#include "../priorityqueue/priorityqueue.cpp"

class AStar
{
private:
    struct node
    {
        int row;
        int col;
        int dist;
    };

public:
    AStar(int height, int width, char** input_maze)
    : m_height(height)
    , m_width(width)
    {
        // initialize all direction traversal using clock direction
        m_directions[0] = {-1, 0};
        m_directions[1] = {0, 1};
        m_directions[2] = {1, 0};
        m_directions[3] = {0, -1};

        // initialization of output
        m_output_maze = new char*[height];
        for (int row = 0; row < height; ++row)
        {
            m_output_maze[row] = new char[width];
            for (int col = 0; col < width; ++col)
            {
                m_output_maze[row][col] = input_maze[row][col];
                if (input_maze[row][col] == 's')
                {
                    m_start = {row, col, 0};
                }
                else if (input_maze[row][col] == 'e')
                {
                    m_end = {row, col, 0};
                }
            }
        }
    }

    ~AStar()
    {
        for (int row = 0; row < m_height; ++row)
        {
            delete [] m_output_maze[row];
        }
        delete [] m_output_maze;
    }

    int get_dist(int row, int col)
    {
        switch(m_output_maze[row][col])
        {
            case '.':
                return 1;
            case ',':
                return 2;
            case ':':
                return 3;
            case ';':
                return 4;
        }
        return 0;
    }

    int abs(int val)
    {
        return val > 0 ? val : -val;
    }

    int heuristic_dist(int row, int col)
    {
        return abs(m_end.row - row) + abs(m_end.col - col);
    }

    char** solve()
    {
        PriorityQueue<node> queue;
        bool in_queue[m_height][m_width]{};
        node prev_node[m_height][m_width]{};

        in_queue[m_start.row][m_start.col] = true;
        queue.push(0, m_start);

        while (!queue.empty())
        {
            node curr = queue.pop();

            if (m_output_maze[curr.row][curr.col] == 'e')
            {
                // traceback to start
                node trace = prev_node[curr.row][curr.col];
                while (trace.row != m_start.row || trace.col != m_start.col)
                {
                    int r = trace.row;
                    int c = trace.col;
                    m_output_maze[r][c] = '+';
                    trace = prev_node[r][c];
                }
                break;
            }
            m_output_maze[curr.row][curr.col] = '-';

            // add adjacent nodes in each direction
            for (int i = 0; i < 4; ++i)
            {
                int r = curr.row + m_directions[i].row;
                int c = curr.col + m_directions[i].col;

                // check if out of bounds
                if (r < 0 || r >= m_height || c < 0 || c >= m_width)
                {
                    continue;
                }
                // check if not passable
                if (m_output_maze[r][c] == 'X')
                {
                    continue;
                }
                // check if already in queue
                if (in_queue[r][c])
                {
                    continue;
                }

                int dist = curr.dist + get_dist(r, c);
                node new_node = {r, c, dist};
                // add to priority queue
                in_queue[r][c] = true;
                prev_node[r][c] = curr;
                // needs to be negative since PriorityQueue prioritizes higher values
                queue.push(-(dist + heuristic_dist(r, c)), new_node);
            }
        }
        m_output_maze[m_start.row][m_start.col] = 's';
        return m_output_maze;
    }

private:
    int m_height;
    int m_width;
    char** m_output_maze;
    node m_start;
    node m_end;
    node m_directions[4];
};
