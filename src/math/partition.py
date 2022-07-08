import sys
import functools

# compute partitions of a given number n
# PE #76 (counting summations)
@functools.lru_cache(maxsize=None)
def partition(n):
	if n < 0:
		return 0
	if n == 0 or n == 1:
		return 1
	nsum = 0
	i = 1
	j = 1
	cneg = 1
	while n-cneg >= 0:
		mp = (-1)**(i+1)
		nsum += mp*partition(n-cneg)
		nsum += mp*partition(n-cneg-i)
		j += 2
		cneg += (i+j)
		i += 1

	return nsum

# compute partitions of a given number n, mod k
# PE #78 (coin partitions)
@functools.lru_cache(maxsize=None)
def partition_mod_k(n,k):
	if n < 0:
		return 0
	if n == 0 or n == 1:
		return 1
	nsum = 0
	i = 1
	j = 1
	cneg = 1
	while n-cneg >= 0:
		mp = (-1)**(i+1)
		nsum += mp*partition(n-cneg)
		nsum %= k
		nsum += mp*partition(n-cneg-i)
		nsum %= k
		j += 2
		cneg += (i+j)
		i += 1

	return nsum % k

# Just a usage example, used to solve PE #78
if __name__ == "__main__":
	for i in range(1,100000):
		if partition_mod_k(i, 1000000) == 0:
			print(i)
			break
		if (i%100 == 0):
			print(".", end="", flush=True)
		if (i%1000 == 0):
			print("")
