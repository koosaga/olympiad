// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci07c2p4
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 10;
const int BUCKET = 320;
deque<int> balde[BUCKET+20];
int n,m,qualbalde[MAXN];
void balance_insert(){
	int idx = 0;
	while(true){
		if(balde[idx].empty()) break;
		if(balde[idx].size() > BUCKET){
			balde[idx+1].push_front(balde[idx].back());
			qualbalde[balde[idx].back()] = idx+1;
			balde[idx].pop_back();
		}
		idx++;
	}
}
void balance_remove(){
	int idx = 0;
	while(true){
		if(balde[idx+1].empty()) break;
		if(balde[idx].size() < BUCKET){
			balde[idx].push_back(balde[idx+1].front());
			qualbalde[balde[idx+1].front()] = idx;
			balde[idx+1].pop_front();
		}
		idx++;
	}
}
void search_delte_show(int u){
	int bucket_id = qualbalde[u];
	int pos = qualbalde[u]*BUCKET;
	int dist = 0;
	deque<int>::iterator it = balde[bucket_id].begin();
	while(true){
		if((*it) == u) break;
		dist++;
		it++;
	}
	printf("%d\n",abs(pos + dist - u));
	balde[bucket_id].erase(it);
	balance_remove();
	qualbalde[u] = u / BUCKET;
	it = balde[qualbalde[u]].begin() + (u % BUCKET);
	balde[qualbalde[u]].insert(it,u);
	balance_insert();
}
int main(){
	scanf("%d",&n);
	for(int i = 0;i<n;i++){
		int x;
		scanf("%d",&x);
		x--;
		qualbalde[x] = i / BUCKET;
		balde[qualbalde[x]].push_back(x);
	}
	int ini = 0,fim = n - 1,flag = 0;
	while(ini <= fim){
		int davez;
		if(flag == 0){
			davez = ini;
			ini++;
			flag = 1;
		}
		else{
			davez = fim;
			fim--;
			flag = 0;
		}
		search_delte_show(davez);
	}
	return 0;
} 0;
}