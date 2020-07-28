// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ioi07p4
#include <cstdio>
#include <cstring>
#include <map>
#include <algorithm>
#define MAXN 100010
#define MP make_pair
#define F first
#define S second
using namespace std;
typedef pair<char,char> cc;
typedef pair<cc,cc> c4;
map<c4,int> dp,temp;
char entrada[MAXN];
int N;
inline int pnt(cc A,char c){
	char a = A.first,b = A.second;
	if(a == 'N'){
		if(b == 'N'){
			return 1;
		}
		if(b == c){
			return 1;
		}
		else{
			return 2;
		}
	}
	if(a == b && a == c){
		return 1;
	}
	if(a != b && a != c && b != c){
		return 3;
	}
	return 2;
}
inline c4 pareia(char c1,char c2,char c3,char c4){
	cc par1 = MP(c1,c2);
	cc par2 = MP(c3,c4);
	if(par1 < par2) swap(par1,par2);
	return MP(par1,par2);
}
int main(){
	scanf("%d",&N);
	scanf("%s",entrada);
	dp[pareia('N','N','N','N')] = 0;
	for(int pos=0;pos<N;pos++){
		temp.clear();
		for(map<c4,int>::iterator it = dp.begin();it != dp.end();it++){
			c4 estado = (*it).first;
			int melhor = (*it).second;
			int ans1 = pnt(estado.F,entrada[pos]) + melhor;
			c4 par1 = pareia(estado.F.S,entrada[pos],estado.S.F,estado.S.S);
			int ans2 = pnt(estado.S,entrada[pos]) + melhor;
			c4 par2 = pareia(estado.F.F,estado.F.S,estado.S.S,entrada[pos]);
			temp[par1] = max(temp[par1],ans1);
			temp[par2] = max(temp[par2],ans2);
		}
		dp = temp;
	}
	int resp = 0;
	for(map<c4,int>::iterator it = dp.begin();it != dp.end();it++){
		int melhor = (*it).second;
		resp = max(resp,melhor);
	}
	printf("%d\n",resp);
	return 0;
}
