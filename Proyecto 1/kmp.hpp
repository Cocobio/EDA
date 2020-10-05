#ifndef KMP
#define KMP

#include <string>
#include <vector>
#include <iostream>

using namespace std;

auto kmp(const char *text, size_t n, const char *pattern, size_t m) -> size_t {
	int lps[m+1];

	lps[0] = -1;
	int i = 0;
	int j = -1;
	while (i < m) {
		while ((j >= 0) && (pattern[i] != pattern[j]))
			j = lps[j];

		++j;
		++i;

		lps[i] = j;
	}

	i = 0;
	j = 0;
	while (i < n) {
		while ((j >= 0) && (text[i] != pattern[j]))
			j = lps[j];

		++i;
		++j;

        // For testing the match of all ocurrances
		// if (j == m)
		// 	return i-m;
	}

	return i;
}




// We tried an implementation from geeks for geeks, because we couldn't belive that kmp was so slow
void computeLPSArray(const char* pat, int M, int* lps); 
  
// Prints occurrences of txt[] in pat[] 
size_t KMPSearch(const char* txt, size_t N, const char* pat, size_t M) 
{ 
    // int M = strlen(pat); 
    // int N = strlen(txt); 
  
    // create lps[] that will hold the longest prefix suffix 
    // values for pattern 
    int lps[M]; 
  
    // Preprocess the pattern (calculate lps[] array) 
    computeLPSArray(pat, M, lps); 
  
    int i = 0; // index for txt[] 
    int j = 0; // index for pat[] 
    while (i < N) { 
        if (pat[j] == txt[i]) { 
            j++; 
            i++; 
        } 
  
        if (j == M) { 
        	// return i-j;
         //    printf("Found pattern at index %d ", i - j); 
            j = lps[j - 1]; 
        } 
  
        // mismatch after j matches 
        else if (i < N && pat[j] != txt[i]) { 
            // Do not match lps[0..lps[j-1]] characters, 
            // they will match anyway 
            if (j != 0) 
                j = lps[j - 1]; 
            else
                i = i + 1; 
        } 
    } 

    return N;
} 
  
// Fills lps[] for given patttern pat[0..M-1] 
void computeLPSArray(const char* pat, int M, int* lps) 
{ 
    // length of the previous longest prefix suffix 
    int len = 0; 
  
    lps[0] = 0; // lps[0] is always 0 
  
    // the loop calculates lps[i] for i = 1 to M-1 
    int i = 1; 
    while (i < M) { 
        if (pat[i] == pat[len]) { 
            len++; 
            lps[i] = len; 
            i++; 
        } 
        else // (pat[i] != pat[len]) 
        { 
            // This is tricky. Consider the example. 
            // AAACAAAA and i = 7. The idea is similar 
            // to search step. 
            if (len != 0) { 
                len = lps[len - 1]; 
  
                // Also, note that we do not increment 
                // i here 
            } 
            else // if (len == 0) 
            { 
                lps[i] = 0; 
                i++; 
            } 
        } 
    } 
} 


#endif
