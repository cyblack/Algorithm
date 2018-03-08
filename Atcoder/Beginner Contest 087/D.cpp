
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

vector<pair<int,int>> adj[100001];
int dist[100001];
bool ok[100001];

struct node{
    int l,r,d;
}query[200001];

void dfs(int x,int d){
    
    ok[x] = true;
    dist[x] = d;
    int sz = (int)adj[x].size();
    for(int i=0;i<sz;i++){
       
        int next = adj[x][i].first;
        if(!ok[next]){
            dfs(next,d+adj[x][i].second);
        }
    }
}
int main(int argc, const char * argv[]) {
    
    
    int n,m;
    
    scanf("%d %d",&n,&m);
    
    for(int i=0,x,y,z;i<m;i++){
        scanf("%d %d %d",&x,&y,&z);
        
        adj[x].push_back({y,z});
        adj[y].push_back({x,-z});
        query[i].l = x;
        query[i].r = y;
        query[i].d = z;
    }
    
    for(int i=1;i<=n;i++){
        if(!ok[i]){
            dfs(i,0);
        }
    }
    
    for(int i=0;i<m;i++){
        if(query[i].d != dist[query[i].r]-dist[query[i].l]){
            printf("No\n");
            return 0;
        }
    }
    
    printf("Yes\n");
    
    return 0;
}


/*
 
    그래프를 만든 후 임의의 정점에 대해 값을 결정한다.
    값을 결정하면 다른 정점의 값들도 결정된다.
    결정된 값과 처음에 들어온 값들과 비교
 
 */
