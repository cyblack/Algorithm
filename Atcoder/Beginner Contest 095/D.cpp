
#include <cstdio>
#include <algorithm>
using namespace std;

long long x[100011];
long long  v[100011];
long long vsum[100010];
long long rsum[100010];
long long lsum[100010];

int main(int argc, const char * argv[]) {
  
   int  n;
    long long ans= 0,c;
    scanf("%d %lld",&n,&c);
    
    
    for(int i=1;i<=n;i++){
        scanf("%lld %lld",&x[i],&v[i]);
        vsum[i] = vsum[i-1] + v[i];
    }
    ans = max(ans,vsum[n]-c);
    
   
    for(int i=1;i<=n;i++) rsum[i] = max(rsum[i-1],vsum[i] - 2*x[i]);
    for(int i=1;i<=n;i++) lsum[i] = max(lsum[i-1],(vsum[n]-vsum[n-i]) - (c-x[n-i+1]));
    for(int i=0;i<=n;i++) ans = max(ans, rsum[i]+lsum[n-i]);
    
    for(int i=1;i<=n;i++) rsum[i] = max(rsum[i-1],vsum[i] - x[i]);
    for(int i=1;i<=n;i++) lsum[i] = max(lsum[i-1],(vsum[n]-vsum[n-i]) - 2*(c-x[n-i+1]));
    for(int i=0;i<=n;i++) ans = max(ans, rsum[i]+lsum[n-i]);
    
    printf("%lld\n",ans);
    
    return 0;
}


/*
 
 
 모든 점에서 마칠 수 있기 때문에
 
 왼쪽으로 갔다가 0으로 돌아와서 오른쪽 가는 경우를 생각해보자
 
 또는
 
 오른쪽으로 갔다가 0으로 돌아와서 왼쪽으로 가는 경우를 생각해보자.
 
 1번 경우에는 왼쪽으로 갔다가 돌아오는 경우이기때문에 거리를 한번더 빼줘야한다.
 
 2번 경우에는 오른쪽이므로 오른쪽거리를 2번 빼준다.
 
 
 오른쪽으로 출발한 경우 칼로리의 합 - 이동거리
 왼쪽으로 출발한 경우 전체칼로리 - 이전칼로리 합 - (전체거리 C - 이동거리)
 
 다시 돌아오는 경우는 *2를 해준다.
 
 v는 누적합으로 계산된다.
 
 rsum은 오른쪽방향으로 i번 째 까지 갔을 때 칼로리의 최대값
 lsum은 왼쪽방향으로 i번 쨰 까지 갔을 때 칼로리의 최대값
 
 그리고 구했다면
 
 오른쪽 출발 2번점
 왼쪽 출발 3번점 인 구간을 찾아 합 중 가장 큰 것을 고른다.
 
 */
