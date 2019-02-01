#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2005;
using pi = pair<int, int>;

int n, m, dw, dr;
int hajimara[MAXN];
int a[MAXN], b[MAXN];
vector<int> wseq[MAXN];

int main(){
	cin >> n >> m >> dw >> dr;
	for(int i=1; i<=n; i++){
		cin >> a[i];
		a[i] /= dw;
	}
	for(int i=1; i<=m; i++) cin >> b[i];
	for(int i=1; i<=m; i++){
		cin >> b[i];
		vector<int> v;
		for(int j=1; j<=n; j++){
			if(i > hajimara[j] && a[j]){
				v.push_back(j);
			}
		}
		sort(v.begin(), v.end(), [&](const int &p, const int &q){
			return a[p] > a[q];
		});
		if(v.size() < b[i]){
			puts("-1");
			return 0;
		}
		v.resize(b[i]);
		for(auto &j : v){
			hajimara[j] = i + dw + dr - 1;
			for(int j=i; j<i+dw; j++){
				b[j]--;
				if(b[j] < 0){
					puts("-1");
					return 0;
				}
			}
			a[j]--;
			wseq[j].push_back(i);
		}
	}
	for(int i=1; i<=n; i++){
		if(a[i]){
			puts("-1");
			return 0;
		}
	}
	puts("1");
	for(int i=1; i<=n; i++){
		for(auto &j : wseq[i]) printf("%d ", j);
		puts("");
	}
}
