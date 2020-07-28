// Ivan Carvalho
// Solution to https://dmoj.ca/problem/bts17p2
#include <bits/stdc++.h>
using namespace std;
int main(){
	double resp = 1.0;
	int n;
	scanf("%d",&n);
	while(n--){
		int e,g;
		scanf("%d %d",&e,&g);
		double fator = (g - e)/double(g);
		resp *= fator;
	}
	printf("%.6lf\n",resp);
	return 0;
}