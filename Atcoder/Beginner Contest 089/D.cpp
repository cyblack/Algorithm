#include <iostream>
#include <cstdio>
#define abs(a,b) (a<b)?b-a:a-b

struct point{
    int x,y;
    
}P[90011];
int sum[90011];

int main(int argc, const char * argv[]) {
  
    int h,w,d,tmp;
    scanf("%d %d %d",&h,&w,&d);
    
    for(int i=1;i<=h;i++){
        for(int j=1;j<=w;j++){
            scanf("%d",&tmp);
            P[tmp].x = i;
            P[tmp].y = j;
        }
    }
    
    for(int i=1;i<=d;i++){
        
        int l = i;
        int r = h*w;
        sum[i]=0;
        while(l<r && l+d <= r){
            sum[l+d] += sum[l];
            sum[l+d] += abs(P[l].x,P[l+d].x);
            sum[l+d] += abs(P[l].y,P[l+d].y);
            l += d;
        }
    }
    
    int cnt;
    scanf("%d",&cnt);
    
    
    for(int i=0;i<cnt;i++){
        int l,r;
        
        scanf("%d %d",&l,&r);
        printf("%d\n",sum[r] - sum[l]);
    }
    
    return 0;
}

/*

 i->j로가고싶은데 +d 만큼 씩 이동 할 수 있다.
 
 
 1->3->5->7->9
 
 2->4->6->8
 
 3->5->7->9
 4->6->8
 
 1->4->7->10->13
 2->5->8->11->14
 3->6->9->12->15
 
 4->(계속 반복 되기 때문에 d까지만 하면된다.)
 누적합을 이용.

*/
