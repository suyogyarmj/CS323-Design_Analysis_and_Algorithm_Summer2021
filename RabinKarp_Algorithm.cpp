/*
CSCI 323-2021-Summer
Assignment 3
Suyogya Rayamajhi
*/

// C++ program for Rabin-Karp Searching algorithm
#include <iostream>
#include <fstream>
#include <chrono>
#include <cstring>
#include <cctype>
#include <algorithm>

using namespace std;

int no_of_comparsions = 0;

// d is the number of characters in the input alphabet
#define d 256

/* pat -> pattern
    txt -> text
    q -> A prime number
*/
void search(const char pat[], char txt[], int q)
{
    int M = strlen(pat);
    int N = strlen(txt);
    int i, j;
    int p = 0; // hash value for pattern
    int t = 0; // hash value for txt
    int h = 1;

    // The value of h would be "pow(d, M-1)%q"
    for (i = 0; i < M - 1; i++)
        h = (h * d) % q;

    // Calculate the hash value of pattern and first
    // window of text
    for (i = 0; i < M; i++)
    {
        p = (d * p + pat[i]) % q;
        t = (d * t + txt[i]) % q;
    }

    // Slide the pattern over text one by one
    for (i = 0; i <= N - M; i++)
    {

        // Check the hash values of current window of text
        // and pattern. If the hash values match then only
        // check for characters one by one
        no_of_comparsions++;
        if ( p == t )
        {
            /* Check for characters one by one */
            for (j = 0; j < M; j++)
            {
                no_of_comparsions++;
                if (txt[i+j] != pat[j])
                    break;
            }

            // if p == t and pat[0...M-1] = txt[i, i+1, ...i+M-1]
            if (j == M)
                cout<<"Pattern found at index "<< i<<endl;
        }

        // Calculate hash value for next window of text: Remove
        // leading digit, add trailing digit
        if ( i < N-M )
        {
            t = (d*(t - txt[i]*h) + txt[i+M])%q;

            // We might get negative value of t, converting it
            // to positive
            if (t < 0)
            t = (t + q);
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

        search(pat.c_str(), txt, q);

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