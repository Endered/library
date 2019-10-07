struct edge{
	int to;
	long long cap;
	int rev;
	edge(){}
	edge(int to, long long cap, int rev):to(to), cap(cap), rev(rev){}
};

class dinic{
	public:
		int n;
		vector<vector<edge>> E;
		vector<int> level;
		vector<int> itr;
		int INF;

		dinic(int N, long long inf=(int)1e9):n(N), E(N), level(N, inf), itr(N), INF(inf){}

		void add_edge(int from, int to, long long cap){
			E[from].emplace_back(to, cap, E[to].size());
			E[to].emplace_back(from, 0, E[from].size()-1);
		}

		void bfs(int s){
			queue<int> que;
			level[s] = 0;
			que.push(s);
			while(que.size()){
				int d = que.front();
				que.pop();
				for(int i=0;i<E[d].size();++i){
					if(E[d][i].cap > 0&&level[d] < level[E[d][i].to]){
						level[E[d][i].to] = level[d] + 1;
						que.push(E[d][i].to);
					}
				}
			}
		}

		LL dfs(int p, int to, LL f){
			if(p==to)return f;
			for(int i=itr[p];i<E[p].size();++i){
				itr[p] = i;
				edge &e = E[p][i];
				if(e.cap > 0 && level[p] < level[e.to]){
					LL d = dfs(e.to, to, min(f, e.cap));
					if(d){
						e.cap -= d;
						E[e.to][e.rev].cap += d;
						return d;
					}
				}
			}
			return 0;
		}

		LL max_flow(int s, int t){
			LL res = 0;
			while(true){
				fill(level.begin(), level.end(), INF);
				bfs(s);
				if(level[t]==INF)return res;
				fill(itr.begin(), itr.end(), 0);
				LL f = dfs(s, t, INF);
				while(f){
					res += f;
					f = dfs(s, t, INF);
				}
			}
		}
};

