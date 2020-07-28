// Ivan Carvalho
// Solution to https://www.spoj.com/problems/ADALIST/
#include <cstdio>
#include <deque>
#define gc getchar_unlocked
void getint(int &x){
    register int c = gc();
    x = 0;
    int neg = 0;
    for(;((c<48 || c>57) && c != '-');c = gc());
    if(c=='-') {neg=1;c=gc();}
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
    if(neg) x=-x;
}
using namespace std;
const int BLOCK_SZ = 548;
const int BUCKET_NUM = 1100;
deque<int> vetor[BUCKET_NUM];
int view(int idx){
	idx--;
	int bucket_a = idx / BLOCK_SZ;
	int bucket_b = idx % BLOCK_SZ;
	return vetor[bucket_a][bucket_b];
}
void balance_insert(int idx){
	while(true){
		if(vetor[idx].empty()) break;
		if(vetor[idx].size() > BLOCK_SZ){
			vetor[idx+1].push_front(vetor[idx].back());
			vetor[idx].pop_back();
		}
		idx++;
	}
}
void balance_remove(int idx){
	while(true){
		if(vetor[idx+1].empty()) break;
		if(vetor[idx].size() < BLOCK_SZ){
			vetor[idx].push_back(vetor[idx+1].front());
			vetor[idx+1].pop_front();
		}
		idx++;
	}
}
void insert(int key,int idx){
	idx--;
	int bucket_a = idx / BLOCK_SZ;
	int bucket_b = idx % BLOCK_SZ;
	vetor[bucket_a].insert(vetor[bucket_a].begin() + bucket_b,key);
	balance_insert(bucket_a);
}
void remove(int idx){
	idx--;
	int bucket_a = idx / BLOCK_SZ;
	int bucket_b = idx % BLOCK_SZ;
	vetor[bucket_a].erase(vetor[bucket_a].begin() + bucket_b);
	balance_remove(bucket_a);
}
int main(){
	int N,Q;
	getint(N);
	getint(Q);
	for(int i=1;i<=N;i++){
		int davez;
		getint(davez);
		insert(davez,i);
	}
	while(Q--){
		int op,k,x;
		getint(op);
		getint(k);
		if(op == 1){
			getint(x);
			insert(x,k);
		}
		if(op == 2) remove(k);
		if(op == 3){
			printf("%d\n",view(k));
		}
	}
	return 0;
}