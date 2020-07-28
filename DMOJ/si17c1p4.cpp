// Ivan Carvalho
// Solution to https://dmoj.ca/problem/si17c1p4
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD1 = 1e9 + 9;
const ll prime1 = 999983;
const ll MOD2 = 1e9 + 7;
const ll prime2 = 999979;
const ll invprime1 = 943912055;
const ll invprime2 = 672490127;
const int MAXN = 2*1e5 + 10;
ll hash1[MAXN],pot1[MAXN],invpot1[MAXN];
int N,M,logaritmo[MAXN],comprimento[MAXN],dp[4*MAXN];
string s1,s2,entrada;
vector<int> SArray,ida,volta;
inline ll get_hash1(int a,int b){
	ll val = ((hash1[b] - hash1[a-1])*invpot1[a-1]) %  MOD1;
	if(val < 0) val += MOD1;
	return val;
}
int LCP(int idx1,int idx2,int tam){
	for(int i = 0;i<=min(tam,15);i++){
		if(entrada[idx1-1+i] != entrada[idx2 - 1 + i]) return i;
		if(tam == i + 1) return tam;
	}
	int atual = 0;
	for(int i = logaritmo[tam];i>=0;i--){
		int novo = atual + (1 << i);
		if(novo <= tam && get_hash1(idx1,idx1+novo-1) == get_hash1(idx2,idx2+novo-1)){
			atual = novo;
		}
	}
	return atual;
}
int compara(int idx1,int idx2){
	int tam = (N + M + 1) - max(idx1,idx2) + 1;
	int prefixo = LCP(idx1,idx2,tam);
	if(prefixo == tam){
		return idx1 > idx2;
	}
	return entrada[idx1 - 1 + prefixo] < entrada[idx2 - 1 + prefixo];
}
template<class Iter>
void merge_sort(Iter first, Iter last){
    if (last - first > 1) {
        Iter middle = first + (last - first) / 2;
        merge_sort(first, middle); // [first, middle)
        merge_sort(middle, last);  // [middle, last)
        std::inplace_merge(first, middle, last,compara);
    }
}
void update(int pos,int left,int right,int x,int y){
	if(left == right){
		dp[pos] = y;
		return;
	}
	int mid = (left+right)/2;
	if(x <= mid) update(2*pos,left,mid,x,y);
	else update(2*pos+1,mid+1,right,x,y);
	dp[pos] = min(dp[2*pos],dp[2*pos+1]);
}
int query(int pos,int left,int right,int i,int j){
	if(left >= i && right <= j) return dp[pos];
	int mid = (left+right)/2;
	if(j <= mid) return query(2*pos,left,mid,i,j);
	else if(i >= mid + 1) return query(2*pos+1,mid+1,right,i,j);
	return min(query(2*pos,left,mid,i,j),query(2*pos+1,mid+1,right,i,j)); 
}
int main(){
	cin >> s1;
	N = s1.size();
	s1.push_back('.');
	cin >> s2;
	M = s2.size();
	entrada = s1 + s2;
	pot1[0] = invpot1[0] = 1;
	for(int i = 1;i<=N+M+1;i++){
		pot1[i] = (pot1[i-1]*prime1) %  MOD1;
		invpot1[i] = (invpot1[i-1]*invprime1) %  MOD1;
		logaritmo[i] = logaritmo[i/2] + 1;
		hash1[i] = (hash1[i-1] + pot1[i]*entrada[i-1]) % MOD1;
		SArray.push_back(i);
		ida.push_back(0);
		volta.push_back(0);
	}
	merge_sort(SArray.begin(),SArray.end());
	for(int pos = 0;pos<SArray.size();pos++){
		if(pos != 0) ida[pos] = ida[pos-1];
		else ida[pos] = -1;
		if(SArray[pos] <= N) ida[pos] = SArray[pos];
	}
	for(int pos = SArray.size()-1;pos>=0;pos--){
		if(pos + 1 < SArray.size()) volta[pos] = volta[pos+1];
		else volta[pos] = -1;
		if(SArray[pos] <= N) volta[pos] = SArray[pos];
 	}
 	for(int pos = 0;pos<SArray.size();pos++){
 		int idx = SArray[pos];
 		if(idx <= N+1) continue;
 		int i = ida[pos];
 		int j = volta[pos];
 		//printf("I %c %d %d %d\n",entrada[idx-1],idx,i,j);
 		int tam = 0;
 		if(i != -1) tam = LCP(i,idx, (N+M+1) - max(i,idx) + 1 );
 		if(j != -1) tam = max(tam,LCP(j,idx, (N+M+1) - max(j,idx) + 1 ));
 		comprimento[idx - (N+1)] = tam;
 	}
 	for(int i = 1;i<=M;i++){
 		if(comprimento[i] == 0){
 			printf("-1\n");
 			return 0;
 		}	
 	}
 	for(int i = 1;i<=4*(M+1);i++) dp[i] = MAXN;
 	update(1,1,M+1,M+1,0);
 	for(int i = M;i>=1;i--){
 		update(1,1,M+1, i, query(1,1,M+1,i+1,i+comprimento[i]) + 1 );
 	}
 	printf("%d\n",query(1,1,M+1,1,1));
	return 0;
}}
 	printf("%d\n",query(1,1,M+1,1,1));
	return 0;
}