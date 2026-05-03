#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
using pi = pair<lint, lint>;
const int MAXN = 100505;

int n;
double L[MAXN], T;
int a[MAXN], b[MAXN];

int main(){
	while(true){
		cin >> n;
		if(n == 0) break;
		cin >> T;
		for(int i=0; i<n; i++){
			int vw, pf, vf, th;
			scanf("%d %d %d %d",&vw,&pf,&vf,&th);
			L[i] = 1.0 * pf / vf;
			a[i] = vw;
			b[i] = th;
		}
		double ret = 0;
		vector<int> v, w;
		for(int i=0; i<n; i++){
			if(a[i] == 0){
				ret += max(0, b[i]) * L[i];
			}
			else if(b[i] == 0){
				if(a[i] < 0) T += -a[i] * L[i];
				continue;
			}
			else if(a[i] * b[i] <= 0){
				if(a[i] < 0){
					T -= a[i] * L[i];
					ret += b[i] * L[i];
				}
				continue;
			}
			else{
				if(a[i] < 0){
					ret += b[i] * L[i];
					T += -a[i] * L[i];
					a[i] *= -1;
					b[i] *= -1;
				}
				v.push_back(i);
			}
		}
		sort(v.begin(), v.end(), [&](const int &x, const int &y){
			return b[x] * a[y] > a[x] * b[y];
		});
		for(auto &i : v){
			double minX = min(L[i], T / a[i]);
			ret += b[i] * minX;
			T -= minX * a[i];
			L[i] -= minX;
		}
		printf("%.10f\n", ret);
	}
}
