#include<cstdio>
#include <algorithm>
using namespace std;

int x[200001];
int y[200001];

int main(){
    
    int n;
    scanf("%d",&n);
    
    for(int i=1;i<=n;i++){
        scanf("%d",&x[i]);
        y[i] = x[i];
    }
    
    sort(y+1,y+n+1);
    int med = y[n/2];
    
    for(int i=1;i<=n;i++){
        if(x[i] > med) printf("%d\n",med);
        else printf("%d\n",y[n/2+1]);
    }
    
    return 0;
}

/*
 
 N은 짝수이고 
 
 X를 정렬 후 median값은 X[N/2]이다.
 (즉, 앞에서 N/2만큼 떨어진 값)
 
 x[1] ....x[N/2] ...x[n] 이라고 할 때
 
 x[N/2]보다 큰 값에 대해서는 median값이 변하지 않는다.
 왜냐하면 1개를 제거하면 전체 개수는 홀수가 되고 앞에서 부터 칸 수는 일정하기 때문이다.
 
 x[N/2]보다 작거나 같은 값에 대해서는 앞에서 부터 칸 수가 하나 줄었기 때문에
 한칸을 뒤로 보내야한다.
 
*/