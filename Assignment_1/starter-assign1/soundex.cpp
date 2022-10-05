/*
 * TODO: remove and replace this file header comment
 * This is a .cpp file you will edit and turn in.
 * Remove starter comments and add your own
 * comments on each function and on complex code sections.
 */
#include "testing/SimpleTest.h"
#include "strlib.h"
#include "filelib.h"
#include "simpio.h"
#include <fstream>
#include <cctype>
#include <string>
#include "vector.h"
using namespace std;

/* This function is intended to return a string which
 * contains only the letter characters from the original
 * (all non-letter characters are removed)
 *
 * The original bug: if the first digit is not a letter,
 * this function will store the non-letter digit.
 */
string removeNonLetters(string s) {
    string result;
    for (int i = 0; i < s.length(); i++) {
        if (isalpha(s[i])) {
            result += s[i];
        }
    }
    return result;
}

/* This function is to transfer letters to numbers.
 * It takes one argument string `s` and return a
 * string which is full of numbers.
 */
string letterToNumber(string s) {
    string result;
    s = toLowerCase(s);

    string letterNum0 = "aeiouhwy";
    string letterNum1 = "bfpv";
    string letterNum2 = "cgjkqsxz";
    string letterNum3 = "dt";
    string letterNum4 = "l";
    string letterNum5 = "mn";
    string letterNum6 = "r";
    for (int i = 0; i < s.length(); ++i) {
        if (stringContains(letterNum0, s[i])) {
            result += "0";
        } else if (stringContains(letterNum1, s[i])) {
            result += "1";
        } else if (stringContains(letterNum2, s[i])) {
            result += "2";
        } else if (stringContains(letterNum3, s[i])) {
            result += "3";
        } else if (stringContains(letterNum4, s[i])) {
            result += "4";
        } else if (stringContains(letterNum5, s[i])) {
            result += "5";
        } else if (stringContains(letterNum6, s[i])) {
            result += "6";
        } else {
            continue;
        }
    }

    return result;
}

/* This function is to coalesce adjacent duplicate digits.
 * It takes one argument string `s` and return a
 * string which removes adjacent duplicate digits.
 */
string coalesceDigits(string s) {
    string result;
    for (int i = 0; i < s.length(); i++) {
        if (i == 0) {
            result += s[i];
        } else if (s[i] != s[i-1]) {
            result += s[i];
        }
    }
    return result;
}

/* This function combines function `letterToNumber`
 * and function `coalesceDigits`. In addition to
 * the above 2 functions, this function replaces
 * the first letter of the code.
 * It takes one argument string `s` and return a
 * string.
 */
string replaceCode(string s) {
    string result;
    result = coalesceDigits(letterToNumber(s));
    result[0] = toUpperCase(s[0]);
    return result;
}

/* This function removes all zeros from the code.
 * It takes one argument string `s` and return a
 * string with no zero.
 */
string removeZero(string s) {
    string result;
    for (int i = 0; i < s.length(); ++i) {
        if (s[i] != '0' ) result += s[i];
    }
    return result;
}

/* This function is to set the code to 4 digits.
 * It takes one argument string `s` and return a
 * string with no zero.
 */
string setFourDigits(string s) {
    string result;
    if (s.length() < 4) {
        result += s;
        for (int i = result.length(); i < 4; ++i){
            result += '0';
        }
    } else {
        result = s.substr(0,4);
    }
    return result;
}



/* This function achieves the Soundex algorithm.
 * It takes one argument string `s` and return a
 * Soundex code.
 */
string soundex(string s) {
    string result;

    result = removeNonLetters(s);
    result = replaceCode(result);
    result = removeZero(result);
    result = setFourDigits(result);

    return result;
}

/* This function is to calculate the soundex result for
 * a name databse.
 * It takes one argument Vector<string> `database` and
 * return a Vector soundex result.
 */
Vector<string> databaseSoundex(Vector<string> database) {
    Vector<string> result;

    for (int i = 0; i < database.size(); ++i) {
        result.add(soundex(database[i]));
    }

    return result;
}

/* This funtion is to find matched names by comparing
 * the passed Soundex value with the database name
 * Soundex value. And this function will print the
 * matched names in sorted sequence on the console.
 * It three argument string string name Soundex value,
 * a Vector<string> database, and a Vector<string>
 * database Soundex result.
 * It uses the name Soundex value to match the same
 * value from the database Soundex result. If matches,
 * it will storesd the name which has a same index in
 * database. And then it sorts the matched names and
 * print them on the console.
 */
void findSoundex(string         nameSoundex,
                 Vector<string> database,
                 Vector<string> databaseResult) {
    Vector<string> nameFound;

    for (int i = 0; i < databaseResult.size(); ++i) {
        if (nameSoundex == databaseResult[i]) {
            nameFound.add(database[i]);
        };
    }
    nameFound.sort();
    cout << "Matches from database: " << nameFound << endl;
}

/* This function is to find matched names for a name database.
 * It takes one argument string flie path, and print matched
 * names on the console.
 */
