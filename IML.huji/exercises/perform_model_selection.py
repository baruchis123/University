from __future__ import annotations
import numpy as np
import pandas as pd
from sklearn import datasets

import IMLearn.metrics
from IMLearn.metrics import mean_square_error
from IMLearn.utils import split_train_test
from IMLearn.model_selection import cross_validate
from IMLearn.learners.regressors import PolynomialFitting, LinearRegression, RidgeRegression
from sklearn.linear_model import Lasso, Ridge


from utils import *
import plotly.graph_objects as go
from plotly.subplots import make_subplots


def select_polynomial_degree(n_samples: int = 100, noise: float = 5):
    """
    Simulate data from a polynomial model and use cross-validation to select the best fitting degree

    Parameters
    ----------
    n_samples: int, default=100
        Number of samples to generate

    noise: float, default = 5
        Noise level to simulate in responses
    """
    # Question 1 - Generate dataset for model f(x)=(x+3)(x+2)(x+1)(x-1)(x-2) + eps for eps Gaussian noise
    # and split into training- and testing portions
    response = lambda x: (x+3)*(x+2)*(x+1)*(x-1)*(x-2)
    X = np.linspace(-1.2, 2, n_samples)
    y_ = response(X)
    y = y_ + np.random.normal(scale=noise, size=len(y_))
    train_x, train_y, test_x, test_y = split_train_test(pd.DataFrame(X), pd.Series(y), 2/3)
    train_x, train_y, test_x, test_y = train_x.to_numpy().flatten(), train_y.to_numpy().flatten(), test_x.to_numpy().flatten(), test_y.to_numpy().flatten()
    fig1 = go.Figure(data=[go.Scatter(x=X, y=y_, mode="markers", name="Real Points",  marker=dict(color="black", opacity=.7)),
        go.Scatter(x=train_x, y=train_y, mode="markers", name="Observed Training Points",  marker=dict(color="red", opacity=.7)),
        go.Scatter(x=test_x, y=test_y, mode="markers", name="Observed Test Points",  marker=dict(color="blue", opacity=.7))],
        layout=go.Layout(title_text=rf"$\text{{Scatter Plot Of True Values vs. Test & Train Values}}\mathcal{{N}}\ left(0,5\right)$",
                         xaxis={"title": r"$x$"},
                         yaxis={"title": r"$y$"}))
    # fig1.show()
    # Question 2 - Perform CV for polynomial fitting with degrees 0,1,...,10
    train_err = []
    validate_err = []
    for k in range(11):
        train_err_k, validate_err_k = cross_validate(PolynomialFitting(k), train_x, train_y, mean_square_error, 5)
        train_err.append(train_err_k)
        validate_err.append(validate_err_k)

    x_k = [k for k in range(11)]

    fig2 = go.Figure(data=[go.Scatter(x=x_k, y=train_err, mode="markers", name="Train Error per Polynomial Degree",  marker=dict(color="black", opacity=.7)),
                               go.Scatter(x=x_k, y=validate_err, mode="markers", name="Validation Error per Polynomial Degree",  marker=dict(color="red", opacity=.7))],
                         layout=go.Layout(title_text=rf"$\text{{5-Fold Validation Error per Polynomial Degree}}$",
                                          xaxis={"title": r"$Polynomial Degree$"},
                                          yaxis={"title": r"$Error$"}))
    # fig2.show()

    # Question 3 - Using best value of k, fit a k-degree polynomial model and report test error
    k_star = np.argmin(np.array(validate_err))
    print(f'The best validation error is {validate_err[k_star].round(2)} \n')
    model = PolynomialFitting(k_star).fit(train_x, train_y)
    print(f'The loss on the test set is {mean_square_error(test_y, model.predict(test_x)).round(2)} and the optimal polynomial degree is {k_star}')




def select_regularization_parameter(n_samples: int = 50, n_evaluations: int = 500):
    """
    Using sklearn's diabetes dataset use cross-validation to select the best fitting regularization parameter
    values for Ridge and Lasso regressions

    Parameters
    ----------
    n_samples: int, default=50
        Number of samples to generate

    n_evaluations: int, default = 500
        Number of regularization parameter values to evaluate for each of the algorithms
    """
    # Question 6 - Load diabetes dataset and split into training and testing portions
    X, y = datasets.load_diabetes(return_X_y=True, as_frame=True)
    train_X = X[:50]
    train_y = y[:50]
    test_X = X[51:]
    test_y = y[51:]
    train_X, train_y, test_X, test_y = train_X.to_numpy(), train_y.to_numpy(), test_X.to_numpy(), test_y.to_numpy()

    # Question 7 - Perform CV for different values of the regularization parameter for Ridge and Lasso regressions
    lambdas = np.linspace(0, 3)
    ridge_train_err = []
    ridge_val_err = []
    lasso_train_err = []
    lasso_val_err = []
    for lam in lambdas:
        ridge_train_lam_err, ridge_val_lam_err = cross_validate(RidgeRegression(lam), train_X, train_y, mean_square_error, 5)
        lasso_train_lam_err, lasso_val_lam_err = cross_validate(Lasso(alpha=lam), train_X, train_y, mean_square_error, 5)
        ridge_train_err.append(ridge_train_lam_err)
        ridge_val_err.append(ridge_val_lam_err)
        lasso_train_err.append(lasso_train_lam_err)
        lasso_val_err.append(lasso_val_lam_err)

    fig3 = go.Figure(data=[go.Scatter(x=lambdas, y=ridge_train_err, mode="markers+lines", name="Train Error per Lambda in Ridge",  marker=dict(color="black", opacity=.7)),
                           go.Scatter(x=lambdas, y=ridge_val_err, mode="markers+lines", name="Validation Error per Lambda in Ridge",  marker=dict(color="red", opacity=.7)),
                           go.Scatter(x=lambdas, y=lasso_train_err, mode="markers+lines", name="Train Error per Lambda in Lasso",  marker=dict(color="blue", opacity=.7)),
                           go.Scatter(x=lambdas, y=lasso_val_err, mode="markers+lines", name="Validation Error per Lambda in Lasso",  marker=dict(color="green", opacity=.7))],
                     layout=go.Layout(title_text=rf"$\text{{5-Fold Train and Validation Error per Regularization Lambda of Ridge and Lasso}}$",
                                      xaxis={"title": r"$Lambda$"},
                                      yaxis={"title": r"$Error$"}))
    # fig3.show()
    # Question 8 - Compare best Ridge model, best Lasso model and Least Squares model
    lambda_star_ridge = lambdas[np.argmin(np.array(ridge_val_err))]
    lambda_star_lasso = lambdas[np.argmin(np.array(lasso_val_err))]
    ridge_model = RidgeRegression(lambda_star_ridge).fit(train_X, train_y)
    lasso_model = Lasso(alpha=lambda_star_lasso).fit(train_X, train_y)
    least_squares_model = LinearRegression().fit(train_X, train_y)
    print(f'The loss on the test set for ridge is {mean_square_error(test_y, ridge_model.predict(test_X)).round(2)} and the optimal lambda is {lambda_star_ridge.round(2)}')
    print(f'The loss on the test set for lasso is {mean_square_error(test_y, lasso_model.predict(test_X)).round(2)} and the optimal lambda is {lambda_star_lasso.round(2)}')
    print(f'The loss on the test set for least squares is {mean_square_error(test_y, least_squares_model.predict(test_X)).round(2)}')

if __name__ == '__main__':
    np.random.seed(0)
    select_polynomial_degree()
    select_polynomial_degree(noise=0)
    select_polynomial_degree(1500, noise=10)
    select_regularization_parameter()
