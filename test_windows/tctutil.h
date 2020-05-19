// [Data Structure] 
// written by SukJoon Oh(2018142216)
//                     
// Visual Studio 2017 Professional
// 
// For more repo, visit https://github.com/dev-acoustikue/

// tctutil.h
//	time-complexity test utility
//	This file contains several re-factored codes,
//	used in 'Practice at Home 10', which was turned in by SukJoon Oh.
//	
//	Structure modified for generalized future use.
//

#pragma once

#include <string>
#include <chrono>
#include <fstream>
#include <iostream>
#include <functional>
#include <cstdlib>

#define TCT_UTIL
#if defined(TCT_UTIL)


// global
#define COUT	std::cout
#define ENDL	std::endl
#define AND		<< " " <<
#define PRINT(MSG)\
	do { COUT << MSG << ENDL; } while(0)

//
// __filectrl namespace
// author: SukJoon Oh
namespace __filectrl {

	std::string record_file_name = "result";
	std::ofstream record_file;

	const bool openCsv(std::ofstream& file = record_file) {
		if (!file.is_open())
			file.open(record_file_name);
		else return false;

		return true;
	}

	const bool closeCsv(std::ofstream& file = record_file) {
		if (file.is_open())
			file.close();
		else return false;

		return true;
	}

	const bool writeCsv(const int data_size, const double time, std::ofstream& file = record_file) {
		if (!file.is_open())
			return false;
		file << data_size << "," << time << "\n";

		return true;
	}
}


// 
// random gen
namespace __random {

	int* rnda = nullptr;

	int* randomGenInt(int* &arr = rnda, const int size = 0) {

		// exception
		if (arr != nullptr || size == 0) {
			PRINT("Target:" AND arr
				AND ", Size:" AND size);
			return nullptr;
		}

		if (arr == nullptr) {
			srand(time(NULL));

			arr = new int[size];
			for (int idx = 0; idx < size; idx++)
				arr[idx] = rand() / 100;

			return arr;
		}
	}
}


//
// __tctutil namespace
// author: SukJoon Oh
//
// To use seqTestTimeComplexity in tctutil namespace, 
// all parameters should meet certain conditions:
//
// rnd_gen_function
// param1: array pointer reference type
// param2: array size
//	
// test_function
// param1: array pointer reference type
// param2: array size
//

namespace __tctutil {

	//std::string record_file_name = "result";
	// default file name will be set to 'result'

#define FNC std::function
	template <class _T>
	void seqTestTimeComplexity(const std::string& title,
		FNC<_T*(_T*&, int)> rnd_gen_function = FNC<_T*(_T*&, int)>(0),
		FNC<void(_T*&, int)> test_function = FNC<void(_T*&, int)>(0)) {

#undef FNC
		__filectrl::record_file_name = title + ".csv"; // set file name
		PRINT("TC TEST START:" AND title);

		__filectrl::openCsv(); // open file, __tctutil::record_file_name

		for (int elem_size = 0; elem_size < 1; elem_size += 100000) {

			_T* rnd_arr = nullptr;
			if (rnd_gen_function)
				rnd_gen_function(rnd_arr, elem_size); // generate random numbers

			auto start_t = std::chrono::steady_clock::now(); // clock tick start

			// test
			if (test_function)
				test_function(rnd_arr, elem_size);

			auto end_t = std::chrono::steady_clock::now(); // end time record
			auto elapsed_seconds // difference
				= std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
			// clock end

			delete[] rnd_arr;

			__filectrl::writeCsv(elem_size, elapsed_seconds * 0.001); // record
			PRINT(elapsed_seconds * 0.001 AND "sec elapsed");
		}

		__filectrl::closeCsv(); // close file

		PRINT("TC TEST END:" AND title);
	}
}


namespace fc = __filectrl;
namespace rnd = __random;

namespace tctu = __tctutil;

#endif
#undef TCT_UTIL