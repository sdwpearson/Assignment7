// 
// walkring_timestep.cc
//
// Time stepping module for 1d random walk on a ring
//

#include "walkring_timestep.h"
#include <random>
#include <iostream>

// Perform a single time step for the random walkers
//
// parameters:
//
//  walkerpositions: the positions of a number of walkers (note that
//                   the number of walker Z can be found from
//                   Z=walkerpositions.size())
//
//  N:               the number of possible positions. All positions
//                   in the walkerpositions array should remain
//                   between 0 and N-1
//
//  prob:            the probability to jump to the left. Also the
//                   probability to just right.  (the probability to
//                   stay on the same spot is thus 1-2p.)
//
// output:
//
//  the content of the walkerpositions arrays should have changed to
//  reflect the random movement of all walker (i.e., they will each
//  have been given a chance to move on position to the left or two
//  the right).
//
void walkring_timestep(rarray<int,1>& walkerpositions, int N, double prob)
{
	int seed = 4;								// Randomization seed
	int Z = walkerpositions.size();				// Number of walkers
	double rand_num = 0.0;						// Random number to decide walking direction

    static std::mt19937 engine(seed);
    std::uniform_real_distribution<double> uniformdouble(0.0, 1.0);

    // Cycle through all of the positions
    for (int i=0; i<Z; i++){
    	rand_num = uniformdouble(engine);

	    if(rand_num >= 0.0 && rand_num < prob){ 				// Move Left (decrement)
			if(walkerpositions[i] == 0)								// Loop around to the other side
				walkerpositions[i] = N-1;
			else
				walkerpositions[i]--;
		}
    	else if (rand_num >= prob && rand_num < 2*prob){		// Move Right (increment)
    		if(walkerpositions[i] == N-1)							// Loop around to the other side
    			walkerpositions[i] = 0;
    		else
    			walkerpositions[i]++;
    	}
        														// Else remain in current position        
    }
}


