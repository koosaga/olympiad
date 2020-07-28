// Ivan Carvalho
// Solution to https://dmoj.ca/problem/cco16p5
#include <bits/stdc++.h>
using namespace std;
typedef tuple<int,int,int,int> quadra;
vector<int> compressao;
vector<quadra> sweep;
int n,R,C,objetivo;
int X[5010],Y[5010];
int ac[20000],soma[20000];
void add(int pos,int left,int right,int i,int j){
	if(left>right||left>j||right<i) return;
	if(left >= i && right <= j){
		ac[pos]++;
		soma[pos] = compressao[right+1] - compressao[left];
	}
	else{
		int mid = (left+right)/2;
		add(2*pos,left,mid,i,j);
		add(2*pos+1,mid+1,right,i,j);
		if(!ac[pos]) soma[pos] = soma[2*pos] + soma[2*pos+1];
	}
}
void remove(int pos,int left,int right,int i,int j){
	if(left>right||left>j||right<i) return;
	if(left >= i && right <= j){
		ac[pos]--;
		if(ac[pos] == 0){
			if(left == right) soma[pos] = 0;
			else soma[pos] = soma[2*pos] + soma[2*pos+1];
		}
	}
	else{
		int mid = (left+right)/2;
		remove(2*pos,left,mid,i,j);
		remove(2*pos+1,mid+1,right,i,j);
		if(!ac[pos]) soma[pos] = soma[2*pos] + soma[2*pos+1];
	}
}
long long solve(int Q){
	long long resp = 0;
	int lastx = 0;
	int tot = 0;
	compressao.clear();
	sweep.clear();
	//printf("R %d C %d\n",R,C);
	for(int i = 1;i<=n;i++){
		int x1 = max(X[i] - Q,1);
		int x2 = min(X[i] + Q,R);
		int y1 = max(Y[i] - Q,1);
		int y2 = min(Y[i] + Q,C);
		sweep.push_back(make_tuple(x1,1,y1,y2+1));
		sweep.push_back(make_tuple(x2+1,-1,y1,y2+1));
		compressao.push_back(y1);
		compressao.push_back(y2+1);
		//printf("Y1 %d Y2 %d\n",y1,y2+1);
	}
	sort(compressao.begin(),compressao.end());compressao.erase(unique(compressao.begin(),compressao.end()),compressao.end());
	sort(sweep.begin(),sweep.end());
	for(int i = 0;i<sweep.size();i++){
		int x = get<0>(sweep[i]),delta = get<1>(sweep[i]),y1 = get<2>(sweep[i]),y2 = get<3>(sweep[i]);
		resp += 1LL*(x - lastx)*soma[1];
		y1 = lower_bound(compressao.begin(),compressao.end(),y1) - compressao.begin();
		y2 = lower_bound(compressao.begin(),compressao.end(),y2) - compressao.begin();
		//printf("Y %d\n",compressao[y2] - compressao[y1]);
		if(delta == 1) add(1,0,compressao.size()+1,y1,y2-1);
		else remove(1,0,compressao.size()+1,y1,y2-1);
		lastx = x;
	}
	return resp;
}
int main(){
	cin.tie(0);cout.tie(0);ios_base::sync_with_stdio(0);
	cin >> R >> C >> n;
	for(int i = 1;i<=n;i++) cin >> X[i] >> Y[i];
	cin >> objetivo;
	cout << solve(objetivo) - solve(objetivo-1) << endl;
	return 0;
}return 0;
}