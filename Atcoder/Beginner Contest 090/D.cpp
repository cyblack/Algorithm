
#include <cstdio>

int main(int argc, const char * argv[]) {
   
    
    int n,k;
    
    scanf("%d %d",&n,&k);
    
    long long ans = 0;
    
    if(k==0){
        ans = (long long)n*n;
        printf("%lld\n",ans);
        return 0;
    }
    
    ans = (long long)(n-k)*(n-k+1)/2;
    
    
    for(int i=k+1;i<n;i++){
        
        int cnt = n-i;
        
        int mul = cnt/i;
        int mod = cnt%i;
        
        ans += (long long)mul * (i-k);
        if(mod >= k)
            ans += mod - k+1;
        
    }
    
    printf("%lld\n",ans);
    
    return 0;
}


/*
 
 (1,1) (1,2) (1,3) (1,4)
 
 (2,1) (2,2) (2,3) (2,4)
 
 (3,1) (3,2) (3,3) (3,4)
 
 (4,1) (4,2) (4,3) (4,4)
 
 대각선을 긋고 위쪽을 생각해보면 
 
 -> 방향으로 (x,y)에 대해 y값에 상관없이 x%y는 x이다.
 
 아래쪽을 생각해보면
 
 아래 방향으로 (x,y)에대해 x%y값이 1,2,3...y-1,0 형태로 반복된다.
 
 그리고 나머지 값이 k보다 크려면 최소한 k+1로 나누어야한다.
 
 **longlong계산에 주의
 
*/
