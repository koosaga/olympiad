#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
using lint = long long;
using real_t = long double;
using pi = pair<int, int>;

struct ptr{
	int a, b, g, idx;
}a[MAXN];

int n;
real_t A, B;
real_t ret[MAXN];

int main(){
	cin >> n >> A >> B;
	real_t unhappy = 0;
	for(int i=0; i<n; i++){
		scanf("%d %d %d",&a[i].g,&a[i].a,&a[i].b);
		unhappy += 1.0 * a[i].g * a[i].b;
		ret[i] = a[i].g;
		a[i].idx = i;
	}
	unhappy = max(unhappy - B, 0.0L);
	vector<ptr> v;
	for(int i=0; i<n; i++){
		if(a[i].a + a[i].b) v.push_back(a[i]);
	}
	sort(v.begin(), v.end(), [&](const ptr &a, const ptr &b){
		return a.a * b.b < b.a * a.b;
	});
	for(auto &i : v){
		if(i.b == 0){
			continue;
		}
		real_t delta = min(1.0L * i.g, unhappy / i.b);
		ret[i.idx] -= delta;
		unhappy -= i.b * delta;
	}
	real_t ansA = 0, ansB = 0;
	for(int i=0; i<n; i++){
		ansA += a[i].a * ret[i];
		ansB += a[i].b * ret[i];
	}
	if(ansA < A - 1e-10 || ansB > B + 1e-10){
		puts("-1 -1");
		return 0;
	}
	printf("%.10Lf %.10Lf\n", ansA, ansB); 
	for(int i=0; i<n; i++) printf("%.10Lf ", ret[i]);
}
