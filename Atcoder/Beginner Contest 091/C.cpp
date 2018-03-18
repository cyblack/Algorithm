
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
using namespace std;

set<int> s;

int check[101];
struct node{
    int x,y;
    bool color;
};

bool comp(struct node &A,struct node B){
    if(A.x < B.x) return 1;
    return 0;
}

int main(int argc, const char * argv[]) {
 
    int n;
    struct node red[101];
    struct node blue[101];
    struct node ball[202];
    scanf("%d",&n);
    
    for(int i=0,a,b;i<n;i++){
        scanf("%d %d",&a,&b);
        red[i].x = a;
        red[i].y = b;
        ball[i].x=a;
        ball[i].y=b;
        ball[i].color = 0;
    }
    
    for(int i=0,c,d;i<n;i++){
        scanf("%d %d",&c,&d);
        blue[i].x = c;
        blue[i].y = d;
        ball[n+i].x =c;
        ball[n+i].y =d;
        ball[n+i].color = 1;
    }
    
    sort(ball,ball+2*n,comp);
    int ans2 = 0;
    for(int i=0;i<2*n;i++){
        if(ball[i].color==0){
            s.insert(ball[i].y);
        }else{
            auto ans = s.lower_bound(ball[i].y);
           
            if(ans == s.begin()) continue; // 10 20 30 40 중 8보다 큰 것 lower하면 1번째값
            // 10 20 30 40 중 30보다 큰 것 lower하면 3번째값
            s.erase(--ans);
            ans2++;
        }
    }
    printf("%d\n",ans2);
    sort(blue,blue+n,comp);
    
    int ans = 0;
    for(int i=0;i<n;i++){ //blue
        int mm = -1;
        int num = -1;
        for(int j=0;j<n;j++){
            if(!check[j] && blue[i].x > red[j].x && blue[i].y > red[j].y){
                
                if(mm < red[j].y){
                    mm = red[j].y;
                    num = j;
                }
            }
        }
        if(num!=-1){
            check[num]=true;
            ans++;
        }
    }
    
    printf("%d\n",ans);
    
    return 0;
}

/*
 
 1) x값들로 파란공을 정렬하고 가능한 빨간 공 중 y축값이 가장 큰 값을 고른다. (ans 첫번째방법)
 
 2) 모든 공들을 x값들로 정렬 하고 빨간 공이라면 y값을 추가하고 파란공이라면 y값이 저장된 집합에서 범위 내의 가장 큰 y값을 찾는다 (ans2두번째방법)

*/