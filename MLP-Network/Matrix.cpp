//
// Created by baruc on 17/06/2020.
//
#include "Matrix.h"

/**
 * The constructor for matrix class, sets the array of values to 0.
 * @param rows - row dimension of matrix.
 * @param cols - col dimension of matrix.
 */
Matrix::Matrix(const int rows, const int cols) :_rows (rows), _cols(cols)
{
    if (rows < 1 || cols < 1) //check bounds are legal
    {
        std::cerr << INVALID_DIM_ERROR << std::endl;
        exit(EXIT_FAILURE);
    }
    _matrix = new float[_rows * _cols] (); // allocate memory on heap
    if (_matrix == nullptr)
    {
        std::cerr << MEM_ERROR << std::endl;
        exit(EXIT_FAILURE);
    }
}

/**
 * Default constructor for the matrix, creates a matrix of 1x1 dimensions, and value set to 0.
 */
Matrix::Matrix() : _rows(1), _cols(1)
{
    _matrix = new float[_rows * _cols] ();
    if (_matrix == nullptr)
    {
        std::cerr << MEM_ERROR << std::endl;
        exit(EXIT_FAILURE);
    }
}

/**
 * Matrix copy constructor, accepts another matrix and deep copies.
 * @param other
 */
Matrix::Matrix(const Matrix& other)
{
    _rows = other._rows;
    _cols = other._cols;
    _matrix = new float[_rows * _cols] ();
    if (_matrix == nullptr)
    {
        std::cerr << MEM_ERROR << std::endl;
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < (_rows * _cols); i++) //deep copy
    {
        _matrix[i] = other._matrix[i];
    }
}

/**
 * the Destructor for the Matrix class.
 */
Matrix::~Matrix()
{
    delete[](_matrix);
}

/**
 * A class method
 * @return row dimension of the matrix.
 */
int Matrix::getRows() const
{
    return _rows;
}

/**
 * A class method
 * @return col dimension of the matrix.
 */
int Matrix::getCols() const
{
    return _cols;
}

/**
 * This method turns a matrix into a single column vector.
 * @return the object.
 */
Matrix& Matrix::vectorize()
{
    _rows = _rows * _cols;
    _cols = 1;
    return *this;
}

/**
 * A class method, this method prints the values of the matrix by row.
 */
void Matrix::plainPrint() const
{
    for (int i = 0; i < _rows; i++)
    {
        for (int j = 0; j < _cols; j++)
        {
            std::cout << _matrix[i*_cols + j] << " " ;
        }
        std::cout << std::endl;
    }
}

/**
 * An operator, overloads the = operator, thus deep copying the values of one matrix to another.
 * @param other - another instance of a matrix.
 * @return a reference to this instance, with values copied.
 */
Matrix& Matrix::operator=(const Matrix &other)
{
    if (this == &other)
    {
        return *this;
    }
    delete[] _matrix; //free memory on heap
    _rows = other._rows;
    _cols = other._cols;
    _matrix = new float[_rows * _cols]; //allocate on heap
    for (int i = 0; i < (_rows * _cols); i++) //deep copy
    {
        _matrix[i] = other._matrix[i];
    }
    return *this;
}

/**
 * An operator, overloads the * operator, enables matrix multiplication.
 * @param other - another instance of a matrix.
 * @return a new instance of a matrix.
 */
Matrix Matrix::operator*(const Matrix& other) const
{
    if (_cols != other._rows) //check bounds are legal
    {
        std::cerr << INVALID_DIM_ERROR << std::endl;
        exit(EXIT_FAILURE);
    }
    Matrix multProduct = Matrix(_rows, other._cols);

    for (int i = 0;  i < _rows; i++)// matrix multiplication
    {
        for (int j = 0; j < other._cols ; j++)
        {
            float sum = 0;
            for (int k = 0; k < _cols; k++)
            {
                sum += (_matrix[(i * _cols) + k] * other._matrix[(k * other._cols) + j]);
            }
            multProduct._matrix[multProduct._cols*i + j] = sum;
        }
    }
    return multProduct;
}

/**
 * An operator, overloads the * operator, enables multiplication of a matrix with a scalar on the right.
 * @param scalar -  a scalar we are multiplying the matrix with.
 * @return a new instance of a matrix.
 */
Matrix Matrix::operator*(float scalar) const
{
    Matrix multProduct = Matrix(_rows, _cols);
    for (int i = 0; i <  (_rows * _cols); i++) // apply multiplication to each value
    {
        multProduct._matrix[i] = (_matrix[i]*scalar);
    }
    return multProduct;
}

/**
 * An operator, overloads the * operator, enables multiplication of a matrix with a scalar on the left.
 * @param scalar
 * @param other
 * @return a new instance of a matrix.
 */
