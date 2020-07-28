// Ivan Carvalho
// Solution to https://dmoj.ca/problem/apio10p1
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
vector<ll> M,B;
int pointer;
bool bad(int l1,int l2,int l3)
{
	/*
	intersection(l1,l2) has x-coordinate (b1-b2)/(m2-m1)
	intersection(l1,l3) has x-coordinate (b1-b3)/(m3-m1)
	set the former greater than the latter, and cross-multiply to
	eliminate division
	*/
	return (B[l3]-B[l1])*(M[l1]-M[l2])<(B[l2]-B[l1])*(M[l1]-M[l3]);
}
//Adds a new line (with lowest slope) to the structure
void add(long long m,long long b)
{
	//First, let's add it to the end
	m *= -1;
	b *= -1;
	M.push_back(m);
	B.push_back(b);
	//If the penultimate is now made irrelevant between the antepenultimate
	//and the ultimate, remove it. Repeat as many times as necessary
	while (M.size()>=3&&bad(M.size()-3,M.size()-2,M.size()-1))
	{
		M.erase(M.end()-2);
		B.erase(B.end()-2);
	}
}
//Returns the minimum y-coordinate of any intersection between a given vertical
//line and the lower envelope
long long query(long long x)
{
	//If we removed what was the best line for the previous query, then the
	//newly inserted line is now the best for that query
	if (pointer>=M.size())
		pointer=M.size()-1;
	//Any better line must be to the right, since query values are
	//non-decreasing
	while (pointer<M.size()-1&&
	  M[pointer+1]*x+B[pointer+1]<M[pointer]*x+B[pointer])
		pointer++;
	return -(M[pointer]*x+B[pointer]);
}
int main(){
	int TC = 1;
	while(TC--){
		M.clear();
		B.clear();
		pointer = 0;
		int n;
		scanf("%d",&n);
		ll a,b,c;
		scanf("%lld %lld %lld",&a,&b,&c);
		add(0LL,0LL);
		ll davez, soma = 0;
		for(int i=1;i<n;i++){
			scanf("%lld",&davez);
			soma += davez;
			ll best = query(soma) + a*soma*soma + b*soma + c;
			add(-2*a*soma,best + a*soma*soma - b*soma);
		}
		scanf("%lld",&davez);
		soma += davez;
		ll best = query(soma) + a*soma*soma + b*soma + c;
		printf("%lld\n",best);
	}
	return 0;
}
