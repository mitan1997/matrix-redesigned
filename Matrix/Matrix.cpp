//
//  Matrix.cpp
//  Test_File
//

#include "Matrix.h"

Matrix::Matrix(size_t height, size_t width)
{
   wdth = (width < MIN_DIM)? MIN_DIM : width;
   hght = (height < MIN_DIM)? MIN_DIM : height;
   data = new double*[hght];
   for (size_t i = 0; i < hght; i++)
      data[i] = new double[wdth];
}

Matrix::Matrix(double** arr, size_t height, size_t width)
{
   if (height < MIN_DIM || width < MIN_DIM)
      throw InvalidMatrixException();
   
}

Matrix::Matrix(const Matrix &other)
{
   if (!other.validMatrix())
      throw InvalidMatrixException();
   data = nullptr;
   *this = other;
}

Matrix::~Matrix()
{
   clearMatrix();
}

Matrix Matrix::parser(const std::string& input)
{
   return Matrix();
}

Matrix & Matrix::operator=(const Matrix &other)
{
   if (!other.validMatrix())
      throw InvalidMatrixException();
   if (this != &other)
   {
      clearMatrix();
      hght = other.height();
      wdth = other.width();
      data = new double* [this->height()];
      for (size_t row = 0; row < height(); row++)
      {
         data[row] = new double[width()];
         for (size_t col = 0; col < width(); col++)
            data[row][col] = other[row][col];
      }
   }
   return *this;

}

Matrix & Matrix::operator+=(const Matrix &rhs)
{
   if (!this->validMatrix() || !rhs.validMatrix())
      throw InvalidMatrixException();
   if (this->height() != rhs.height() || this->width() != rhs.width())
      throw DimensionsMismatchException();
   for (size_t row = 0; row < height(); row++)
      for (size_t col = 0; col < width(); col++)
         data[row][col] += rhs[row][col];
   return *this;
}

Matrix & Matrix::operator-=(const Matrix &rhs)
{
   if (!this->validMatrix() || !rhs.validMatrix())
      throw InvalidMatrixException();
   if (this->height() != rhs.height() || this->width() != rhs.width())
      throw DimensionsMismatchException();
   for (size_t row = 0; row < height(); row++)
      for (size_t col = 0; col < width(); col++)
         data[row][col] -= rhs[row][col];
   return *this;
}

Matrix & Matrix::operator*=(double mult)
{
   if (!this->validMatrix())
      throw InvalidMatrixException();
   for (size_t row = 0; row < height(); row++)
      scale(row, mult);
   return *this;
}

double * Matrix::operator[](size_t row) const
{
   if (row >= hght)
      throw OutOfRangeException();
   if (!this->validMatrix())
      throw InvalidMatrixException();
   return data[row];
}

double *& Matrix::operator[](size_t row)
{
   if (row >= hght)
      throw OutOfRangeException();
   if (!validMatrix())
      throw InvalidMatrixException();
   return data[row];
}

Matrix Matrix::operator*(const Matrix &other) const
{
   if (!this->validMatrix() || !other.validMatrix())
      throw InvalidMatrixException();
   if (this->width() != other.height())
      throw DimensionsMismatchException();
   Matrix newMatrix(this->height(), other.width());
   for (size_t row = 0; row < newMatrix.height(); row++)
      for (size_t col = 0; col < newMatrix.width(); col++)
      {
         double sum = 0;
         for (size_t i = 0; i < this->width(); i++)
            sum += data[row][i] * other[i][col];
         newMatrix[row][col] = sum;
      }
   return newMatrix;
}

Matrix Matrix::operator*(double mult) const
{
   if (!this->validMatrix())
      throw InvalidMatrixException();
   Matrix newMatrix = Matrix(*this);
   for (size_t row = 0; row < height(); row++)
      newMatrix.scale(row, mult);
   return newMatrix;
}

Matrix Matrix::operator-(const Matrix &other) const
{
   if (!this->validMatrix() || !other.validMatrix())
      throw InvalidMatrixException();
   if (this->height() != other.height() || this->width() != other.width())
      throw DimensionsMismatchException();
   
   Matrix newMatrix(height(), width());
   for (size_t row = 0; row < height(); row++)
      for (size_t col = 0; col < width(); col++)
         newMatrix[row][col] = (*this)[row][col] - other[row][col];
   return newMatrix;
}

Matrix Matrix::operator+(const Matrix &other) const
{
   if (!this->validMatrix() || !other.validMatrix())
      throw InvalidMatrixException();
   if (this->height() != other.height() || this->width() != other.width())
      throw DimensionsMismatchException();
   Matrix newMatrix(height(), width());
   for (size_t row = 0; row < height(); row++)
      for (size_t col = 0; col < width(); col++)
         newMatrix[row][col] = (*this)[row][col] + other[row][col];
   return newMatrix;
}

