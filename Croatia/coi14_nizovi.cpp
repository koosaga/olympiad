#include "header.h"

void norm(int s, int m, int e){
	if(s == m || m == e) return;
	reverse(s, e-1);
	reverse(s, s + (e - m) - 1);
	reverse(s + (e-m), e-1);
}

void sort() {
	int A = A_size();
	int B = B_size();
	int pnt = A+1;
	for(int i=1; i<=A; i++){
		int s = pnt-1, e = A+B;
		while(s != e){
			int m = (s+e+1)/2;
			if(cmp(pnt - (A - i + 1), m) == 1) s = m;
			else e = m-1;
		}
		s++;
		norm(pnt - (A - i + 1), pnt, s);
		pnt = s;
	}
}
