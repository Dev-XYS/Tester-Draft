#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<cmath>
#include<queue>
#include<cstring>
#include<stack>
#define min(a,b) ((a) < (b) ? (a) : (b))
#define max(a,b) ((a) > (b) ? (a) : (b))
using namespace std;

const int maxn = 155;
const int maxm = 5005;
const int INF = ~0U>>1;

struct data{
	int x,y,z; data(){}
	data(int x,int y,int z): x(x),y(y),z(z){}
	bool operator < (const data &B) const {return y < B.y;}
};

struct Point{
	int x,y,z; Point(){}
	Point(int x,int y,int z): x(x),y(y),z(z){}
	bool operator < (const Point &B) const {return z > B.z;}
};

int n,m,q,Max,dis[maxm][maxn],Ans[maxm];
bool vis[maxm][maxn];

vector <data> v[maxn],task[maxn],g[maxm];
priority_queue <Point> Q; vector <int> from[maxn];

void Dijkstra(int s)
{
	if (!task[s].size()) return;
	for (int i = 0; i < task[s].size(); i++)
		Max = max(Max,task[s][i].y); Max = min(Max,n - 1);
	for (int i = 0; i < v[s].size(); i++)
	{
		data now = v[s][i];
		g[0].push_back(data(now.z,now.y,1));
	}
	for (int i = 0; i <= m; i++)
		for (int j = 0; j <= Max; j++)
			dis[i][j] = INF,vis[i][j] = 0;
	Q.push(Point(0,0,0)); dis[0][0] = 0;
	while (!Q.empty())
	{
		Point k = Q.top(); Q.pop();
		if (vis[k.x][k.y]) continue; vis[k.x][k.y] = 1;
		for (int i = 0; i < g[k.x].size(); i++)
		{
			data e = g[k.x][i];
			if (k.y + e.z > Max) continue;
			if (dis[e.x][k.y + e.z] > dis[k.x][k.y] + e.y)
			{
				dis[e.x][k.y + e.z] = dis[k.x][k.y] + e.y;
				Q.push(Point(e.x,k.y + e.z,dis[e.x][k.y + e.z]));
			}
		}
	}
	for (int i = 1; i <= m; i++)
		for (int j = 2; j <= Max; j++)
			dis[i][j] = min(dis[i][j],dis[i][j - 1]);
	for (int i = 0; i < task[s].size(); i++)
	{
		data now = task[s][i];
		for (int j = 0; j < from[now.x].size(); j++)
			Ans[now.z] = min(Ans[now.z],dis[from[now.x][j]][now.y]);
	}
	g[0].clear(); Max = 0;
}

int getint()
{
	char ch = getchar(); int ret = 0;
	while (ch < '0' || '9' < ch) ch = getchar();
	while ('0' <= ch && ch <= '9')
		ret = ret * 10 + ch - '0',ch = getchar();
	return ret;
}

int main()
{
	#ifdef DMC
		freopen("DMC.txt","r",stdin);
	#else
		freopen("ha.in","r",stdin);
		freopen("ha.out","w",stdout);
	#endif
	
	n = getint(); m = getint(); q = getint();
	for (int i = 1; i <= m; i++)
	{
		int x = getint(),y = getint(),z = getint();
		v[x].push_back(data(y,z,i)); from[y].push_back(i);
	}
	for (int i = 1; i <= n; i++)
	{
		sort(v[i].begin(),v[i].end());
		if (!v[i].size()) continue;
		for (int j = 0; j < v[i].size() - 1; j++)
		{
			data a = v[i][j],b = v[i][j + 1];
			g[a.z].push_back(data(b.z,b.y - a.y,0));
		}
	}
	for (int i = 1; i <= n; i++)
		for (int j = 0; j < v[i].size(); j++)
		{
			data a = v[i][j];
			for (int k = 0; k < v[a.x].size(); k++)
			{
				data b = v[a.x][k]; if (b.y <= a.y) continue;
				g[a.z].push_back(data(b.z,b.y,1)); break;
			}
		}
	for (int i = 1; i <= q; i++)
	{
		int x = getint(),y = getint(),z = getint();
		task[x].push_back(data(y,z,i)); Ans[i] = INF;
	}
	for (int i = 1; i <= n; i++) Dijkstra(i);
	for (int i = 1; i <= q; i++) printf("%d\n",Ans[i] == INF ? -1 : Ans[i]);
	return 0;
}