void soundexSearch(string filepath) {
    // The proivded code opens the file with the given name
    // and then reads the lines of that file into a vector.
    ifstream in;
    Vector<string> databaseNames;

    if (openFile(in, filepath)) {
        readEntireFile(in, databaseNames);
    }
    cout << "Read file " << filepath << ", "
         << databaseNames.size() << " names found." << endl;

    // The names in the database are now stored in the provided
    // vector named databaseNames
    Vector<string> databaseResults;
    string name;
    string nameResult;

    databaseResults = databaseSoundex(databaseNames);

    cout << endl;
    name = getLine("Enter a surname (RETURN to quit): ");

    while (name != "") {
        nameResult = soundex(name);
        cout << "Soundex code is " << nameResult << endl;

        findSoundex(nameResult, databaseNames, databaseResults);

        cout << endl;
        name = getLine("Enter a surname (RETURN to quit): ");
    }
    cout << "All done!" << endl;
    return;
}


/* * * * * * Test Cases * * * * * */


PROVIDED_TEST("Test removing puntuation, digits, and spaces") {
    string s = "O'Hara";
    string result = removeNonLetters(s);
    EXPECT_EQUAL(result, "OHara");
    s = "Planet9";
    result = removeNonLetters(s);
    EXPECT_EQUAL(result, "Planet");
    s = "tl dr";
    result = removeNonLetters(s);
    EXPECT_EQUAL(result, "tldr");
}


PROVIDED_TEST("Sample inputs from handout") {
    EXPECT_EQUAL(soundex("Curie"), "C600");
    EXPECT_EQUAL(soundex("O'Conner"), "O256");
}

PROVIDED_TEST("hanrahan is in lowercase") {
    EXPECT_EQUAL(soundex("hanrahan"), "H565");
}

PROVIDED_TEST("DRELL is in uppercase") {
    EXPECT_EQUAL(soundex("DRELL"), "D640");
}

PROVIDED_TEST("Liu has to be padded with zeros") {
    EXPECT_EQUAL(soundex("Liu"), "L000");
}

PROVIDED_TEST("Tessier-Lavigne has a hyphen") {
    EXPECT_EQUAL(soundex("Tessier-Lavigne"), "T264");
}

PROVIDED_TEST("Au consists of only vowels") {
    EXPECT_EQUAL(soundex("Au"), "A000");
}

PROVIDED_TEST("Egilsdottir is long and starts with a vowel") {
    EXPECT_EQUAL(soundex("Egilsdottir"), "E242");
}

PROVIDED_TEST("Jackson has three adjcaent duplicate codes") {
    EXPECT_EQUAL(soundex("Jackson"), "J250");
}

PROVIDED_TEST("Schwarz begins with a pair of duplicate codes") {
    EXPECT_EQUAL(soundex("Schwarz"), "S620");
}

PROVIDED_TEST("Van Niekerk has a space between repeated n's") {
    EXPECT_EQUAL(soundex("Van Niekerk"), "V526");
}

PROVIDED_TEST("Wharton begins with Wh") {
    EXPECT_EQUAL(soundex("Wharton"), "W635");
}

PROVIDED_TEST("Ashcraft is not a special case") {
    // Some versions of Soundex make special case for consecutive codes split by hw
    // We do not make this special case, just treat same as codes split by vowel
    EXPECT_EQUAL(soundex("Ashcraft"), "A226");
}

// TODO: add your test cases here

STUDENT_TEST("My test removing puntuation, digits, and spaces") {
    string s = "'*/!@#$%^&*()<>?pc***WAN*G*";
    string result = removeNonLetters(s);
    EXPECT_EQUAL(result, "pcWANG");
}

STUDENT_TEST("My test about transfering letters to numbers") {
    string s = "AEIOUHWYBFPVCGJKQSXZDTLMNR";
    string result = letterToNumber(s);
    EXPECT_EQUAL(result, "00000000111122222222334556");
}

STUDENT_TEST("My test about coalescing adjacent duplicate digits from the code") {
    string s = "222025";
    string result = coalesceDigits(s);
    EXPECT_EQUAL(result, "2025");
}

STUDENT_TEST("My test about replace the first number of the code") {
    string s = "ABCD3***";
    string result = replaceCode(s);
    EXPECT_EQUAL(result, "A123");
}

STUDENT_TEST("My test about remove all zero from the code") {
    string s = "A100304";
    string result = removeZero(s);
    EXPECT_EQUAL(result, "A134");
}

STUDENT_TEST("My test about set the code to four digits") {
    string s = "A12345";
    string result = setFourDigits(s);
    EXPECT_EQUAL(result, "A123");
    s = "B25";
    result = setFourDigits(s);
    EXPECT_EQUAL(result, "B250");
}

STUDENT_TEST("My test about function soundex") {
    string s = "Angelou";
    string result = soundex(s);
    EXPECT_EQUAL(result, "A524");
    s = "*/!@#$%^&*()<>?wAN*G*";
    result = soundex(s);
    EXPECT_EQUAL(result, "W520");
}
