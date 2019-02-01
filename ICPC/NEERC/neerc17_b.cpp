#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using real_t = double;
const int MAXN = 22;

int w, h, a[3];

int main(){
	cin >> a[0] >> a[1] >> a[2];
	sort(a, a + 3);
	cin >> w >> h;
	if(w > h) swap(w, h);
	do{
		int p1 = a[0] + 2 * a[1];
		int p2 = 2 * a[1] + 2 * a[2];
		int p3 = 3 * a[0] + a[1] + a[2];
		int p4 = a[1] + a[2];
		if(p3 > p4) swap(p3, p4);
		if(p1 > p2) swap(p1, p2);
		if(p1 <= w && p2 <= h){
			puts("Yes");
			return 0;
		}
		if(p3 <= w && p4 <= h){
			puts("Yes");
			return 0;
		}
	}while(next_permutation(a, a + 3));
	puts("No");
}
