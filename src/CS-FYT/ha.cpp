#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define N 5005
#define Pii pair<int, int>
#define fi first
#define se second
#define mk make_pair
using namespace std;
inline int read(){
	int sum = 0, t = 1; char ch = getchar();
	while(ch < '0' || ch > '9'){ if(ch == '-') t = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9'){ sum = sum * 10 + ch - '0'; ch = getchar(); }
	return sum * t;
}

int n, m, q, deg[N];
int u[N], v[N], w[N];
vector<Pii>in[N], out[N];

int fir[N], nxt[N<<2], to[N<<2], cnt, val[N<<2];

void add(int x, int y, int v){
	nxt[++cnt] = fir[x]; to[cnt] = y; fir[x] = cnt; val[cnt] = v;
	deg[y]++;
}

int f[N][N], bl[N];
bool vis[N][N];

int main(){
	freopen("ha.in", "r", stdin);
	freopen("ha.out", "w", stdout);
	n = read(); m = read(); q = read();
	for(int i = 1; i <= m; i++){
		u[i] = read(), v[i] = read(); w[i] = read();
		out[u[i]].push_back(mk(w[i], i));
		in[v[i]].push_back(mk(w[i], i));
	}
	for(int i = 1; i <= n; i++){
		sort(out[i].begin(), out[i].end()),
		sort(in[i].begin(), in[i].end());
		vector<Pii>::iterator it2 = out[i].begin(), it;
		for(it = in[i].begin(); it != in[i].end(); it++){
			while(it2 != out[i].end () && it2->fi < it->fi) it2++;
			if(it2 != out[i].end()) add(it->se, it2->se, it->fi);
		}
		it = out[i].begin();
		if(it != out[i].end()) it++;
		for(it2 = out[i].begin(); it != out[i].end(); it++, it2++)
			add(it2->se, it->se, 0);
		for(it = out[i].begin(); it != out[i].end(); it++)
			bl[it->se] = i;
	}
	for(; q ; q--){
		int a = read(), b = read(), c = read();
		queue<Pii>q;
		for(int i = 1; i <= m; i++)
			for(int j = 1; j <= c; j++)
				f[i][j] = 0x3f3f3f3f, vis[i][j] = 0;
		for(int i = 0; i < out[a].size(); i++)
			q.push(mk(out[a][i].se, 1)), f[out[a][i].se][1] = 0, vis[out[a][i].se][1] = true;
		while(!q.empty()){
			Pii x = q.front(); q.pop();
			vis[x.fi][x.se] = false;
			for(int i = x.se + 1; i <= c; i++) if(f[x.fi][i] > f[x.fi][x.se])
				f[x.fi][i] = f[x.fi][x.se];
				else break;
			if(x.se == c) continue ;
			for(int i = fir[x.fi]; i ; i = nxt[i]){
				int y = to[i];
				int nw = x.se + (bl[x.fi] != bl[y]);
				if(f[y][nw] > f[x.fi][x.se] + val[i]){
					f[y][nw] = f[x.fi][x.se] + val[i];
					if(!vis[y][nw]) q.push(mk(y, nw)), vis[y][nw] = true;
				}
			}
		}
		int ans = 1e9;
		for(int i = 0; i < in[b].size(); i++)
			ans = min(ans, f[in[b][i].se][c] + in[b][i].fi);
		if(ans == 1e9) puts("-1");
		else printf("%d\n", ans);
	}
}

