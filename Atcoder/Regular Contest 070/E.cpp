#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;

int n;

int l[405],r[405];
int d[405][405];

int go(int now, int leftx){
    
    if(now == n+1) return 0;
    
    int &ans = d[now][leftx];
    if(ans!=-1) return ans;
    
    int rightx = leftx+r[now-1]-l[now-1];
    
    ans = 987654321;
    
    for(int left=1;left<=400;left++){
        int right = left + r[now] - l[now];
        
        if(right < leftx || rightx < left) continue;
        ans = min(ans, go(now+1,left) + abs(left-l[now]));
    }
    return ans;
}

int main(){
    
    scanf("%d",&n);
    if(n>=401) return 0;

    for(int i=1;i<=n;i++){
        scanf("%d %d",&l[i],&r[i]);
    }
    memset(d,-1,sizeof(d));
    int res = 987654321;
    for(int i=1;i<=400;i++){
        res = min(res,go(1,i));
    }
    printf("%d\n",res);
    return 0;
}

/*
 
 i번째 직사각형을 움직여서 i-1 번째 직사각형범위에 포함되는지 체크
 
 idx와 이전의  left값만 알면 오른쪽값은 idx-1의 값으로 구할 수 있다.
 
 첫번째 직사각형도 1~400구간에 이동시켜 확인.
 
*/