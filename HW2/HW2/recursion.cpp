//
//  main.cpp
//  HW2
//
//  Created by James Wu on 7/19/22.
//

#include <iostream>
#include <cassert>
using namespace std;

/*========== Question 1 ==========*/

// Returns the product of two non-negative integers, m and n,
// using only repeated addition.
int multiplyTwoNumbers(unsigned int m, unsigned int n)
{
    if(n == 0) return 0;
    
    int prod = m + multiplyTwoNumbers(m, n-1);
    
    return prod;
}


// Returns the number of occurrences of digit in the decimal
// representation of num. digit is an int between 0 and 9
// inclusive.
//
// Pseudocode Example:
// tabulationStation(18838, 8) => 3
// tabulationStation(55555, 3) => 0
// tabulationStation(0, 0) => 0 or 1 (either if fine)
//
int tabulationStation(int num, int digit)
{
    if(num == 0) return 0;
    
    int count = tabulationStation(num/10, digit);
    //Account for neg numbers with the OR statement
    if(num % 10 == digit || (num * -1) % 10 == digit) count++;
    
    return count;
}


// Returns a string where the same characters next each other in
// string n are separated by "55" (you can assume the input
// string will not have 5’s)
//
// Pseudocode Example:
// highFives("goodbye") => "go55odbye"
// highFives("yyuu") => "y55yu55u"
// highFives("aaaa") => "a55a55a55a"
//
string highFives(string n)
{
    //Edge case if string n doesn't even have any input
    if(n == "") return n;
    
    string result = n.substr(0,1);
    
    if(n.size() == 1) return n; //Can't compare two chars with only string length 1
    else if(n[0] == n[1]){
        result += "55";
        result += highFives(n.substr(1));
    }
    else{
        result += highFives(n.substr(1));
    }
    
    return result;
        
}


// str contains a single pair of parentheses, return a new
// string made of only the parentheses and whatever those
// parentheses contain
//
// Pseudocode Example:
// jheriCurls("abc{ghj}789") => "{ghj}"
// jheriCurls("{x}7") => "{x}"
// jheriCurls("4agh{y}") => "{y}"
// jheriCurls("4agh{}") => "{}"
//
string jheriCurls(string str)
{    
    string result;
    
    //Think of it like two pointers, front and back. Increment until we have target string.
    if(str[0] != '{'){
        return jheriCurls(str.substr(1));
    }
    else if(str[str.size() - 1] != '}'){
        return jheriCurls(str.substr(0, str.size() - 1));
    }
    
    return str;
}


// Return true if the total of any combination of elements in
// the array a equals the value of the target.
//
// Pseudocode Example:
// aggregationNation({2, 4, 8}, 3, 10) => true
// aggregationNation({2, 4, 8}, 3, 6) => true
// aggregationNation({2, 4, 8}, 3, 11) => false
// aggregationNation({2, 4, 8}, 3, 0) => true
// aggregationNation({}, 0, 0) => true
//
bool aggregationNation(const int a[], int size, int target)
{
    //If target is 0, always true
    if(target == 0) return true;
    if(size == 0 && target != 0) return false;
    
    //Catch all control paths by using just "target" instead of always decrementing.
    //If you always decrement, then target will only linearly go down.
    //Therefore, keep target the same for some cases and just decrement size to brute-force check every combo.
    bool subtract = aggregationNation(a, size-1, target - a[size-1]);
    bool decrementSize = aggregationNation(a, size-1, target);
    
    return subtract || decrementSize;
    
}


/*========== Question 2 ==========*/

// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise
bool onMyWayHome(string maze[], int nRows, int nCols,
                 int sr, int sc, int er, int ec){
    
    /*If the start location is equal to the ending location, then
     we've solved the maze, so return true.
     Mark the start location as visited.
     For each of the four directions,
      If the location one step in that direction (from the
      start location) is unvisited,
      then call onMyWayHome starting from that
      location and ending at the same ending location
      as in the current call).
      If that returned true,
      then return true.
     Return false.*/
    
    
    if(sr == er && sc == ec) return true;
        
    //Use 'v' char to represent that this point is visisted
    maze[sr][sc] = 'v';
    
    //North
    if(sr - 1 >= 0 && maze[sr - 1][sc] == '.' ){
        bool res = onMyWayHome(maze, nRows, nCols, sr - 1, sc, er, ec);
        if(res) return true;
    }
        
    //West
    if(sc - 1 >= 0 && maze[sr][sc - 1] == '.'){
        bool res = onMyWayHome(maze, nRows, nCols, sr, sc - 1, er, ec);
        if(res) return true;
    }
    
    //South
    if(sr + 1 < nRows && maze[sr + 1][sc] == '.'){
        bool res = onMyWayHome(maze, nRows, nCols, sr + 1, sc, er, ec);
        if(res) return true;
    }
    
    //East
    if(sc + 1 < nCols && maze[sr][sc + 1] == '.'){
        bool res = onMyWayHome(maze, nRows, nCols, sr, sc+ + 1, er, ec);
        if(res) return true;
    }
    
    return false;
}



