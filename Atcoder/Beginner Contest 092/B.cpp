

#include <cstdio>

int main(int argc, const char * argv[]) {
    
    int n,d,x;
    
    scanf("%d %d %d",&n,&d,&x);
    int ans = 0;
    for(int i=0,tmp;i<n;i++){
        scanf("%d",&tmp);
        ans += (d-1)/tmp;

    }
    
    printf("%d\n",ans+x+n);
    return 0;
}

/*

 처음 choco의 개수를 구하는 문제
 
 1일 부터 ai일 간격마다 초콜렛을 먹는다.
 
 캠프는 N일 동안
 
 1 + 1+ai + 1+2*ai +....<=d가 되는 개수..
 
 간격을 구하기 위해 (d-1)/tmp
 
 + 남은 개수 + n은 참가자 수 (첫날은 무조건 먹음)

*/