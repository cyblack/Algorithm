#include <cstdio>
int a[4][4];

int main(){
    
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            scanf("%d",&a[i][j]);
        }
    }
    
    bool acc = false;
    
    for(int i=0;i<4;i++){
        for(int j=1;j<=3;j++){
            if( (a[i][3-j] && a[(i+j)%4][3]) || ( a[i][3] && a[i][3-j])) {
                acc = true;
            }
        }
    }
    
    if(acc) printf("YES\n");
    else printf("NO\n");
    return 0;
}


/*
   2
 3   1
   0
 
 사고가 난 2가지 case :  1) 보행자가 건너는 도로에서 차가 존재할 때 2) 왼쪽/오른쪽/가운데 도로와의 보행자와 만날 때
 
 특정 번호에서 
    왼쪽 : (현재위치 + 3)%4
    가운데 : (현재위치 +2)%4
    오른쪽 : (현재위치+1)%4
    
 
    +1 +2 +3 -> for문으로 표현할 수 있음
 
    상황 표는 왼쪽(0)/가운데(1)/오른쪽(2) 형태
               +3      +2      +1
    
    합이 3으로 일정함
 
    j=1~3할 때 표값을 확인하려면 3-j로 표현하면 얻을 수 있다.
*/