#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
typedef vector<int> vi;
 
int n, m;
int cnt[1000005], col[1000005];
int rev[1000005], zeros;
 
int a[1000005];
 
int main(){
	scanf("%d %d",&n,&m);
	lint sum = 0;
	for(int i=1; i<=m; i++){
		scanf("%d",&cnt[i]);
		sum += cnt[i];
	}
	if(sum > n){
		puts("0");
		return 0;
	}
	for(int i=1; i<=m; i++){
		scanf("%d",&col[i]);
		rev[col[i]] = i;
	}
	for(int i=0; i<n; i++){
		scanf("%d",&a[i]);
	}
	zeros = 0;
	for(int i=0; i<sum; i++){
		if(cnt[rev[a[i]]] == 0) zeros--;
		cnt[rev[a[i]]]--;
		if(cnt[rev[a[i]]] == 0) zeros++;
	}
	int ret = (zeros == m);
	for(int i=sum; i<n; i++){
		if(cnt[rev[a[i]]] == 0) zeros--;
		cnt[rev[a[i]]]--;
		if(cnt[rev[a[i]]] == 0) zeros++;
		if(cnt[rev[a[i-sum]]] == 0) zeros--;
		cnt[rev[a[i-sum]]]++;
		if(cnt[rev[a[i-sum]]] == 0) zeros++;
		if(zeros == m) ret++;
	}
	cout << ret;
}