#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;

long long d[51][51];
long long num[51];

void combi(int n){
    
    for(int i=1;i<=n;i++){
        for(int j=0;j<=i;j++){
            if(i==j || j==0) d[i][j]=1;
            else d[i][j] = d[i-1][j-1] + d[i-1][j];
        }
    }
}

int main(int argc, const char * argv[]) {
    
    int n,a,b;
    
    scanf("%d %d %d",&n,&a,&b);
    
    for(int i=0;i<n;i++){
        scanf("%lld",&num[i]);
    }
    combi(n);
    sort(num,num+n);
    reverse(num, num+n);
    
    double sum = 0.0;
    double sum_average;
    for(int i=0;i<a;i++){
        sum+=num[i];
    }
    sum_average = sum/a;
    int same_cnt = 0;
    int need_cnt = 0;
    for(int i=0;i<n;i++){
        if(num[i] == num[a-1]){
            
            same_cnt++;
            if(i<a){
                need_cnt++;
            }
        }
    }
    long long ans = 0;
    if(need_cnt==a){
        for(int i=a;i<=b;i++) ans += d[same_cnt][i];
    }else{
        ans += d[same_cnt][need_cnt];
    }
    printf("%lf\n",(double)sum/a);
    printf("%lld\n",ans);
    
    return 0;
}



/*
 
 * 큰값 -> 작은 값 sort
 
 * 최소 A개를 하는것이 평균이 최대가 될 수 밖에 없다. (ex) 6 6 6 다음에 6이 와야 유지 / 8 6 6 평균 유지하려면 다음에 6보다 큰수가 와야함(모순)
 
 * 같은합을 가지는 개수 가 중요한데,
 
 * 만약에 A개 모두가 a[A-1]과 같다면 개수를 늘려도 상관없다 (전체 a[A-1]개수 C 최소 A개~최대B개)
 
 * 하지만 A개 안의 개수와  a[A-1]개수가 다른경우 전체 a[A-1]에서 A개이하의 a[A-1]개수와 같다. (전체 a[A-1] 개수 C A개 안의 a[A-1] 개수)
 
*/