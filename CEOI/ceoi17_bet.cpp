#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 100005;

int n;
double a[MAXN], b[MAXN];

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++) scanf("%lf %lf",&a[i],&b[i]);
	sort(a, a+n);
	reverse(a, a+n);
	sort(b, b+n);
	reverse(b, b+n);
	int p1 = 0, p2 = 0;
	double ans = 0;
	double sum1 = 0, sum2 = 0;
	while(p1 < n || p2 < n){
		double bet1 = (p1 != n ? min(a[p1] + sum1, sum2) : -1e9);
		double bet2 = (p2 != n ? min(sum1, b[p2] + sum2) : -1e9);
		if(bet1 < bet2){
			sum2 += b[p2++];
			ans = max(ans, min(sum1, sum2) - p1 - p2);
		}
		else{
			sum1 += a[p1++];
			ans = max(ans, min(sum1, sum2) - p1 - p2);
		}
	}
	printf("%.4f\n", ans);
}
