from IMLearn.learners import UnivariateGaussian, MultivariateGaussian
import numpy as np
import plotly.graph_objects as go
import plotly.io as pio
import plotly.express as px
pio.templates.default = "simple_white"


def test_univariate_gaussian():
    # Question 1 - Draw samples and print fitted model
    batch = np.random.normal(10, 1, (1000, ))
    gaussian_estimator = UnivariateGaussian()
    gaussian_estimator.fit(batch)
    print((gaussian_estimator.mu_, gaussian_estimator.var_))


    # Question 2 - Empirically showing sample mean is consistent
    X = np.linspace(0, 1000, 100)
    mean_samples = []
    for i in range(1, 101):
        gaussian_estimator.fit(batch[:i*10])
        mean_samples.append(gaussian_estimator.mu_)
    Y = abs(np.array(mean_samples) - 10)
    go.Figure([go.Scatter(x=X, y=Y, mode='lines', name=r'$text{Distance}$')],
          layout=go.Layout(title=r"$\text{Absolute Distance between Expectation and Mean of Sample per Sample Size}$",
                           xaxis_title=r"$\text{Sample Size}$",
                           yaxis_title=r"$\text{Distance between Expectation and Mean}$",
                           height=500)).show()


    # Question 3 - Plotting Empirical PDF of fitted model
    Y_pdf = gaussian_estimator.pdf(batch)
    go.Figure([go.Scatter(x=batch, y=Y_pdf, mode='markers', name=r'$text{Gaussian PDF}$')],
              layout=go.Layout(title=r"$\text{Gaussian Pdf per Sample Drawn}$",
                               xaxis_title=r"$\text{Samples}$",
                               yaxis_title=r"$\text{PDF}$",
                               height=500)).show()



def test_multivariate_gaussian():
    # Question 4 - Draw samples and print fitted model
    cov = np.array([[1, 0.2, 0, 0.5], [0.2, 2, 0, 0], [0, 0, 1, 0], [0.5, 0, 0, 1]])
    batch = np.random.multivariate_normal(np.array([0, 0, 4, 0]), cov, (1000, ))
    multi_variate_gaussian_estimator = MultivariateGaussian()
    multi_variate_gaussian_estimator.fit(batch)
    print(multi_variate_gaussian_estimator.mu_)
    print(multi_variate_gaussian_estimator.cov_)

    # Question 5 - Likelihood evaluation
    f1 = np.linspace(-10, 10, 200)
    f3 = np.linspace(-10, 10, 200)
    likelihood_samples = []
    for i in f1:
        f3_likelihood_samples = []
        for j in f3:
            mu = np.array([i, 0, j, 0])
            likelihood = MultivariateGaussian.log_likelihood(mu, cov, batch)
            f3_likelihood_samples.append(likelihood)
        likelihood_samples.append(f3_likelihood_samples)
    likelihood_matrix = np.array(likelihood_samples)
    fig = px.imshow(likelihood_matrix,
                labels=dict(x="f1", y="f3", color="Log Likelihood"),
                x=f1,
                y=f3)
    fig.show()

    # Question 6 - Maximum likelihood
    max_val = np.max(likelihood_matrix)
    max_index = np.unravel_index(np.argmax(likelihood_matrix), likelihood_matrix.shape)
    print(max_val.round(4), f1[max_index[0]].round(4), f3[max_index[1]].round(4))


if __name__ == '__main__':
    np.random.seed(0)
    test_univariate_gaussian()
    test_multivariate_gaussian()