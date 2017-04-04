#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<cmath>
#include<queue>
#include<cstring>
#include<stack>
using namespace std;

const int maxn = 3030;
const int N = 1E7 + 7;
typedef long long LL;
const LL mo = 1000000007;

int n,m,Ans,A[maxn],B[maxn],pos[maxn],Fac[N],Inv[N],f[N];

inline int Mul(const LL &x,const LL &y) {return x * y % mo;}
inline int Add(const int &x,const int &y) {return x + y < mo ? x + y : x + y - mo;}
inline int C(const int &N,const int &M) {return Mul(Fac[N],Mul(Inv[M],Inv[N - M]));}

int ksm(int x,int y)
{
	int ret = 1;
	for (; y; y >>= 1)
	{
		if (y & 1) ret = Mul(ret,x);
		x = Mul(x,x);
	}
	return ret;
}

void Pre_Work()
{
	Fac[0] = 1; for (int i = 1; i <= n; i++) Fac[i] = Mul(Fac[i - 1],i);
	Inv[n] = ksm(Fac[n],mo - 2); for (int i = n - 1; i >= 0; i--) Inv[i] = Mul(Inv[i + 1],i + 1);
	f[0] = f[1] = 1; for (int i = 2; i <= n; i++) f[i] = Add(Mul(i - 1,f[i - 2]),f[i - 1]);
}

bool Check(int N)
{
	for (int i = 1; i <= N; i++)
	{
		if (A[i] == B[i]) continue;
		if (A[pos[A[i]]] != B[i]) return 0;
	}
	return 1;
}

int main()
{
	#ifdef DMC
		freopen("DMC.txt","r",stdin);
	#else
		freopen("ya.in","r",stdin);
		freopen("ya.out","w",stdout);
	#endif
	
	cin >> n >> m; Pre_Work();
	if (n < m) {cout << 0 << endl; return 0;}
	for (int i = 1; i <= m; i++) scanf("%d",&B[i]),pos[B[i]] = i;
	for (int i = 0; i <= m; i++)
	{
		A[i] = B[i]; sort(A + 1,A + i + 1); if (!Check(i)) continue;
		int x = m - i <= n - m ? C(n - m,m - i) : 0;
		int y = i + 2 * (m - i) <= n ? f[n - i - 2 * (m - i)] : 0;
		Ans = Add(Ans,Mul(x,y));
	}
	cout << Ans << endl;
	return 0;
}
