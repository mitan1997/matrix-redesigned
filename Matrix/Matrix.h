//
//  Matrix.h
//  Test_File
//

#ifndef __Personal_Projects__Matrix__Matrix__
#define __Personal_Projects__Matrix__Matrix__

#include <iostream>
#include <vector>

class Matrix
{
   /// Matrix class implemented with 2D array, supporting operations such as row operations and augmentation
private:
   double **data;
   size_t wdth, hght; // implemented top to bottom, left to right

public:
   static const size_t MIN_DIM = 2;

   explicit Matrix(size_t height = MIN_DIM, size_t width = MIN_DIM);
   explicit Matrix(double** arr, size_t height, size_t width);
   Matrix(const Matrix &other);
   ~Matrix();
   static Matrix parser(const std::string& input);
   Matrix & operator=(const Matrix &rhs);
   Matrix & operator+=(const Matrix &rhs);
   Matrix & operator-=(const Matrix &rhs);
   Matrix & operator*=(double mult);

   size_t width() const {return wdth;}
   size_t height() const {return hght;}
   double * operator[](size_t row) const;
   double *& operator[](size_t row);

   Matrix operator*(const Matrix &other) const;
   Matrix operator*(double mult) const;
   Matrix operator-(const Matrix &other) const;
   Matrix operator+(const Matrix &other) const;
   bool operator==(const Matrix &rhs) const;

   double determinant() const;
   Matrix transpose() const;
   Matrix inverse() const;
   Matrix echelon() const;
   Matrix rref() const;
   static Matrix identity(size_t dim);

   bool validMatrix() const {return data != nullptr;}

public:
   class DimensionsMismatchException{};
   class OutOfRangeException{};
   class NonInvertibleException{};
   class InvalidMatrixException{};

private: // helper methods
   void clearMatrix();
   void scale(size_t row, double mult);
   void swap(size_t row1, size_t row2);
   size_t findFirstNonZero(size_t col) const;

   // determinant helper functions
   void removeRow(size_t row);
   void removeCol(size_t col);
   Matrix subMatrix(size_t startRow, size_t startCol, size_t ht = MIN_DIM,
                    size_t wdt = MIN_DIM);
   Matrix augment(const Matrix &mat);
};

std::ostream & operator<<(std::ostream &ostrm, const Matrix &mat);
std::vector<double> parser(const std::string& input);

#endif /* defined(__Test_File__Matrix__Matrix__) */
