

#include <cstdio>

int main(int argc, const char * argv[]) {
   
    int n,m;

    scanf("%d %d",&n,&m);
    
    if(n==1 && m==1){
        printf("1\n");
        return 0;
    }
    else if(n==1){
        printf("%d\n",m-2);
        return 0;
    }else if(m==1){
        printf("%d\n",n-2);
    }else{
        long long ans= 0;
        
        ans = (long long)(n-2)*(m-2);
        printf("%lld\n",ans);
    }
    
    return 0;
}
