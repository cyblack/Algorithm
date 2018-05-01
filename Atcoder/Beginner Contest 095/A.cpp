
#include <cstdio>

int main(int argc, const char * argv[]) {
 
    int ans = 700;
    
    for(int i=0;i<3;i++){
        char tmp;
        scanf("%c",&tmp);
        if(tmp=='o') ans+=100;
    }
    
    printf("%d\n",ans);
    
    
    return 0;
}
