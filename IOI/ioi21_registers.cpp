#include "registers.h"
#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

void construct_instructions(int s, int n, int k, int q) {
	auto swap = [&](int a, int b, int filterPos){
		append_not(2, a);
		append_add(2, b, 2);
		append_add(2, 98, 2);
		// c = b + (~a) + 1 = b - a
		{
			append_xor(3, a, 2);
			append_xor(3, b, 3);
			append_and(95, 3, filterPos); // only contains carry
			append_right(96, 95, k);
			append_not(96, 96);
			append_add(96, 96, 98);
			append_add(94, 95, 96);
		}
		append_xor(2, a, b);
		append_and(2, 94, 2);
		append_xor(a, a, 2);
		if(s == 1) append_xor(b, b, 2);
	};
	if(s == 0){
		int b = 1;
		while(b < n) b <<= 1;
		{
			vector<bool> vect(2000);
			fill(vect.begin() + n * k, vect.begin() + b * k, 1);
			append_store(99, vect);
			append_or(0, 0, 99);
			fill(all(vect), 0);
			vect[0] = 1;
			append_store(98, vect);
		}
		while(b > 1){
			append_right(1, 0, (b / 2) * k);
			{
				vector<bool> vect(2000);
				for(int i = 0; i < b / 2; i++) vect[i * k + k] = 1;
				append_store(97, vect);
			}
			swap(0, 1, 97);
			b >>= 1;
		}
		{
			vector<bool> vect(2000);
			fill(vect.begin(), vect.begin() + k, 1);
			append_store(99, vect);
			append_and(0, 0, 99);
		}
	}
	if(s == 1){
		{
			vector<bool> vect(2000);
			for(int i = 0; i < n/2; i++) vect[i * k + k] = 1;
			append_store(80, vect);
		}
		{
			vector<bool> vect(2000);
			for(int i = 0; i < (n-1)/2; i++) vect[i * k + k] = 1;
			append_store(81, vect);
		}
		const int HALF = 79;
		const int ONE = 78;
		const int TMP = 77;
		const int BACKUP = 76;
		{
			vector<bool> vect(2000);
			fill(vect.begin(), vect.begin() + (n/2)*k, 1);
			append_store(HALF, vect);
			fill(all(vect), 0);
			fill(vect.begin(), vect.begin() + k, 1);
			append_store(ONE, vect);
			fill(all(vect), 0);
			vect[0] = 1;
			append_store(98, vect);
		}
		append_left(TMP, 0, 0);
		for(int i = 0; i < n/2+1; i++){
			append_and(0, TMP, HALF);
			append_right(1, TMP, (n/2)*k);
			swap(0, 1, 80);
			append_and(BACKUP, ONE, 1);
			append_right(1, 1, k);
			swap(1, 0, 81);
			append_left(1, 1, k);
			append_or(1, 1, BACKUP);
			append_left(1, 1, (n/2)*k);
			append_or(TMP, 0, 1);
		}
		vector<int> b;
		if(n % 2 == 1) b.push_back(n - 1);
		for(int i = n / 2 - 1; i >= 0; i--){
			b.push_back(i);
			b.push_back(i + n/2);
		}
		reverse(all(b));
		append_left(0, 42, 0);
		for(auto &i : b){
			append_right(69, TMP, i * k);
			append_and(69, 69, ONE);
			append_left(0, 0, k);
			append_or(0, 0, 69);
		}
	}
}

