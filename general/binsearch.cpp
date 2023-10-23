// binary search the answer
int l=0,h=S.size();
while (h > l) {
	int m = (l+h)/2;
	if (f(S[m])) h = m;
	else l = m+1;
}

// this gives h as the first element that is false, and l as the last element
// that is true. If h == l, then it can be used for finding a particular element
// in an array
