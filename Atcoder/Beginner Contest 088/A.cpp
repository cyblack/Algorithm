#include <cstdio>


int main(){
    
    int n,a;
    
    scanf("%d %d",&n,&a);
    
    if(n<500){
        if(n<=a) printf("Yes");
        else printf("No");
        return 0;
    }else {
        n = n - (n/500)*500;
        if(n<=a) printf("Yes");
        else printf("No");
    }
    
    
    return 0;

}