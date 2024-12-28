#ifndef HEADER_H
#define HEADER_H

#include "List.hpp"

class MyMemoryBlock {
	private:
		int index;
		int length;
	public:
		MyMemoryBlock(int ind=0, int len=0);
		int get_length();
		int get_index();
		int allocate_mem(int len);
		void free_mem(int len);
};

class MyMemory {
	private:
		cop4530::List<MyMemoryBlock> mlist;
		int max_index;
		int block_size;
	public:
		MyMemory(int num=0, int len=0);
		~MyMemory();
		void resize(int num=100, int len=100);
		int req_mem(int len);
		bool release_mem(int ind, int len);
		void merge_mem();
		void dump();
};

#endif
