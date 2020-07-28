// Ivan Carvalho
// Solution to https://dmoj.ca/problem/fastbit
#include <cstdio>
int setbits(unsigned long long w)
{
    w -= (w >> 1) & 0x5555555555555555ULL;
    w = (w & 0x3333333333333333ULL) + ((w >> 2) & 0x3333333333333333ULL);
    w = (w + (w >> 4)) & 0x0f0f0f0f0f0f0f0fULL;
    return (w * 0x0101010101010101ULL) >> 56;
}
int main(){
	return 0;
}