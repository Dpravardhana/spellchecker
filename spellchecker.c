#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
struct variables
{
    char suggestion[10];
    char sentence[100];
} s;
// this function returns the part of string starting from (start)^th index till (end)^th index
char *substring(char *str, int start, int end)
{

    int i;
    int size = (end - start) + 2;
    char *output = (char *)malloc(size * sizeof(char));

    for (i = 0; start <= end; start++, i++)
    {
        output[i] = str[start]; // stores characters between index start to end
    }

    output[size] = '\0';

    return output;
}
int min(int a, int b)
{ // minimum function for 2 arguments
    return (a < b) ? a : b;
}
int min_3(int x, int y, int z)
{ // minimum function of 3 arguments
    return min(min(x, y), z);
}
// this function takes 2 strings and their length as input and returns the editdistance.
int editdist(char *str1, char *str2, int m, int n)
{
    if (m == 0)                                    // if the first string is empty
        return n;                                  // length of second string is the edit distance
    if (n == 0)                                    // if the second string is empty
        return m;                                  // length of first string is the edit distance
    if (str1[m - 1] == str2[n - 1])                // if the last character is same
        return editdist(str1, str2, m - 1, n - 1); // edit distance of the remaining string is the total edit distance
    return 1 + min_3(editdist(str1, str2, m, n - 1), editdist(str1, str2, m - 1, n), editdist(str1, str2, m - 1, n - 1));
    // else minimum of 1. Inserting  2. Deleting  3. Replacing is the edit distance
}
// takes a string as an input checks if that's an error and returns 0 if it's an error
int iserror(char word[10])
{
    int flag = 0;
    int i;
    char dictionary[32][10] = {"an", "apple", "a", "day", "keeps", "the", "doctor", "away", "time", "is", "precious", "good", "things", "take", "old", "gold", "actions", "speak", "louder", "than", "words", "honesty", "best", "policy", "journey", "of", "thousand", "miles", "begins", "with", "single", "step"};
    for (i = 0; i <= 31; i++)
    { // traverses the whole dictionary
        if (strcmp(dictionary[i], word) == 0)
        { // compares error and each word in dictionary
            flag = flag + 1;
        }
    }
    return flag;
}
const char *suggestions(char error[])
{
    // This function sorts words based on the editdistance of the error and prints the top results.
    char dictionary[32][10] = {"an", "apple", "a", "day", "keeps", "the", "doctor", "away", "time", "is", "precious", "good", "things", "take", "old", "gold", "actions", "speak", "louder", "than", "words", "honesty", "best", "policy", "journey", "of", "thousand", "miles", "begins", "with", "single", "step"};

    // sorting
    // ↓
    int n, a, d, i, j;
    char b[10], c[10];

    n = 32;
    for (i = 0; i <= 2; i++)
    {          // unsorted subarray
        d = i; // minimum element
        for (j = i + 1; j <= n - 1; j++)
        { // sorted sub array
            if (editdist(error, dictionary[d], strlen(error), strlen(dictionary[d])) > editdist(error, dictionary[j], strlen(error), strlen(dictionary[d])))
            {
                d = j; // new minimum element
            }
        }
        strcpy(c, dictionary[i]); // swapping of strings
        strcpy(b, dictionary[d]);
        strcpy(dictionary[i], b);
        strcpy(dictionary[d], c);
    }

    // ↑
    // sorting
    strcpy(s.suggestion, dictionary[0]);
    printf("Suggestions:\n");
    for (i = 0; i <= 1; i++)
    {
        printf("%d. %s\n", i + 1, dictionary[i]);
    }
}
// This function breaks the string "sentence" into words
void words(char sentence[])
{
    int i, j, k, a, b, count, x, y, z, errorcount;
    char correctsentence[100] = "";
    count = 0;
    errorcount = 0;
    i = 0;
    j = 0;
    for (i = 0; i <= strlen(sentence) - 1; i++)
    { // counts number of spaces along with the full stop
        if (sentence[i] == ' ' || sentence[i] == '.')
        {
            count = count + 1;
        }
    }
    int spaces[count];

    for (i = 0; i <= strlen(sentence) - 1; i++)
    { // storing the index of spaces and the full stop
        if (sentence[i] == ' ' || sentence[i] == '.')
        {
            spaces[j] = i;
            j = j + 1;
        }
    }
    char words[count][10];

    x = 0;
    k = 0;
    for (k = 0; k <= count - 1; k++)
    {
        strcpy(words[k], substring(sentence, x, spaces[k] - 1)); // string slicing based on the index of spaces using substring function
        x = spaces[k] + 1;
    }
    for (y = 0; y <= count - 1; y++)// checking for error using iserror() and replacing the error with the topmost suggestion
    { 
        if (iserror(words[y]) == 0)
        {
            errorcount = errorcount + 1;
            printf("Incorrect word %d : %s\n", errorcount, words[y]);
            suggestions(words[y]);
            strcpy(words[y], s.suggestion);//replacing the error with the top most suggestion
        }
    }
    if (errorcount == 0)
    {
        printf("Great!! This sentence does not have any error\n");
    }
    else
    {
        for (i = 0; i <= count - 1; i++)
        {
            strcat(correctsentence, " ");
            strcat(correctsentence, words[i]);
        }
        printf("\n");
        printf("Corrected Sentence:%s.\n", correctsentence); // printing the correct sentence
    }
    printf("\n\n");
}
int main()
{
    printf("WELCOME\n");
    printf("Enter a sentence (with a fullstop):\n");
    fgets(s.sentence, 100, stdin);
    words(s.sentence);
    printf("THANK YOU FOR USING OUR SPELLCHECKER :)\n");
    return 0;
}
