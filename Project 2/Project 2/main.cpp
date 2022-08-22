//#include "WeddingGuest.h"
//#include <type_traits>
//
//#define CHECKTYPE(f, t) { auto p = (t)(f); (void)p; }
//static_assert(std::is_default_constructible<WeddingGuest>::value
//, "Map must be default-constructible.");
//
//static_assert(std::is_copy_constructible<WeddingGuest>::value,
// "Map must be copy-constructible.");
//void ThisFunctionWillNeverBeCalled() {
// CHECKTYPE(&WeddingGuest::operator=, WeddingGuest&
// (WeddingGuest::*)(const WeddingGuest&));
// CHECKTYPE(&WeddingGuest::noGuests, bool
// (WeddingGuest::*)() const);
// CHECKTYPE(&WeddingGuest::guestCount, int
// (WeddingGuest::*)() const);
// CHECKTYPE(&WeddingGuest::inviteGuest, bool (WeddingGuest::*)
// (const std::string&, const std::string&, const
//GuestType&));
// CHECKTYPE(&WeddingGuest::alterGuest, bool
// (WeddingGuest::*)(const std::string&, const std::string&,
// const GuestType&));
// CHECKTYPE(&WeddingGuest::inviteOrAlter, bool
// (WeddingGuest::*)(const std::string&, const std::string&,
// const GuestType&));
// CHECKTYPE(&WeddingGuest::crossGuestOff, bool
//(WeddingGuest::*)
// (const std::string&, const std::string&));
// CHECKTYPE(&WeddingGuest::invitedToTheWedding, bool
// (WeddingGuest::*)(const std::string&, const std::string&)
// const);
// CHECKTYPE(&WeddingGuest::matchInvitedGuest, bool
//(WeddingGuest::*)
// (const std::string&, const std::string&, GuestType&)
//const);
// CHECKTYPE(&WeddingGuest::verifyGuestOnTheList, bool
//(WeddingGuest::*)
// (int, std::string&, std::string&, GuestType&)
// const);
// CHECKTYPE(&WeddingGuest::swapWeddingGuests, void
// (WeddingGuest::*)(WeddingGuest&));
// CHECKTYPE(joinGuests, bool (*)(const WeddingGuest&, const
// WeddingGuest&, WeddingGuest&));
// CHECKTYPE(attestGuests, void (*)(const std::string&,
// const std::string&, const WeddingGuest&, WeddingGuest&));
//}
//int main() {}

//#include "WeddingGuest.h"
//#include <string>
//#include <iostream>
//#include <cassert>
//using namespace std;
//void test() {
// WeddingGuest eliteSingles;
//
// assert(eliteSingles.inviteGuest("Jackie", "S",
// "jackies@elitesingles.com"));
// assert(eliteSingles.inviteGuest("Mark", "P",
// "markp@elitesingles.com"));
// assert(eliteSingles.guestCount() == 2);
// string first, last, e;
// assert(eliteSingles.verifyGuestOnTheList(0, first, last, e)
// && e == "markp@elitesingles.com");
// assert(eliteSingles.verifyGuestOnTheList(1, first, last, e)
// && (first == "Jackie" && e == "jackies@elitesingles.com"));
// return;
//}
//int main() {
// test();
// cout << "Passed all tests" << endl;
// return 0;
//}

//#include "WeddingGuest.h"
//#include <string>
//#include <iostream>
//#include <cassert>
//using namespace std;
//void test() {
// WeddingGuest youngins;
// assert(youngins.inviteGuest("Lauren", "U", 23));
// assert(youngins.inviteGuest("James", "H", 29));
// assert(youngins.guestCount() == 2);
// string first, last;
// int a;
// assert(youngins.verifyGuestOnTheList(0, first, last, a) && a
//== 29);
// assert(youngins.verifyGuestOnTheList(1, first, last, a) &&
//(first == "Lauren" && a == 23));
// return;
//}
//int main() {
// test();
// cout << "Passed all tests" << endl;
// return 0;
//}


//Test cases
#include <iostream>
#include <cassert>
#include "WeddingGuest.h"
using namespace std;

