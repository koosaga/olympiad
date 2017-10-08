#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, int> pi;
const int mod = 1e9 + 7;

double t[30005];
int main(){
	double x, p;
	cin >> x >> p;
	x *= 0.01;
	p *= 0.01;
	p = (1 - p) / p;
	for(int i=-25000; i<=5000; i++) t[i + 25000] = pow(p, i);
	double ret = 0;
	for(int w=0; w<=4000; w++){
		for(int l=-25000; l<=0; l++){
			if(w == l) continue;
			double winProf = w * (1 - t[l + 25000]) / (t[w + 25000] - t[l + 25000]);
			double loseProf = l * (1 - x) * (t[w + 25000] - 1) / (t[w + 25000] - t[l + 25000]);
			ret = max(ret, winProf + loseProf);
		}
	}
	printf("%.10f", ret);
}
