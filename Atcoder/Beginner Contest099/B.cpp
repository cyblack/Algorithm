
#include <cstdio>

int main(int argc, const char * argv[]) {
    
    int a,b;
    
    scanf("%d %d",&a,&b);
    
    int diff = b-a;
    
    int tmp = 0;
    for(int i=1;i<=diff;i++)tmp+=i;
    
    printf("%d\n",tmp-b);
    
    return 0;
}

/*
 
 답이 존재한다는 가정하에
 
 A + x : (1+..+n)
 B + x : (1+..+n+(n+1))
 구조니까
 
 위에서 아래를 빼면
 
 b-a = (n+1)이다
 

*/