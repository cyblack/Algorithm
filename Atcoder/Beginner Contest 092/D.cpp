#include <cstdio>
#define W 1
#define B 2
int board[101][101];
int main(int argc, const char * argv[]) {
    
    int a,b;
    
    scanf("%d %d",&a,&b);
    a--;b--;
    
    for(int i=1;i<=100;i++){
        for(int j=1;j<=50;j++){
            board[i][j]=W;
        }
    }
    
    for(int i=1;i<=100;i++){
        for(int j=51;j<=100;j++){
            board[i][j]=B;
        }
    }
    
    int row = 1;
    int col = 1;
    for(int i=1;i<=b;i++){
        board[row][col] = B;
        
        if(col>=49){
            col = 1;
            row += 2;
            continue;
        }
        col+=2;
    }
    row = 1;
    col = 52;
    
    for(int i=1;i<=a;i++){
        board[row][col] = W;
        if(col>=100){
            row += 2;
            col = 52;
            continue;
        }
        col+=2;
    }
    
    printf("100 100\n");
    
    for(int i=1;i<=100;i++){
        for(int j=1;j<=100;j++){
            if(board[i][j]==W) printf(".");
            else printf("#");
        }
        printf("\n");
    }
    
    return 0;
}




/*
 
100 * 100 행렬 에서 검은색과 흰색으로 영역을 나눌 경우는 5000개 , 5000개 
 (oxoxoxoxox..
  xoxoxoxoxo.. 경우) -> 크기를 최대값으로 결정할 수 있음
 
 A,B 범위는 500개, 500개 이므로 충분히 가능하다.
 
 100*100행렬에서 100*50 영역으로 검은색과 흰색을 1:1비율로 나누고
 
 추가적인 부분에 대해서는
 
 검은색 부분에는 흰색을 2칸 단위로 찍어내고
 흰색 부분에는 검은색을 2칸 단위로 찍어낸다.
 
*/