Matrix operator*(float scalar, Matrix& other)
{
    Matrix multProduct = Matrix(other._rows, other._cols);
    for (int i = 0; i < (other._cols * other._rows); i++) // apply multiplication to each value
    {
        multProduct._matrix[i] = scalar*other._matrix[i];
    }
    return multProduct;
}

/**
 * An operator, overloads the + operator, enables addition of two matrices.
 * @param other - another instance of a matrix.
 * @return a new instance of a matrix.
 */
Matrix Matrix::operator+(const Matrix& other) const
{
    if (other._cols != _cols || other._rows != _rows) //check bounds are legal
    {
        std::cerr << INVALID_DIM_ERROR << std::endl;
        exit(EXIT_FAILURE);
    }
    Matrix sumProduct = Matrix(_rows, _cols);
    for (int i = 0; i < (_rows * _cols); i++) // sum values of both matrices at index
    {
        sumProduct._matrix[i] = (_matrix[i] + other._matrix[i]);
    }
    return sumProduct;
}

/**
 * An operator, overloads the += operator, enables accumulative addition of two matrices.
 * @param other - another instance of a matrix.
 * @return the accumulating matrix
 */
Matrix& Matrix::operator+=(const Matrix& other)
{
    if (other._cols != _cols || other._rows != _rows) //check bounds are legal
    {
        std::cerr << INVALID_DIM_ERROR << std::endl;
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < (_rows * _cols); i++) // sum values of both matrices at index
    {
        _matrix[i] += other._matrix[i];
    }
    return *this;
}

/**
 * An operator, overloads the [] operator, enables access by index (according to array shape of the matrix).
 * @param index
 * @return returns the value at the index
 */
float Matrix::operator[](const int index) const
{
    if (index < 0 || _rows * _cols <= index) // check bounds are legal
    {
        std::cerr << INDEX_ERROR << std::endl;
        exit(EXIT_FAILURE);
    }
    return _matrix[index];
}

/**
 * An operator, overloads the [] operator, enables setting a new value at index (by array shape of the matrix).
 * @param index
 * @return returns a ref to value at the index
 */
float& Matrix::operator[](int index)
{
    if (index < 0 || _rows * _cols <= index) // check bounds are legal
    {
        std::cerr << INDEX_ERROR << std::endl;
        exit(EXIT_FAILURE);
    }
    return _matrix[index];
}

/**
 * An operator, overloads the () operator, enables access to value at index (by matrix shape).
 * @param i - index of row.
 * @param j - index of column.
 * @return - value at index.
 */
float Matrix::operator()(const int i, const int j) const
{
    if ((i < 0 || j < 0) || (_rows <= i || _cols <= j)) // check bounds are legal
    {
        std::cerr << INDEX_ERROR << std::endl;
        exit(EXIT_FAILURE);
    }
    return _matrix[(i*_cols + j)];
}

/**
 * An operator, overloads the () operator, enables setting a new value at index (by matrix shape).
 * @param i - index of row.
 * @param j - index of column.
 * @return ref to value at index.
 */
float& Matrix::operator()(const int i, const int j)
{
    if ((i < 0 || j < 0) || (_rows <= i || _cols <= j)) // check bounds are legal
    {
        std::cerr << INDEX_ERROR << std::endl;
        exit(EXIT_FAILURE);
    }
    return _matrix[(i*_cols + j)];
}

/**
 * An operator, overloads the >> operator, enables inputting values to the matrix.
 * @param is - input stream.
 * @param matrix - matrix accepting info.
 * @return ref to is.
 */
std::istream& operator>>(std::istream& is, Matrix& matrix)
{
    if (is.peek() == EOF) //check if file is empty
    {
        std::cerr << EOF_ERROR << std::endl;
        exit(EXIT_FAILURE);
    }
    is.read((char*)matrix._matrix, (long int) matrix.getCols() * matrix.getRows() * sizeof(float)); //read stream
    if(!is.good()) //check for no errors
    {
        std::cerr << EOF_ERROR << std::endl;
        exit(EXIT_FAILURE);
    }
    if (is.peek() != EOF) //make sure EOF
    {
        std::cerr << EOF_ERROR << std::endl;
        exit(EXIT_FAILURE);
    }
    return is;
}

/**
 * An operator, overloads the << operator, enables printing values of the matrix.
 * @param os - output stream
 * @param matrix - matrix who's values are being outputted.
 * @return a ref to os
 */
std::ostream& operator<<(std::ostream& os, Matrix& matrix)
{
    for ( int i = 0; i < matrix._rows; i++)
    {
        for (int j = 0; j < matrix._cols; j++)
        {
            if (matrix(i , j) > 0.1f)
            {
                std::cout << "**";
            }
            else
            {
                std::cout << "  ";
            }
        }
        std::cout << std::endl;
    }
    return os;
}