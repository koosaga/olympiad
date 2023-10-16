#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 200005;

int n, a[MAXN];

int main(){
	scanf("%d",&n);
	for(int i=0; i<n*(n-1)/2; i++) scanf("%d",&a[i]);
	sort(a, a + n*(n-1)/2);
	lint minv = 0;
	lint maxv = 0;
	for(int i=0; i<n-1; i++){
		minv += a[i];
		maxv += a[i*(i+1)/2];
	}
	cout << minv << " " << maxv << endl;
}
