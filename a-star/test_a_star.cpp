#include <iostream>
#include "a_star.cpp"
#include "gtest/gtest.h"

constexpr int MAX_NUM_CASES = 10;

struct data
{
    char** expected;
    char** actual;
    int height;
    int width;
};

class StdinParser {
public:
    StdinParser()
    : m_index(0)
    {
        std::string input_line;
        do
        {
            std::cin >> input_line;
            if (input_line == "input:")
            {
                std::cin >> m_height[m_index] >> m_width[m_index];
                m_input[m_index] = get_maze_from_stdin(m_index);
            }
            else if (input_line == "expected_output:")
            {
                m_expected_output[m_index] = get_maze_from_stdin(m_index);
                m_solver[m_index] = new AStar(m_height[m_index], m_width[m_index], m_input[m_index]);
                m_actual_output[m_index] = m_solver[m_index]->solve();
                m_index++;
            }
        }
        while (!input_line.empty() && input_line != "legends:");
    }

    ~StdinParser()
    {
        for (int i = 0; i < m_index; ++i)
        {
            for (int row = 0; row < m_height[i]; ++row)
            {
                delete [] m_input[i][row];
                delete [] m_expected_output[i][row];
            }
            delete [] m_input[i];
            delete [] m_expected_output[i];
            delete m_solver[i];
        }
    }

    char** get_maze_from_stdin(int index)
    {
        char** maze = new char*[m_height[index]];
        for (int row = 0; row < m_height[index]; ++row)
        {
            maze[row] = new char[m_width[index]];
            for (int col = 0; col < m_width[index]; ++col)
            {
                std::cin >> maze[row][col];
            }
        }
        return maze;
    }

    void print(int index)
    {
        std::cout << "============================\n";
        std::cout << "Input:\n";
        for (int row = 0; row < m_height[index]; ++row)
        {
            for (int col = 0; col < m_width[index]; ++col)
            {
                std::cout << m_input[index][row][col] << " ";
            }
            std::cout << "\n";
        }
        std::cout << "\nExpected output:\n";
        for (int row = 0; row < m_height[index]; ++row)
        {
            for (int col = 0; col < m_width[index]; ++col)
            {
                std::cout << m_expected_output[index][row][col] << " ";
            }
            std::cout << "\n";
        }
        std::cout << "\nActual output:\n";
        for (int row = 0; row < m_height[index]; ++row)
        {
            for (int col = 0; col < m_width[index]; ++col)
            {
                std::cout << m_actual_output[index][row][col] << " ";
            }
            std::cout << "\n";
        }
    }

    data get_data(int index)
    {
        return {m_expected_output[index], m_actual_output[index], m_height[index], m_width[index]};
    }

private:
    int m_index;
    char** m_input[MAX_NUM_CASES];
    char** m_expected_output[MAX_NUM_CASES];
    char** m_actual_output[MAX_NUM_CASES];
    AStar* m_solver[MAX_NUM_CASES];
    int m_height[MAX_NUM_CASES];
    int m_width[MAX_NUM_CASES];
};

class AStarParameterizedTestFixture :public ::testing::TestWithParam<int>
{
};

StdinParser* stdin_data;

TEST_P(AStarParameterizedTestFixture, PerTestCase)
{
    int index = GetParam();
    data d = stdin_data->get_data(index);
    stdin_data->print(index);
    for (int row = 0; row < d.height; ++row)
    {
        for (int col = 0; col < d.width; ++col)
        {
            EXPECT_EQ(d.expected[row][col], d.actual[row][col]) <<
                "Does not match at row: " << row << ", col: " << col;
        }
    }
}

INSTANTIATE_TEST_CASE_P(
    AStarTests,
    AStarParameterizedTestFixture,
    ::testing::Values(0, 1, 2, 3, 4)
);

int main(int argc, char **argv)
{
    setlocale(LC_ALL, "C.UTF-8");
    testing::InitGoogleTest(&argc, argv);
    stdin_data = new StdinParser;
    return RUN_ALL_TESTS();
}
