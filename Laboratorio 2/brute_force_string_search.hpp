#ifndef BRUTE_FORCE_STRING_SEARCH
#define BRUTE_FORCE_STRING_SEARCH

#include <string>

size_t brute_force_string_search(const std::string &text, const std::string &pattern) {
	size_t i,j, n=0;

	for (i=0; i<text.size(); i++) {
		for (j=0; j<pattern.size(); j++)
			if (text[i+j]!=pattern[j])
				break;

		if (j==pattern.size())// n++;
			break;
	}

	return i;
	// return n;
}

size_t brute_force_string_search(const char *text, size_t n, const char *pattern, size_t m) {
	size_t i,j;

	for (i=0; i<n; i++) {
		for (j=0; j<m; j++)
			if (text[i+j]!=pattern[j])
				break;
			
        // For testing the match of all ocurrances
		// if (j==m)
		// 	return i;
	}

	return n;
}

#endif

