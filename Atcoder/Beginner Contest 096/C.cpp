#include <cstdio>
#include <queue>
using namespace std;
char board[51][51];
int dx[4]={1,-1,0,0};
int dy[4]={0,0,-1,1};
bool check[51][51];
queue<pair<int,int>> q;
int n,m;
void bfs(int i,int j){
    
    q.push({i,j});
    check[i][j]=true;
    
    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        
        for(int k=0;k<4;k++){
            int nx = x + dx[k];
            int ny = y + dy[k];
            if(0<=nx && nx < n && 0<= ny && ny<m){
                if(board[nx][ny]=='#' && !check[nx][ny]){
                    q.push({nx,ny});
                    check[nx][ny] = true;
                }
            }
        }
    }
}

int main(int argc, const char * argv[]) {
    
    scanf("%d %d",&n,&m);
    
    for(int i=0;i<n;i++){
        scanf("%s",board[i]);
    }
    
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            
            if(check[i][j]) continue;
            if(board[i][j]=='.') continue;
            int cnt = 0;
            for(int k=0;k<4;k++){
                int nx = i + dx[k];
                int ny = j + dy[k];
                if(0<=nx && nx < n && 0<= ny && ny<m){
                    if(board[nx][ny]=='#')cnt++;
                }
            }
            
            if(cnt>=1) bfs(i,j);
        }
    }
    
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(!check[i][j] && board[i][j]=='#'){
                printf("No\n");
                return 0;
            }
        }
    }
    printf("Yes\n");
    return 0;
}

/*
 
 검은색자리에서 인접한 위치면 칠 할 수 있는 경우이다.
 
 즉 자기혼자 있는 경우에는 칠할 수 없다.
 
 현재위치가 검은색이고 상하좌우중 하나이상 검은색이라면 칠할 수 있고,
 
 현재위치가 검은색인데 상하좌우에 검은색이 존재하지않는다면 그위치는 칠할 수 없고 답은 No이다.
 
 2중포문과 if문내의 5개값을 비교하는 것으로 끝나지만,
 
 bfs로구현했다.
 
 */
