#ifndef __STRUCTS_H_
#define __STRUCTS_H_

struct cacheTestStr
{
	int a;
	int b;
	char c;
	bool d;
	float e;
};


struct memoryFragmentationStr
{
	void *rndMemory;
	struct memoryFragmentationStr * prev;
};


#endif /// __STRUCTS_H_
