//
// Created by baruc on 18/06/2020.
//
#include "Activation.h"

/**
 * A constructor for an instance of an ActivationType.
 * @param actType - an enum of the activation type of this instance.
 */
Activation::Activation(ActivationType actType) : _type(actType){}

/**
 * A static class method. This method is an implementation of the relu func.
 * @param input - a matrix who's values are accepted into the relu func.
 * @param output - a matrix after the use of the relu func.
 */
void Activation::_relu(Matrix& input, Matrix& output)
{
    for (int i = 0; i < output.getCols()*output.getRows(); i++)
    {
        if (input[i] >= 0)
        {
            output[i] = input[i];
        }
    }
}

/**
 * A static class method. This method is an implementation of the Softmax func.
 * @param input - a matrix who's values are accepted into the Softmax func.
 * @param output - a matrix after the use of the Softmax func.
 */
void Activation::_softmax(Matrix& input, Matrix& output)
{
    float sum = 0;
    for (int i = 0; i < output.getCols()*output.getRows(); i++)
    {
        sum += std::exp(input[i]);
    }
    for (int i = 0; i < output.getCols()*output.getRows(); i++)
    {
        output[i] = (1 / sum) * std::exp(input[i]);
    }
}

/**
 * A getter for this classes activation type.
 * @return An enum of ActivationType.
 */
ActivationType Activation::getActivationType(){return _type; }

/**
 * An operator, overloads the () operator, enabling use of the activation types on vecs.
 * @param input - a vector we wan't to inupt into one of the cativation types.
 * @return An instance of a matrix, that the activation type was used on.
 */
Matrix Activation::operator()(Matrix& input)
{
    Matrix output = Matrix(input.getRows(), input.getCols());
    if (_type == Relu)
    {
        _relu(input, output);
    }
    else
    {
        _softmax(input, output);
    }
    return output;
}