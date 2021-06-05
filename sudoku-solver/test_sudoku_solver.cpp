#include <iostream>
#include "sudoku_solver.cpp"
#include "gtest/gtest.h"

constexpr int MAX_NUM_CASES = 10;

struct data
{
    int const** expected;
    int const** actual;
    int size;
};

class StdinParser {
public:
    StdinParser()
    : m_index(0)
    {
        std::string input_line;
        do
        {
            input_line.clear();
            std::cin >> input_line;
            if (input_line == "input:")
            {
                std::cin >> m_size[m_index];
                m_input[m_index] = get_data_from_stdin(m_index);
            }
            else if (input_line == "expected_output:")
            {
                m_expected_output[m_index] = get_data_from_stdin(m_index);
                m_solver[m_index] = new SudokuSolver(m_size[m_index], m_input[m_index]);
                m_actual_output[m_index] = m_solver[m_index]->solve();
                m_index++;
            }
        }
        while (!input_line.empty());
    }

    ~StdinParser()
    {
        for (int i = 0; i < m_index; ++i)
        {
            for (int row = 0; row < m_size[i]; ++row)
            {
                delete [] m_input[i][row];
                delete [] m_expected_output[i][row];
            }
            delete [] m_input[i];
            delete [] m_expected_output[i];
            delete m_solver[i];
        }
    }

    int const** get_data_from_stdin(int index)
    {
        int** maze = new int*[m_size[index]];
        for (int row = 0; row < m_size[index]; ++row)
        {
            maze[row] = new int[m_size[index]];
            for (int col = 0; col < m_size[index]; ++col)
            {
                std::cin >> maze[row][col];
            }
        }
        return const_cast<int const**>(maze);
    }

    void print_arr(int index, int const** arr)
    {
        for (int row = 0; row < m_size[index]; ++row)
        {
            for (int col = 0; col < m_size[index]; ++col)
            {
                if (arr[row][col] < 10 && arr[row][col] >= 0)
                {
                    std::cout << " ";
                }
                std::cout << arr[row][col] << " ";
            }
            std::cout << "\n";
        }
    }

    void print(int index)
    {
        std::cout << "============================\n";

        std::cout << "Input:\n";
        print_arr(index, m_input[index]);

        std::cout << "\nExpected output:\n";
        print_arr(index, m_expected_output[index]);

        std::cout << "\nActual output:\n";
        print_arr(index, m_actual_output[index]);
    }

    data get_data(int index)
    {
        return {m_expected_output[index], m_actual_output[index], m_size[index]};
    }

private:
    int m_index;
    int const** m_input[MAX_NUM_CASES];
    int const** m_expected_output[MAX_NUM_CASES];
    int const** m_actual_output[MAX_NUM_CASES];
    SudokuSolver* m_solver[MAX_NUM_CASES];
    int m_size[MAX_NUM_CASES];
};

class SudokuParameterizedTestFixture :public ::testing::TestWithParam<int>
{
};

StdinParser* stdin_data;

TEST_P(SudokuParameterizedTestFixture, PerTestCase)
{
    int index = GetParam();
    data d = stdin_data->get_data(index);
    stdin_data->print(index);
    for (int row = 0; row < d.size; ++row)
    {
        for (int col = 0; col < d.size; ++col)
        {
            EXPECT_EQ(d.expected[row][col], d.actual[row][col]) <<
                "Does not match at row: " << row << ", col: " << col;
        }
    }
}

INSTANTIATE_TEST_CASE_P(
    SudokuTests,
    SudokuParameterizedTestFixture,
    ::testing::Values(0, 1, 2, 3, 4)
);

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    stdin_data = new StdinParser;
    return RUN_ALL_TESTS();
}
