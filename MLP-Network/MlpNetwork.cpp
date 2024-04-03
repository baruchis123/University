//
// Created by baruc on 18/06/2020.
//

#include "MlpNetwork.h"

/**
 * The constructor of an instance of the class.
 * @param weights - arr of weights.
 * @param biasis - arr of biases.
 */
MlpNetwork::MlpNetwork(Matrix weights[4], Matrix biasis[4])
{
    for (int i = 0; i < 4; i++)
    {
        _weights[i] = weights[i];
        _biasis[i] = biasis[i];
    }
}

/**
 * An operator, overloads the () operator, enabling activating the whole neural network on a col vec representing a
 * picture to be recognized by the network.
 * @param input - vec reps. img
 * @return Digit struct with value recognized by network and probability.
 */
Digit MlpNetwork::operator()(Matrix& input)
{
    Matrix result = input;
    for (int i = 0; i < 4; i++)
    {
        if (i != 3) // first three layers are activated by relu
        {
            Dense dense = Dense(_weights[i], _biasis[i], Relu);
            result = dense(result);
        }
        else // last layer activated by Softmax
        {
            Dense dense = Dense(_weights[i], _biasis[i], Softmax);
            result = dense(result);
        }
    }
    float max = 0;
    int index = 0;
    for (int i = 0; i < 10; i++) // find value with highest probability
    {
        if (result[i] > max)
        {
            max = result[i];
            index = i;
        }
    }
    Digit digit;
    digit.probability = result[index];
    digit.value = index;
    return digit;
}