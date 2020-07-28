// Ivan Carvalho
// Solution to https://www.spoj.com/problems/UPDATEIT/
#include <cstdio>
#include <cstring>
#define LSOne(S) (S&(-S))
#define MAXN 11000
int bit[MAXN];
void update(int pos, int val){
	while(pos<MAXN){
		bit[pos]+=val;
		pos += LSOne(pos);
	}
}
int sum(int pos){
	int result = 0;
	while(pos>0){
		result += bit[pos];
		pos -= LSOne(pos);
	}
	return result;
}
int main(){
	int t,n,u,q;
	scanf("%d",&t);
	while(t--){
		memset(bit,0,sizeof(bit));
		scanf("%d %d",&n,&u);
		for(int i=0;i<u;i++){
			int l,r,val;
			scanf("%d %d %d",&l,&r,&val);
			l++;
			r++;
			update(l,val);
			update(r+1,-val);
		}
		scanf("%d",&q);
		while(q--){
			int index;
			scanf("%d",&index);
			printf("%d\n",sum(index+1));
		}
	}
	return 0;
}