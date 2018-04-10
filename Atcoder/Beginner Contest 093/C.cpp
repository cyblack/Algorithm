#include <cstdio>
#include <algorithm>
using namespace std;
int a[3];

int main(int argc, const char * argv[]) {
   
 
    
    scanf("%d %d %d",&a[0],&a[1],&a[2]);
    
    sort(a,a+3);
    
    int diff = a[2]-a[1];
    int ans = diff;
    a[0] += diff;
    
    diff = a[2]-a[0];
    
    if(diff&1) printf("%d\n",ans+diff/2+2);
    else printf("%d\n",ans+diff/2);


    return 0;
}


/*

 3개의 수를 특정수로 모두 일치시키는 최소횟수를 구하는 문제이다.
 
 2가지 동작을 살펴보면 모두 증가시키는 형태이다 (2개의값을 1씩증가 , 1개의 값을 2증가)
 
 결국 값은 어떤 동작을 하던 2씩 증가 하게 된다. (무슨 동작을 하든 상관없다는 뜻)
 
 특정수를 X라 부르면 X >= Max(a,b,c) 성립한다.
 
 그리고 모든 경우에 대해서 A,A,B 형태로 만들어 진다.
 
 2,3번째 수를 (1번째-2번째)수만큼 증가시키면 가능.
 
 이제 B를 2씩 증가시켜서 A를 만들 수 있느냐 문제인데,
 
 A-B가 2의배수라면 (A-B)/2가 횟수가 되겠지만,
 
 떨어지지 않는 경우에는 A A A-1까지 가능하게되고 ->  A+1,A+1,A-1 -> A+1,A+1,A+1로 일치 시킬 수 있다.
 
 즉, (A-B)/2에 2번 동작을 더 추가하면 된다.
 

*/