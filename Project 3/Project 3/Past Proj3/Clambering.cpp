/*
 James Wu
 CS32
 Project 3
 */

#include <iostream>
#include <fstream>
#include <istream>
#include <cstring>
using namespace std;

#include <cassert>


/*========= Constants ==========*/
const int MAXRESULTS   = 20;    // Max matches that can be found
const int MAXDICTWORDS = 30000; // Max words that can be read in


/*========== Functions ==========*/
//Function declaration so all other functions can use it
void printPermutations(string prefix, string rest, string permutations[], int& count);


int lexiHelper(istream &dictfile, string dict[], int max){
    //Base case
    string s;
    if(!getline(dictfile, s) || max == 0) return 0;

    max--;
    dict[0] = s;    //Read line into first index of dict

    return 1 + lexiHelper(dictfile, dict + 1, max);
}

//Put each string in dictFile into array dict[], return #words read into dict (Can't be more than MAXDICTWORDS).
int lexiconBuilder(istream &dictfile, string dict[]){
    return lexiHelper(dictfile, dict, MAXDICTWORDS);
}


//Jumbler Helper functions

//Returns if the provided word is already added in results
bool repeats(char cur, const string unique, int uniSize){
    //Base case
    if(uniSize == 0) return false;
    if(cur == unique[uniSize - 1]) return true; //Repeat character has been detected
    
    return repeats(cur, unique, uniSize - 1);
}

//Substitute for for loop in printPermutations function
void loop(int i, int max, string prefix, string rest, string permutations[], int& count, string unique, int uniSize) {
    //Base case
    if (i > max) return;
    //Current char is already present, so ignore this permutation.
    if(repeats(rest[i], unique, uniSize)){
//        cout << "\nUnique: " << unique << endl;
//        cout << "rest[i]: " << rest[i] << endl;
        loop(i + 1, max, prefix, rest, permutations, count, unique, uniSize);
    }
    else {
        //Statement: Remove char from rest and add it to prefix
        printPermutations(prefix + rest[i], rest.substr(0, i) + rest.substr(i+1, rest.size() - 1), permutations, count);
        loop(i + 1, max, prefix, rest, permutations, count, unique += rest[i], uniSize + 1);
    }
}

//Test to see if word is in dictionary. Insert into results array if so.
void valid(string word, const string dict[], int size, string results[], int& totResults){
    //Base case
    if(size == 0 || totResults >= MAXRESULTS) return;   //No matches
    //If match exists, insert into results array
    if(dict[0] == word){
        results[totResults] = word;
        totResults++;
        return;
    }
    
    return valid(word, dict + 1, size - 1, results, totResults);
}

void loop2(int i, int max, const string permutations[], const string dict[], int size, string results[], int& totResults){
    
    //Normal for-loop implementation of this function:
    /*    for(int i = 0; i < count; i++)
            valid(permutations[i], dict, size, results, totResults);
    */
    
    //Base case
    if(i > max) return;
    valid(permutations[i], dict, size, results, totResults);
    loop2(i + 1, max, permutations, dict, size, results, totResults);
}

void printPermutations(string prefix, string rest, string permutations[], int& count){

    //Base case: entire scrambled word is in prefix and "rest" is empty.
    if(rest == "") {
        //Insert permutation into permutation array WITHOUT REPEATS.
        permutations[count] = prefix;
        count++;
    }
    else {
        string unique;
        int uniSize = 0;
        //For each character in "rest", add char to prefix, remove char from rest, generate permutations with updated vals
        loop(0, rest.size() - 1, prefix, rest, permutations, count, unique, uniSize);
    }

}

//Puts all possiblities of "word" found in "dict" into "results". Returns # of matched words found (Can't be more than MAXRESULTS). Size is # words inside dict array.
//results should have no duplicates.
int theJumbler(string word, const string dict[], int size, string results[]){
    int count = 0;
    int totResults = 0;
    //Array of all possible permutations. The max length word is 10 chars, so 10! = 3628800 possible combos.
    string permutations[3628800];
    printPermutations("", word, permutations, count);
    
    //Permutations is now populated with all possible, non-repeating permutations.
    //Check permutations with each word in dictionary. If matched, insert dictionary word into results[].
    loop2(0, count, permutations, dict, size, results, totResults);
    
    return totResults;
}

//Displays "size" # of strings from "results", printed in any order.
void divulgeSolutions(const string results[], int size){
    if(size == 0) return;

    cout << results[0] << endl;

    divulgeSolutions(results + 1, size - 1);
}



int main()
{

    string results[MAXRESULTS];

//    string exampleDict[] = {"kool", "moe", "dee", "okol", "look", "olok", "oo", "lkoo"};
//     int numResults = theJumbler("kloo", exampleDict, 8, results);
//     assert(numResults == 5);
//    divulgeSolutions(results, 5);

    string dict[MAXDICTWORDS];
    ifstream dictfile;         // file containing the list of words
    int nwords;                // number of words read from dictionary
    string word;

//    dictfile.open("/Users/jameswu/Desktop/sample.txt");    //Local Testing with different dictionaries
    dictfile.open("/Users/jameswu/Desktop/Project 3/Project 3/words.txt");    //Local Testing with provided dictionary
    if (!dictfile) {
        cout << "File not found!" << endl;
        return (1);
    }

    nwords = lexiconBuilder(dictfile, dict);
    

    cout << "Num words: "<< nwords << endl;
    cout << "Last entry: " << dict[MAXDICTWORDS - 1] << endl;
    
    
    while(word != "exit"){
        cout << "Please enter a string for an anagram: ";
        cin >> word;

        int numMatches = theJumbler(word, dict, nwords, results);

        cout << endl;
        if (!numMatches)
            cout << "No matches found" << endl;
        else
            divulgeSolutions(results, numMatches);

        cout << endl;
    }

    return 0;
}
