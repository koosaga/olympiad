#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 100005;

int n, m;
pair<int, string> a[MAXN];
string b[MAXN];
char buf[55];

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		scanf("%s %d",buf,&a[i].first);
		a[i].second = buf;
	}
	scanf("%d",&m);
	for(int i=0; i<m; i++){
		scanf("%s", buf);
		b[i] = buf;
	}
	sort(a, a + n);
	int ptr = 0;
	for(int i=0; ptr<m&&i<n; ){
		int e = i;
		while(e < n && a[i].first == a[e].first) e++;
		for(int j=i; j<e; j++){
			if(b[ptr] == a[j].second){
				ptr++;
				break;
			}
		}
		i = e;
	}
	puts(ptr == m ? "Yes" : "No");
}
