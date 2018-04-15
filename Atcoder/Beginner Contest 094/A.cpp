
#include <cstdio>

int main(int argc, const char * argv[]) {
   
    int a,b,x;
    
    scanf("%d %d %d",&a,&b,&x);
    
    if(a>x) printf("NO\n");
    else{
        if(a+b >= x) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
