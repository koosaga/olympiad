// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ioi13p4
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5010;

int isDefined[MAXN],definedState[MAXN],whichNumber[MAXN],N;
int queryArray[MAXN];

int opens_kth(int got_ans,int target){
	if(got_ans == -1) return 1;
	return got_ans > target;
}

void divide_and_conquer(int target,int left,int right,int known_color){

	if(left == right){
		isDefined[left] = 1;
		definedState[left] = known_color;
		whichNumber[left] = target;
		return;
	}

	memset(queryArray,0,sizeof(queryArray));
	int mid = (left + right)/2;
	for(int i = 0;i<N;i++){
		if(left <= i && i <= mid){
			queryArray[i] = known_color;
		}
		else{
			queryArray[i] = 1 ^ known_color;
		}
	}
	for(int i = 0;i<N;i++){
		if(isDefined[i]) queryArray[i] = definedState[i];
	}

	int ans = tryCombination(queryArray);
	if(opens_kth(ans,target)){
		divide_and_conquer(target,left,mid,known_color);
	}
	else{
		divide_and_conquer(target,mid+1,right,known_color);
	}

}

int which_color(int target){

	memset(queryArray,0,sizeof(queryArray));
	for(int i = 0;i<N;i++){
		queryArray[i] = 0;
	}
	for(int i = 0;i<N;i++){
		if(isDefined[i]) queryArray[i] = definedState[i];
	}

	int ans = tryCombination(queryArray);
	if(opens_kth(ans,target)) return 0;
	else return 1;

}

void exploreCave(int n) {
    
    N = n;

    for(int i = 0;i<N;i++){
    	int known_color = which_color(i);
    	divide_and_conquer(i,0,N-1,known_color);
    }

    answer(definedState,whichNumber);

}
