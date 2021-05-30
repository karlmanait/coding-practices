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
        m_discovered = new bool*[height];
        for (int row = 0; row < height; ++row)
        {
            m_output_maze[row] = new char[width];
            m_discovered[row] = new bool[width];
            for (int col = 0; col < width; ++col)
            {
                m_output_maze[row][col] = input_maze[row][col];
                m_discovered[row][col] = false;
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

    bool branch_out(node curr)
    {
        m_discovered[curr.row][curr.col] = true;
        if (m_output_maze[curr.row][curr.col] == 'e')
        {
            return true;
        }
        m_output_maze[curr.row][curr.col] = '-';

        // recursively branch out in each adjacent nodes
        for (int i = 0; i < 4; ++i)
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
            // check if already discovered
            if (m_discovered[r][c])
            {
                continue;
            }
            // recursive call
            if (branch_out(new_node))
            {
                m_output_maze[curr.row][curr.col] = '+';
                return true;
            }
        }
        return false;
    }

    char** solve()
    {
        branch_out(m_start);
        m_output_maze[m_start.row][m_start.col] = 's';
        return m_output_maze;
    }

private:
    int m_height;
    int m_width;
    char** m_output_maze;
    bool** m_discovered;
    node m_start;
    node m_directions[4];
};
