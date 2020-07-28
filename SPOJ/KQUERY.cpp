// Ivan Carvalho
// Solution to https://www.spoj.com/problems/KQUERY/
#include <cstdio>
#include <algorithm>
#include <deque>
#define MP make_pair
#define LSOne(S) (S&(-S))
#define MAXN 200010
using namespace std;
typedef pair<int,int> i2;
typedef pair<int,i2> i3;
typedef pair<int,i3> i4;
i4 queries[MAXN];
int bit[MAXN],n,q,resposta[MAXN];
void update(int pos){
	while(pos <= n){
		bit[pos]++;
		pos += LSOne(pos);
	}
}
int sum(int pos){
	int answer = 0;
	while(pos > 0){
		answer += bit[pos];
		pos -= LSOne(pos);
	}
	return answer;
}
int main(){
	deque<i2> insertions;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		int davez;
		scanf("%d",&davez);
		insertions.push_back(MP(-davez,i));
	}
	scanf("%d",&q);
	for(int i=1;i<=q;i++){
		int x,y,z;
		scanf("%d %d %d",&x,&y,&z);
		queries[i] = MP(-z,MP(i,MP(x,y)));
	}
	sort(queries+1,queries+q+1);
	sort(insertions.begin(),insertions.end());
	for(int i=1;i<=q;i++){
		i4 davez = queries[i];
		int val = -davez.first, idx = davez.second.first, left = davez.second.second.first, right = davez.second.second.second;
		//printf("Val %d Idx %d Left %d Right %d\n",val,idx,left,right);
		while(!insertions.empty() && val < -insertions.front().first){
			//printf("Insert %d Pos %d\n",insertions.front().first,insertions.front().second);
			update(insertions.front().second);
			insertions.pop_front();
		}
		resposta[idx] = sum(right) - sum(left-1);
	}
	for(int i=1;i<=q;i++) printf("%d\n",resposta[i]);
	return 0;
} 
