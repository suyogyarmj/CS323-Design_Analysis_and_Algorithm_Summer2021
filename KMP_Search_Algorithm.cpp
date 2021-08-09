/*
CSCI 323-2021-Summer
Assignment 3
Suyogya Rayamajhi
*/

// C++ program for implementation of KMP pattern searching
// algorithm

#include <iostream>
#include <fstream>
#include <chrono>
#include <cstring>
#include <cctype>
#include <algorithm>

using namespace std;

int no_of_comparsions = 0;

void computeLPSArray(const char* pat, int M, int* lps);

// Prints occurrences of txt[] in pat[]
void KMPSearch(const char* pat, char* txt)
{
    int M = strlen(pat);
    int N = strlen(txt);

    // create lps[] that will hold the longest prefix suffix
    // values for pattern
    int lps[M];

    // Preprocess the pattern (calculate lps[] array)
    computeLPSArray(pat, M, lps);

    int i = 0; // index for txt[]
    int j = 0; // index for pat[]
    while (i < N) {

        no_of_comparsions++;
        if (pat[j] == txt[i]) {
            j++;
            i++;
        }

        no_of_comparsions++;
        if (j == M) {
            printf("Found pattern at index %d\n", i - j);
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
        no_of_comparsions++;
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


// Driver Code
int main(int argc, char** argv)
{


    const char* pattern_file_name = "input3_patterns.txt";
    const char* text_file_name = "input3_text1.txt";
    // A prime number
    int q = 101;

    // check if pattern and text file name are provided as commandline arguments
    if (argc > 1)
    {

        // if text file name is provided
        text_file_name = argv[1];


        // if patterns file name is provided
        if (argc > 2)
        {
            pattern_file_name = argv[2];
        }
    }


    // starting timestamp to measure the time
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();



    // open the pattern file
    ifstream fin_pat;

    fin_pat.open(pattern_file_name);

    // if pattern file doesn't exit then show an error message
    if (!fin_pat.is_open())
    {
        cout << "File " << pattern_file_name << " not found" << endl;

        return -1;

    }



    // open the text file
    ifstream fin_t;

    fin_t.open(text_file_name);


    // if text file doesn't exist then show an error message
    if (!fin_t.is_open())
    {
        cout << "File " << text_file_name << " not found" << endl;
        fin_pat.close();
        return -1;
    }



    // count the number of characters in the text file
    char ch;
    int length_text = 0;
    while (fin_t >> ch)
    {
        length_text++;
    }



    // allocate memory to store the text
    char* txt = new char[length_text + 1];

    fin_t.close();



    // reopen the text file and read all the text into the memory
    fin_t.open(text_file_name);


    int i = 0;

    while (fin_t >> ch)
    {
        txt[i] = toupper(ch);
        i++;
    }

    txt[i] = '\0';

    fin_t.close();


    // read the each pattern and find it in the text
    string pat;
    while (getline(fin_pat, pat))
    {

        // convert pattern to upper case
        transform(pat.begin(), pat.end(),pat.begin(), ::toupper);
        cout << "Pattern: " << pat << endl;

        KMPSearch(pat.c_str(), txt);

        cout << endl << endl;
    }

    fin_pat.close();



    // measure the time
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    cout << "Time taken (sec) = " << (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) / 1000000.0 << std::endl;
    cout << "Total comparisons: " << no_of_comparsions << endl;

    delete[] txt;
    return 0;
}