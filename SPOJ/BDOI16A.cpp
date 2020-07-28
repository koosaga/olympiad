// Ivan Carvalho
// Solution to https://www.spoj.com/problems/BDOI16A/
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200010;
const int BUCKET = 449;
deque<int> baldes[BUCKET+10];
map<int,int> ida,volta;
int qualbalde[MAXN];
int get_id(int val){
	if(ida.count(val)) return ida[val];
	int tam = ida.size();
	ida[val] = tam + 1;
	volta[ida[val]] = val;
	return ida[val];
}
void balance_insert(){
	for(int i = 0;i+1<BUCKET;i++){
		if(baldes[i].empty()) break;
		if(baldes[i].size() <= BUCKET) continue;
		int last = baldes[i].back();
		baldes[i].pop_back();
		baldes[i+1].push_front(last);
		qualbalde[last] = i + 1;
	}
}
void balance_remove(){
	for(int i = 0;i+1<BUCKET;i++){
		if(baldes[i+1].empty()) break;
		if(baldes[i].size() >= BUCKET) continue;
		int first = baldes[i+1].front();
		baldes[i+1].pop_front();
		baldes[i].push_back(first);
		qualbalde[first] = i;
	}
}
void insert_front(int val){
	val = get_id(val);
	baldes[0].push_front(val);
	qualbalde[val] = 0;
	balance_insert();
}
void insert_back(int val){
	val = get_id(val);
	int idx = 0;
	while(!baldes[idx+1].empty()) idx++;
	baldes[idx].push_back(val);
	qualbalde[val] = idx;
	balance_insert();
}
void remove_front(){
	baldes[0].pop_front();
	balance_remove();
}
void remove_back(){
	int idx = 0;
	while(!baldes[idx+1].empty()) idx++;
	baldes[idx].pop_back();
	balance_remove();
}
int kth(int k){
	k--;
	return volta[baldes[k/BUCKET][k % BUCKET]];
}
int find(int val){
	val = ida[val];
	int id = qualbalde[val];
	int pos = id*BUCKET;
	for(int i = 0;i<baldes[id].size();i++){
		if(baldes[id][i] == val) return i + pos + 1;
	}
	return -1;
}
int main(){
	int TC;
	scanf("%d",&TC);
	for(int tc = 1;tc <= TC;tc++){
		printf("Case %d:\n",tc);
		int N;
		scanf("%d",&N);
		int tot = (N-1)/BUCKET;
		for(int i = 0;i<=tot;i++) baldes[i].clear();
		ida.clear();volta.clear();
		while(N--){
			int op;
			scanf("%d",&op);
			if(op == 1){
				char x;
				int y;
				scanf(" %c %d",&x,&y);
				if(x == 'B') insert_back(y);
				else insert_front(y);
			}
			else if(op == 2){
				char x;
				scanf(" %c",&x);
				if(x == 'B') remove_back();
				else remove_front();
			}
			else if(op == 3){
				char x;
				int y;
				scanf(" %c %d",&x,&y);
				if(x == 'D') printf("%d\n",kth(y));
				else printf("%d\n",find(y));
			}
		}
	}
	return 0;
}