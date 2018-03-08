#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int board[2][101];
int d[2][101];
int n;
int go(int x,int y){
    
    if(x>1 || y>n-1) return -987654321;
    
    if(x==1 && y==n-1) return board[x][y];
    
    int &ans = d[x][y];
    if(ans != -1) return ans;
    ans = 0;
    ans = max(go(x+1,y), go(x,y+1)) + board[x][y];
    
    return ans;
    
}
int main(int argc, const char * argv[]) {
   
    
    scanf("%d",&n);
    
    for(int i=0;i<2;i++){
        for(int j=0;j<n;j++){
            scanf("%d",&board[i][j]);
        }
    }
    
    memset(d,-1,sizeof(d));
    
    printf("%d\n",go(0,0));
    
    return 0;
}
