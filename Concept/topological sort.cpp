#include <iostream>
#include <vector>
#include <queue>
#include <cstdio>

using namespace std;

vector<int> adj[10001];
int indegree[10001];
queue<int> q;

int main(){
    
    //make graph
    int n;
    
    for(int i=1;i<=n;i++){
        if(indegree[i] == 0){
            q.push(i);
        }
    }
    
    while(!q.empty()){
        
        int curr = q.front();
        q.pop();
        
        for(int i=0;i<adj[curr].size();i++){
            int next = adj[curr][i];
            
            indegree[next]--;
            
            if(indegree[next]==0){
                q.push(next);
            }
        }
        
        
    }
    
    return 0;
}



/*
 
 위상정렬은 싸이클이 없는 방향그래프(DAG)에서 사용가능하다.
 
 예를들어 1->2라고 한다면,
 indegree변수를 두어 indegree[2]++ : 2번 으로 들어가는 방향선이 있다는 것을 알려줌(선행관계 의미)
 
 그리고 indegree가 0인 것 부터 큐에넣고 BFS를 시작한다.
 bfs내에서는 연결된 곳(next)의 indegree값을 감소시킨다.
 그리고 다시 indegree가 0인값을 큐에 넣어주면서 반복한다.
 

*/