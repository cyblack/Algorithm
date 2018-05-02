#include <cstdio>

int main(){
    
    int n;
    
    scanf("%d",&n);
    char x;
    getchar();
    bool ok = false;
    for(int i=0;i<n;i++){
        scanf("%c ",&x);
        if(x=='Y') ok = true;
    }
    
    if(ok) printf("Four\n");
    else printf("Three\n");
    
    return 0;
}