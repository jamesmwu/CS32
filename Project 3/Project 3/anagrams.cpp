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
void printPermutations(string prefix, string rest, const string dict[], int size, string results[], int& count);

//Helper function to read in dictionary
int lexiHelper(istream &dictfile, string dict[], int max){
    //Base case-- if max entries are reached or dictionary runs out of entries, exit
    string s;
    if(!getline(dictfile, s) || max == 0) return 0;

    max--;
    dict[0] = s;    //Read line into first index of dict

    return 1 + lexiHelper(dictfile, dict + 1, max); //Iterate dictionary
}

//Put each string in dictFile into array dict[], return #words read into dict (Can't be more than MAXDICTWORDS).
int lexiconBuilder(istream &dictfile, string dict[]){
    return lexiHelper(dictfile, dict, MAXDICTWORDS);
}


//Jumbler Helper functions

//Returns if the provided word is already added in results
bool repeats(int i, string word, const string results[], int size){
    //Base case
    if(i >= size) return false;
    if(word == results[i]) return true;
    return repeats(i + 1, word, results, size);
}

//Test to see if word is in dictionary. Insert into results array if so.
bool valid(int i, string word, const string dict[], int size){
    if(i >= size) return false;
    if(dict[i] == word) return true;
    return valid(i + 1, word, dict, size);
}

//Substitute for for loop in printPermutations function
void loop(int i, int max, string prefix, string rest, const string dict[], int size, string results[], int& count) {
    //Base case
    if (i == max) return;
    
    //Statement: Remove char from rest and add it to prefix. Generate permutations.
    printPermutations(prefix + rest[i], rest.substr(0, i) + rest.substr(i+1, rest.size() - 1), dict, size, results, count);
    loop(i + 1, max, prefix, rest, dict, size, results, count);

}

//Function to generate permutations of the provided word
void printPermutations(string prefix, string rest, const string dict[], int size, string results[], int& count){

    //Base case: entire scrambled word is in prefix and "rest" is empty.
    if(rest == "") {
        //Insert permutation into permutation array WITHOUT REPEATS, if valid to do so.
        if(count >= MAXRESULTS) return;
        if(valid(0, prefix, dict, size) && !repeats(0, prefix, results, count)){
            results[count] = prefix;
            count++;
        }
        return;
    }
    else {
        //For each character in "rest", add char to prefix, remove char from rest, generate permutations with updated vals
        loop(0, rest.size(), prefix, rest, dict, size, results, count);
    }

}


//Puts all possiblities of "word" found in "dict" into "results". Returns # of matched words found (Can't be more than MAXRESULTS). Size is # words inside dict array.
//results should have no duplicates.
int theJumbler(string word, const string dict[], int size, string results[]){
    int count = 0;

    //Calculate each non-repeating permutation and check each one with all words in the dictionary. If matched, insert dictionary word into results[].
    printPermutations("", word, dict, size, results, count);

    return count;
}

//Displays "size" # of strings from "results", printed in any order.
void divulgeSolutions(const string results[], int size){
    if(size == 0) return;

    if(results[0] != "")
        cout << "Matching word " << results[0] << endl;

    divulgeSolutions(results + 1, size - 1);
}



int main()
{

    string results[MAXRESULTS];

//    string exampleDict[] = {"kool", "moe", "dee", "okol", "look", "olok", "oo", "lkoo"};
//     int testResults = theJumbler("kloo", exampleDict, 8, results);
//     assert(testResults == 5);
//    divulgeSolutions(results, 5);

    string dict[MAXDICTWORDS];
    ifstream dictfile;         // file containing the list of words
    int nwords;                // number of words read from dictionary
    string word;

//    dictfile.open("/Users/jameswu/Desktop/sample.txt");    //Local Testing with different dictionaries
//    dictfile.open("/Users/jameswu/Desktop/Project 3/Project 3/words.txt");    //Local Testing with provided dictionary
    dictfile.open("words.txt"); //g32 Testing
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
