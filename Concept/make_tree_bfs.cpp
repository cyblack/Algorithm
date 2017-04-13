#include <iostream>
#include <vector>
#include <queue>
#include <cstdio>

using namespace std;
int N;
vector<int> adj[10001];
vector<int> child[1001];
int parent[1001];

void make_tree(int root){
    
    vector<bool> visited(N,false);
    queue<int> q;
    
    visited[root] = true;
    q.push(root);
    
    while(!q.empty()){
        
        int curr = q.front();
        q.pop();
        
        for(int next : adj[curr]){
            if(!visited[next]){
                visited[next]=true;
                q.push(next);
                child[curr].push_back(next);
                parent[next]=curr;
            }
        }
    }
}

/*

 그래프를 트리로 바꿀때, bfs를 이용해서 만들어준다.
 
 child[x][] : x의 자식들을 저장 (여러개)
 parent[x] : x의 부모를 저장 (1개)
 
*/