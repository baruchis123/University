//
// Created by baruc on 17/06/2020.
//

#ifndef EX4_DENSE_H
#define EX4_DENSE_H

#include "Matrix.h"
#include "Activation.h"

/**
 * A class that represents a layer of a neural network. The class has three class variables.
 * @param _w - the weights of the layer.
 * @param _b - the bias of the layer.
 * @param _actType - an instance of ActivationType representing the func activating the layer.
 */
class Dense
{

private:
    Matrix _w;
    Matrix _b;
    ActivationType _actType;

public:
    /**
     * The constructor of the class.
     * @param w - weights of layer.
     * @param b - bias of layer.
     * @param actType - activation type of layer.
     */
    Dense(const Matrix& w, const Matrix& b, ActivationType actType);

    /**
     * a getter for the weights of the layer.
     * @return the weights of the layer.
     */
    const Matrix& getWeights()const;

    /**
     * a getter for the bias of the layer.
     * @return the bias of the layer.
     */
    const Matrix& getBias()const;

    /**
     * a getter for the activation type of the layer.
     * @return the activation type of the layer.
     */
    Activation getActivation()const;

    /**
     * An operator, overloads the () operator, enabling using the activation func on vector of layer.
     * @param input - a matrix to be activated.
     * @return a new instance of a matrix, product of activation of input.
     */
    Matrix operator()(Matrix& input);
};
#endif //EX4_DENSE_H
