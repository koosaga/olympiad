// Ivan Carvalho
// Solution to https://www.spoj.com/problems/ACQUIRE/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int pointer;
typedef pair<int,int> ii;
vector<long long> M;
vector<long long> B;
bool bad(int l1,int l2,int l3){
	return (B[l3]-B[l1])*(M[l1]-M[l2])<(B[l1]-B[l2])*(M[l3]-M[l1]);
}
void add(long long m,long long b){
	M.push_back(m);
	B.push_back(b);
	while (M.size()>=3&&bad(M.size()-3,M.size()-2,M.size()-1))
	{
		M.erase(M.end()-2);
		B.erase(B.end()-2);
	}
}
long long query(long long x){
	if (pointer>=M.size())
		pointer=M.size()-1;
	while (pointer<M.size()-1&&
	  M[pointer+1]*x+B[pointer+1]<M[pointer]*x+B[pointer])
		pointer++;
	return M[pointer]*x+B[pointer];
}
int main(){
	int M,N,i;
	vector<ii> rect,a;
	scanf("%d",&M);
	for (i=0; i<M; i++){
		int aa,bb;
		scanf("%d %d",&aa,&bb);
		a.push_back(make_pair(aa,bb));
	}
	sort(a.begin(),a.end());
	for (i=0; i<M; i++){
		while (rect.size()>0&&rect[rect.size()-1].second<=a[i].second) rect.pop_back();
		rect.push_back(a[i]);
	}
	N = rect.size();
	long long best;
	add(rect[0].second,0);
	pointer=0;
	for (i=0; i<N; i++){
		best=query(rect[i].first);
		add(rect[i+1].second,best);
	}
	printf("%lld\n",best);
	return 0;
}