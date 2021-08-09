/*
CSCI 323-2021-Summer
Assignment 3
Suyogya Rayamajhi
*/

// C++ program for implementation of Boyer Moore's Algorithm

#include <iostream>
#include <fstream>
#include <chrono>
#include <cstring>
#include <cctype>
#include <algorithm>

using namespace std;
 
#define NO_OF_CHARS 256
int no_of_comparsions = 0;

// The preprocessing function for Boyer Moore's
// bad character heuristic
void badCharHeuristic( string str, int size,
                        int badchar[NO_OF_CHARS])
{
    int i;

    // Initialize all occurrences as -1
    for (i = 0; i < NO_OF_CHARS; i++)
        badchar[i] = -1;

    // Fill the actual value of last occurrence
    // of a character
    for (i = 0; i < size; i++)
        badchar[(int) str[i]] = i;
}

/* A pattern searching function that uses Bad
Character Heuristic of Boyer Moore Algorithm */
void search(string txt, string pat)
{
    int m = pat.size();
    int n = txt.size();

    int badchar[NO_OF_CHARS];

    /* Fill the bad character array by calling
    the preprocessing function badCharHeuristic()
    for given pattern */
    badCharHeuristic(pat, m, badchar);

    int s = 0; // s is shift of the pattern with
                // respect to text
    while(s <= (n - m))
    {
        int j = m - 1;

        /* Keep reducing index j of pattern while
        characters of pattern and text are
        matching at this shift s */
        while(j >= 0 && pat[j] == txt[s + j])
        {
            no_of_comparsions++;
            j--;
        }

        /* If the pattern is present at current
        shift, then index j will become -1 after
        the above loop */
        if (j < 0)
        {
            cout << "pattern occurs at shift = " << s << endl;

            /* Shift the pattern so that the next
            character in text aligns with the last
            occurrence of it in pattern.
            The condition s+m < n is necessary for
            the case when pattern occurs at the end
            of text */
            no_of_comparsions++;
            s += (s + m < n)? m-badchar[txt[s + m]] : 1;

        }

        else
            /* Shift the pattern so that the bad character
            in text aligns with the last occurrence of
            it in pattern. The max function is used to
            make sure that we get a positive shift.
            We may get a negative shift if the last
            occurrence of bad character in pattern
            is on the right side of the current
            character. */
            s += max(1, j - badchar[txt[s + j]]);
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
    string txtStr(txt);
    while (getline(fin_pat, pat))
    {

        // convert pattern to upper case
        transform(pat.begin(), pat.end(),pat.begin(), ::toupper);
        cout << "Pattern: " << pat << endl;

        search(txtStr, pat);

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