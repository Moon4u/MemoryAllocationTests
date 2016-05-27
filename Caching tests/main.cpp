#include <iostream>
#include <cstdlib>
#include <cassert>

#include "timing.h"
#include "structs.h"

#define FRAGMENTATION

#define NUMBER_OF_TESTS 100
#define TESTCASES_PER_TEST 2000

#define NUMBER_OF_ITERATION 26000

#define NUMBER_OF_ALLOCATION_TYPES 4
const int memoryAllocation[] = {200, 300, 400, 500};//{50, 20, 30, 40};


int main() 
{
	uint64 startTime = GetTimeMs64();
	uint64 tempStartTime;
	uint64 iterationStartTimer;

	uint64 avrgTime = 0;
	uint64 avrgIterationTimer = 0;

	int index = 0;
	struct memoryFragmentationStr* mFrag = new memoryFragmentationStr;
	mFrag->prev = nullptr;

	for ( int j = 0; j < NUMBER_OF_TESTS; j++ ) 
	{
		tempStartTime				= GetTimeMs64();
		struct cacheTestStr** tests = new cacheTestStr*[ TESTCASES_PER_TEST ];

		for ( int i = 0; i < TESTCASES_PER_TEST; i++ ) 
		{
			tests[ i ] = new cacheTestStr;
#ifndef FRAGMENTATION
		}
		
		for ( int i = 0; i < TESTCASES_PER_TEST; i++ ) 
		{
#endif
			struct memoryFragmentationStr* temp = new memoryFragmentationStr;

			temp->rndMemory = ( void * ) new char[ memoryAllocation[ index ] ];
			index = ( index + 1 ) % NUMBER_OF_ALLOCATION_TYPES;

			temp->prev = mFrag;
			mFrag = temp;
		}

		iterationStartTimer = GetTimeMs64();
		for ( int k = 0; k < NUMBER_OF_ITERATION; k++ ) // one of these loops will get optimised away, most likely
		{
			for ( int i = 0; i < TESTCASES_PER_TEST; i++ )
			{
				tests[ i ]->a = 4;
				tests[ i ]->b = 3;
				tests[ i ]->c = 3;
				tests[ i ]->d = true;
				tests[ i ]->e = .3f;
			}
		}
		avrgIterationTimer += GetTimeMs64() - iterationStartTimer;

		for ( int i = 0; i < TESTCASES_PER_TEST; i++ )
		{
			delete tests[ i ];
			struct memoryFragmentationStr* temp = mFrag->prev;
				
			assert( mFrag != NULL );
			assert( mFrag->rndMemory != NULL );

			delete mFrag->rndMemory;
			delete mFrag;

			mFrag = temp;
		}

		//delete tests;
		avrgTime += GetTimeMs64() - tempStartTime;
	}

	delete mFrag;

	uint64 endTime = GetTimeMs64();

	std::cout << "Total time that it takes to process the data is: " << endTime - startTime << std::endl;
	std::cout << "Average time per " << TESTCASES_PER_TEST << " tests is: " << avrgTime / NUMBER_OF_TESTS << std::endl;
	std::cout << "Average time per iterations cycle is: " << avrgIterationTimer / NUMBER_OF_TESTS << std::endl;
	return 0;
}