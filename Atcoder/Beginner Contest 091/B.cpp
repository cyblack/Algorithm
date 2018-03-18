

#include <iostream>
#include <string>
#include <map>
#include <cstdio>
using namespace std;

string a[101];
string b[101];
map<string,int> mymap;
int main(int argc, const char * argv[]) {
    
    
    int n,m;
    
    scanf("%d",&n);
    
    for(int i=0;i<n;i++){
        cin >> a[i];
        
        mymap[a[i]]++;
        
    }
    scanf("%d",&m);
    for(int i=0;i<m;i++){
        cin >> b[i];
        mymap[b[i]]--;
    }
    
    int ans = 0;
    for (map<string,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it){
     //   cout << it->first << " " << it->second << '\n';
        if(ans < it->second){
            ans = it->second;
        }
    }
    printf("%d\n",ans);
    
    return 0;
}

/*
 
 map iterator 사용
 
 */
