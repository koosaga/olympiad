#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
#define HAS(msk, x) (((msk) >> (x)) & 1)
const int MAXN = 250005;

struct point{
	int x, y, idx;
}a[MAXN];

int n, chk[MAXN];

void Do(){
	sort(a, a + n, [&](const point &a, const point &b){
		return pi(a.x, a.y) < pi(b.x, b.y);
	});
	int minv = -2e9;
	for(int i=0; i<n; i++){
		if(minv <= a[i].y){
			chk[a[i].idx] = 1;
			minv = a[i].y;
		}
	}
}

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		int p, q; scanf("%d %d",&p,&q);
		a[i] = {p + q, p - q, i};
	}
	for(int i=0; i<4; i++){
		if(i & 2) for(int j=0; j<n; j++) a[j].x *= -1;
		if(i & 1) for(int j=0; j<n; j++) a[j].y *= -1;
		Do();
		if(i & 2) for(int j=0; j<n; j++) a[j].x *= -1;
		if(i & 1) for(int j=0; j<n; j++) a[j].y *= -1;
	}
	cout << count(chk, chk + n, 1) << endl;
}
