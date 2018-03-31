#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int b[100001];
int main(int argc, const char * argv[]) {
    
    int n,h,ans = 0;
    
    scanf("%d %d",&n,&h);
    
    int ma = 0;
    
    for(int i=0,a;i<n;i++){
        scanf("%d %d",&a,&b[i]);
        if(ma < a)  ma = a;
    }
    
    sort(b,b+n);
    
    for(int i=n-1; i>=0;i--){
        if(ma > b[i]) break;
        
        h = h - b[i];
        ans++;
        if(h<=0){
            printf("%d\n",ans);
            return 0;
        }
    }
    
    if(h%ma != 0) ans+=1; //가장큰 a칼로 hp가 나누어 떨어지지 않는 경우 한 번더 찔러야함
    
    printf("%d\n",ans + h/ma);
    
    return 0;
}


/*
 
 
 사용가능한 칼 중 최대값을 구하고 
 
 그 값 보다 큰 재사용불가 칼을 모두 사용한다.
 
 그 이후에 남은 에너지값은 사용가능한 칼 중 최대값으로 처리한다.
 

*/