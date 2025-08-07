// 2D grid based filter
#ifndef GRID_METHOD
#define GRID_METHOD

#include "Eigen/Dense"

namespace gm
{
/////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// Grid /////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
    class grid {
        private:
            const int num_cells;
            const float size_cells;

        public:
            // 2D, arbitrary probability distribution or likelihood
            Eigen::Array<float, Eigen::Dynamic, Eigen::Dynamic> distribution;

            // Mesh of x, y coordinates to underlay an estimation distribution
            Eigen::Array<float, Eigen::Dynamic, Eigen::Dynamic> x_coords;
            Eigen::Array<float, Eigen::Dynamic, Eigen::Dynamic> y_coords;

            grid(int num_cells, float size_cells, Eigen::Array2f center_coords);
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