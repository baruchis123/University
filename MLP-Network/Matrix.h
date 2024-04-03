// Matrix.h

#ifndef MATRIX_H
#define MATRIX_H

/**
 * An Error message in case of incomplete memory allocation.
 */
#define MEM_ERROR "Error: memory not allocated successfully"

/**
 * An Error message in case of invalid matrix dimensions.
 */
#define INVALID_DIM_ERROR "Error: matrix dimensions invalid"

/**
 * An Error message in case of invalid index when accessing matrix.
 */
#define INDEX_ERROR "Error: Index Error"

/**
 * An Error message in case the file wasn't read until the end.
 */
#define EOF_ERROR "Error: EOF"

#include <iostream>

/**
 * @struct MatrixDims
 * @brief Matrix dimensions container
 */
typedef struct MatrixDims
{
    int rows, cols;
} MatrixDims;

/**
 * A matrix class, with 3 class variables.
 * @param rows - the num of rows in the matrix
 * @param cols - the num of cols in the matrix
 * @param matrix - an array of floats containing the values of the matrix.
 */
class Matrix
{
private:
    int _rows;
    int _cols;
    float *_matrix;


public:
    /**
     * The constructor for matrix class, sets the array of values to 0.
     * @param rows - row dimension of matrix.
     * @param cols - col dimension of matrix.
     */
    Matrix (int rows, int cols);

    /**
     * Default constructor for the matrix, creates a matrix of 1x1 dimensions, and value set to 0.
     */
    Matrix();

    /**
     * Matrix copy constructor, accepts another matrix and deep copies.
     * @param other
     */
    Matrix(const Matrix &other);

    /**
     * the Destructor for the Matrix class.
     */
    ~Matrix();

    /**
     * A class method
     * @return row dimension of the matrix.
     */
    int getRows() const;

    /**
     * A class method
     * @return col dimension of the matrix.
     */
    int getCols() const;

    /**
     * This method turns a matrix into a single column vector.
     * @return the object.
     */
    Matrix& vectorize();

    /**
     * A class method, this method prints the values of the matrix by row.
     */
    void plainPrint() const;

    /**
     * An operator, overloads the = operator, thus deep copying the values of one matrix to another.
     * @param other - another instance of a matrix.
     * @return a refrence to this instance, with values copied.
     */
    Matrix& operator=(const Matrix &other);

    /**
     * An operator, overloads the * operator, enables matrix multiplication.
     * @param other - another instance of a matrix.
     * @return a new instance of a matrix.
     */
    Matrix operator*(const Matrix& other) const;

    /**
     * An operator, overloads the * operator, enables multiplication of a matrix with a scalar on the right.
     * @param scalar -  a scalar we are multiplying the matrix with.
     * @return a new instance of a matrix.
     */
    Matrix operator*(float scalar) const;

    /**
     * An operator, overloads the * operator, enables multiplication of a matrix with a scalar on the left.
     * @param scalar
     * @param other
     * @return a new instance of a matrix.
     */
    friend Matrix operator*(float scalar, Matrix& other) ;

    /**
     * An operator, overloads the + operator, enables addition of two matrices.
     * @param other - another instance of a matrix.
     * @return a new instance of a matrix.
     */
    Matrix operator+(const Matrix& other) const;

    /**
     * An operator, overloads the += operator, enables accumulative addition of two matrices.
     * @param other - another instance of a matrix.
     * @return the accumulating matrix
     */
    Matrix& operator+=(const Matrix& other);

    /**
     * An operator, overloads the [] operator, enables access by index (according to array shape of the matrix).
     * @param index
     * @return returns the value at the index
     */
    float operator[](int index)const;

    /**
     * An operator, overloads the [] operator, enables setting a new value at index (by array shape of the matrix).
     * @param index
     * @return returns a ref to value at the index
     */
    float& operator[](int index);

    /**
     * An operator, overloads the () operator, enables access to value at index (by matrix shape).
     * @param i - index of row.
     * @param j - index of column.
     * @return - value at index.
     */
    float operator()(int i, int j)const;

    /**
     * An operator, overloads the () operator, enables setting a new value at index (by matrix shape).
     * @param i - index of row.
     * @param j - index of column.
     * @return ref to value at index.
     */
    float& operator()(int i, int j);

    /**
     * An operator, overloads the >> operator, enables inputting values to the matrix.
     * @param is - input stream.
     * @param matrix - matrix accepting info.
     * @return ref to is.
     */
    friend std::istream& operator>>(std::istream& is, Matrix& matrix);

    /**
     * An operator, overloads the << operator, enables printing values of the matrix.
     * @param os - output stream
     * @param matrix - matrix who's values are being outputted.
     * @return a ref to os
     */
    friend std::ostream& operator<<(std::ostream& os, Matrix& matrix);

};
#endif //MATRIX_H
