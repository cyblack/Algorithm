

#include <cstdio>
#include <algorithm>
using namespace std;

int a[100001];
int abs(int x){ return x > 0 ? x : -x;}
int main(int argc, const char * argv[]) {
   
    int n;
    scanf("%d",&n);
    
    for(int i=0;i<n;i++) scanf("%d",&a[i]);
    
    
    sort(a,a+n);
    int diff = 2100000000;
    
    if(n&1){
        int l = a[n-1]/2;
        int r = a[n-1]/2+1;
        for(int i=0;i<n-1;i++){
        
            if(abs(l-diff) > abs(a[i]-l)){
                diff =a[i];
            }
            if(abs(r-diff) > abs(a[i]-r)){
                diff =a[i];
            }
            
        }
        printf("%d %d\n",a[n-1],diff);
        
    }else{
        int val = a[n-1]/2;
        for(int i=0;i<n-1;i++){
            if(abs(val-diff) > abs(a[i]-val)){
                diff =a[i];
            }
        }
        printf("%d %d\n",a[n-1],diff);
        
    }
    
    return 0;
}


/*
 
 (n+1)Cr > nCr 이다. (n+1)Cr = nCr + nC(r-1)
 
 파스칼 삼각형을 생각해보면 NCR
 
 N이 가장 클 때가 값이 클 확률이 높고
 
 가운데에 가까울 수록 값이 커진다(정규분포그래프형태)
 
 홀 짝으로 나눈 이유는
 
 홀수일때는 0추가 때문에 가운데 값은 2개이다.
 
 짝수일때는 0추가 되서 홀수 이다.
 
 즉, 가운데 값과 가까운 수를 찾으면 된다.
 
 */
