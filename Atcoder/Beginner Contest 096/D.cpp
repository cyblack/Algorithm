

#include <cstdio>
bool prime[60000];

int main(int argc, const char * argv[]) {
   
    
    int n;
    int cnt = 0;
    
    for(int i=2;i<=55555;i++){
        for(int j=i+i;j<=55555;j+=i){
            if(!prime[j]) prime[j] = true;
        }
    }
    
    scanf("%d",&n);
    
    for(int i=2;i<=55555;i++){
        if(!prime[i] && i%10==1){
           printf("%d ",i);
            cnt++;
        }
        if(cnt==n) break;
    }
    
    return 0;
}


/*
 
 
 5개 이상의 수에서 임의의 다섯 수를 뽑아 합성수가 되게 만들기.
 
 5개 수를 뽑는 것이니까 5를 나눈나머지 1인 수들을 모아보자
 
 그렇게되면 그들의 합또한 5로 나누어질것이다.
 
 5(a+b+c+d+e) + 5형태가 될테니깐.
 
 소수중 5로 나누었을때 1이 되는값을 찾아야하는데 6,11,16 등이 있지만 자세히보면, 끝자리가 1, 6으로 끝난다.
 
 6으로 끝나는 자리는 소수가 될 수 없으므로. 끝자리가 1인 수를 구하면된다.
 
*/
