#include "header.h"
using namespace std;

void print_menu() {
	cout << string(20, '=') << endl;
	cout << "d: memory dump" << endl;
	cout << "r: request memory" << endl;
	cout << "l: release memory" << endl;
	cout << "m: merge memory" << endl;
	cout << "x: quit program" << endl;
	cout << "Your choice: ";	
}

int main() {

	int mem_blocks;
	int block_size;
	char choice;

	cout << "Memory configuraton:\n";
	cout << "Number of memory blocks (integer) : ";
	cin >> mem_blocks;
	cout << "Memory block size (integer) : ";
	cin >> block_size;

	MyMemory list(mem_blocks,block_size);

	while(choice != 'x') {
		print_menu();

		cin >> choice;

		cout << "choice: " << choice << endl;

		switch(choice) {
			case 'd':
				list.dump();
				break;
			case 'r':
				int req_memsize;
				cout << "requested memory size (integer): ";
				cin >> req_memsize;
				list.req_mem(req_memsize);
				break;
			case 'l':
				int i;
				int l;
				cout << "Release memory index (integer): ";
				cin >> i;
				cout << "Release memory length (integer): ";
				cin >> l;
				bool tf = list.release_mem(i,l);
				if (!tf)
					cout << "Memory release operation failed.\n";
				break;
			case 'm':
				list.merge_mem();
				break;
			case 'x':
				exit(1);
				break;
			default:
				cout << "\n*****Error: Invalid input. Try Again.\n";
		}
	}

	return 0;
}

