#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

int board[16][101];
int d[16][2];
int n,m;
int no = -1;

int go(int i,int j){
    
    if(i<=no){
        int last = 0;
        
        if(j==0) {
            for(int k=1;k<m+2;k++) if(board[i][k]) last = k;
            return last;
        }else{
            for(int k=m+1;k>0;k--) if(board[i][k]) last = k;
            return (m+1)-last;
        }
    }
    
    int &ans = d[i][j];
    if(ans!=-1) return ans;
    int dist= -1;
    ans = 987654321;
    
    if(j==0){
        
        for(int k=1;k<m+2;k++) if(board[i][k]) dist = k;
        
        if(dist !=-1) ans = min(go(i-1,0) + dist*2 + 1, go(i-1,1) + (m+1) + 1);
        else ans = go(i-1,0)+1;
        
    }else{
        
        for(int k=m+1;k>0;k--) if(board[i][k]) dist = k;
        
        if(dist !=-1) ans = min(go(i-1,0)+ (m+1) + 1, go(i-1,1) + (m+1-dist)*2 + 1);
        else ans = go(i-1,1)+1;
        
    }
    return ans;
}

int main(int argc, const char * argv[]) {
    
    scanf("%d %d",&n,&m);
    for(int i=0;i<n;i++){
        for(int j=0;j<m+2;j++){
            scanf("%1d",&board[i][j]);
        }
        
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m+2;j++){
            if(board[i][j]==1){
                no = i;
                break;
            }
        }
        if(no!=-1) break;
    }
    if(no==-1) no = n-1;
    memset(d,-1,sizeof(d));
    
    printf("%d\n",go(n-1,0));
    return 0;
}

/*

    d[i][j] : i층에 있고 j==0이면 왼쪽 j==1이면 오른쪽일 때, 최소 이동거리
 
    뒤에 층이 있지만 불이 모두 꺼져 있다면, 올라갈 필요가 없다. -> 그래서 미리 끝낼 층을 계산해둔다.(변수명 no)
 
    그리고 각 층마다 
            왼쪽에 있을 때      -> 방향에서 가장 먼 점까지 거리를 찾은 후에 왼쪽/오른쪽 방향결정
            오른쪽에 있을 때    <- 방향에서 가장 먼 점까지 거리를 찾은 후에 왼쪽/오른쪽 방향결정
 

*/
