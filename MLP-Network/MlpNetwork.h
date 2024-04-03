//MlpNetwork.h

#ifndef MLPNETWORK_H
#define MLPNETWORK_H

#include "Matrix.h"
#include "Digit.h"
#include "Activation.h"
#include "Dense.h"

#define MLP_SIZE 4

const MatrixDims imgDims = {28, 28};
const MatrixDims weightsDims[] = {{128, 784}, {64, 128}, {20, 64}, {10, 20}};
const MatrixDims biasDims[]    = {{128, 1}, {64, 1}, {20, 1},  {10, 1}};

/**
 * This class represents a neural network of 4 layer. It's class variable's are an arr of weights and an arr of biases.
 * @param _weights[MLP_SIZE] - arr of weights
 * @param _biasis[MLP_SIZE] - arr of biases
 */
class MlpNetwork
{
private:
    Matrix _weights[MLP_SIZE];
    Matrix _biasis[MLP_SIZE];

public:
    /**
     * The constructor of an instance of the class.
     * @param weights - arr of weights.
     * @param biasis - arr of biases.
     */
    MlpNetwork(Matrix weights[MLP_SIZE], Matrix biasis[MLP_SIZE]);

    /**
     * An operator, overloads the () operator, enabling activating the whole neural network on a col vec representing a
     * picture to be recognized by the network.
     * @param input - vec reps. img
     * @return Digit struct with value recognized by network and probability.
     */
    Digit operator()(Matrix& input);
};

#endif // MLPNETWORK_H
