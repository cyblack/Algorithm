#include <iostream>
#include <queue>
#include <cstdio>
#include <vector>
using namespace std;

bool check[1001];
queue<int> q;
vector<int> adj[1001];
void bfs(int x){
    
    //큐에 넣을 때 방문했다고 체크해야함
    check[x]=true;
    q.push(x);
    while(!q.empty()){ // 큐에는 지금위치에서 갈 수 있는 점들을 모두 넣음
        
        int now = q.front();
        q.pop();
        for(int i=0;i<adj[now].size();i++){
            int next = adj[now][i];
            if(!check[next]){
                q.push(next);
                check[next]=true;
            }
        }
    }
}

int main(int argc, const char * argv[]) {
    
    int n,m,v;
    
    scanf("%d %d %d",&n,&m,&v);
    
    
    //그래프 만들기
    for(int i=0;i<m;i++){
        int x,y;
        scanf("%d %d",&x,&y);
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    memset(check,false,sizeof(check));
    bfs(v);
    return 0;
}

/*
 시간복잡도
        인접리스트 구현 : O(v+e)
        인접행렬  구현 : O(v^2)
*/
