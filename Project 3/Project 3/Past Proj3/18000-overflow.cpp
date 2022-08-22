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

//Puts the characters of word in alphabetical order using selection sort
int nextIndex(string s, int left, int right){
    //Base case
    if(left == right) return left;

    int minLeft = nextIndex(s, left + 1, right);    //Advances iterator to the right

    return s[left] <= s[minLeft] ? left : minLeft;   //This ensures the characters are alphabetically coorect
}

string wordAlpha(string s, int index, int size){
    
    if(index == size) return "";
    
    int min = nextIndex(s, index, size - 1);
    
    if(min != index){
        char temp = s[index];
        s[index] = s[min];
        s[min] = temp;
    }
    
    return s[index] + wordAlpha(s, index + 1, size);
    
}


//"i" is used to keep track of the index in results[].
int jumbleHelper(string word, const string dict[], int size, string results[], int i){
    //Base case: Ensure no more than MAXRESULTS entries are entered, and that program breaks if no more words in dict
    //Do i == MAXRESULTS because i starts at 0.
    if(i == MAXRESULTS || size == 0) return 0;

//    cout << 25144 - size + 1 << endl;

    //Pseudocode: Put word in alphabetical order, then for every word in dict, put that in alphabetical order too. If chars are same, add to results.
    if(word == wordAlpha(dict[0], 0, dict[0].size())){
        results[i] = dict[0];
        return 1 + jumbleHelper(word, dict + 1, size - 1, results, i + 1);
    }

    return jumbleHelper(word, dict + 1, size - 1, results, i);
}


//Puts all possiblities of "word" found in "dict" into "results". Returns # of matched words found (Can't be more than MAXRESULTS). Size is # words inside dict array.
//results should have no duplicates.
int theJumbler(string word, const string dict[], int size, string results[]){
    return jumbleHelper(wordAlpha(word, 0, word.size()), dict, size, results, 0);
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

//    dictfile.open("/Users/jameswu/Desktop/Project 3/Project 3/words.txt");    //Local Testing
    dictfile.open("words.txt");  //g32 Testing
    if (!dictfile) {
        cout << "File not found!" << endl;
        return (1);
    }

    nwords = lexiconBuilder(dictfile, dict);

    cout << "Num words: "<< nwords << endl;
            
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
