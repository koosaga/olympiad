#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 30005;

int n, w, a[MAXN];

int trial(int v){
	for(int i=0; i<v; i++){
		if(a[i] + a[2 * v - i - 1] > w){
			return false;
		}
	}
	return true;
}

int main(){
	scanf("%d %d",&w,&n);
	for(int i=0; i<n; i++) scanf("%d",&a[i]);
	sort(a, a+n);
	int s = 0, e = n/2;
	while(s != e){
		int m = (s+e+1)/2;
		if(trial(m)) s = m;
		else e = m-1;
	}
	cout << n - s << endl;
}
