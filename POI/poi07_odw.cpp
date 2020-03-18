#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 100005;

int n, m, a[MAXN], b[MAXN];

int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<n; i++) scanf("%d",&a[i]);
	for(int i=0; i<m; i++) scanf("%d",&b[i]);
	sort(b, b + m);
	for(int i=0; i<n; i++) a[i] /= b[0];
	vector<int> sack;
	for(int i=0; i<m; ){
		int e = i; while(e < m && b[i] == b[e]) e++;
		int nxt = b[e] / b[i];
		if(e == m) nxt = 2e9;
		for(int j=i; j<e; j++){
			sack.push_back(1);
		}
		sort(all(sack));
		for(int j=0; j<n; j++){
			int dx = a[j] % nxt;
			a[j] /= nxt;
			while(dx && sz(sack)){
				dx--;
				sack.pop_back();
			}
		}
		vector<int> new_sack;
		while(sz(sack)){
			int tmp = 0;
			for(int j=0; j<nxt; j++){
				if(!sz(sack)) break;
				tmp += sack.back();
				sack.pop_back();
			}
			new_sack.push_back(tmp);
		}
		sack = new_sack;
		i = e;
	}
	cout << m - accumulate(all(sack), 0) << endl;
}
