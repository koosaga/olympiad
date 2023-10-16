#include <bits/stdc++.h>
using namespace std;
const int MAXN = 3005;

int n;
char buf[MAXN];
int win[MAXN];

int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		scanf("%s", buf);
		win[i] = count(buf, buf + n, 'W');
	}
	int ans = max_element(win + 1, win + n + 1) - win;
	printf("%d %d\n", (win[ans] != n - 1 ? 2 : 1), ans);
}
