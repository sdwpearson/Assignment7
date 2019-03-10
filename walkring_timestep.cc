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
	int seed = 4;
	double rand_num = 0.0;

	// Copy the original positions
	rarray<int,1> walkerpositions_old = walkerpositions.copy();
	int Z_old = walkerpositions_old.size();

	// Blank out the new positions
	walkerpositions.fill(0);

    static std::mt19937 engine(seed);
    std::uniform_int_distribution<int> uniformint(0, 1);

    // Cycle through all of the positions
    for (int i=0; i<N; i++){

        // Go through each of the walkers at each position
        for(int k=0; k<walkerpositions_old[i]; k++){
			rand_num = uniformint(engine);

        	if(rand_num >= 0.0 && rand_num < prob){ 			// Move Left
        		if(k == 0)											// Loop around to the other side
        			walkerpositions[N-1]++;
        		else
        			walkerpositions[k-1]++;
        	}
        	else if (rand_num >= prob && rand_num < 2*prob){	// Move Right
        		if(k == N-1)											// Loop around to the other side
        			walkerpositions[0]++;
        		else
        			walkerpositions[k+1]++;
        	}
        	else {												// Remain in current position
    			walkerpositions[k]++;
        	}
    	}
    }

    int Z_new = walkerpositions.size();
    // Make sure the total amount of walkers remains unchanged
    std::cout << Z_old << ' ' << Z_new << std::endl;
}


