
#include <iostream>
#include <string>
#include <cstdio>
#include <queue>
using namespace std;
string map[51];
int check[51][51];
queue<pair<int,int>> q;
int dx[4] = {0,0,-1,1};
int dy[4] = {1,-1,0,0};
int main(int argc, const char * argv[]) {
   
    
    int n,m;
    
    scanf("%d %d",&n,&m);
    
    for(int i=0;i<n;i++){
        cin >> map[i];
    }
    int cnt = 0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(map[i][j]=='.'){
                cnt++;
            }
        }
    }
    
    check[0][0]=1;
    q.push({0,0});
    
    while(!q.empty()){
        
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        if(x == n-1 && y==m-1) break;
        for(int k=0;k<4;k++){
            int nx = x + dx[k];
            int ny = y + dy[k];
            
            if( 0<=nx && nx< n && 0<=ny && ny<m){
                if(map[nx][ny]=='.' && check[nx][ny]==0){
                    q.push({nx,ny});
                    check[nx][ny] = check[x][y] + 1;
                }
            }
        }
    }
    
    int sz = check[n-1][m-1];
    
    if(sz==0) printf("-1\n");
    else printf("%d\n",cnt-sz);
    
    
    return 0;
}


/*

 흰->검으로 바꾸는 최대 횟수를 찾는 것이므로
 
 시작점에서 도착점까지 갈 수 있는지 확인 후(bfs로 최단거리)
 
 총 흰색개수에서 빼주면 된다.
 
 
*/