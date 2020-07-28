// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ioi15p4
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1e9 + 7;
const ll MAXN = 5*1e5 + 10;
struct node{
	double maximum,total;
	ll max_product,tot_product;
	node operator*(const node& other)const{
		//printf("Joining\n");
		//printf("%lld %lld %.9lf %.9lf\n",max_product,tot_product,maximum,total);
		//printf("%lld %lld %.9lf %.9lf\n",other.max_product,other.tot_product,other.maximum,other.total);
		node novo;
		novo.total = total + other.total;
		novo.tot_product = (tot_product * other.tot_product) % MOD;
		if(other.maximum + total >= maximum){
			novo.maximum = total + other.maximum;
			novo.max_product = (tot_product * other.max_product) % MOD;
		}
		else{
			novo.maximum = maximum;
			novo.max_product = max_product;
		}
		//printf("%lld %lld %.9lf %.9lf\n",novo.max_product,novo.tot_product,novo.maximum,novo.total);
		return novo;
	}
};
node seg[4*MAXN];
ll X[MAXN],Y[MAXN],N,M;
void build(int pos,int left,int right){
	if(left == right){
		seg[pos].max_product = (Y[left] * X[left]) % MOD;
		seg[pos].tot_product = X[left];
		seg[pos].maximum = log(Y[left]) + log(X[left]);
		seg[pos].total = log(X[left]);
		return;
	}
	int mid = (left+right)/2;
	build(2*pos,left,mid);
	build(2*pos+1,mid+1,right);
	seg[pos] = seg[2*pos]*seg[2*pos+1];
}
void update(int pos,int left,int right,int x){
	if(left == right){
		seg[pos].max_product = (Y[left] * X[left]) % MOD;
		seg[pos].tot_product = X[left];
		seg[pos].maximum = log(Y[left]) + log(X[left]);
		seg[pos].total = log(X[left]);
		return;
	}
	int mid = (left+right)/2;
	if(x <= mid) update(2*pos,left,mid,x);
	else update(2*pos+1,mid+1,right,x);
	seg[pos] = seg[2*pos]*seg[2*pos+1];
}
int init(int n,int x[], int y[]){
	N = n;
	for(int i = 0;i<n;i++){
		X[i] = x[i];
		Y[i] = y[i];
	}
	build(1,0,N-1);
	return (int)seg[1].max_product;
}
int updateX(int pos,int val){
	X[pos] = (ll)val;
	update(1,0,N-1,pos);
	return (int)seg[1].max_product;
}
int updateY(int pos,int val){
	Y[pos] = (ll)val;
	update(1,0,N-1,pos);
	return (int)seg[1].max_product;
}
int main(){
	return 0;
}
