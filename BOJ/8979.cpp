#include <algorithm>
#include <cstdio>
#define INF 987654321
using namespace std;

struct node{
    int idx,gold,silver,bronze;
}a[1001];

bool comp(struct node &A, struct node &B){
    
    if(A.gold == B.gold){
        if(A.silver == B.silver) return A.bronze > B.bronze;
        return A.silver > B.silver;
    }
    return A.gold > B.gold;
}

int main(int argc, const char * argv[]) {
    
    int n,k;
    
    scanf("%d %d",&n,&k);
    
    for(int i=0;i<n;i++){
        scanf("%d %d %d %d",&a[i].idx,&a[i].gold,&a[i].silver,&a[i].bronze);
    }
    
    sort(a,a+n,comp);
    
    int q=a[0].gold,w=a[0].silver,e=a[0].bronze;
    int level=1;
    int cnt=1;
    
    if(k==a[0].idx){
        printf("%d\n",1);
        return 0;
    }
    
    for(int i=1;i<n;i++){
        
        if(q == a[i].gold ){ // 골드 개수가 앞과 같음 - 실버 개수를 비교해야함
            if(w == a[i].silver){
                if(e == a[i].bronze){ // 3 3 3 - 3 3 3인 경우에 등수가 늘어나지 않음
                    cnt++;
                }else{ //브론즈 개수가 적음
                    level+=cnt;
                    cnt=1;
                }
            }else{//실버 개수가 적음
                level+=cnt;
                cnt=1;
            }
        }else{ // 골드 개수가 적음
            level+=cnt;
            cnt=1;
        }
        
        q=a[i].gold;
        w=a[i].silver;
        e=a[i].bronze;
        
        if(a[i].idx == k){
            printf("%d\n",level);
        }
    }
    return 0;
}