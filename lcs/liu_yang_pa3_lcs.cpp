#include <stdio.h>
#include <vector>
#include <string.h>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

//global variable matrix to store string similarity
vector<vector<int> > matrix;
vector<vector<char> > direction;
string str_1;
string str_2;

// declaration of functions
void getString(string& mystr); // get one string from the user
void prepareMatrix(const string& str_1, const string& str_2); // using two strings make a matrix
void lengthLCS(); // using the LCS algorithm to get longest common subsequence
void printMatrix(); // print the matrix
void printLCS(); // print the longest common subsequence

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
  direction = vector<vector<char> >(str_1.length()+1, vector<char>(str_2.length()+1));
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
        direction.at(i).at(j) = 'd';
      } else {
        if (matrix.at(i).at(j-1) > matrix.at(i-1).at(j)) {
          matrix.at(i).at(j) = matrix.at(i).at(j-1);
          direction.at(i).at(j) = 'l';
        } else {
          matrix.at(i).at(j) = matrix.at(i-1).at(j);
          direction.at(i).at(j) = 'u';
        }
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
    cin.clear();
    cin.ignore();
    getString(str_1);
    getString(str_2);
    prepareMatrix(str_1, str_2);
    printMatrix();
    cout << "The lenth of the longest common subsequence is: ";
    cout << matrix.at(matrix.size()-1).at(matrix.at(0).size()-1);
    cout << endl;
    printLCS();
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
  cout << "matrix.\n";
  for (int i = 0; i < matrix.size(); i++) {
    for (int j = 0; j < matrix.at(i).size(); j++){
      cout << matrix.at(i).at(j) << " ";
    }
    cout << endl;
  }
  cout << "direction.\n";
  for (int i = 0; i < direction.size(); i++) {
    for (int j = 0; j < direction.at(i).size(); j++){
      cout << direction.at(i).at(j) << " ";
    }
    cout << endl;
  }
}

void printLCS() {
  int i = direction.size()-1;
  int j = direction.at(i).size()-1;
  string temp = "";
  while (i > 0 && j > 0) {
    if (direction.at(i).at(j) == 'u'){
      i --;
    } else if (direction.at(i).at(j) == 'l') {
      j --;
    } else {
      temp += str_2.at(j-1);
      i --; j --;
    }
  }
  if ( temp.size() == 0) return;
  string lcs = "";
  for (int i = temp.length()-1; i >=0 ; i--) {
    lcs += temp.at(i);
  }
  cout << "longest common subsequence is:" << lcs << endl;
}
