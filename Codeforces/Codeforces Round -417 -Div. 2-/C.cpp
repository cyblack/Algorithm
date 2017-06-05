#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;
int s,n;

struct node{
    int idx;
    int cost;
};
struct node cc[100001];

long long find(int k){
    
    long long sum = 0;
    long long dd[100001];
    
    for(int i=0;i<n;i++) dd[i] = (long long)cc[i].cost + (long long)k*cc[i].idx;
    
    sort(dd,dd+n);
    
    for(int i=0;i<k;i++) sum += dd[i];
    
    return sum;
}

int main(int argc, const char * argv[]) {
    
    
    scanf("%d %d",&n,&s);
    
    for(int i=0;i<n;i++){
        scanf("%d",&cc[i].cost);
        cc[i].idx = i+1;
    }
    
    int l = 0;
    int r = n;
    int ans = 0;
    
    while(l<=r){
        
        int mid = (l+r)/2;
        
        if(find(mid) <= s){
            l = mid+1;
            ans = max(ans,mid);
        }else{
            r = mid-1;
        }
    }
    
    cout << ans << " " << find(ans);
    
    return 0;
}

/*
 
  구하는 것 :  기념품의 최대개수이고 최소비용인 값
 
  기념품의 최대 개수를 결정하고 그 비용이 내가 가진 비용안에 드는 지 확인

  현재 개수를 살 수 있다면 기념품 개수를 더 늘림
 
  최소비용은 변환된 값에서 작은 것 부터 더해주면 된다. 항상 특정 개수에 따른 최소비용이 하나뿐이다.
 
*/
