//#include "Matrix.h"
#include <iostream>
#include <ctime>
#include <sstream>
#include <ostream>

using namespace std;

template <class T>
T input() {
   string userInput;
   getline(cin, userInput);

}

const string& operator+(int x, string s) {
   ostringstream oss;
   oss << "dfsfds";
   return oss.str() + s;
}

int main(int argc, const char* argv[])
{
   srand((unsigned)time(0L));
   /*
   size_t testRow = 4, testCol = 5;
   Matrix newMat(testRow, testCol);
   for (size_t row = 0; row < testRow; row++)
      for (size_t col = 0; col < testCol; col++)
         newMat[row][col] = rand() % 10;
   cout << newMat << endl;
   Matrix mat2;
   mat2 = newMat;
   cout << mat2 << endl;
   Matrix mat3(mat2);
   cout << mat3 << endl;
   cout << mat3.transpose() << endl;
   */

   string str = "HELLO";
   cout << "34235" << endl;
   std::cout << 38742 + str << endl;  
   cout << "342" << endl; // Shifts to the right

   /*
   Matrix A(2, 2), C(2, 4);
   A[0][0] = 1; A[0][1] = 4;
   A[1][0] = 2; A[1][1] = 3;

   C[0][0] = 1; C[0][1] = 9; C[0][2] = 5; C[0][3] = 7;
   C[1][0] = 4; C[1][1] = 3; C[1][2] = 2; C[1][3] = 2;
   cout << A * C << endl;
   */

   return 0;
}

