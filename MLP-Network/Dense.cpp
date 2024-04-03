//
// Created by baruc on 18/06/2020.
//
#include "Dense.h"

/**
 * The constructor of the class.
 * @param w - weights of layer.
 * @param b - bias of layer.
 * @param actType - activation type of layer.
 */
Dense::Dense(const Matrix& w, const Matrix& b, ActivationType actType): _w(w), _b(b), _actType(actType){}

/**
 * a getter for the weights of the layer.
 * @return the weights of the layer.
 */
const Matrix& Dense::getWeights()const
{
    return _w;
}

/**
 * a getter for the bias of the layer.
 * @return the bias of the layer.
 */
const Matrix& Dense::getBias()const
{
    return _b;
}

/**
 * a getter for the activation type of the layer.
 * @return the activation type of the layer.
 */
Activation Dense::getActivation()const
{
    Activation active = Activation(_actType);
    return active;
}

/**
 * An operator, overloads the () operator, enabling using the activation func on vector of layer.
 * @param input - a matrix to be activated.
 * @return a new instance of a matrix, product of activation of input.
 */
Matrix Dense::operator()(Matrix& input)
{
    Matrix weights = _w;
    Matrix bias = _b;
    Activation active = getActivation();
    // a product of the multiplication of the weights and input of prev layer, summed with the bias
    Matrix toActivate = (weights*input) + bias;
    // the output of the input after the activation func was applied.
    Matrix output = active(toActivate);
    return output;
}