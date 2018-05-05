
#include <cstdio>

int main(int argc, const char * argv[]) {
   
    int a,b;
    
    scanf("%d %d",&a,&b);
    
    if(a==b) printf("%d\n",a);
    else if(a>b){ //11 3
        printf("%d\n",a-1);
    }else { //3 11
        printf("%d\n",a);
    }
    
    
    return 0;
}
