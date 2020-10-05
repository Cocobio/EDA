#ifndef BOYER_MOORE
#define BOYER_MOORE

#include <string>
#include <algorithm>
#include <string.h>
#include <unordered_map>

#include <iostream>

size_t boyer_moore(const std::string &text, const std::string &pattern) {
	// preprocess pattern
	std::unordered_map<char,size_t> bad_match_table;

	for (size_t i=0; i<pattern.size(); i++)
		bad_match_table[pattern[i]] = std::max(size_t(1), pattern.size()-i-1);

	// compare
	for (int i=0, step; i<=text.size()-pattern.size(); i+=step) {
		step = 0;

		for (int j=pattern.size()-1; j>=0; j--) {
			if (text[i+j]!=pattern[j]) {
				if (bad_match_table.find(text[i+j])!=bad_match_table.end()) {
					step = bad_match_table[text[i+j]];
					break;
				}
				else {
					step = pattern.size();
					break;
				}
			}
		}
		if (step==0) { 
	        // For testing the match of all ocurrances
			step = 1;
			// return i;
		}
	}

	return text.size();
}

using namespace std;

size_t boyer_moore(const char *text, size_t n, const char *pattern, size_t m, size_t Sigma=256) {
	// preprocess pattern
	size_t* bad_match_table = new size_t[Sigma];
	memset(bad_match_table,0,Sigma*sizeof(size_t));

	for (size_t i=0; i<m; i++)
		bad_match_table[pattern[i]] = std::max(1ul, m-i-1);

	// compare
	for (int i=0, step; i<=n-m; i+=step) {
		step = 0;

		// check pattern
		for (int j=m-1; j>=0; j--) {
			// If missmatch
			if (text[i+j]!=pattern[j]) {
				if (bad_match_table[text[i+j]]!=0 and 0<=text[i+j]) {
					step = bad_match_table[text[i+j]];
					break;
				}
				else {
					step = m;
					break;
				}
			}
		}
		if (step==0) {
	        // For testing the match of all ocurrances
			step = 1;
			// delete[] bad_match_table;
			// return i;
		}
		// cout << i << endl;
	}

	delete[] bad_match_table;
	return n;
}

#endif
