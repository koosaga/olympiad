// Ivan Carvalho
// Solution to https://www.spoj.com/problems/KGSS/
#include <iostream>
#include <algorithm>
#define MAXN 100001
#define MP make_pair
#define endl '\n'
using namespace std;
typedef pair<int,int> ii;
int vetor[MAXN],n,q;
ii arvore[4*MAXN],nulo;
ii join(ii A,ii B){
	int p1 = A.first, p2 = A.second, p3 = B.first, p4 = B.second;
	if (p1 > p4) swap(p1,p4);
	if (p1 > p3) swap(p1,p3);
	if (p1 > p2) swap(p1,p2);
	if (p2 > p4) swap(p2,p4);
	if (p2 > p3) swap(p2,p3);
	if (p3 > p4) swap(p3,p4);
	return MP(p4,p3);
}
void build(int pos, int left, int right){
	if (left == right){
		arvore[pos] = MP(vetor[left],0);
		return;
	}
	int mid = (left+right)/2;
	build(2*pos,left,mid);
	build(2*pos+1,mid+1,right);
	arvore[pos] = join(arvore[2*pos],arvore[2*pos+1]);
}
ii query(int pos, int left, int right, int i, int j){
	if (left > right || left > j || right < i) return nulo;
	if (left >= i && right <= j){
		return arvore[pos];
	}
	int mid = (left+right)/2;
	ii p1 = query(2*pos,left,mid,i,j);
	ii p2 = query(2*pos+1,mid+1,right,i,j);
	return join(p1,p2);
}
void update(int pos, int left, int right, int idx,int val){
	if (left > right || left > idx || right < idx) return;
	if (left == right){
		arvore[pos] = MP(val,0);
		return;
	}
	int mid = (left+right)/2;
	update(2*pos,left,mid,idx,val);
	update(2*pos+1,mid+1,right,idx,val);
	arvore[pos] = join(arvore[2*pos],arvore[2*pos+1]);
}
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	nulo = MP(0,0);
	cin >> n;
	for(int i=1;i<=n;i++) cin >> vetor[i];
	build(1,1,n);
	cin >> q;
	while(q--){
		char op;
		int a,b;
		cin >> op >> a >> b;
		if (op == 'Q'){
			ii resposta = query(1,1,n,a,b);
			cout << resposta.first + resposta.second << endl;
		}
		if (op == 'U') update(1,1,n,a,b);
	}
	return 0;
}