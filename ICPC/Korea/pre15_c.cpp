#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;

int n, l,  a[MAXN], ord[MAXN];

int main(){
	int tc;
	scanf("%d",&tc);
	while(tc--){
		scanf("%d %d",&n,&l);
		for(int i=0; i<n; i++) scanf("%d",&a[i]);
		for(int i=0; i<n; i++){
			int p; scanf("%d",&p);
			ord[p-1] = i;
		}
		int ptr1 = 0, ptr2 = 0, ans = 1;
		set<int> s;
		for(int i=0; i<n; i++){
			while(ptr2 < n && a[ptr2] <= a[i] + l){
				s.insert(ord[ptr2++]);
			}
			while(ptr1 < n && a[ptr1] < a[i] - l){
				s.erase(ord[ptr1++]);
			}
			if(s.size() != *s.rbegin() - *s.begin() + 1) ans = -1;
		}
		printf("%d\n", ans);
	}
}