bool Matrix::operator==(const Matrix &rhs) const
{
   if (!validMatrix() || !rhs.validMatrix())
      throw InvalidMatrixException();
   
   if (this->height() != rhs.height() || this->width() != rhs.width())
      return false;
   
   for (size_t row = 0; row < height(); row++)
      for (size_t col = 0; col < width(); col++)
         if (data[row][col] != rhs[row][col])
            return false;
   return true;
}

double Matrix::determinant() const
{
   if (!validMatrix())
      throw InvalidMatrixException();
   if (width() == 2)
   {
      double sum = 0;
   }
}

Matrix Matrix::transpose() const
{
   if (!validMatrix())
      throw InvalidMatrixException();
   Matrix newMatrix(width(), height());
   for (size_t row = 0; row < newMatrix.height(); row++)
      for (size_t col = 0; col < newMatrix.width(); col++)
         newMatrix[row][col] = (*this)[col][row];
   return newMatrix;
}

Matrix Matrix::inverse() const
{
   if (!this->validMatrix())
      throw InvalidMatrixException();
   if (this->height() != this->width())
      throw DimensionsMismatchException();
}

Matrix Matrix::echelon() const
{
   if (!this->validMatrix())
      throw InvalidMatrixException();
}

Matrix Matrix::rref() const
{
   if (!this->validMatrix())
      throw InvalidMatrixException();
}

Matrix Matrix::identity(size_t dim)
{
   Matrix newMat = Matrix(dim, dim);
   for (size_t i = 0; i < dim; i++)
      newMat[i][i] = 1;
   return newMat;
}

void Matrix::clearMatrix()
{
   if (data == nullptr)
      return;
   
   for (size_t row = 0; row < hght; row++)
      delete [] data[row];
   delete [] data;
   data = nullptr;
}

void Matrix::scale(size_t row, double mult)
{
   if (!validMatrix())
      throw InvalidMatrixException();
   if (row >= hght)
      throw OutOfRangeException();

   for (size_t col = 0; col < height(); col++)
      data[row][col] *= mult;
}

void Matrix::swap(size_t row1, size_t row2)
{
   if (row1 >= height() || row2 >= height())
      throw OutOfRangeException();
   if (!validMatrix())
      throw InvalidMatrixException();
   double *temp = data[row1];
   data[row1] = data[row2];
   data[row2] = temp;
}

size_t Matrix::findFirstNonZero(size_t col) const
{
   if (!this->validMatrix())
      throw InvalidMatrixException();
   for (size_t row = 0; row < this->height(); row++)
      if (data[row][col] != 0)
         return row;
   return std::string::npos;
}

void Matrix::removeRow(size_t row)
{
   if (!validMatrix())
      throw InvalidMatrixException();
   if (row >= height())
      throw OutOfRangeException();
   double *rowToBeDeleted = data[row];
   for (size_t r = row; r < height() - 1; r++)
      data[r] = data[r + 1];
   data[height() - 1] = nullptr;
   delete [] rowToBeDeleted;
   hght--;
}

void Matrix::removeCol(size_t col)
{
   if (!validMatrix())
      throw InvalidMatrixException();
   if (col >= width())
      throw OutOfRangeException();
   for (size_t row = 0; row < height(); row++)
   {
      for (size_t c = col; c < width() - 1; c++)
         data[row][c] = data[row][c + 1]; // shift to last
      // last element in each row only hidden from client
      // is there a way to handle memory leak without recopying array?
      for (size_t r = 0; r < height(); r++)
      {
         double* newRow = new double[width() - 1];
         for (size_t c = 0; c < width() - 1; c++)
            newRow[c] = data[row][c];
      }
   }
   wdth--;
}

Matrix Matrix::subMatrix(size_t startRow, size_t startCol, size_t ht,
                         size_t wdt)
{
   if (!validMatrix() || ht < MIN_DIM || wdt < MIN_DIM)
      throw InvalidMatrixException();
   if (startRow + ht - 1>= height() || startCol + wdt - 1 >= width())
      throw OutOfRangeException();
   Matrix newMatrix(ht, wdt);
   for (size_t r = 0; r < ht; r++)
      for (size_t c = 0; c < wdt; c++)
         newMatrix[r][c] = data[startRow + r][startCol + c];
   return newMatrix;
}

Matrix Matrix::augment(const Matrix& other)
{
   if (!this->validMatrix() || !other.validMatrix())
      throw InvalidMatrixException();
   if (!this->height() != other.height())
      throw DimensionsMismatchException();
   Matrix newMatrix(this->height(), this->width() + other.width());

   return newMatrix;
}

std::vector<double> parser(const std::string& input) {
   std::vector<double> result;
}

std::ostream & operator<<(std::ostream &ostrm, const Matrix &mat)
{
   for (size_t row = 0; row < mat.height(); row++)
   {
      for (size_t col = 0; col < mat.width(); col++)
         ostrm << mat[row][col] << " ";
      ostrm << std::endl;
   }
   
   return ostrm;
}