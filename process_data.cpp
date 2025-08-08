#include <iostream>
#include <vector>

#include "grid_method.h"

int main() {
    std::vector<std::string> dim_names = {"x", "y"};
    std::vector<float> dim_resolutions = {1.0, 1.0};
    std::vector<float> dim_lengths = {2.0, 1.0};
    std::vector<float> dim_origins = {3.0, 3.0};

    // gm::grid testy(4); //, dim_names, dim_resolutions, dim_lengths, dim_origins

    // char iny;
    std::cout << dim_names[0] + '\n';
    // std::cin >> iny;
    return 0;
}