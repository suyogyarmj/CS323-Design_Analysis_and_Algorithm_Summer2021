/*
CSCI 323-2021-Summer
Assignment 3
Suyogya Rayamajhi
*/

// C++ program for Naive Pattern Searching algorithm

#include <iostream>
#include <fstream>
#include <chrono>
#include <cstring>
#include <cctype>
#include <algorithm>

using namespace std;

int no_of_comparsions = 0;

void search(const char* pat, char* txt)
{
    int M = strlen(pat);
    int N = strlen(txt);

    /* A loop to slide pat[] one by one */
    for (int i = 0; i <= N - M; i++) {
        int j;

        /* For current index i, check for pattern match */
        for (j = 0; j < M; j++)
        {
            no_of_comparsions++;
            if (txt[i + j] != pat[j])
                break;
        }

        if (j == M) // if pat[0...M-1] = txt[i, i+1, ...i+M-1]
            cout << "Pattern found at index "
            << i << endl;
    }
}

// Driver Code
int main(int argc, char** argv)
{
    const char* pattern_file_name = "input3_patterns.txt";
    const char* text_file_name = "input3_text1.txt";

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

        search(pat.c_str(), txt);

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