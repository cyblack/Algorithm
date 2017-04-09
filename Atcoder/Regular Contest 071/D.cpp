#include <cstdio>
#define mod 1000000007
using namespace std;
int x[100001];
int y[100001];
int main(){
    
    int n,m;
    
    scanf("%d %d",&n,&m);
    
    for(int i=1;i<=n;i++) scanf("%d",&x[i]);
    for(int j=1;j<=m;j++) scanf("%d",&y[j]);
    
    long long xx = 0,yy=0;
    
    for(int i=1;i<=n;i++){
        xx += 1LL*(i-1)*x[i] - 1LL*(n-i)*x[i];
        xx%=mod;
    }
    for(int i=1;i<=m;i++){
        yy += 1LL*(i-1)*y[i] - 1LL*(m-i)*y[i];
        yy%=mod;
    }
    
    printf("%lld\n", (xx*yy)%mod);
    
    return 0;
}

/*
 
 가로 : a1 <= a2 <= a3 <= a4 ... <= an
 세로 : b1 <= b2 <= b3 <= b4 ... <= bn
 
 x축 2개와 y축 2개로 만들 수 있는 직사각형
 
 ex) a1 a2 a3 a4 a5 // b1 b2 b3 b4 b5
 
 가능한 변은 총 10가지
 1. a2-a1
 2. a3-a2
 3. a4-a3
 4. a5-a4
 5. a3-a1
 6. a4-a2
 7. a5-a3
 8. a4-a1
 9. a5-a2
 10. a5-a1
 
 각각에 대해 세로길이도 10가지가 나오므로 
 가로 따로 계산 세로 따로 계산해서 마지막에 곱해주면 된다.
 가로 10가지를 A라 표현 / 세로 10가지를 B라 표현
 답은 (A*B)%mod
 
 그렇다면 A를 빠르게 구해야하는데 
 식을 적어보면 시그마(1<=i<=j<=n)(aj-ai) 형태로 N^2복잡도가 나온다
 
 식을 잘 정리하면 변수하나로 표현할 수 있다. (식의 구성은 O-O 형태)
 
 왼쪽 편과 오른쪽 편을 잘 구분해 보자
 
 왼쪽       /    오른쪽
 a5 4개    /  a5 0개
 a4 3개    /  a4 1개
 a3 2개    /  a3 2개
 a2 1개    /  a2 3개
 a1 0개    /  a1 4개
 
 일반화 하면,
 시그마(1<=i<=n) (k-1)ak - (n-k)ak 
 : n만에 구할 수 있다
 
 세로도 똑같이 구할 수 있으므로
 
 시간복잡도 O(n+m)만에 해결가능하다


*/