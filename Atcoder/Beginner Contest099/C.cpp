#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

int state[13];
int d[100001];
int go(int x){
    if(x==0) return 0;
    if(x==1 || x==6 || x==9) return 1;
    int &ans = d[x];
    if(ans!=-1)return ans;
    ans = 987654321;
    for(int i=0;i<=12;i++){
        if(x-state[i]>=0){
            ans = min(ans,go(x-state[i])+1);
        }
    }
    return ans;
}



int main(int argc, const char * argv[]) {
    
    int n;
    
    scanf("%d",&n);
    
    state[0] = 1;
    state[1] = 6;
    state[8] = 9;
    for(int i=2;i<=7;i++) state[i] = state[i-1]*6;
    for(int i=9;i<=12;i++) state[i] = state[i-1]*9;
    memset(d,-1,sizeof(d));
    printf("%d\n",go(n));
    return 0;
}

/*
 13가지 경우에 대해 dp점화식 d[i] : i를 만들 수 있는 최소 횟수
 13가지 경우에 대해서는 미리구해놓음. 
 */
