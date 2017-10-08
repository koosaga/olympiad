#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
const int mod = 1e9 + 7;
typedef pair<int, int> pi;

int w, n;
llf h, ans;

llf eval(llf r){
	llf ret = ans * r * r;
	ret += h * r * (1 - r) * (1 + h) / 2;
	ret += h * (1 - r) * (1 - h) / 2;
	ret += (1 - r) * (1 - r) * (h * h + 1) / 4;
	ret += h * h / 2;
	return ret;
}

vector<llf> v;

int main(){
	cin >> w >> h >> n;
	h /= w;
	ans = (h * h + 2 * h + 1) / 4;
	for(int i=1; i<=n; i++){
		llf s = 0, e = 1;
		for(int j=0; j<200; j++){
			llf m1 = eval((2 * s + e) / 3);
			llf m2 = eval((s + 2 * e) / 3);
			if(m1 < m2) e = (s + 2 * e) / 3;
			else s = (2 * s + e) / 3;
		}
		v.push_back(s);
		ans = eval(s);
	}
	ans *= w * w;
	printf("%.10Lf\n", ans);
	llf tmp = w;
	for(int i=v.size()-1; i>=0; i--){
		tmp *= v[i];
		v[i] = tmp;
	}
	for(int i=0; i<v.size() && i<10; i++){
		printf("%.10Lf\n", v[i]);
	}
}

