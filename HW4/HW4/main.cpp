#include <fstream>
#include <iostream>
#include <cctype>
#include <string>
#include <cassert>
#include "WordTree.h"
using namespace std;

int main() {
    ifstream fin;
    ofstream fout;
    string filename;

    cout << "Enter name of file with text to analyze: ";
    cin >> filename;

    //g32 testing
//    fin.open(filename.c_str());
    
    //Local testing
    string result = "/Users/jameswu/Desktop/HW4/HW4/" + filename + ".txt";
    fin.open(result.c_str());


    if (fin.fail()) {
        cout << "Error opening file.\n";
        exit(1);
    }

    cout << "\nAnalyzing " << filename << ".\n";
    WordTree myTree;

    //insert code here
    WordType word;
    //Writes fin word to WordType "word"
    while(fin >> word){

        WordType res = "";
        //Only add alphabetical words
        for(int i = 0; i < word.size(); i++){
            //Hyphenated word found
            if(word[i] == '-' && i + 1 != word.size() && word[i + 1] != '-'){
                if(res != "") myTree.add(res);
                res = "";
                continue;
            }

            if(isalpha(word[i]) || word[i] == '\'') res += tolower(word[i]);
        }

        if(res != "") myTree.add(res);

    }

    fin.close();
//    fout.open("results.txt");
    fout.open("/Users/jameswu/Desktop/results.txt");   //Local testing
    
    cout << "\nWord counts:\n\n";
    cout << myTree;
    fout << myTree;
    cout << "\nTotal number of words in text: " << myTree.totalWords() << ".\n";
    fout << "\nTotal number of words in text: " << myTree.totalWords() << ".\n";
    cout << "Number of distinct words appearing in text: " << myTree.distinctWords() << ".\n";
    fout << "Number of distinct words appearing in text: " << myTree.distinctWords() << ".\n";
    fout.close();
    
    
    
    /*========== Test cases ==========*/
    WordTree k;

    k.add("Kim");
    k.add("Kanye");
    k.add("Kanye");
    k.add("Kanye");
    assert(k.distinctWords() == 2);
    assert(k.totalWords() == 4);
    
    WordTree w;

    w.add("Harry");
    w.add("Niall");
    w.add("Niall");
    w.add("Liam");
    w.add("Louis");
    w.add("Harry");
    w.add("Niall");
    w.add("Zayn");
    assert(w.distinctWords() == 5);
    assert(w.totalWords() == 8);
    
    WordTree alphabet;
    alphabet.add("m");
    alphabet.add("a");
    alphabet.add("z");
    alphabet.add("b");
    alphabet.add("y");
    alphabet.add("c");
    alphabet.add("a");
    alphabet.add("a");
    assert(alphabet.distinctWords() == 6);
    assert(alphabet.totalWords() == 8);
    
//    cout << alphabet << endl;
    
    WordTree dupe = alphabet;
    assert(dupe.distinctWords() == 6);
    assert(dupe.totalWords() == 8);
    
//    cout << dupe << endl;
    
    WordTree dupe2;
    dupe2.add("mango");
    dupe2.add("UCLA");
    dupe2.add("Hydroflask");
    assert(dupe2.distinctWords() == 3);
    assert(dupe2.totalWords() == 3);
    
    dupe2 = alphabet;
    assert(dupe2.distinctWords() == 6);
    assert(dupe2.totalWords() == 8);
    
//    cout << dupe2 << endl;
    
    //Aliasing
    alphabet = alphabet;
    assert(alphabet.distinctWords() == 6);
    assert(alphabet.totalWords() == 8);
//    cout << alphabet << endl;
    
    
//    cout << endl << "Success" << endl << endl;
    
    return 0;
}
