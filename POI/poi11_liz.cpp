#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int mod = 1e9 + 7;
const int MAXN = 1000005;

int n, m;
char str[MAXN];
int st[2*MAXN], ed[2*MAXN];

int main(){
	scanf("%d %d %s",&n,&m,str);
	int p = find(str, str + n, 'W') - str;
	if(p == n){
		while(m--){
			int q;
			scanf("%d",&q);
			if(q%2 == 0) printf("%d %d\n", 1, q/2);
			else puts("NIE");
		}
		return 0;
	}
	st[1] = p, ed[1] = p;
	int cnt = 1;
	int lastEven = -987654320, lastOdd = 1;
	for(int i=p+1; i<n; i++){
		cnt += (str[i] == 'W' ? 1 : 2);
		st[cnt] = p, ed[cnt] = i;
		if(str[i] == 'T'){
			st[cnt-1] = p+1;
			ed[cnt-1] = i;
		}
		if(cnt % 2 == 0) lastEven = cnt;
		else lastOdd = cnt;
	}
	while(m--){
		int q;
		scanf("%d",&q);
		if(q <= cnt) printf("%d %d\n", st[q] + 1, ed[q] + 1);
		else{
			if(q % 2 == 0 && (q - lastEven) / 2 <= p){
				printf("%d %d\n", p - (q - lastEven) / 2 + 1, ed[lastEven] + 1); 
			}
			else if(q % 2 == 1 && (q - lastOdd) / 2 <= p){
				printf("%d %d\n", p - (q - lastOdd) / 2 + 1, ed[lastOdd] + 1); 
			}
			else puts("NIE");
		}
	}
}
