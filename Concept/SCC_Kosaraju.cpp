#include <iostream>
#include <stack>
#include <vector>
using namespace std;
vector<int> a[101];
vector<int> ar[101];
bool c[101];
stack<int> s;
int component[10001];


/*

    방향그래프에서 cycle을 없애기 위한 알고리즘
 
*/


void dfs(int x){
    
    c[x]=true;
    for(int next : a[x]) if(!c[next]) dfs(next);
    s.push(x);//탐색이 끝나는 순서대로 스택에 집어넣습니다.
}
void dfs_rev(int x, int cn) {
    c[x] = true;
    component[x] = cn;
    for (int next : ar[x]) if(!c[next]) dfs_rev(next,cn);
}
int main(int argc, const char * argv[]) {
    
    
    int n,m;
    
    scanf("%d %d",&n,&m);
    
    while(m--){
        
        int u,v;
        scanf("%d %d",&u,&v);
        
        a[u].push_back(v); //일반 그래프
        ar[v].push_back(u); //간선을 뒤집은 그래프
    }
    
    for(int i=1;i<=n;i++){
        if(!c[i]) dfs(i);
    }
    
    memset(c,false,sizeof(c));
    int cnt =0;
    while(!s.empty()){ //가장 탐색이 마지막에 끝난 점부터시작
        if(component[s.top()]==0){
            dfs_rev(s.top(),++cnt); //component번호를 1부터 매긴다.
        }
        s.pop();
    }
    return 0;
}
