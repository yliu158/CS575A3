#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

//global variable matrix to store string similarity
vector<vector<int> > matrix;


// declaration of functions
void getString(string& mystr); // get one string from the user
void prepareMatrix(const string& str_1, const string& str_2); // using two strings make a matrix
void lengthLCS(); // using the LCS algorithm to get longest common subsequence
void printMatrix(); // print the matrix

// main function
int main() {
  lengthLCS();
  return 0;
}


// implementation of functions
// get one string from the user
void getString(string& mystr){
  cout << "Please input a string ";
  getline(cin, mystr);
  while (cin.fail()) {
    cin.clear();
    cin.ignore();
    cout << "Please input a string ";
    getline(cin, mystr);
  }
  cout << "The string you input is: " << mystr << ".\n";
  return;
}

// using two strings to make a matrix about the similarity of the two
void prepareMatrix(const string& str_1, const string& str_2){
  matrix = vector<vector<int> >(str_1.length()+1, vector<int>(str_2.length()+1));
  // str_1 str_2
  for (int i = 0; i < str_1.length()+1; i++) {
    matrix.at(i).at(0) = 0;
  }
  for (int i = 0; i < str_2.length()+1; i++) {
    matrix.at(0).at(i) = 0;
  }

  for (int i = 1; i < str_1.length()+1 ; i++){
    for (int j = 1; j < str_2.length()+1; j++) {
      if (str_1.at(i-1) == str_2.at(j-1)) {
        matrix.at(i).at(j) = matrix.at(i-1).at(j-1)+1;
      } else {
        matrix.at(i).at(j) = max(matrix.at(i).at(j-1), matrix.at(i-1).at(j));
      }
    }
  }
}

// implement the LCS algorithm
// run in an infinite loop until the user stop it
void lengthLCS() {
  string input = "";
  bool sign = true;
  while (sign) {

    string str_1;
    string str_2;
    getString(str_1);
    getString(str_2);
    prepareMatrix(str_1, str_2);
    printMatrix();
    cout << "The longest common subsequence is: ";
    cout << matrix.at(matrix.size()-1).at(matrix.at(0).size()-1);
    cout << endl;

    cout << "Press any other button to continue." << endl;
    cout << "Press e to Exit." << endl;
    cin >> input;
    if (input[0] == 'e' || input[0] == 'E') {
      sign = false;
    }

    while (cin.fail()) {
      cin.clear();
      cin.ignore();
      cin >> input;
      if (input[0] == 'e' || input[0] == 'E') {
         sign = false;
      }
    }
  }
  cout << "Successfully Exited" << endl;

}

// print the matrix to check the answer
void printMatrix() {
  for (int i = 0; i < matrix.size(); i++) {
    for (int j = 0; j < matrix.at(i).size(); j++){
      cout << matrix.at(i).at(j) << " ";
    }
    cout << endl;
  }
}
