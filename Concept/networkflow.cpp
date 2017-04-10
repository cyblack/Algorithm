#include <iostream>
#include <vector>
#include <queue>
#include <cstdio>
#define INF 987654321
using namespace std;

struct network_flow{
    
    struct Edge{
        int to,cap;
        Edge*rev;
        Edge(int t1,int c1) : to(t1), cap(c1) {}
    };
    
    int n,S,E;
    
    vector<vector<Edge*>> graph;
    vector<pair<int,int>> from;
    
    network_flow(int size,int source,int sink): n(size),S(source),E(sink){
        graph.resize(n);
        from.resize(n);
    }
    
    void add_edge(int u,int v,int c){
        
        Edge * ori = new Edge(v,c);
        Edge * rev = new Edge(u,0);
        
        ori->rev = rev;
        rev->rev = ori;
        
        graph[u].push_back(ori);
        graph[v].push_back(rev);
    }
    
    void add_edge_from_source(int v,int c){
        add_edge(S,v,c);
    }
    
    void add_edge_from_sink(int v, int c){
        add_edge(v,E,c);
    }
    
    int flow(){
        
        int total = 0;
        
        while(1){
            
            fill(from.begin(),from.end(),make_pair(-1,-1));
            queue<int> q;
            
            q.push(S);
            
            while(!q.empty()){
                
                int curr = q.front();
                q.pop();
                
                for(int i=0;i<graph[curr].size();i++){
                    
                    struct Edge * e = graph[curr][i];
                    int next = e->to;
                    
                    if(from[next].first == -1 && e->cap >0){
                        from[next] = {curr,i};
                        q.push(next);
                    }
                }
            }
            
            if(from[E].first == -1) break;
            int x = E;
            int f = 987654321;
            
            while(x!=S){
                
                if(f > graph[from[x].first][from[x].second]->cap){
                    f = graph[from[x].first][from[x].second]->cap;
                }
                x = from[x].first;
            }
            x = E;
            
            while(x!=S){
                graph[from[x].first][from[x].second]->cap -= f;
                graph[from[x].first][from[x].second]->rev->cap += f;
                x=from[x].first;
            }
            total+=f;
        }
        return total;
    }
};