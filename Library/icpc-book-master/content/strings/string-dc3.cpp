/**
 * Author:
 * Description: Linear-time SA+LCP+Tree
 */

const int N=1000010;
char s[N];
int *h;
 
namespace SuffixArray {
 
const int N=1000010;
 
int sa[N],rk[N],ht[N];
bool t[N<<1];
 
bool islms(const int i,const bool *t) { /// start-hash
	return i>0&&t[i]&&!t[i - 1];
} /// end-hash
 
template<class T>
inline void sort(T s,int *sa,const int len,const int sz,const int sigma,
					bool *t,int *b,int *cb,int *p) { /// start-hash
	memset(b,0,sizeof(int)*sigma);
	memset(sa,-1,sizeof(int)*len);
	rep(i,0,len) b[(int)s[i]]++;
	cb[0]=b[0];
	rep(i,1,sigma) cb[i]=cb[i-1]+b[i];
	per(i,0,sz) sa[--cb[(int)s[p[i]]]]=p[i];
	rep(i,1,sigma) cb[i]=cb[i-1]+b[i-1];
	rep(i,0,len) if (sa[i]>0&&!t[sa[i]-1]) sa[cb[(int)s[sa[i]-1]]++]=sa[i]-1;
	cb[0]=b[0];
	rep(i,1,sigma) cb[i]=cb[i-1]+b[i];
	per(i,0,len) if (sa[i]>0&&t[sa[i]-1]) sa[--cb[(int)s[sa[i]-1]]]=sa[i]-1;
} /// end-hash
 
template<class T>
inline void sais(T s,int *sa,const int len,bool *t,int *b,int *b1,
				const int sigma) { /// start-hash
	int p=-1,*cb=b+sigma;
	t[len-1]=1;
	per(i,0,len-1) t[i]=s[i]<s[i+1]||(s[i]==s[i+1]&&t[i+1]);
	int sz=0,cnt=0;
	rep(i,1,len) if (t[i]&&!t[i-1]) b1[sz++]=i;
	sort(s,sa,len,sz,sigma,t,b,cb,b1);
	sz=0;
	rep(i,0,len) if (islms(sa[i],t)) sa[sz++]=sa[i];
	rep(i,sz,len) sa[i]=-1;
	rep(i,0,sz) {
		int x=sa[i];
		rep(j,0,len) {
			if (p==-1||s[x+j]!=s[p+j]||t[x+j]!=t[p+j]) {
				cnt++; p=x;
				break;
			} else if (j>0&&(islms(x+j,t)||islms(p+j,t))) {
				break;
			}
		}
		sa[sz+(x>>=1)]=cnt-1;
	}
	for (int i=len-1,j=len-1;i>=sz;i--) if (sa[i]>=0) sa[j--]=sa[i];
	int *s1=sa+len-sz,*b2=b1+sz;
	if (cnt<sz) sais(s1,sa,sz,t+len,b,b1+sz,cnt);
	else rep(i,0,sz) sa[s1[i]]=i;
	rep(i,0,sz) b2[i]=b1[sa[i]];
	sort(s,sa,len,sz,sigma,t,b,cb,b2);
} /// end-hash
 
template<class T>
inline void getHeight(T s,int n) { /// start-hash
	rep(i,1,n+1) rk[sa[i]]=i;
	int j=0,k=0;
	for (int i=0;i<n;ht[rk[i++]]=k)
		for (k?k--:0,j=sa[rk[i]-1];s[i+k]==s[j+k];k++);
} /// end-hash
 
template<class T>
inline void init(T s,const int len,const int sigma) { /// start-hash
	sais(s,sa,len,t,rk,ht,sigma);
} /// end-hash
 
inline void solve(char *s,int len) {
	init(s,len+1,124);
	getHeight(s,len);
}
} // namespace SuffixArray
 
 
int n;
 
int stk[N],top,a[N],l[N],r[N],sz[N],par[N];

void build() { /// start-hash
	int top=0;
	h=SuffixArray::ht+1;
	rep(i,1,n) l[i]=r[i]=par[i]=0;
	rep(i,1,n) {
		int k=top;
		while (k>0&&h[stk[k-1]]>h[i]) --k;
		if (k) r[stk[k-1]]=i;
		if (k<top) l[i]=stk[k];
		stk[k++]=i;
		top=k;
	}
	int t=0,rt=stk[0];
	int *q=stk;
	q[t++]=rt;
	rep(i,0,t) {
		int u=q[i]; sz[u]=1;
		if (l[u]) q[t++]=l[u],par[l[u]]=u;
		if (r[u]) q[t++]=r[u],par[r[u]]=u;
	}
}/// end-hash
