from __future__ import annotations
from copy import deepcopy
from typing import Tuple, Callable
import numpy as np
from IMLearn import BaseEstimator


def cross_validate(estimator: BaseEstimator, X: np.ndarray, y: np.ndarray,
                   scoring: Callable[[np.ndarray, np.ndarray, ...], float], cv: int = 5) -> Tuple[float, float]:
    """
    Evaluate metric by cross-validation for given estimator

    Parameters
    ----------
    estimator: BaseEstimator
        Initialized estimator to use for fitting the data

    X: ndarray of shape (n_samples, n_features)
       Input data to fit

    y: ndarray of shape (n_samples, )
       Responses of input data to fit to

    scoring: Callable[[np.ndarray, np.ndarray, ...], float]
        Callable to use for evaluating the performance of the cross-validated model.
        When called, the scoring function receives the true- and predicted values for each sample
        and potentially additional arguments. The function returns the score for given input.

    cv: int
        Specify the number of folds.

    Returns
    -------
    train_score: float
        Average train score over folds

    validation_score: float
        Average validation score over folds
    """
    k_samples = np.array_split(X, cv)
    k_labels = np.array_split(y, cv)
    train_score_list = []
    valid_score_list = []
    for i in range(cv):
        k_minus_i_samples = np.concatenate(k_samples[:i] + k_samples[i+1:])
        k_minus_i_labels = np.concatenate(k_labels[:i] + k_labels[i+1:])
        h_i = estimator.fit(k_minus_i_samples, k_minus_i_labels)
        validation_pred = h_i.predict(k_samples[i])
        training_pred = h_i.predict(k_minus_i_samples)
        validation_score = scoring(validation_pred, k_labels[i])
        training_score = scoring(training_pred, k_minus_i_labels)
        train_score_list.append(training_score)
        valid_score_list.append(validation_score)
    train_err_mean = np.array(train_score_list).mean()
    valid_err_mean = np.array(valid_score_list).mean()
    return train_err_mean, valid_err_mean



