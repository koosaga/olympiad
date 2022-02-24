#include <bits/stdc++.h>
using lint = long long;
#include "books.h"

using namespace std;
//
// --- Sample implementation for the task books ---
//
// To compile this program with the sample grader, place:
//     books.h books_sample.cpp sample_grader.cpp
// in a single folder and run:
//     g++ books_sample.cpp sample_grader.cpp
// in this folder.
//

void solve(int N, int K, long long A, int S) {
	vector<lint> fst(K);
	vector<int> idx;
	lint sum = 0;
	for(int i = 0; i < K; i++){
		fst[i] = skim(i + 1);
		idx.push_back(i + 1);
		sum += fst[i];
	}
	if(sum > 2 * A){
		impossible();
		return;
	}
	if(sum >= A){
		answer(idx); return;
	}
	for(int i = K - 1; i >= 0; i--){
		lint newVal = skim(N - K + i + 1) - fst[i];
		if(sum + newVal >= A){
			int s = i, e = N - K + i;
			while(s != e){
				int m = (s + e + 1) / 2;
				if(sum + skim(m + 1) - fst[i] >= A) s = m;
				else e = m - 1;
			}
			if(sum + skim(s + 1) - fst[i] <= 2 * A){
				idx[i] = s + 1;
				answer(idx);
			}
			else{
				assert(i == K - 1);
				N = s;
				for(int j = K - 1; j >= 0; j--){
					lint newVal = skim(N - K + j + 1) - fst[j];
					idx[j] += N - K;
					if(sum + newVal >= A){
						answer(idx);
						return;
					}
					sum += newVal;
				}
				impossible();
			}
			return;
		}
		else{
			sum += newVal;
			idx[i] += N - K;
		}
	}
	impossible();
}
