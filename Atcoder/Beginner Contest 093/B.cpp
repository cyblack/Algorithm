#include <iostream>
#include <cstdio>

int main(int argc, const char * argv[]) {
   
    int a,b,k;
    
    
    scanf("%d %d %d",&a,&b,&k);
    
    
    int diff = b-a+1;
    
    
    if(diff >= 2*k){
        for(int i=0;i<k;i++) printf("%d\n",a+i);
        for(int i=0;i<k;i++) printf("%d\n",b-k+1+i);
    }else{
        for(int i=a;i<=b;i++) printf("%d\n",i);
        
    }
    return 0;
}

/*

 앞에서 부터 k개 뒤에서 부터 k개를 (a,b)구간에서 출력하는것(중복은 1번만)
 
 정확하게 k로 나누어지는 경우를 살펴보자
 
 a,a+1,a+2...,a+k-1 (앞)

 a+k,a+k+1,....b; (뒤)
 
 k=3이라고 하면 b-a+1이 2*k랑 같아지면 (a~b)구간을 모두 출력하면 되고,
 
 b-a+1이 2*k보다 큰 경우에는 중복이 없기 때문에 a부터 k개, b부터 k개를 출력하면된다.
 
 중복인 경우는  b-a+1이 2*k보다 작아지는 경우이다.
 
 사실 중복이라는 말은 출력해야되는 것이 (a~b)전 구간이라는 말과 동치이다.
 

*/