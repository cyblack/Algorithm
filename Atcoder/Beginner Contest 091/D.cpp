#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int c[200001];
int a[200001];
int b[200001];
int n;

int bs(int x){ // x보다 작은 값들이 몇개 있나?  x보다 작은 경우 가능 x보다 크거나 같은 경우 불가능(이분탐색)
    
    int l = 0, r = n-1;
   
    while(l<=r){
        
        int mid = (l+r)/2;
        if(c[mid] < x) l = mid+1;
        else r = mid-1;
    }
    return l;
}

int main(int argc, const char * argv[]) {

    
    scanf("%d",&n);
    
    for(int i=0;i<n;i++) scanf("%d",&a[i]);
    
    
    for(int i=0;i<n;i++) scanf("%d",&b[i]);
    
    int T = 1;
    int ans = 0;
    
    for(int i=0;i<29;i++){
        
        
        for(int j=0;j<n;j++) c[j] = b[j]%(2*T);
        
        int cnt = 0;
        
        sort(c,c+n);
        for(int j=0;j<n;j++){
            int tmp = (a[j]%(2*T));
            cnt += bs(2*T-tmp) - bs(T-tmp);
            cnt += bs(4*T-tmp) - bs(3*T-tmp);
            cnt%=2;
        }
        if(cnt&1) ans |= T;
        T*=2;
    }
    
    printf("%d\n",ans);
    
    return 0;
}


/*
 
 n이 20만 이므로 모든 경우를 따지면 20만*20만이므로 TLE
 각 자리 별로 1의 개수를 카운트한다.
 
 2^0자리에 1의 개수가 몇개인 지 확인하기 위해 T=2^0으로 잡고
 
 배열의 값들을 2*T로 나눈 나머지 값들을 저장한다.
 
 그렇게 되면 0<= a[i] < 2T가 되고 동일한 방법으로 0<= b[i] <2T
 
 즉, 0<= a[i] + b[j] <4T
 
 구간을 살펴보면  4가지가 나온다
 
 0  <= a[i] + b[j] < 1T --> 2^k의 자리값을 보면 모두 0
 1T <= a[i] + b[j] < 2T --> 2^k의 자리값을 보면 모두 1
 2T <= a[i] + b[j] < 3T --> 2^k의 자리값을 보면 모두 0
 3T <= a[i] + b[j] < 4T --> 2^k의 자리값을 보면 모두 1
 
 XOR을 하기위해선 자릿수에 1의 개수를 구해야한다.
 
 필요한 구간은 [1T,2T) , [3T,4T) 구간이다.
 
 a[i]를 고정시키고 구간을 다시 설정하면
 
 [1T-a[i],2T-a[i]) , [3T-a[i],4T-a[i]) 의 개수를 구하면 된다.
 
 개수가 홀수라면 정답의 2^k비트값은 1이 된다.
 
 */

