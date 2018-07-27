#include "Memory_lib.h"
#include <bits/stdc++.h>

struct Cont{ // Continuation
	int mode;
	int pos, height; // f(pos, height)
	int count, kth; // g(pos, count, kth)
	int opB, nxt; // h(pos, height, opB, nxt)
};

Cont num2cont(int x){
	Cont ret;
	if(x < (1<<14)){
		ret.mode = 1;
		ret.pos = (x >> 7);
		ret.height = x & ((1<<7) - 1);
	}
	else if(x < (1<<21)){
		ret.mode = 2;
		x -= (1<<14);
		ret.pos = (x >> 14);
		x &= ((1<<14) - 1);
		ret.count = (x >> 7);
		x &= ((1<<7) - 1);
		ret.kth = x;
	}
	else{
		ret.mode = 3;
		x -= (1<<21);
		ret.pos = (x >> 14);
		x &= ((1<<14) - 1);
		ret.opB = (x >> 13);
		x &= ((1<<13) - 1);
		ret.height = (x >> 7);
		x &= ((1<<7) - 1);
		ret.nxt = x;
	}
	return ret;
}

int cont2num(Cont c){
	if(c.mode == 1){
		return c.pos * (1<<7) + c.height;
	}
	if(c.mode == 2){
		return (1<<14) + c.pos * (1<<14) + c.count * (1<<7) + c.kth;
	}
	if(c.mode == 3){
		return (1<<21) + c.pos * (1<<14) + c.height * (1<<7) + c.opB * (1<<13) + c.nxt;
	}
	assert(false);
}

Cont F(int pos, int height){ 
	Cont ret; 
	ret.pos = pos; ret.height = height; ret.mode = 1; 
	return ret;
}

Cont G(int pos, int count, int kth){
	Cont ret;
	ret.pos = pos; ret.count = count; ret.kth = kth; ret.mode = 2;
	return ret;
}

Cont H(int pos, int height, int opB, int nxt){
	Cont ret;
	ret.pos = pos; ret.height = height; ret.opB = opB; ret.nxt = nxt; ret.mode = 3;
	return ret;
}

int Memory(int N, int M) {
	Cont c = num2cont(M);
	if(c.pos + 1 > N || c.pos + 1 <= 0) return 0;
	char x = Get(c.pos + 1);
	if(c.mode == 1){
		if(x == '<' || x == '[') c.height++;
		else c.height--;
		if(c.height < 0) return -2;
		if(c.pos + 1 == N){
			if(c.height != 0) return -2;
			return cont2num(G(0, 0, 0));
		}
		else return cont2num(F(c.pos + 1, c.height));
	}
	if(c.mode == 2){
		if(x == '<' || x == '[') return cont2num(G(c.pos + 1, c.count, c.kth));
		if(x == '>' || x == ']'){
			if(c.count == c.kth){
				return cont2num(H(c.pos - 1, 1, x == ']', c.kth + 1)); 
			}
			else return cont2num(G(c.pos + 1, c.count + 1, c.kth));
		}
	}
	if(c.mode == 3){
		if(x == '>' || x == ']') return cont2num(H(c.pos - 1, c.height + 1, c.opB, c.nxt));
		if(x == '<' || x == '['){
			if(c.height == 1){
				if(c.opB && x == '<') return -2;
				if(!c.opB && x == '[') return -2;
				if(c.nxt == N / 2) return -1;
				return cont2num(G(0, 0, c.nxt));
			}
			else{
				return cont2num(H(c.pos - 1, c.height - 1, c.opB, c.nxt));
			}
		}
	}
	assert(false);
}
