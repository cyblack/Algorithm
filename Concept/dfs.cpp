#include <iostream>
#include <vector>
#include <queue>
#include <cstdio>
using namespace std;
bool check[1001];
queue<int> q;
vector<int> a[1001];

void dfs(int x){
    
    check[x]=true;
    for(int i=0;i<a[x].size();i++){
        int next = a[x][i];
        if(!check[next]) dfs(next);
    }
}

int main(int argc, const char * argv[]) {
    
    int n,m,v;
    
    scanf("%d %d %d",&n,&m,&v);
    
    for(int i=0;i<m;i++){
        int x,y;
        scanf("%d %d",&x,&y);
        a[x].push_back(y);
        a[y].push_back(x);
    }
    dfs(v);
    return 0;
}


