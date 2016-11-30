#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int n, cnt[4];
char str[10005];

int main(){
	cin >> n >> str;
	for(int i=0; i<n; i++){
		if(str[i] == 'A') cnt[0]++;
		if(str[i] == 'C') cnt[1]++;
		if(str[i] == 'G') cnt[2]++;
		if(str[i] == 'T') cnt[3]++;
	}
	int w = min_element(cnt, cnt+4) - cnt;
	printf("%d\n", cnt[w]);
	for(int i=0; i<n; i++){
		if(w == 0) putchar('A');
		if(w == 1) putchar('C');
		if(w == 2) putchar('G');
		if(w == 3) putchar('T');
	}
}