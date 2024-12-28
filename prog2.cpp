#include "header.h"

// MYMEMORYBLOCK CLASS

MyMemoryBlock::MyMemoryBlock(int ind, int len) {
	index = ind;
	length = len;
}

int MyMemoryBlock::get_length() {
	return length;
}

int MyMemoryBlock::get_index() {
	return index;
}

int MyMemoryBlock::allocate_mem(int len) {
	if (len > length) {
		return -1;
	}
	else {
		length-=len;
		return len;
	}
}

void MyMemoryBlock::free_mem(int len) {
	length+=len;
}


// MYMEMORY CLASS

MyMemory::MyMemory(int num, int len) {
	max_index = num-1;
	block_size=len;
	for (int i=0; i<num; i++)
		mlist.push_back(MyMemoryBlock(i,len));
}

MyMemory::~MyMemory() {
	mlist.clear();
}

void MyMemory::resize(int num, int len) {
	mlist.clear();
	max_index=num-1;
	block_size=len;
	for (int i=0; i<num; i++) 
		mlist.push_back(MyMemoryBlock(i,len));
}

int MyMemory::req_mem(int len) {
	for (auto i = mlist.begin(); i!=mlist.end(); i++) {
		if (i->get_length()>=len) {
			i->allocate_mem(len);
			int ind = i->get_index();
			if (i->get_length()==0)
				mlist.erase(i);
			return ind;
		}
	}
	return -1;
}

bool MyMemory::release_mem(int ind, int len) {
	if (ind < 0 || ind > max_index || len < 0 || len > block_size)
		return false;
	for (auto i=mlist.begin(); i!=mlist.end(); i++) {
		if (i->get_index() == ind) {
			i->free_mem(len);
			return true;
		}
	}
	return false;
}

void MyMemory::merge_mem() {
	auto i = mlist.begin();
	while (i!=mlist.end()) {
		auto next_i = i;
		next_i++;
		if (next_i!=mlist.end() && i->get_length()+next_i->get_length()<=block_size) {
			i->free_mem((next_i)->get_length());
			mlist.erase(next_i);
		}
		else 
			i++;
	}
}

void MyMemory::dump() {
	int count=0;
	std::cout<< "Number of blocks: " << mlist.size() << std::endl; 
	for (auto i=mlist.begin(); i!=mlist.end(); i++) {
		std::cout << "Block(index = " << count << "): " << i->get_length() << std::endl;
		count++;
	}
}
