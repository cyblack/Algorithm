
#include <cstdio>
#include <iostream>
int map[3][3];
int a[3];
int b[3];

bool check(){
    
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(map[i][j] != a[i]+b[j]){
                return false;
            }
        }
    }
    return true;
}

int main(int argc, const char * argv[]) {
    
    int sm = 101;
    int x=0,y=0;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            scanf("%d",&map[i][j]);
            if(sm > map[i][j]){
                sm = map[i][j];
                x=i,y=j;
            }
        }
    }
    int sz = (sm>100)? 100 : sm;
    for(int i=0;i<=sz;i++){
        
        a[x] = i;
        b[y] = sm-i;
        for(int k=-2;k<=2;k++){
            if(k==0) continue;
            if( 0 <= x+k && x+k<=2){
                if(map[x+k][y]-a[x] < 0) continue;
                a[x+k] = map[x+k][y]-b[y];
               
            }
            if( 0 <= y+k && y+k <=2){
                if(map[x][y+k]-b[y] < 0) continue;
                b[y+k] = map[x][y+k]-a[x];
            }
        }
        
        if(check()){
            printf("Yes\n");
            return 0;
        }
    }

    printf("No\n");
    return 0;
}


/*
 
 3x3행렬이므로 모든 경우의 수를 다 구해보고 찾았다.
 
 다른방법으로는
 
 a1+b1  a1+b2  a1+b3
 
 a2+b1  a2+b2  a2+b3
 
 a3+b1  a3+b2  a3+b3
 
 에서 2x2행렬로 4번 확인해서 모두 가능하면 각각을 직접 구하지 않아도 확인가능
 
 1) a1 b1 a2 b2 가 2번씩
 2) a1 b2 a2 b3 가 2번씩
 3) a2 b1 a3 b2 가 2번씩
 4) a2 b2 a3 b3 가 2번씩 나오기 때문
 
 */
