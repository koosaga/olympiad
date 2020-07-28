// Ivan Carvalho
// Solution to https://dmoj.ca/problem/dmpg16g6
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 262244;
const int BUCKET = 512;
const int MOD = (1 << 18);
long precalc[BUCKET+10][BUCKET+10];
int freq[BUCKET+10][MAXN];
int vetor[MAXN];
int tempfreq[MAXN];
int seen[MAXN];
int bdiv[MAXN];
int N,Q;
long last;
void build(int id){
	memset(tempfreq,0,sizeof(tempfreq));
	long tempresp = 0;
	for(int i = 0;i < min((id+1)*BUCKET,N);i++){
		freq[id][vetor[i]]++;
	}
	for(int i = id*BUCKET;i<N;i++){
		int elemento = vetor[i];
		tempresp += (tempfreq[elemento] << 1L) | 1L;
		tempfreq[elemento]++;
		tempresp %= MOD;
		precalc[id][bdiv[i]] = tempresp;
	}
}
int main(){
	scanf("%d %d",&N,&Q);
	for(int i = 0;i<N;i++){
		bdiv[i] = i / BUCKET;
		scanf("%d",&vetor[i]); 
	}
	int tot = (N-1)/BUCKET;
	for(int i = 0;i<=tot;i++) build(i);
	for(int q = 1;q<=Q;q++){
		int l,r;
		scanf("%d %d",&l,&r);
		l ^= last;r ^= last;last = 0;
		int l_bucket = bdiv[l], r_bucket = bdiv[r];
		if(l_bucket == r_bucket){
			for(int i = l;i<=r;i++){
				int elemento = vetor[i];
				if(seen[elemento] != q){
					seen[elemento] = q;
					tempfreq[elemento] = 0;
				}
				last += (tempfreq[elemento] << 1L) | 1L;
				tempfreq[elemento]++;
			}
		}
		else{
			last = precalc[l_bucket+1][r_bucket-1];
			for(int i = l;i < (l_bucket + 1)*BUCKET;i++){
				int elemento = vetor[i];
				if(seen[elemento] != q){
					seen[elemento] = q;
					tempfreq[elemento] = freq[r_bucket-1][elemento] - freq[l_bucket][elemento];
				}
				last += (tempfreq[elemento] << 1L) | 1L;
				tempfreq[elemento]++;
			}
			for(int i = r_bucket*BUCKET;i<=r;i++){
				int elemento = vetor[i];
				if(seen[elemento] != q){
					seen[elemento] = q;
					tempfreq[elemento] = freq[r_bucket-1][elemento] - freq[l_bucket][elemento];
				}
				last += (tempfreq[elemento] << 1L) | 1L;
				tempfreq[elemento]++;
			}
		}
		last %= MOD;
		printf("%ld\n",last);
	}
	return 0;	
}turn 0;	
}