#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pi;
using lint = long long;

int main(){
	int q; scanf("%d",&q);
	while(q--){
		int l, d; scanf("%d %d",&l,&d);
		long double s = 0, e = acos(-1);
		long double r;
		for(int i=0; i<100; i++){
			long double theta = (s+e)/2;
			if(0.5 * l * theta > sin(theta / 2) * (l + d)) e = theta;
			else s = theta;
		}
		r = 0.5 * l / sin(s / 2);
		printf("%.0Lf\n",r - sqrt(r * r- 0.25 * l * l));
	}
}