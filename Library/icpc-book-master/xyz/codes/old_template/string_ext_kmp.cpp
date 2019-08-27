///////////////////////////
//
// ext_kmp
//
///////////////////////////
for (next[1]=0,i=2,k=1;i<=l;i++)
{
	next[i]=max(0,min(next[i-k+1],k+next[k]-i));
	while (S[i+next[i]]==S[next[i]+1])	next[i]++;
	if (i+next[i]>k+next[k])	k=i;
}
