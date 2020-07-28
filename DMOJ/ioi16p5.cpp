// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ioi16p5
#include <bits/stdc++.h>
using namespace std;

int whichNumber[129];
int N;

void solve_add(int left,int right){

	if(left == right) return;

	int mid = left + (right - left)/2;
	string s;

	for(int i = 0;i<N;i++){
		if(left <= i && i <= right){
			s.push_back('0');
		}
		else{
			s.push_back('1');
		}
	}

	for(int i = left;i<=mid;i++){
		s[i] = '1';
		add_element(s);
		s[i] = '0';
	}

	solve_add(left,mid);
	solve_add(mid+1,right);

}

void solve_check(int left,int right,vector<int> possible){

	if(left == right){
		whichNumber[possible[0]] = left;
		return;
	}

	int mid = left + (right - left)/2;

	vector<int> firstHalf,lastHalf;

	string s;
	for(int i = 0;i<N;i++) s.push_back('1');
	for(int i : possible) s[i] = '0';

	for(int i : possible){
		s[i] = '1';
		if(check_element(s)){
			firstHalf.push_back(i);
		}
		else{
			lastHalf.push_back(i);
		}
		s[i] = '0';
	}

	solve_check(left,mid,firstHalf);
	solve_check(mid+1,right,lastHalf);

}

int* restore_permutation(int n, int w, int r){

	N = n;
	vector<int> allElements;
	for(int i = 0;i<N;i++) allElements.push_back(i);

	solve_add(0,N-1);
	compile_set();
	solve_check(0,N-1,allElements);

	return whichNumber;

}
