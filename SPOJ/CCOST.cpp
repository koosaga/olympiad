// Ivan Carvalho
// Solution to https://www.spoj.com/problems/CCOST/
#include <bits/stdc++.h>
#define MP make_pair
#define LSOne(S) (S & (-S))
#define gc getchar_unlocked
inline void getint(int &x){
    register int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}
inline void print(int n)
{
	if (n == 0)
	{
		putchar_unlocked('0');
		putchar_unlocked('\n');
	}
	else
	{
		char buf[11];
		buf[10] = '\n';
		int i = 9;
		while (n)
		{
			buf[i--] = n % 10 + '0';
			n /= 10;
		}
		while (buf[i] != '\n')
			putchar_unlocked(buf[++i]);
	}
}
using namespace std;
typedef pair<int,int> i2;typedef pair<int,i2> i3;typedef pair<int,i3> i4;
const int MAXN = 1*1e5 + 10;
vector<int> compressao;
vector<i4> sweep;
vector<i3> pontos;
int bit[MAXN],subtrai[MAXN],adiciona[MAXN],n,m;
inline void update(int idx,int delta){
	while(idx < MAXN){
		bit[idx]+=delta;
		idx += LSOne(idx);
	}
}
inline int read(int idx){
	int ans = 0;
	while(idx > 0){
		ans += bit[idx];
		idx -= LSOne(idx);
	}
	return ans;
}
inline int query(int a,int b){
	return read(b) - read(a-1);
}
int main(){
	int TC;
	getint(TC);
	while(TC--){
		memset(bit,0,sizeof(bit));
		sweep.clear();
		pontos.clear();
		compressao.clear();
		getint(n);
		for(int i=1;i<=n;i++){
			int x,y,z;
			getint(x);getint(y);getint(z);
			pontos.push_back(MP(x,MP(y,z)));
			compressao.push_back(y);
		}
		sort(compressao.begin(),compressao.end());
		sort(pontos.begin(),pontos.end());
		compressao.erase(unique(compressao.begin(),compressao.end()),compressao.end());
		getint(m);
		for(int i=1;i<=m;i++){
			int x1,y1,x2,y2;
			getint(x1);getint(y1);getint(x2);getint(y2);
			sweep.push_back(MP(x1-1,MP(-i,MP(y1,y2))));
			sweep.push_back(MP(x2,MP(i,MP(y1,y2))));
		}
		sort(sweep.begin(),sweep.end());
		int ptr = 0;
		for(int i =0;i<sweep.size();i++){
			int x = sweep[i].first;
			while(ptr < n && pontos[ptr].first <= x){
				int y = lower_bound(compressao.begin(),compressao.end(),pontos[ptr].second.first) - compressao.begin() + 1;
				update(y,pontos[ptr].second.second);
				ptr++;
			}
			int idx = sweep[i].second.first;
			int l = sweep[i].second.second.first;
			int r = sweep[i].second.second.second;
			int ans;
			if(r < compressao[0] || l > compressao.back()){
				ans = 0;
			}
			else{
				l = lower_bound(compressao.begin(),compressao.end(),l) - compressao.begin() + 1;
				r = prev(upper_bound(compressao.begin(),compressao.end(),r)) - compressao.begin() + 1;
				ans = query(l,r);
			}
			if(idx < 0) subtrai[-idx] = ans;
			else adiciona[idx] = ans;
		}
		for(int i=1;i<=m;i++) print(adiciona[i] - subtrai[i]);
	}
	return 0;
} 