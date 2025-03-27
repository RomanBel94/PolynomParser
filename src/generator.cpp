#include <fstream>

int main()
{
    std::ofstream output("polynoms.txt");
    if (!output.is_open())
        exit(EXIT_FAILURE);

    for (int i{0}; i < 2; ++i)
    {
        for (int j{0}; j < 256; ++j)
        {
            output << j << ' ' << j + 1 << '\n';
        }
        output << '\n';
    }

    return EXIT_SUCCESS;
}