int main() {
    //muliplyTwoNumbers
      assert( multiplyTwoNumbers(3, 4) == 12);
      assert( multiplyTwoNumbers(4, 4) == 16);
      assert( multiplyTwoNumbers(0, 0) == 0);
      assert( multiplyTwoNumbers(103, 4) == 412);
      assert( multiplyTwoNumbers(4, 103) == 412);
      assert( multiplyTwoNumbers(1, 4) == 4);
      assert( multiplyTwoNumbers(4, 1) == 4);
      assert( multiplyTwoNumbers(1, 1) == 1);
      assert( multiplyTwoNumbers(5, 9) == 45);
      
      //tabulationStation
      assert (tabulationStation(32433, 3) == 3);
      assert (tabulationStation(0, 0) == 1 || tabulationStation(0, 0) == 0); // or 0
      assert (tabulationStation(428229292, 2) == 5);
      assert (tabulationStation(1000000, 0) == 6);
      assert (tabulationStation(3, 3) == 1);
      assert (tabulationStation(111111111, 1) == 9);
      assert (tabulationStation(111111111, 9) == 0);
      assert (tabulationStation(111111111, 3) == 0);
      assert (tabulationStation(-111111111, 1) == 9);
      assert (tabulationStation(-32433, 3) == 3);
      assert (tabulationStation(-428229292, 2) == 5);
      assert (tabulationStation(-1000000, 0) == 6);
      assert (tabulationStation(-3, 3) == 1);
      
      
      //highFives
      assert( highFives("") == "");
      assert( highFives("goodbye") == "go55odbye");
      assert( highFives("yyuu") == "y55yu55u");
      assert( highFives("aaaa") == "a55a55a55a");
      assert( highFives("yuuy") == "yu55uy");
      assert( highFives("bb") == "b55b");
      assert( highFives("22222") == "2552552552552");
      assert( highFives("..") == ".55.");
      assert( highFives("bejeijofqm") == "bejeijofqm");
      assert( highFives(".") == ".");
      assert( highFives("3") == "3");
      assert( highFives("123466") == "12346556");
      
      //jheriCurls
      assert( jheriCurls("{}") == "{}");
      assert( jheriCurls("fdsj{s}s") == "{s}");
      assert( jheriCurls("fdsj{dews}s") == "{dews}");
      assert( jheriCurls("fdsj{}s") == "{}");
      assert( jheriCurls("hfjsdhf{hi}") == "{hi}");
      assert( jheriCurls("{dfdff}") == "{dfdff}");
      assert( jheriCurls("{123}") == "{123}");
      assert( jheriCurls("asdf{rrrr}dsfewkfjwejf") == "{rrrr}");
      assert( jheriCurls("{*7@#}1@#@") == "{*7@#}");
      
      //aggregationNation
      int barr[] = {2,5,7};
      assert( aggregationNation(barr, 3, 5) == true);
      assert( aggregationNation(barr, 3, 12) == true);
      assert( aggregationNation(barr, 3, 12) == true);
      assert( aggregationNation(barr, 3, 12) == true);
        
      int carr[] = {2,4,8};
      assert(aggregationNation(carr, 3, 10) == true);
      assert(aggregationNation(carr, 3, 6) == true);
      assert(aggregationNation(carr, 3, 11) == false);
      assert(aggregationNation(carr, 3, 0) == true);
      assert(aggregationNation(carr, 2, 8) == false);
      assert(aggregationNation(carr, 1, 10) == false);
      assert(aggregationNation(carr, 1, 2) == true);
      
      int darr[] = {-3, 7, 1, -5, 5};
      assert(aggregationNation(darr, 5, 4) == true);
      assert(aggregationNation(darr, 3, -5) == false);
      assert(aggregationNation(darr, 5, -8) == true);
      assert(aggregationNation(darr, 4, 0) == true);
      assert(aggregationNation(darr, 2, 4) == true);
      assert(aggregationNation(darr, 1, 1) == false);
      assert(aggregationNation(darr, 5, 6) == true);
      assert(aggregationNation(darr, 0, 0) == true);

      //onMyWayHome
      string maze[10] = {
            "XXXXXXXXXX",
            "X.......@X",
            "XX@X@@.XXX",
            "X..X.X...X",
            "X..X...@.X",
            "X....XXX.X",
            "X@X....XXX",
            "X..XX.XX.X",
            "X...X....X",
            "XXXXXXXXXX"
         };
      string maze1[10] = {
            "XXXXXXXXXX",
            "X.......@X",
            "XX@X@@.XXX",
            "X..X.X...X",
            "X..X...@.X",
            "X....XXX.X",
            "X@X....XXX",
            "X..XX.XX.X",
            "X...X....X",
            "XXXXXXXXXX"
         };
      string maze2[10] = {
            "XXXXXXXXXX",
            "X.......@X",
            "XX@X@@.XXX",
            "X..X.X...X",
            "X..X...@.X",
            "X....XXX.X",
            "X@X....XXX",
            "X..XX.XX.X",
            "X...X....X",
            "XXXXXXXXXX"
         };
      string maze3[10] = {
            "XXXXXXXXXX",
            "X.......@X",
            "XX@X@@.XXX",
            "X..X.X...X",
            "X..X...@.X",
            "X....XXX.X",
            "X@X....XXX",
            "X..XX.XX.X",
            "X...X....X",
            "XXXXXXXXXX"
         };
      
      assert(onMyWayHome(maze, 10, 10, 6, 4, 1, 1));
      assert(!onMyWayHome(maze1, 10, 10, 1, 1, 8, 1));
      assert(!onMyWayHome(maze2, 10, 10, 8, 1, 1, 1));
      assert(onMyWayHome(maze3, 10, 10, 1, 5, 4, 4));
      
      string maze4[6] = {
          "XXXXXXXXXX",
          "X..@....@X",
          "XX@X@@.XXX",
          "X..X.X.X.X",
          "X..X.X.@.X",
          "XXXXXXXXXX",
      };
      string maze5[6] = {
          "XXXXXXXXXX",
          "X..@....@X",
          "XX@X@@.XXX",
          "X..X.X.X.X",
          "X..X.X.@.X",
          "XXXXXXXXXX",
      };
      string maze6[6] = {
          "XXXXXXXXXX",
          "X..@....@X",
          "XX@X@@.XXX",
          "X..X.X.X.X",
          "X..X.X.@.X",
          "XXXXXXXXXX",
      };
      string maze7[6] = {
          "XXXXXXXXXX",
          "X..@....@X",
          "XX@X@@.XXX",
          "X..X.X.X.X",
          "X..X.X.@.X",
          "XXXXXXXXXX",
      };
      string maze8[6] = {
          "XXXXXXXXXX",
          "X..@....@X",
          "XX@X@@.XXX",
          "X..X.X.X.X",
          "X..X.X.@.X",
          "XXXXXXXXXX",
      };
      assert(!onMyWayHome(maze4, 6, 10, 1, 1, 1, 4));
      assert(!onMyWayHome(maze5, 6, 10, 4, 2, 4, 4));
      assert(onMyWayHome(maze6, 6, 10, 1, 1, 1, 2));
      assert(onMyWayHome(maze7, 6, 10, 1, 4, 4, 6));
      assert(onMyWayHome(maze8, 6, 10, 2, 6, 4, 6));
      
      cout << "all done";
         return 0;


//
//    /*========== Q1 Tests ==========*/
//    //Given tests
//    assert(tabulationStation(18838, 8) == 3);
//    assert(tabulationStation(55555, 3) == 0);
//    assert(tabulationStation(0, 0) == 0 || tabulationStation(0, 0) == 1);
//
//    assert(highFives("goodbye") == "go55odbye");
//    assert(highFives("yyuu") == "y55yu55u");
//    assert(highFives("aaaa") == "a55a55a55a");
//
//    assert(jheriCurls("abc{ghj}789") == "{ghj}");
//    assert(jheriCurls("{x}7") == "{x}");
//    assert(jheriCurls("4agh{y}") == "{y}");
//    assert(jheriCurls("4agh{}") == "{}");
//
//    int arr[] = {2,4,8};
//    assert(aggregationNation(arr, 3, 10) == true);
//    assert(aggregationNation(arr, 3, 6) == true);
//    assert(aggregationNation(arr, 3, 11) == false);
//    assert(aggregationNation(arr, 3, 0) == true);
//    assert(aggregationNation({}, 0, 0) == true);
//
//    //Own tests for each function
//    assert(multiplyTwoNumbers(2, 3) == 6);
//    assert(multiplyTwoNumbers(44, 2) == 88);
//    assert(multiplyTwoNumbers(1001, 365) == 365365);
//    assert(multiplyTwoNumbers(0, 3) == 0);
//    assert(multiplyTwoNumbers(0, 0) == 0);
//    assert(multiplyTwoNumbers(100, 100) == 10000);
//    assert(multiplyTwoNumbers(1, 4) == 4);
//    assert(multiplyTwoNumbers(9, 9) == 81);
//
//    assert(tabulationStation(121011, 1) == 4);
//    assert(tabulationStation(100, 1) == 1);
//    assert(tabulationStation(-515151515, 5) == 5);
//    assert(tabulationStation(667, 6) == 2);
//    assert(tabulationStation(22222, 2) == 5);
//    assert(tabulationStation(22, 2) == 2);
//    assert(tabulationStation(0, 0) == 1 || tabulationStation(0, 0) == 0);
//    assert(tabulationStation(-55, 2) == 0);
//    assert(tabulationStation(-55, 5) == 2);
//    assert(tabulationStation(-5223341, 2) == 2);
//    assert(tabulationStation(-654, 2) == 0);
//    assert(tabulationStation(-11111, 1) == 5);
//    assert(tabulationStation(1001, 0) == 2);
//    assert(tabulationStation(-1, 1) == 1);
//
//    assert(highFives("aa") == "a55a");
//    assert(highFives("aabbccddaaaaaa") == "a55ab55bc55cd55da55a55a55a55a55a");
//    assert(highFives("hello there") == "hel55lo there");
//    assert(highFives("  ") == " 55 ");
//    assert(highFives("no consecutive") == "no consecutive");
//    assert(highFives("turtle") == "turtle");
//    assert(highFives("") == "");
//    assert(highFives("scooby doo") == "sco55oby do55o");
//    assert(highFives("aaaaaaaaaa") == "a55a55a55a55a55a55a55a55a55a");
//    assert(highFives("1234") == "1234");
//    assert(highFives("11223344") == "1551255235534554");
//    assert(highFives("poop") == "po55op");
//    assert(highFives("jimmy") == "jim55my");
//    assert(highFives("computer science sksksksk") == "computer science sksksksk");
//    assert(highFives("sheepee") == "she55epe55e");
//
//    assert(jheriCurls("{}") == "{}");
//    assert(jheriCurls("{aksjdbaskdbhjhsfbsfsd}adiuwahdaiu882932u84932y4") == "{aksjdbaskdbhjhsfbsfsd}");
//    assert(jheriCurls("123456789{10111213141516}17181920") == "{10111213141516}");
//    assert(jheriCurls("{skskbskskbskbskbskbksbkskb}") == "{skskbskskbskbskbskbksbkskb}");
//    assert(jheriCurls("abcd{efg}hijk") == "{efg}");
//    assert(jheriCurls("{p}") == "{p}");
//    assert(jheriCurls("james{phillip}kat") == "{phillip}");
//    assert(jheriCurls("{{{{{}}") == "{{{{{}}");
//
//
//    /*========== Q2 Tests ==========*/
//    string maze[10] = {
//     "XXXXXXXXXX",
//     "X.......@X",
//     "XX@X@@.XXX",
//     "X..X.X...X",
//     "X..X...@.X",
//     "X....XXX.X",
//     "X@X....XXX",
//     "X..XX.XX.X",
//     "X...X....X",
//     "XXXXXXXXXX"
//     };
//    assert(onMyWayHome(maze, 10, 10, 6, 4, 1, 1));
//
//    string maze1[3] = {
//        ".XX",
//        "..X",
//        "X..",
//    };
//    assert(onMyWayHome(maze1, 3, 3, 0, 0, 2, 2));
//
//    string maze2[5] = {
//        ".XXXXX.",
//        ".XXXXX.",
//        ".XXXXX.",
//        ".XXXXX.",
//        ".......",
//    };
//    assert(onMyWayHome(maze2, 5, 7, 0, 0, 0, 6));
//
//    string maze3[5] = {
//        "...X.",
//        ".X.X.",
//        "XX.XX",
//        ".X...",
//        "XXXXX",
//    };
//
//    string maze4[5] = {
//        "...X.",
//        ".X.X.",
//        "XX.XX",
//        ".X...",
//        "XXXXX",
//    };
//
//    string maze5[5] = {
//        "...X.",
//        ".X.X.",
//        "XX.XX",
//        ".X...",
//        "XXXXX",
//    };
//
//    string maze6[5] = {
//        "...X.",
//        ".X.X.",
//        "XX.XX",
//        ".X...",
//        "XXXXX",
//    };
//
//    string maze7[5] = {
//        "...X.",
//        ".X.X.",
//        "XX.XX",
//        ".X...",
//        "XXXXX",
//    };
//
//    string maze8[5] = {
//        "...X.",
//        ".X.X.",
//        "XX.XX",
//        ".X...",
//        "XXXXX",
//    };
//
//    string maze9[5] = {
//        "...X.",
//        ".X.X.",
//        "XX.XX",
//        ".X...",
//        "XXXXX",
//    };
//
//    string maze10[5] = {
//        "...X.",
//        ".X.X.",
//        "XX.XX",
//        ".X...",
//        "XXXXX",
//    };
//
//    assert(onMyWayHome(maze3, 5, 5, 0, 0, 3, 4));
//    assert(!onMyWayHome(maze4, 5, 5, 0, 0, 3, 0));
//    assert(onMyWayHome(maze5, 5, 5, 0, 4, 1, 4));
//    assert(!onMyWayHome(maze6, 5, 5, 3, 4, 1, 4));
//    assert(onMyWayHome(maze7, 5, 5, 3, 4, 0, 0));
//    assert(onMyWayHome(maze8, 5, 5, 1, 2, 1, 2));
//    assert(onMyWayHome(maze9, 5, 5, 1, 2, 3, 4));
//    assert(!onMyWayHome(maze10, 5, 5, 1, 2, 4, 4));
//
//
//
//    cout << "All tests successful" << endl;
}
