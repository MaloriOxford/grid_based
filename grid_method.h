// 2D grid based filter
#ifndef GRID_METHOD
#define GRID_METHOD

#include <vector>
#include "Eigen/Dense"

namespace gm
{
/////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// Grid /////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
    class grid {
        private:
            const int num_dims; // The number of dimensions of this grid
            const std::vector<std::string> dim_names; // The names of each dimension being stored (e.g. x, y, x_vel, y_vel)
            const std::vector<float> dim_resolutions; // The resolutions of each dimension in their appropriate units (e.g. 0.05 m)
            std::vector<float> dim_lengths;  // How long each dimension is (e.g. 10 m, 5 m/s)
            std::vector<float> dim_origins; // The value of the first cell in each dimension
            std::vector<int> dim_sizes;  // How many cells long each dimension is.  Note: Equals dim_lengths / dim_resolutions and should be an odd number

        public:
            Eigen::Vector<float, Eigen::Dynamic> distribution; // The distribution being tracked by this grid

            grid(int num_dims); //, std::vector<std::string> dim_names, std::vector<float> dim_resolutions, std::vector<float> dim_lengths, std::vector<float> dim_origins
    };

/////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// Grid Filter //////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

    class grid_filter_2d {
    private:
        // The grid containing the probability distribution representing the estimate of the x, y position
        // grid estimation_grid;
        const float delta_t;
        const float delta_grid;
        
        float tether_margin;

        // Covarriance matricies for sensor noise, all 2 x 2
        Eigen::Matrix2f noise_dvl;
        Eigen::Matrix2f noise_camera;
        Eigen::Matrix2f noise_sonar;
        
        // Sensor bounds, lower then upper in radians
        Eigen::Array2f bounds_camera;
        Eigen::Array2f bounds_sonar;
        
        // Constant, uniform current as x vel, y vel in m/s
        Eigen::Array2f velocity_current;
        
        void update_grid(Eigen::Array2f xy_usv_k, float tether_len_k, float tether_len_km1, float z_uuv_k, float z_uuv_km1);
        void camera_likelihood();
        void sonar_likelihood();
        void tether_likelihood();
    
    public:
        // Computes probabalistic FRS and applies it to the estimate
        void predict(Eigen::Array2f velocity_dvl, float psi_uuv_k);

        // Applies corrections from sensor readings to the estimate
        void correct(float tether_len_k, Eigen::Array2f xy_uuv_k, Eigen::Array3f xyp_usv_k, Eigen::Array4f xyzp_uuv_true_k, Eigen::Array3f xyp_usv_true_k);
        
        // Returns the x, y mean of the estimation distribution function
        Eigen::Array2f point_estimate(void);

        grid_filter_2d(float delta_t, float delta_grid);
    };
}

#endif /* GRID_METHOD */