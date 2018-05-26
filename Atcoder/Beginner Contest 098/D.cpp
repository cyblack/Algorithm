

#include <iostream>
#include <cstdio>
using namespace std;
int a[200011];

bool check(long long x, long long y,long long z){
    
    long long sum = x+z;
    
    long long tmp = y^z;
    
    if(sum==tmp) return true;
    return false;

}
int main(int argc, const char * argv[]) {
    
    int n;
    
    scanf("%d",&n);
    
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
    
    
    int l = 0;
    int r = 0;
    long long tmp = a[l];
    long long xo = a[l];
    long long ans = 0;
    while(r<n){
        if(l==r){
            tmp = a[l];
            xo = a[l];
            r++;
        }
        else if(check(tmp,xo,a[r])){
            ans+= r-l;
            tmp += a[r];
            xo ^= a[r];
            r++;
        }else{
            tmp-=a[l];
            xo = tmp;
            l++;
        }
        
    }
    
    printf("%lld\n",ans+n);
    
    return 0;
}

/*
 
 
 l~r까지 가능하다면 그 안의 i<j를 만족하는 값도 가능하다.
 
 예를들어 1~5라면 2~3, 2~5 형태가 모두 가능하다.
 
 즉 r이 추가될수록 r-l개씩 추가된다.
 
 예를들어 1~3까지 일때 4가 가능하다면 (1,4) (2,4) (3,4) 4-1=3개가 가능.
 
 만약에 두개 값이 일치하다면 R을 증가시키고, 
 일치하지 않는다면 L을 증가시킨다.
 
 L=R이 같은경우에는 다시 초기화를 해준다.
 

*/