// [Data Structure] 
// written by SukJoon Oh(2018142216)
//                     
// Visual Studio 2017 Professional
// 
// For more repo, visit https://github.com/dev-acoustikue/

#include "asm3_bin.h"
#include "tctutil.h"
#include "quicksort.h"

#define UNIT_TEST
#ifdef UNIT_TEST

int main() {

	// files
	const char* files[] = {
		"1K.bin", // 0
		"2K.bin",
		"4K.bin",
		"8K.bin",
		"16K.bin",
		"32K.bin",
		"64K.bin",
		"128K.bin",
		"256K.bin",
		"512K.bin",
		"1M.bin",
		"2M.bin",
		"4M.bin",
		"8M.bin" // 13
	};

	//arr_info box = asm3_bin(files[1]);

	for (int i = 0; i < 14; i++) {

		arr_info box = asm3_bin(files[i]);

		__tctutil::seqTestTimeComplexity<int>(
			std::string("naive_") + files[i],
			std::function<int*(int*&, int)>(0),
			[&](int*&, int) -> int* {
				
				kthSmallestNaive(box.offset, box.length, 50);
				return nullptr;
			}
		);

		delete[] box.offset;
	}


	for (int i = 0; i < 14; i++) {

		arr_info box = asm3_bin(files[i]);

		__tctutil::seqTestTimeComplexity<int>(
			files[i],
			std::function<int*(int*&, int)>(0),
			[&](int*&, int) -> int* {

			kthSmallest(box.offset, box.length, 50);
			return nullptr;
		}
		);

		delete[] box.offset;
	}

	return 0;
}
#endif




