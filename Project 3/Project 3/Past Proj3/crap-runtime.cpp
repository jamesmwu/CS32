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
const int MAXDICTWORDS = 1000; // Max words that can be read in


/*========== Functions ==========*/
//Function declaration so all other functions can use it
void printPermutations(string prefix, string rest, const string dict[], int size, string results[], int& count);


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
//Substitute for for loop in printPermutations function
void loop(int i, int max, string prefix, string rest, const string dict[], int size, string results[], int& count) {
    //Base case
    if (i > max) return;

    //Statement: Remove char from rest and add it to prefix
    printPermutations(prefix + rest[i], rest.substr(0, i) + rest.substr(i+1, rest.size() - 1), dict, size, results, count);
    loop(i + 1, max, prefix, rest, dict, size, results, count);
}

//Test to see if word is in dictionary. Return true if yes.
bool valid(string word, const string dict[], int size){
    //Base case
    if(size == 0) return false;
    if(dict[0] == word) return true;
    return valid(word, dict + 1, size - 1);
}

//Returns if the provided word is already added in results
bool repeats(string word, const string results[], int count){
    //Base case
    if(count == 0) return false;
    if(word == results[0]) return true;

    return repeats(word, results + 1, count - 1);
}

void printPermutations(string prefix, string rest, const string dict[], int size, string results[], int& count){

    //Base case: entire scrambled word is in prefix and "rest" is empty.
    if(rest == "") {
        //Compare each permutation with each word in the dictionary. If there's valid space in results and no repeats of the prefix then add the prefix to results.
        if(count < MAXRESULTS && !repeats(prefix, results, count) && valid(prefix, dict, size)){
            //No repeat word found in results array
            results[count] = prefix;
            count++;
        }
        return;
    }
    else {
        //For each character in "rest", add char to prefix, remove char from rest, generate permutations with updated vals
        loop(0, rest.size() - 1, prefix, rest, dict, size, results, count);
    }

}

//Puts all possiblities of "word" found in "dict" into "results". Returns # of matched words found (Can't be more than MAXRESULTS). Size is # words inside dict array.
//results should have no duplicates.
int theJumbler(string word, const string dict[], int size, string results[]){
    int count = 0;
    printPermutations("", word, dict, size, results, count);
    return count;
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



//
//int main()
//{
//    string results[MAXRESULTS];
//    string dict[MAXDICTWORDS];
//    ifstream dictfile;         // file containing the list of words
//    int nwords;                // number of words read from dictionary
//    string word;
//    dictfile.open("/Users/jameswu/Desktop/Project 3/Project 3/words.txt");
//    if (!dictfile) {
//        cout << "File not found!" << endl;
//        return (1);
//    }
//    nwords = lexiconBuilder(dictfile, dict);
//    cout << "Please enter a string for an anagram: ";
//    cin >> word;
//    int numMatches = theJumbler(word, dict, nwords, results);
//    if (!numMatches) {
//        cout << "No matches found" << endl;
//}
//    else {
//        divulgeSolutions(results, numMatches);
//}
//return 0;
//}
