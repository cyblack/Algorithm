
#include <cstdio>

int main(int argc, const char * argv[]) {

    int n,k;
    
    scanf("%d %d",&n,&k);
    
    int sum = k/1000-n;
    for(int i=0;9*i<=sum;i++){
        for(int j=0;j<=n-i;j++){
            
            if( 9*i+ 4*j == sum){
                printf("%d %d %d\n",i,j,n-i-j);
                return 0;
            }
        }
    }
    printf("-1 -1 -1\n");
    
    return 0;
}


/*
10000x + 5000y + 1000z = k;
 
10x + 5y + z = (k/1000)
 
 
 x + y + z = n;
 
 9x + 4y = (k/1000) - n 인 (x,y)쌍을 구하면 답은 (x,y,n-x-y)가 된다.
 

*/