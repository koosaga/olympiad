#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

using llf = long double;
using punk = complex<llf>;

struct line{
	lint a, b, c;
};

punk cross(line a, line b){
	long double det = a.a * b.b - b.a * a.b;
	auto ans = make_pair((a.c * b.b - a.b * b.c) / det, (a.a * b.c - a.c * b.a) / det);
	return punk(ans.first, ans.second);
}

int main(){
	int tc; scanf("%d",&tc);
	while(tc--){
		line v[3];
		scanf("%*d");
		for(int i=0; i<3; i++){
			scanf("%lld %lld %lld",&v[i].a,&v[i].b,&v[i].c);
			v[i].c *= -1;
		}
		punk a = cross(v[0], v[1]);
		punk b = cross(v[2], v[1]);
		punk c = cross(v[0], v[2]);
		llf area = abs(imag(conj(b - a) * (c - a)));
		llf dis = abs(a - b) + abs(b - c) + abs(c - a);
		if(dis < 1e-8L) puts("0");
		else printf("%.20Lf\n", area / dis);
	}
}
