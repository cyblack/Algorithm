#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
vector<int> a;
int main(){
    
    int n;
    
    scanf("%d",&n);
    
    for(int i=0,tmp;i<n;i++) {
        
        scanf("%d",&tmp);
        a.push_back(tmp);
    }
    
    sort(a.begin(),a.end());
    
    int al = 0;
    int sl = 0;
    
    for(int i=0;i<n;i++){
        if(i&1) sl+=a[i];
        else al +=a[i];
    }
    
    printf("%d\n",(sl-al > 0) ? sl-al : -(sl-al));
    return 0;
}