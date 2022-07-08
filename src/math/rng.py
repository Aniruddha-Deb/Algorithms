# random.py
# implementing various random number generators from scratch

from abc import ABC, abstractmethod
from time import time
import matplotlib.pyplot as plt

class RNG(ABC):

    def __init__(self, seed):
        self.seed = seed

    # Generates a random number according to the distribution specified. It's 
    # generally an integer between 0 and the class's RAND_MAX 
    @abstractmethod
    def generate(self):
        pass

#
# Linear congruential generator
# the simplest RNG, the state transition of a LCG is given by 
# X_n+1 = (aX_n + c) mod m
#
# choices for a, c and m:
# 1. m and c are coprime
# 2. If q is a prime number that divides m, then q divides a-1
# 3. If 4 divides m, then 4 divides a-1 
#
# some precomputed choices:
# - For m a power 2, m=2^b, and c≠0, Longest possible period P=m=2^b is achieved 
#   if c is relative prime to m and a=1+4k, where k is an integer
# - For m a power 2, m=2b, and c=0, Longest possible period P=m/4=2^{b-2} is achieved
#   if the seed X0 is odd and a=3+8k or a=5+8k, for k=0,1,...
# - For m a prime and c=0, Longest possible period P=m-1 is achieved if the 
#   multiplier a has property that smallest integer k such that a*k-1 is 
#   divisible by m is k = m-1
#
class LCG(RNG):

    def __init__(self, seed):
        super().__init__(seed)
        self.RAND_MAX = (2**31 - 1)
        self.m = 2**31
        self.c = 17
        self.a = 25214903917 # picked from java's RNG 
        self.xn = seed

    def generate(self):
        n = (self.xn*self.a+self.c)%self.m
        self.xn = n
        return n

if __name__ == "__main__":
    # testing
    lcg = LCG(int(time()))
    nums = []
    for i in range(10000):
        nums.append(lcg.generate()/lcg.RAND_MAX)

    # should be uniform
    plt.hist(nums, bins=50)
    plt.show()