
#include <iostream>
char ans[51][51];
int main(int argc, const char * argv[]) {
    
    
    int a,b,c,d;
    
    scanf("%d %d %d %d",&a,&b,&c,&d);
    
    for(int i=1;i<=25;i++) for(int j=1;j<=25;j++) ans[i][j]='A';
    for(int i=1;i<=25;i++) for(int j=26;j<=50;j++) ans[i][j]='B';
    for(int i=26;i<=50;i++) for(int j=1;j<=25;j++) ans[i][j]='C';
    for(int i=26;i<=50;i++) for(int j=26;j<=50;j++) ans[i][j]='D';
    
    int start_i = 1;
    int start_j = 27;
    int cnt = 0;
    while(--a){
        ans[start_i][start_j] ='A';
        cnt++;
        start_j+=2;
        if(cnt>=11){
            start_i += 2;
            start_j = 27;
            cnt = 0;
        }
    }
    start_i = 1;
    start_j = 1;
    cnt = 0;
    while(--b){
        ans[start_i][start_j] ='B';
        cnt++;
        start_j+=2;
        if(cnt>=11){
            start_i+=2;
            start_j = 1;
            cnt = 0;
        }
    }
    start_i = 26;
    start_j = 27;
    cnt = 0;
    while(--c){
        ans[start_i][start_j] ='C';
        cnt++;
        start_j+=2;
        
        if(cnt>=11){
            start_i+=2;
            start_j = 27;
            cnt = 0;
        }
    }
    start_i = 26;
    start_j = 1;
    cnt = 0;
    
    while(--d){
        ans[start_i][start_j] ='D';
        cnt++;
        start_j+=2;
        
        if(cnt>=11){
            start_i+=2;
            start_j = 1;
            cnt = 0;
        }
    }
    printf("50 50\n");
    for(int i=1;i<=50;i++){
        for(int j=1;j<=50;j++){
            printf("%c",ans[i][j]);
        }printf("\n");
    }
    return 0;
}

/*
 
 50*50 행렬에
 
 4등분 후 A,B,C,D영역으로 나눈다.
 
 AB
 CD
 
 그 이후에 반대쪽 영역에 대해 1칸씩 건너뛰며 색칠
 
 A는 B에
 B는 A에
 C는 D에
 D는 C에 그려준다.
 
 */
