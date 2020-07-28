// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ioi98p4
#include <bits/stdc++.h>
#define MT make_tuple
using namespace std;
typedef tuple<int,int,int,int> quadra;
const int MAXN = 20100;
const int ADD = 10001;
vector<quadra> sweepx,sweepy;
int ac[4*MAXN+40],soma[4*MAXN+40],n,last,resp;
void add(int pos,int left,int right,int i,int j){
	if(left>right||left>j||right<i) return;
	if(left >= i && right <= j){
		ac[pos]++;
		soma[pos] = right - left + 1;
		return;
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
int main(){
	cin.tie(0);ios_base::sync_with_stdio(0);
	cin >> n;
	for(int i = 0;i<n;i++){
		int x1,y1,x2,y2;
		cin >> x1 >> y1 >> x2 >> y2;
		x1 += ADD;x2+=ADD;y1+=ADD;y2+=ADD;
		sweepx.push_back(MT(x1,1,y1,y2));
		sweepx.push_back(MT(x2,2,y1,y2));
		sweepy.push_back(MT(y1,1,x1,x2));
		sweepy.push_back(MT(y2,2,x1,x2));
	}
	sort(sweepx.begin(),sweepx.end());
	sort(sweepy.begin(),sweepy.end());
	for(int i = 0;i < sweepx.size();i++){
		int x = get<0>(sweepx[i]);
		int delta = get<1>(sweepx[i]);
		int y1 = get<2>(sweepx[i]);
		int y2 = get<3>(sweepx[i]);
		if(delta == 1) add(1,1,MAXN,y1,y2-1);
		else remove(1,1,MAXN,y1,y2-1);
		resp += abs(last - soma[1]);
		last = soma[1];
	}
	for(int i = 0;i < sweepy.size();i++){
		int x = get<0>(sweepy[i]);
		int delta = get<1>(sweepy[i]);
		int y1 = get<2>(sweepy[i]);
		int y2 = get<3>(sweepy[i]);
		if(delta == 1) add(1,1,MAXN,y1,y2-1);
		else remove(1,1,MAXN,y1,y2-1);
		resp += abs(last - soma[1]);
		last = soma[1];
	}
	cout << resp << endl;
	return 0;
}turn 0;
}