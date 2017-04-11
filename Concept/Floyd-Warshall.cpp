#include <algorithm>
#include <cstdio>
#include <vector>
#define INF 987654321
using namespace std;

int d[101][101];

int main(int argc, const char * argv[]) {
    
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            d[i][j] = (i==j) ? 0 : INF;
        }
    }
   
    /*
        입력(그래프만들기)
    */
    
    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                d[i][j] = min(d[i][j],d[i][k]+d[k][j]);
            }
        }
    }
    return 0;
}

/*
 
    시간복잡도 O(V^3)
 
    모든 쌍의 최단거리를 알 수 있다.
 
    다익스트라로도 구할 수 있다 (시간복잡도 O( V(E+VlogV) ))
    
    벨만포드로도 구할 수 있다 ( 시간복잡도 O(V^2*E))

 
    아이디어는 다이나믹 프로그래밍이다.
 
    Floyd(i,j,k) : i정점에서 j정점까지 가는데 1~k정점만을 이용할 때, 최단거리 정의
 
    k   단계 : 1 ~ k 정점을 이용
    k-1 단계 : 1 ~ k-1 정점을 이용
    
    k단계를 구할 때 k-1단계만 이용하고 그 이전 단계는 필요 없으므로 덮어쓰는 방식을 사용해서 2차원으로 줄일 수 있다.
    
 
    핵심 : d[i][j] > d[i][k] + d[k][j]
 
*/
