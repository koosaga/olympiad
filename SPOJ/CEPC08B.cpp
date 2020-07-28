// Ivan Carvalho
// Solution to https://www.spoj.com/problems/CEPC08B/
#include <cstdio>
#include <algorithm>
#define gc getchar_unlocked
void getint(int &x){
    register int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}
inline void print(int n){
	if (n == 0)
	{
		putchar_unlocked('0');
		putchar_unlocked('\n');
	}
	else if (n == -1)
	{
		putchar_unlocked('-');
		putchar_unlocked('1');
		putchar_unlocked('\n');
	}
	else
	{
		char buf[11];
		buf[10] = ' ';
		int i = 9;
		while (n)
		{
			buf[i--] = n % 10 + '0';
			n /= 10;
		}
		while (buf[i] != ' ')
			putchar_unlocked(buf[++i]);
	}
}
using namespace std;
typedef pair<int,int> ii;
const int MAXN = 1e6 + 10;
ii predios[MAXN];
int estado[MAXN],ptr,resp,n,q;
int main(){
	int TC;
	scanf("%d",&TC);
	while(TC--){
		getint(n);
		getint(q);
		for(int i=1;i<=n;i++){
			int x;
			getint(x);
			estado[i] = 1;
			predios[i] = ii(x,i);
		}
		estado[0] = 0;
		estado[n+1] = 0;
		sort(predios+1,predios+n+1);
		resp = 1;
		ptr = 1;
		while(q--){
			int t;
			getint(t);
			while(ptr <= n && predios[ptr].first <= t){
				int pos = predios[ptr].second;
				if(estado[pos-1] == 0 && estado[pos+1] == 0){
					resp--;
				}
				else if(estado[pos-1] == 1 && estado[pos + 1] == 1){
					resp++;
				}
				estado[pos] = 0;
				ptr++;
			}
			print(resp);
		}
		printf("\n");
	}
	return 0;
}