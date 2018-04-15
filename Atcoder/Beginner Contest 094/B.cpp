

#include <cstdio>
#include <algorithm>
using namespace std;
int sum[101];
bool toll[101];
int main(int argc, const char * argv[]) {
   
    int n,m,x;
    
    
    scanf("%d %d %d",&n,&m,&x);
    
    for(int i=0,tmp;i<m;i++){
        scanf("%d",&tmp);
        toll[tmp]=true;
    }
    
    for(int i=1;i<n;i++) sum[i] = sum[i-1] + toll[i];
    
    int left = sum[x];
    int right = sum[n-1]-sum[x];
    
    printf("%d\n",min(left,right));
    return 0;
}

/*
 
 현재 값 기준으로 0~ X 까지 수의 합
 
 X+1 ~ n-1까지의 합을 비교해서 작은 값 출력
 

*/