

#include <iostream>
#include <cstring>
#include <cstdio>
int cnt[100001];
bool prime[100001];
int main(int argc, const char * argv[]) {
 
    
    //에라토스테네스의 체 (소수 빨리 구하기)
    for(int i=2;i<=100000;i++){
        if(!prime[i]){
            for(int j=i*2;j<=100000;j+=i){
                prime[j]=true;
            }
        }
    }
    
    for(int i=3;i<=100000;i+=2){
        if(!prime[i] && !prime[(i+1)/2]) cnt[i]++;
    }
    //개수는 누적되므로 미리 구해놓으면 빨리 구할 수 있음
    for(int i=3;i<=100000;i++){
        cnt[i] += cnt[i-1];
    }
    
    int q;
    
    scanf("%d",&q);
    
    while(q--){
        
        int l,r;
        
        scanf("%d %d",&l,&r);
        printf("%d\n",cnt[r]-cnt[l-1]);
        
    }
    
    return 0;
}

/*
 
 x 가 소수이고 (x+1)/2 소수인 경우의 수 를 구하는것
 
 범위는 (a~b) 구간내..
 
 위의 조건을 만족하는 개수를 누적한다면 답은 sum[b]-sum[a-1]로 구할 수 있다.
 
 소수를 빨리 구하는법은 에라토스테네스의 체가 있다.
 
 1은 소수가 아니므로 2부터 시작한다.
 
 처음에 모두 false로 되어있으므로 
 
 false인것은 소수 인 것이고 +=i값을 통해 true로 변경 해준다.
 
 처음값을 true로 하고 아닌것을 false로 해야하는데 그렇게 하려면 초기배열값을 true로 잡아야한다.
 
 초기화를 하지않고 진행하기 위해 반대로 입력한다.
 
 다음은 조건에 맞는 개수를 구하고
 
 그 값들을 누적해서 쿼리에 따라 값을 출력한다.
 
 */
