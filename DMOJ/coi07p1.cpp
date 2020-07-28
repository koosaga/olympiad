// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coi07p1
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 10;

int N;
double T[MAXN],pos_i[MAXN],pos_f[MAXN],K;

int main(){
	scanf("%lf",&K);
	scanf("%d",&N);
	for(int i = 1;i<=N;i++){
		scanf("%lf",&pos_i[i]);
		if(i == 1) continue;
		if(pos_f[i-1] + K >= pos_i[i]){
			pos_f[i] = min(pos_f[i-1] + K,pos_i[i] + T[i-1]);
			T[i] = T[i-1];
		}
		else if(pos_f[i-1] + K >= pos_i[i] - T[i-1]){
			pos_f[i] = pos_f[i-1] + K;
			T[i] = T[i-1];
		}
		else{
			double pos_temp = pos_i[i] - T[i-1];
			pos_f[i] = (pos_temp + pos_f[i-1] + K)*0.5;
			T[i] = T[i-1] + (pos_temp - pos_f[i-1] - K)*0.5;
		}
	}
	printf("%.3lf\n",T[N]);
	return 0;
}