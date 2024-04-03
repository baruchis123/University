//Activation.h
#ifndef ACTIVATION_H
#define ACTIVATION_H

#include <cmath>

#include "Matrix.h"

/**
 * @enum ActivationType
 * @brief Indicator of activation function.
 */
enum ActivationType
{
    Relu,
    Softmax
};

/**
 * A class with one class variable.
 * @param type - the activation type of the class instance.
 */
class Activation
{
private:
    ActivationType _type;

    /**
     * A static class method. This method is an implementation of the relu func.
     * @param input - a matrix who's values are accepted into the relu func.
     * @param output - a matrix after the use of the relu func.
     */
    static void _relu(Matrix& input, Matrix& output);

    /**
     * A static class method. This method is an implementation of the Softmax func.
     * @param input - a matrix who's values are accepted into the Softmax func.
     * @param output - a matrix after the use of the Softmax func.
     */
    static void _softmax(Matrix& input, Matrix& output);

public:
    /**
     * A constructor for an instance of an ActivationType.
     * @param actType - an enum of the activation type of this instance.
     */
    explicit Activation(ActivationType actType);

    /**
     * A getter for this classes activation type.
     * @return An enum of ActivationType.
     */
    ActivationType getActivationType();

    /**
     * An operator, overloads the () operator, enabling use of the activation types on vecs.
     * @param input - a vector we wan't to inupt into one of the cativation types.
     * @return An instance of a matrix, that the activation type was used on.
     */
    Matrix operator()(Matrix& input);
};

#endif //ACTIVATION_H
