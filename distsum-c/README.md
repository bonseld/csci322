Readme for distsum-c
Author: Dylan Bonsell
Date: 1/24/2014

distsum-c requires a single argument with a number of cores, and then prints out a step-by-step table with each core's usage.

The algorithm I used for odd cores, is actually exactly the same as the even core algorithm, to determine which core to sent to you add terms, 
to determine which to send too you subtract terms.
i(+/-)2^(step)

