#include <cstdio>

int main(int argc, const char * argv[]) {
  
    int a,b,x;
    
    scanf("%d %d %d",&x,&a,&b);
    
    x-=a;
    
    printf("%d\n",x-(x/b)*b);
    
    return 0;
}
