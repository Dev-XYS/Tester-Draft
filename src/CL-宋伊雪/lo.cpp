#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<cmath>
#include<queue>
#include<cstring>
#include<stack>
using namespace std;

const int maxm = 505;
const int maxn = 1E5 + 10;
const int INF = 1E9 + 233;
typedef long long LL;
typedef double DB;

struct Point{
	LL x,y; Point(){}
	Point(LL x,LL y): x(x),y(y){}
	Point operator - (const Point &B) {return Point(x - B.x,y - B.y);}
	bool operator < (const Point &B) const
	{
		if (x < B.x) return 1;
		if (x > B.x) return 0;
		return y < B.y;
	}
	bool operator == (const Point &B) const {return x == B.x && y == B.y;}
	bool operator != (const Point &B) const {return x != B.x || y != B.y;}
}A[maxn],B[maxm],stk[maxn*2];
typedef Point Vector;

int n,m,Ans,Min,Max,tp,cur,f[maxm][maxm],g[maxm][maxm];
bool ok[maxm][maxm];

inline DB Cross(const Vector &v1,const Vector &v2) {return (DB)(v1.x)*(DB)(v2.y)-(DB)(v2.x)*(DB)(v1.y);}

int getint()
{
	char ch = getchar(); int ret = 0,a = 1;
	while (ch < '0' || '9' < ch)
	{
		if (ch == '-') a = -1;
		ch = getchar();
	}
	while ('0' <= ch && ch <= '9')
		ret = ret * 10 + ch - '0',ch = getchar();
	return ret * a;
}

void Check(int k)
{
	Vector v;
	for (int i = 1; i <= tp; i++)
	{
		v = stk[i] - B[k];
		if (!v.x && !v.y) continue;
		else break;
	}
	for (int i = 1; i <= tp; i++)
	{
		Vector now = stk[i] - B[k];
		if (!now.x && !now.y) continue;
		if (Cross(v,now) < 0) v = now;
	}
	for (int i = 1; i <= tp; i++)
	{
		Vector now = stk[i] - B[k];
		if (!now.x && !now.y) continue;
		if (Cross(v,now) < 0) return;
	}
	for (int i = 1; i <= m; i++)
	{
		if (i == k) continue;
		Vector now = B[i] - B[k];
		if (Cross(v,now) <= 0) ok[k][i] = 1;
	}
}

void SPJ()
{
	for (int i = 2; i <= n; i++)
		if (A[i] != A[i - 1]) return;
	for (int i = 1; i <= m; i++)
		if (A[1] == B[i]) {cout << 1 << endl; exit(0);}
}

void Pre_Work()
{
	for (int i = 1; i <= n; i++)
	{
		int x = getint(),y = getint();
		A[i] = Point(x,y); Min = min(Min,x); Max = max(Max,x);
	}
	for (int i = 1; i <= m; i++)
	{
		int x = getint(),y = getint();
		B[i] = Point(x,y);
	}
	sort(A + 1,A + n + 1); stk[tp = 1] = A[1];
	for (int i = 2; i <= n; i++)
	{
		while (tp > 1 && Cross(A[i] - stk[tp - 1],stk[tp] - stk[tp - 1]) >= 0)
			--tp; stk[++tp] = A[i];
	}
	cur = tp;
	for (int i = n - 1; i; i--)
	{
		while (tp > cur && Cross(A[i] - stk[tp - 1],stk[tp] - stk[tp - 1]) >= 0)
			--tp; stk[++tp] = A[i];
	}
	SPJ(); sort(B + 1,B + m + 1); Ans = maxm;
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= m; j++)
			f[i][j] = g[i][j] = maxm;
}

int main()
{
	#ifdef DMC
		freopen("DMC.txt","r",stdin);
	#else
		freopen("lo.in","r",stdin);
		freopen("lo.out","w",stdout);
	#endif
	
	Min = INF; Max = -INF;
	n = getint(); m = getint(); Pre_Work();
	for (int i = 1; i <= m; i++) Check(i);
	for (int i = 1; i <= m; i++)
	{
		if (B[i].x > Min) break; f[i][i] = 0;
		for (int j = i + 1; j <= m; j++)
			for (int k = i; k < j; k++)
				if (ok[k][j]) f[i][j] = min(f[i][j],f[i][k] + 1);
	}
	for (int i = m; i; i--)
	{
		if (B[i].x < Max) break; g[i][i] = 0;
		for (int j = i - 1; j; j--)
			for (int k = i; k > j; k--)
				if (ok[k][j]) g[i][j] = min(g[i][j],g[i][k] + 1);
	}
	for (int i = 1; i <= m; i++)
		for (int j = i + 1; j <= m; j++)
			Ans = min(Ans,f[i][j] + g[j][i]);
	cout << (Ans == maxm ? -1 : Ans) << endl;
	return 0;
}
