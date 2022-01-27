class SudokuSolver
{
private:
    struct cell
    {
        int row;
        int col;
    };

public:
    SudokuSolver(int size, int const** input)
    : m_size(size)
    , m_sqrt_size(sqrt_int(size))
    {
        m_output = new int*[m_size];
        for (int row = 0; row < m_size; ++row)
        {
            m_output[row] = new int[m_size];
            for (int col = 0; col < m_size; ++col)
            {
                m_output[row][col] = input[row][col];
            }
        }

    }

    ~SudokuSolver()
    {
        for (int row = 0; row < m_size; ++row)
        {
            delete [] m_output[row];
        }
        delete [] m_output;
    }

    int sqrt_int(int val)
    {
        for (int i = 1; i*i <= val; ++i)
        {
            if (i*i == val)
            {
                return i;
            }
        }
        return -1;
    }

    cell next_cell(cell c)
    {
        return {c.row + ((c.col + 1)/m_size), (c.col + 1) % m_size};
    }

    cell get_start_cell_by_square_id(int square_id)
    {
        return {
            (square_id/m_sqrt_size)*m_sqrt_size,
            (square_id % m_sqrt_size)*m_sqrt_size
        };
    }

    int get_square_id(cell c)
    {
        return (c.row/m_sqrt_size)*m_sqrt_size + (c.col/m_sqrt_size);
    }

    bool valid_state(cell c)
    {
        // check row
        for (int col = 0; col < m_size; ++col)
        {
            if (col != c.col && m_output[c.row][col] == m_output[c.row][c.col])
            {
                return false;
            }
        }

        // check column
        for (int row = 0; row < m_size; ++row)
        {
            if (row != c.row && m_output[row][c.col] == m_output[c.row][c.col])
            {
                return false;
            }
        }

        // check local square
        int square_id = get_square_id(c);
        cell start = get_start_cell_by_square_id(square_id);
        cell end = {start.row + m_sqrt_size, start.col + m_sqrt_size};
        for (int row = start.row; row < end.row; ++row)
        {
            for (int col = start.col; col < end.col; ++col)
            {
                if (row != c.row && col != c.col && m_output[row][col] == m_output[c.row][c.col])
                {
                    return false;
                }
            }
        }
        return true;
    }

    bool check_cell(cell c)
    {
        bool val = false;

        // if end is reached
        if (c.row == m_size)
        {
            return true;
        }

        // if pre-filled with value
        if (m_output[c.row][c.col])
        {
            return check_cell(next_cell(c));
        }

        // if cell has no value
        for (int cell_val = 1; cell_val <= m_size; ++cell_val)
        {
            m_output[c.row][c.col] = cell_val;
            if (valid_state(c))
            {
                val = check_cell(next_cell(c));
                if (val)
                {
                    break;
                }
            }
            m_output[c.row][c.col] = 0;
        }
        return val;
    }

    int const** solve()
    {
        if (!check_cell({0, 0}))
        {
            // if there is no solution
            for (int row = 0; row < m_size; ++row)
            {
                for (int col = 0; col < m_size; ++col)
                {
                    if (!m_output[row][col])
                    {
                        m_output[row][col] = -1;
                    }
                }
            }
        }
        return const_cast<int const**>(m_output);
    }
private:
    const int m_size;
    const int m_sqrt_size;
    int** m_output;
};
