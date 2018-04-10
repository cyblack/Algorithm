
#include <cstdio>
long long a,b,s;

bool check(long long x){
    if(x*x < s) return true;
    return false;
}

void swap(long long &a, long long &b){
    a = a^b;
    b = a^b;
    a = a^b;
}
int main(int argc, const char * argv[]) {
   
    int q;
    
    scanf("%d",&q);
    
    for(int i=0;i<q;i++){
        
        scanf("%lld %lld",&a,&b);
        
        s = a*b;
        long long ans = 0;
        if(a<b){ //a가 작은경우
            ans += 2*(a-1);
        }else if(a==b){
            printf("%lld\n",2*(b-1));
            continue;
        }else{
            ans += 2*(b-1);
            swap(a,b);
        }
        
        if(a+1 != b){
            
            long long l = a+1;
            long long r = b-1;
            long long val = 0;
            while(l<=r){
                
                long long mid = (l+r)/2;
                
                if(check(mid)){
                    l = mid+1;
                    val = mid;
                }else{
                    r = mid-1;
                }
            }
            
            if(val!=0){
                if(val *(val+1) < s) ans += 2*(val-a);
                else ans += 2*(val-a) - 1 ;
            }
            ans++;
            
        }
        printf("%lld\n",ans);
    }
    return 0;
}


/*
 
 손으로 몇번 그려보면 (a<b)인 경우에
 
 
 a-1개*2개는 모두 아래의 특정값과 일치 시킬 수 있다. (ans += 2*(a-1)
 
 
 다음은 a~b사이 구간이다.
 
 a+1 = b 인 경우에는 존재하지않음
 
 a+1 != b인 경우네는
 

 
 X*X < S 인 X값에 대해 
 대칭적으로 이루어 지게 된다.
 
 
 a   a
 
 a+1 a+1
 
 a+2 a+2
 
 ...  ...
 
 X   X
 
 ... ...
 
 b-2 b-2
 
 b-1 b-1

 b   b
 
 에서 X < ab를 만족하는 최대 X값을 구하면
 
 X값을 기준으로 (a+1~b-2)구간사이에 대칭되게 구할 수 있다.(2개씩)
 
 예외 케이스는 X*X == AB인 경우 인데, 이경우는 1개만 가능하다.
 
 최대 X를 구해야하는데 이부분은 0~10억이므로
 
 이분탐색을 통해 빠르게 구할 수 있다.
 
 그리고 a와 b-1은 무조건 가능하므로 1개를 추가한다. (a*(b-1) <ab)
 
 */
