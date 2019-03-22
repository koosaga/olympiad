#include "Device.h"
#include <bits/stdc++.h>
using namespace std;

#define generate_seq fuck
#define seq fuckk

vector<int> generate_seq(){
	double rat = 1.05;
	vector<int> v = {1};
	while(v.size() < 256){
		int curV = (int)round(rat);
		if(curV != v.back()) v.push_back(curV);
		rat *= 1.05;
	}
	return v;
}

vector<int> seq;

void InitDevice(){
	seq = generate_seq();
}

int Answer(long long S, long long T){
	int dfnS = (S >> 8);
	int szS = S & ((1<<8) - 1);
	szS = seq[szS];
	int dfnT = (T >> 8);
	int szT = T & ((1<<8) - 1);
	szT = seq[szT];
	if(dfnS <= dfnT && dfnT + szT <= dfnS + szS){
		return 1;
	}
	if(dfnT <= dfnS && dfnS + szS <= dfnT + szT){
		return 0;
	}
	return 2;
}
