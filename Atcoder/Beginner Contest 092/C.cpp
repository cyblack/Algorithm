
#include <cstdio>
int a[100010];
int dist[100010];
int ch[100010];
int abs(int x){
    if(x>0) return x;
    return -x;
}
int main(int argc, const char * argv[]) {
    
    int n;
    
    scanf("%d",&n);
    
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    long long ans = 0;
    
    for(int i=0;i<=n;i++){
        dist[i+1] = abs(a[i+1]-a[i]);
        
        ans+=abs(a[i+1]-a[i]);
        if(i>=2) {
            ch[i] = abs(a[i]-a[i-2]);
        }
    }
    ch[n+1]=abs(0-a[n-1]);
    
    
    for(int i=1;i<=n;i++){
        printf("%lld\n",ans-dist[i]-dist[i+1]+ch[i+1]);
    }
    return 0;
}


/*
 
 
 특정 i 위치를 뺴고 여행할 때 비용의 합을 모두 구하는 것
 
 
 0 -> A -> B -> C -> D -> E -> 0 일 때,
 
 모든 여행을 하는 비용을 sum(화살표의 값 모두)
 
 1) A를 뺸 경우는
 
 sum - 0A - AB + 0B
 
 
 2) B를 뺀 경우는
 
 sum - AB - BC + AC
 
 ...
 
 일반화 해보면 특정 X를 뺀 경우
 
 X랑 연결된 좌우 값을 빼고 그다음을 이어주면 된다.

 
 인접한 값을 과 2칸 차이 나는 값도 미리 구해놓는다.
 
 ch[i]배열 : i-2 -> i 가는 비용
 
 dist[i] 배열 : i-1 -> i 가는 비용
 
 
 */
