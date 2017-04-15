#include <iostream>
#include <vector>
#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>


using namespace std;
int a[5020];
int n,k;
bool d[5020];
bool need(int idx){
    
    if(a[idx]>=k) return true;
    
    memset(d,false,sizeof(d));
    d[0]=true;
    for(int i=0;i<n;i++){
        
        if(i==idx) continue;
        
        for(int j = k-1;j>=0;j--){
            if(!d[j])continue;
            if(j+a[i]<=k) d[j+a[i]]=true;
        }
    }
    
    for(int i=k-a[idx];i<k;i++){
        if(d[i]) return true;
    }
    return false;
}

int main(){
    
    scanf("%d %d",&n,&k);
    
    for(int i=0;i<n;i++) scanf("%d",&a[i]);
    
    
    sort(a,a+n);
    
    
    //필요한 부분에서 찾는 방법
    int l = 0;
    int r = n-1;
    int ans = 100000;
    
    while(l<=r){
        
        int mid = (l+r)/2;
        if(need(mid)){ //필요하다
            r=mid-1;
           ans = min(ans,mid);
        }else{ //불필요하다
            l=mid+1;
        }
    }
    
    if(ans ==0) printf("0\n");
    else if(ans==100000) printf("%d\n",n);
    else printf("%d\n",ans);
    
    /* 불필요한 부분에서 찾는 방법
     int l = 0;
     int r = n-1;
     int ans = -1;
    
     while(l<=r){
        
        int mid = (l+r)/2;
        
        if(test(mid)){
            r=mid-1;
            //  ans = max(ans,mid);
        }else{
            l=mid+1;
            ans = max(ans,mid);
        }
    }
    
    if(ans ==0) printf("1\n");
    else if(ans==-1) printf("0\n");
    else printf("%d\n",ans+1);
    */
    
    
    return 0;
}
/*

 
 구하고자 하는 것 : 불필요한 카드의 개수
 
 불필요하다는것 : 필요한 곳이 아무곳도 없다. / 필요한 곳이 하나라도 있으면 불필요하지 않다는것
 
 필요한 경우 하나를 찾아서 불필요하지 않다는 것을 증명해보기
 
 현재 카드(i)를 제외하고 N-1 개의 카드로 만들수있는 값들을 모두 찾는다.
 그 이후에 K-a[i] <= x < k 의 범위안에 만들수있는값이 존재한다면 현재 카드로 K이상을 만들 수 있다.
 즉, 필요한 곳 한군데 발견 = 불필요하지 않다는것
 
 ==> 위의 과정은 동전으로 만들수있는 값들 구할때 dp하듯이 구하면됨 (N^2)
 
 다음은 N개의 카드마다 모두 다해보면 N^3인데 시간초과

 잘 보면 A(i) < A(j) 인 경우, A(j)가 불필요하면, A(i)도 불필요하다.
 이점을 이용하면 이분탐색으로 빠르게 구할 수 있다(N^2logN)
 
 전제조건은 A(i) < A(j)이고 A(i)가 필요하다
 명제증명)  위의 조건에 따라 A(j)도 필요하다
 
 그렇게 되면 각각의 범위는
 
 A(i) : k-A(i) <= x < k
 A(j) : k-A(j) <= x < k
 

 구간이 3군데 나오는데, 필요하다는 조건에 의해 왼쪽,오른쪽 구간은 무시한채 가운데 구간에 속한 값만 확인한다.
 먼저 x라 했을때,
 
 x가 A(j)를 포함한 경우 : 범위 큰곳으로 넘어갈때 X -> X-A(j)+A(i) 가 되고 왼쪽 구간값은 X-A(i) -> X-A(j)로 변한다.
                        증가량이 -A(j) + A(i)로 같기 때문에 평행이동 효과이고 (필요!)
 
 x가 A(j)를 포함하지 않은 경우 : 더 증가하거나 그대로인데, 그대로인 경우는 구간안에 또 포함 되므로 (필요!)
 

 위의 두 조건에 따라 A(i) < A(j)이고 A(i)가 필요하면 A(j)도 필요하다.
 
 이를 이용해 이분탐색을 할때 필요하다면 값의 최대값 범위를 줄여나갈 수 있다( R = mid-1 )
 
 *답 출력 부분 (불필요한 부분에서 찾기)
 ans == 0 인 경우는  3 6 / 1 4 3 
 즉, 불필요,필요,필요 인 경우 인덱스가 0으로 나옴
 
 ans == -1인 경우는 3 100 / 100 100 100
 즉, 필요 필요 필요 인 경우 인덱스가 -1로 나옴
 
 나머지는 index값으로 나오니까 +1 해준다. (불불불 필필 형태에서 불의 마지막지점인 2로 나오기때문에 +1한다)
 
 *답 출력 부분 (필요한 부분에서 찾기)
 
 ans == 100000인경우는 필요한곳을 들리지 않았고 모두 불필요한 경우이다 / 구하는것은 불필요한 경우이므로 N개 모두 해당
 ans == 0인 경우는 모두 필요한 경우 / 불필요한 경우는 0개
 나머지는 index값 그대로 하면 된다 (불불불 필필 형태이므로 필의 시작점이 3이기때문에 바로 출력)
 
*/