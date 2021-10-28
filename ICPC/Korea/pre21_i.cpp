#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 100005;
const int MAXT = 1000005;

struct foo{
	int x, p, q, r;
	bool operator<(const foo &f)const{
		if(p*q*r != f.p*f.q*f.r) return p*q*r < f.p*f.q*f.r;
		if(p+q+r != f.p+f.q+f.r) return p+q+r < f.p+f.q+f.r;
		return x < f.x;
	}
};

int main(){
	int n; cin >> n;
	vector<foo> v(n);
	for(auto &i : v){
		cin >> i.x >> i.p >> i.q >> i.r;
	}
	sort(all(v));
	for(int i = 0; i < 3; i++) cout << v[i].x << " ";
}
