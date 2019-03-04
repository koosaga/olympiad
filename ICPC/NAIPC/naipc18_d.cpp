#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200005;
const int mod = 1e9 + 7;
using lint = long long;

int n, m;
int a[MAXN], b[MAXN];

int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<m; i++){
		scanf("%d",&a[i]);
		b[a[i]] = 1;
	}
	int ptr = 1;
	for(int i=0; i<m; i++){
		while(ptr < a[i]){
			if(!b[ptr]) printf("%d\n", ptr);
			ptr++;
		}
		printf("%d\n", a[i]);
	}
	while(ptr <= n){
		if(!b[ptr]) printf("%d\n", ptr);
		ptr++;
	}
}
