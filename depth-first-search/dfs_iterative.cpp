#include "../sizedstack/sizedstack.cpp"

class Dfs
{
private:
    struct node
    {
        int row;
        int col;
    };

public:
    Dfs(int height, int width, char** input_maze)
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
                    m_start = {row, col};
                }
            }
        }
    }

    ~Dfs()
    {
        for (int row = 0; row < m_height; ++row)
        {
            delete [] m_output_maze[row];
        }
        delete [] m_output_maze;
    }

    char** solve()
    {
        SizedStack<node> stack = SizedStack<node>(m_height*m_width);
        bool in_stack[m_height][m_width]{};
        node prev_node[m_height][m_width]{};

        in_stack[m_start.row][m_start.col] = true;
        stack.push(m_start);

        while (!stack.empty())
        {
            node curr = stack.pop();

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

            // add adjacent nodes in each direction in reverse order
            for (int i = 3; i >= 0; --i)
            {
                node new_node = {curr.row + m_directions[i].row, curr.col + m_directions[i].col};
                int r = new_node.row;
                int c = new_node.col;

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
                // check if already in stack
                if (in_stack[r][c])
                {
                    continue;
                }
                // Add to stack
                in_stack[r][c] = true;
                prev_node[r][c] = curr;
                stack.push(new_node);
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
    node m_directions[4];
};