int main(){
    
    //Sample from spec
    // default constructor
    WeddingGuest lal;
    // For an empty list:
    assert(lal.guestCount() == 0); // test size
    assert(lal.noGuests()); // test empty
    assert(!lal.crossGuestOff("Malik", "Monk")); // nothing to erase

    //Test constructor
    WeddingGuest james;
    assert(james.noGuests());
    assert(james.guestCount() == 0);

    //Test functions (GuestType is a string)
    //inviteGuest, noGuests, guestCount, verifyGuestOnList, alterGuest
    string first;
    string last;
    GuestType val;
    james.inviteGuest("James", "Wu", "19");
    james.inviteGuest("Phillip", "Ma", "18");
    james.inviteGuest("Kat", "Wang", "19");
    james.inviteGuest("Nathan", "Zhang", "19");
    assert(james.noGuests() == false);
    assert(james.guestCount() == 4);
    bool test = james.verifyGuestOnTheList(0, first, last, val);
    assert(first == "Phillip" && last == "Ma" && val == "18" && test);
    test = james.alterGuest("Phillip", "Ma", "20");    // Phillip val should now equal 20
    james.verifyGuestOnTheList(0, first, last, val);
    assert(val == "20" && test);
    test = james.alterGuest("Scrooge", "McDuck", "100");
    assert(!test);
    test = james.alterGuest("Phillip", "Ma", "20"); //Even though this value already exists, test should still be true
    assert(test);

    //inviteOrAlter, crossGuestOff, invitedToTheWedding
    test = james.inviteOrAlter("James", "Wu", "20");    //Name equal to name on list
    james.verifyGuestOnTheList(2, first, last, val);
    assert(test && first == "James" && last == "Wu" && val == "20");
    test = james.inviteOrAlter("Scooby", "Doo", "5");   //Name not on list, invite
    james.verifyGuestOnTheList(0, first, last, val);
    assert(test && first == "Scooby" && last == "Doo" && val == "5" && james.guestCount() == 5 && james.noGuests() == false);
    james.crossGuestOff("Scooby", "Doo");
    james.crossGuestOff("Kat", "Wang");
    assert(james.guestCount() == 3 && !james.noGuests());
    assert(james.invitedToTheWedding("Phillip", "Ma") && james.invitedToTheWedding("James", "Wu") && james.invitedToTheWedding("Nathan", "Zhang") && !james.invitedToTheWedding("james", "Wu") && !james.invitedToTheWedding("Scooby", "Doo") && !james.invitedToTheWedding("JAMES", "wu"));

    //List is now: Phillip, James, Nathan

    //matchInvitedGuest, verifyGuestOnTheList
    test = james.matchInvitedGuest("Nathan", "Zhang", val);
    assert(test && val == "19");
    test = james.matchInvitedGuest("Master", "Oogway", val);
    assert(!test && val == "19");
    test = james.verifyGuestOnTheList(-1, first, last, val);
    assert(!test);
    test = james.verifyGuestOnTheList(1, first, last, val);
    assert(test && first == "James" && last == "Wu" && val == "20");
    test = james.verifyGuestOnTheList(james.guestCount(), first, last, val);
    assert(!test);

    //Copy Constructor, assignment operator, swapWeddingGuests
    WeddingGuest michael(james);    //Copy constructor called
    string first2;
    string last2;
    GuestType val2;
    //Guest counts should be equivalent for michael and james
    for(int i = 0; i < michael.guestCount(); i++){
        michael.verifyGuestOnTheList(i, first2, last2, val2);
        james.verifyGuestOnTheList(i, first, last, val);
        assert(first == first2 && last == last2 && val == val2 && james.guestCount() == michael.guestCount() && james.noGuests() == michael.noGuests());
    }
    WeddingGuest wendy;
    wendy.inviteGuest("Harry", "Potter", "18");
    wendy.inviteGuest("Albus", "Dumbledore", "100");
    wendy.inviteGuest("Ron", "Weasley", "5");
    michael = wendy;    //Assignment operator called
    //Repeat process to test for equality
    for(int i = 0; i < michael.guestCount(); i++){
        michael.verifyGuestOnTheList(i, first2, last2, val2);
        wendy.verifyGuestOnTheList(i, first, last, val);
        assert(first == first2 && last == last2 && val == val2 && james.guestCount() == michael.guestCount() && james.noGuests() == michael.noGuests());
    }
    james.inviteGuest("Kat", "Wang", "20"); //Just to test for different lengths
    james.swapWeddingGuests(michael);   //Items should now be swapped
    assert(james.noGuests() == false && james.guestCount() == 3);
    assert(michael.noGuests() == false && michael.guestCount() == 4);
    for(int i = 0; i < james.guestCount(); i++){
        james.verifyGuestOnTheList(i, first, last, val);
        wendy.verifyGuestOnTheList(i, first2, last2, val2);
        assert(first == first2 && last == last2 && val == val2 && james.guestCount() == wendy.guestCount());
    }
    assert(michael.invitedToTheWedding("James", "Wu") && michael.invitedToTheWedding("Nathan", "Zhang") && michael.invitedToTheWedding("Phillip", "Ma") && michael.invitedToTheWedding("Kat", "Wang") && !michael.invitedToTheWedding("james", "wu"));
    james.swapWeddingGuests(james); //Aliasing-- james should be unchanged.
    for(int i = 0; i < james.guestCount(); i++){
        james.verifyGuestOnTheList(i, first, last, val);
        wendy.verifyGuestOnTheList(i, first2, last2, val2);
        assert(first == first2 && last == last2 && val == val2 && james.guestCount() == wendy.guestCount());
    }

    //joinGuests, attestGuests
    WeddingGuest jla;
    WeddingGuest avengers;
    jla.inviteGuest("Bruce", "Wayne", "20");
    jla.inviteGuest("Clark", "Kent", "30");
    jla.inviteGuest("Barry", "Allen", "20");
    avengers.inviteGuest("Tony", "Stark", "30");
    avengers.inviteGuest("Steve", "Rogers", "100");
    avengers.inviteGuest("Bruce", "Wayne", "20");
    WeddingGuest result;

    test = joinGuests(jla, avengers, result);
    assert(test);
    result.verifyGuestOnTheList(0, first, last, val);
    assert(first == "Barry" && last == "Allen" && val == "20");
    result.verifyGuestOnTheList(1, first, last, val);
    assert(first == "Clark" && last == "Kent" && val == "30");
    result.verifyGuestOnTheList(2, first, last, val);
    assert(first == "Steve" && last == "Rogers" && val == "100");
    result.verifyGuestOnTheList(3, first, last, val);
    assert(first == "Tony" && last == "Stark" && val == "30");
    result.verifyGuestOnTheList(4, first, last, val);
    assert(first == "Bruce" && last == "Wayne" && val == "20");
    assert(result.guestCount() == 5);
    avengers.alterGuest("Bruce", "Wayne", "10");
    test = joinGuests(jla, avengers, result);
    assert(!test && result.guestCount() == 4 && !result.invitedToTheWedding("Bruce", "Wayne"));
    test = joinGuests(jla, jla, result);
    assert(test);
    avengers.alterGuest("Bruce", "Wayne", "20");
    test = joinGuests(jla, avengers, jla);
//    jla.dump();
    assert(test);
    jla.verifyGuestOnTheList(0, first, last, val);
    assert(first == "Barry" && last == "Allen" && val == "20");
    jla.verifyGuestOnTheList(1, first, last, val);
    assert(first == "Clark" && last == "Kent" && val == "30");
    jla.verifyGuestOnTheList(2, first, last, val);
    assert(first == "Steve" && last == "Rogers" && val == "100");
    jla.verifyGuestOnTheList(3, first, last, val);
    assert(first == "Tony" && last == "Stark" && val == "30");
    jla.verifyGuestOnTheList(4, first, last, val);
    assert(first == "Bruce" && last == "Wayne" && val == "20");
    assert(jla.guestCount() == 5);

    test = joinGuests(avengers, avengers, avengers);
    assert(test);
//    avengers.dump();
    test = joinGuests(jla, avengers, avengers);
    assert(test);
//    avengers.dump();

    WeddingGuest sv;
    sv.inviteGuest("Gavin", "Belson", "50");
    sv.inviteGuest("Richard", "Hendricks", "26");
    sv.inviteGuest("Jared", "Dunn", "24");
    sv.inviteGuest("Nelson", "Belson", "20");
    sv.inviteGuest("Jared", "Wack", "24");
    sv.inviteGuest("Rick", "Hendricks", "18");
    sv.inviteGuest("Steve", "Jobs", "40");

    attestGuests("Steve", "Jobs", sv, result);
//    result.dump();
    attestGuests("Richard", "Hendricks", sv, result);
//    result.dump();
    attestGuests("*", "Belson", sv, result);
    assert(result.guestCount() == 2 && !result.noGuests());
//    result.dump();
    attestGuests("Jared", "*", sv, result);
    assert(result.guestCount() == 2 && !result.noGuests());
//    result.dump();
    attestGuests("*", "*", sv, result);
    assert(result.guestCount() == 7 && !result.noGuests());
//    result.dump();
    attestGuests("*", "belson", sv, result);
    assert(result.guestCount() == 0 && result.noGuests());
    attestGuests("*", "Belson", sv, sv);    //This should alter sv.
    assert(sv.guestCount() == 2 && !sv.noGuests());
//    sv.dump();
    attestGuests("James", "Wu", sv, sv);   //sv should be empty after this
    assert(sv.guestCount() == 0 && sv.noGuests());
//    sv.dump();

    cerr << "All tests passed\n";

}
