#include "grid_method.h"

#include <iostream>
#include "Eigen/Dense"

/////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// Grid /////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
gm::grid::grid(int num_dims) //, std::vector<std::string> dim_names, std::vector<float> dim_resolutions, std::vector<float> dim_lengths, std::vector<float> dim_origins
    : num_dims(num_dims)//, dim_names(dim_names), dim_resolutions(dim_resolutions), dim_origins(dim_origins)
    {
        if (dim_names.size() != num_dims or dim_resolutions.size() != num_dims or dim_lengths.size() != num_dims) {
            std::cout << "You done goofed, the inputs should all be the same length!";
        }

        // dim_sizes = 
    }

/////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// Grid Filter //////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
gm::grid_filter_2d::grid_filter_2d(float delta_t, float delta_grid)
    : delta_t(delta_t), delta_grid(delta_grid)
    {}