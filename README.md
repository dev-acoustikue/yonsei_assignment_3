# [DATA STRUCTURE AND ALGORITHMS] Assignment 3

[Video Link](https://drive.google.com/file/d/1SN-pIo3v6IboR4xFyvt48KFCookeno-U/view?usp=sharing)

## Part 1: Implement a QuickSort function (50pts)
### Instructions

- The quicksort sorts elements in a given integer array from the smallest to the largest one.
- The array and its size are given as an argument.
- The quicksort should handle sorted case efficiently as well.

### Implementation






## Part 2: K’th Smallest Element
### Instructions
- Given an integer array and a number k where k is smaller than size of the array, find the k’th smallest element from the given array. 
- Implement a naïve solution (20pts). The naïve solution executes the quick sort for the given array, and returns the k’th elements.
- Implement a better solution (20pts)

Time complexity of the naïve solution is $$O(nlogn)$$ on average. There exists a better algorithm which time complexity is $$O(n)$$ on average. Design and Implement the $$O(n)$$ algorithm. 

- Performance comparison of the naïve and better solution (10pts)
- Execute the solution for given .bin files, and compares their execution times in the report  (Performance.docx).


### Implementation





## Additional: Tests

```cpp
// [Data Structure] 
// written by SukJoon Oh(2018142216)
//                     
// Visual Studio 2017 Professional
// 
// For more repo, visit https://github.com/dev-acoustikue/

#pragma once

// asm3_bin.h
//	This file contains a single function asm3_bin,
//	for controlling given binary files.
//	The main algorithm was given in main function,
//	but slightly modded for tests.
//

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>


struct arr_info {
	int* offset;
	size_t length;
	arr_info() : offset(nullptr), length(0) { };
};


// Use this function as,
// asm3_bin("1K.bin");
arr_info asm3_bin(const char* file_name) {

	arr_info info;

	// It was originally used as,
	// ./sort data_10.txt 5
	size_t len = 0;
	int * arr;
	std::ifstream is;
	is.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	std::string fname = file_name;

	try {
		is.open(file_name, std::ios::binary);
		is.read(reinterpret_cast<char *>(&len), sizeof(size_t));
		arr = new int[len];
		is.read(reinterpret_cast<char *>(arr), len * sizeof(int));

		info.length = len;
	}
	catch (...) {
		is.close();
		std::cerr << "Cannot read file " << file_name << std::endl;
		return info; // moded
	}
	is.close();

	// return information
	int *tmp = new int[len];
	std::copy(arr, arr + len, tmp); // copies to tmp

	delete[] arr;

	info.offset = tmp;
	
	return info;
	// After returning this pointer, it should be manually deleted
	// otherwise, memory leak will exist.
}
```











```cpp
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
```