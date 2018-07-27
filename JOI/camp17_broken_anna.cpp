#include "Annalib.h"
#include <bits/stdc++.h>
using namespace std;

int seq[222];
int chk[222];

void Embed(int pos, int val){
	Set(pos, val >> 2);
	Set(pos + 1, (val >> 1) & 1);
	Set(pos + 2, val & 1);
}

void Anna( int N, long long X, int K, int P[] ){
	for(int i=0; i<60; i++){
		seq[i] = (X >> i) & 1;
	}
	for(int i=0; i<150; i++) chk[i] = 1;
	for(int i=0; i<K; i++){
		chk[P[i]] = 0;
	}
	int ptr = 0;
	for(int i=0; i<150; i+=3){
		if(chk[i] + chk[i+1] + chk[i+2] <= 1){
			Embed(i, 0);
		}
		else if(chk[i] + chk[i+1] + chk[i+2] == 3){
			if(seq[ptr] == 0 && seq[ptr+1] == 0){
				Embed(i, 4);
			}
			else if(seq[ptr] == 0 && seq[ptr+1] == 1){
				Embed(i, 6);
			}
			else if(seq[ptr] == 1 & seq[ptr+1] == 0){
				Embed(i, 3);
			}
			else{
				Embed(i, 7);
			}
			ptr += 2;
		}
		else{
			if(seq[ptr] == 0){
				if(chk[i+2] == 1){
					Embed(i, 1);
					ptr++;
				}
				else{
					if(seq[ptr+1] == 0){
						Embed(i, 4);
					}
					else{
						Embed(i, 6);
					}
					ptr += 2;
				}
			}
			else{
				if(chk[i+1] == 0) Embed(i, 5);
				else Embed(i, 2);
				ptr++;
			}
		}
	}
}
