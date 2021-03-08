template<class flow=long long>
class dinic{
public:
    struct edge{
        int to;
        flow cap;
        int rev;
        edge(){}
        edge(int to, long long cap, int rev):to(to), cap(cap), rev(rev){}
    };
    int n;
    vector<vector<edge>> E;
    vector<int> level;
    vector<size_t> itr;
    flow FLOW_INF;
    const int LEVEL_INF = 1e9;

    dinic(int N, flow inf = numeric_limits<flow>::max() / 2):n(N), E(N), level(N), itr(N), FLOW_INF(inf){}

    void add_edge(int from, int to, flow cap, flow cap2=0){
        E[from].emplace_back(to, cap, E[to].size());
        E[to].emplace_back(from, cap2, E[from].size()-1);
    }

    void bfs(int s){
        queue<int> que;
        level[s] = 0;
        que.push(s);
        while(que.size()){
            int d = que.front();
            que.pop();
            for(size_t i=0;i<E[d].size();++i){
                if(E[d][i].cap > 0 and level[d] + 1 < level[E[d][i].to]){
                    level[E[d][i].to] = level[d] + 1;
                    que.push(E[d][i].to);
                }
            }
        }
    }

    flow dfs(int p, int to, flow f){
        if(p==to)return f;
        for(size_t i=itr[p];i<E[p].size();++i){
            itr[p] = i;
            edge &e = E[p][i];
            if(e.cap > 0 && level[p] < level[e.to]){
                flow d = dfs(e.to, to, min(f, e.cap));
                if(d){
                    e.cap -= d;
                    E[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }

    flow max_flow(int s, int t){
        flow res = 0;
        while(true){
            fill(level.begin(), level.end(), LEVEL_INF);
            bfs(s);
            if(level[t]==LEVEL_INF)return res;
            fill(itr.begin(), itr.end(), 0);
            flow f = dfs(s, t, FLOW_INF);
            while(f){
                res += f;
                f = dfs(s, t, FLOW_INF);
            }
        }
    }
};
