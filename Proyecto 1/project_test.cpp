#include "boyer_moore.hpp"
#include "kmp.hpp"
#include "../Laboratorio 2/brute_force_string_search.hpp"
#include <string>
#include <iostream>
#include <cstring>
#include <functional>
#include <sstream>
#include <fstream>
#include <ctime>

#include "../Laboratorio 2/SuffixArray.hpp"
#include <algorithm>

using namespace std;

// Function for reading text from a file
string* read_txt_file(const string &infile) {
	ifstream f(infile); //taking file as inputstream

	if(f) {
		ostringstream ss;
		ss << f.rdbuf(); // reading data
		return new string(ss.str());
	}

	return nullptr;
}

// Function for measuring time of the algorithms, varying the size of the pattern
void test(string infile, bool mess_with_pattern=false) {
	string *in = read_txt_file(infile);

	srand(time(0));
	// For csv table
	cout << "m;boyer;kmp;time_brute" << endl;

	int t_samples = 10;
	int step = 5;

	for (int i=0; i<20; i++) {

		// TESTING BOYER MOORE
		double t = 0.0;
		for (int j=0; j<t_samples; j++) {
			bool valid;
			string pattern;

			// Make sure that doesnt contains a negative value (for accessing table purpose)
			do {
				pattern = in->substr(rand()%(in->size()/3),step*(i+1));
				valid = true;
				for (auto &c : pattern)
					if (c<0) {
						valid = false;
						break;
					}
			} while (!valid);

			// For the 1 character mismatch test
			if (mess_with_pattern)
				for (auto &c : pattern)
					c++;

			auto start = clock();
			boyer_moore(in->data(), in->size(), pattern.data(), pattern.size());
			auto end = clock();

			t+= ((double) (end-start)) / CLOCKS_PER_SEC;
		}
		cout << step*(i+1) << ";" << 1000*t/t_samples;

		//TESTING KMP
		t = 0.0;
		for (int j=0; j<t_samples; j++) {
			string pattern = in->substr(rand()%(in->size()/3),step*(i+1));

			// For the 1 character mismatch test
			if (mess_with_pattern)
				for (auto &c : pattern)
					c++;

			auto start = clock();
			kmp(in->data(), in->size(), pattern.data(), pattern.size());
			auto end = clock();
			t+= ((double) (end-start)) / CLOCKS_PER_SEC;
		}
		cout << ";" << 1000*t/t_samples;

		//TESTING BRUTE FORCE
		t = 0.0;
		for (int j=0; j<t_samples; j++) {
			string pattern = in->substr(rand()%(in->size()/3),step*(i+1));

			// For the 1 character mismatch test
			if (mess_with_pattern)
				for (auto &c : pattern)
					c++;

			auto start = clock();
			brute_force_string_search(in->data(), in->size(), pattern.data(), pattern.size());
			auto end = clock();
			t+= ((double) (end-start)) / CLOCKS_PER_SEC;
		}
		cout << ";" << 1000*t/t_samples << endl;
	}

	delete in;
}

// Comparing the use of different containers 
void boyer_moore_testing(string infile) {
	string *in = read_txt_file(infile);

	srand(time(0));

	// For csv table
	cout << "m;hash;array" << endl;

	int t_samples = 10;
	int step = 5;

	for (int i=0; i<20; i++) {

		// TESTING BOYER MOORE HASH
		double t = 0.0;
		for (int j=0; j<t_samples; j++) {
			string pattern = in->substr(rand()%(in->size()/3),step*(i+1));

			auto start = clock();
			boyer_moore(*in, pattern);
			auto end = clock();

			t+= ((double) (end-start)) / CLOCKS_PER_SEC;
		}
		cout << step*(i+1) << ";" << 1000*t/t_samples;

		//TESTING BOYER MOORE ARRAY
		t = 0.0;
		for (int j=0; j<t_samples; j++) {
			string pattern = in->substr(rand()%(in->size()/3),step*(i+1));

			auto start = clock();
			boyer_moore(in->data(), in->size(), pattern.data(), pattern.size());
			auto end = clock();
			t+= ((double) (end-start)) / CLOCKS_PER_SEC;
		}
		cout << ";" << 1000*t/t_samples << endl;
	}

	delete in;
}

int main() {
	string file_text;

	// Uncomment for testing a dataset
	// file_text = "../text database/generic.1MB";
	// file_text = "../text database/generic.10MB";
	file_text = "../text database/generic.50MB";
	// file_text = "../text database/english.50MB";
	// file_text = "../text database/dna.50MB";
	// file_text = "../text database/proteins.50MB";
	// file_text = "../text database/single_char.50MB";
	// file_text = "../text database/single_char.1MB";
	test(file_text, false); 	// change to true if want to mess with the pattern (used with single_char.1MB and pattern with full mismatch)
	// boyer_moore_testing(string("../text database/proteins.50MB"));

	return 0;
}




