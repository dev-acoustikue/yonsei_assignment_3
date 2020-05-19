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
