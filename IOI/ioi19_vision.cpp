#include "vision.h"
using namespace std;

int solve(int H, int W, int K){
	vector<int> X[444], Y[444];
	for(int i=0; i<H; i++){
		for(int j=0; j<W; j++){
			X[i+j].push_back(i*W+j);
			Y[i+W-1-j].push_back(i*W+j);
		}
	}
	vector<int> XC, YC, XP, YP;
	vector<int> dap;
	for(int i=0; i<=H+W-2; i++){
		XC.push_back(add_or(X[i]));
		YC.push_back(add_or(Y[i]));
		XP.push_back(add_or(XC));
		YP.push_back(add_or(YC));
		if(i >= K){
			dap.push_back(add_and({XC[i], XP[i-K]}));
			dap.push_back(add_and({YC[i], YP[i-K]}));
		}
	}
	return add_or(dap);
}

void construct_network(int H, int W, int K) {
	if(H+W-2 == K) solve(H, W, K);
	else add_xor({solve(H, W, K), solve(H, W, K + 1)});
}
