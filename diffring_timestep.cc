// 
// diffring_timestep.cc
//
// Time step module for 1d diffusion on a ring
//

#include "diffring_timestep.h"
#include <cblas.h>
#include <cmath>

// perform a single time step for the random walkers
void diffring_timestep(const rarray<double,2>& F, rarray<double,1>& P)
{
    ////////////////////////////////////////////////
    //                                            //
    // IMPLEMENT THIS AS PART OF YOUR ASSIGNMENT! //
    //                                            //
    ////////////////////////////////////////////////
}

// fill the matrix needed in perform_time_step
void diffring_fill_timestep_matrix(rarray<double,2>& F, double D, double dt, double dx)
{
    int N = F.extent(1);            // Number of points in the x dimension
    double alpha = D*dt/(dx^2);     // timestepping coefficient

    // Initialize F as 0s
    F.fill(0.0);

    // Row index
    for(int i=0; i<N; i++){
        if(i == 0){                 // B.C. #1
            F[i][N-1] = alpha;
            F[i][1] = alpha;
            F[i][0] = 1-2*alpha;
        }
        else if (i == (N-1)){       // B.C. #2
            F[i][0] = alpha;
            F[i][N-2] = alpha;
            F[i][N-1] = 1-2*alpha;
        }
        else {                      // All other points
            F[i][i-1] = alpha;
            F[i][i+1] = alpha;
            F[i][i] = 1-2*alpha;
        }
    }

}
