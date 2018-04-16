#include <cstdio>
#define _MAX 100000
bool prime[100001];

int main(int argc, const char * argv[]) {
    
    for(int i=2;i<=_MAX;i++){
        
        if(!prime[i]){
            for(int j=i*2;j<=_MAX;j+=i){
                prime[j]=true;
            }
        }
    }
    
    for(int i=2;i<=100;i++){
        if(!prime[i]) printf("prime is %d\n",i);
    }
    
    return 0;
}

/*
 에라토스테네스의 체 : 소수 빨리 구하는법.
 
 false가 소수이다.
 1은 소수가 아니다.
 
 false가 소수인 이유 : true로 하려면 초기값을 true로 변경 후 false를 해줘야하는데 초기값을 변경하지않고 반대로 이용
 
 */