from rng import LCG
import random
from time import time
from math import sqrt, log, cos, pi, exp, factorial
import matplotlib.pyplot as plt

# generates a random value uniformly distrbuted between (0,1)
def gen_unif_val(rng):
    return rng.random()

# samples from a N(mean, var) distrib using the box-muller transform
def gen_norm_val(rng, mean, var):
    u = gen_unif_val(rng)
    v = gen_unif_val(rng)
    transform = sqrt(-2*log(u))*cos(2*pi*v)
    return transform*var + mean

def exp_dist(l):
    def f(x):
        if x < 0:
            return 0
        else:
            return l*exp(-l*x)
    return f

def norm_dist(mu, sigma):
    def f(x):
        return (exp(-((x-mu)**2)/(2*sigma**2)))/(sqrt(2*pi)*sigma)
    return f

def metropolis_hastings(rng, nsamples, tgt_distrib):
    prev = gen_unif_val(rng)
    samples = [prev]
    for i in range(nsamples-1):
        # TODO change the variance of the normal distribution used as the candidate
        # sampling distribution
        candidate = gen_norm_val(rng, prev, 25)
        accept_ratio = tgt_distrib(candidate)/tgt_distrib(prev)
        if accept_ratio > gen_unif_val(rng):
            prev = candidate
        samples.append(prev)
    return samples

if __name__ == "__main__":
    random.seed()
    plt.hist(metropolis_hastings(random, 50000, norm_dist(0, 1)), bins=50)
    plt.show()