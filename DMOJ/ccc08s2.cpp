// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ccc08s2
#include <cstdio>
#include <cstdlib>
#include <cmath>
using namespace std;
int main(){
	int r;
	while(scanf("%d",&r) && r){
		int resp = 0;
		for(int x = -r;x <= r;x++){
			int delta = abs(x);
			double resta = sqrt( r*r - delta*delta);
			int y1 = (int)ceil(-resta);
			int y2  = (int)floor(resta);
			resp += y2 - y1 + 1;
		}
		printf("%d\n",resp);
	}
	return 0;
}