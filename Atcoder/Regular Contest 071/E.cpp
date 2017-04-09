#include <cstdio>
#include <string>
#include <iostream>
using namespace std;
string s,t;
int sa[100001];
int ta[100001];
int main(){
    
    cin >> s;
    cin >> t;
  
    for(int i=0;i<s.size();i++) sa[i+1] = sa[i] + ((s[i]=='A') ? 1 : 2);
    for(int i=0;i<t.size();i++) ta[i+1] = ta[i] + ((t[i]=='A') ? 1 : 2);

    int q,a,b,c,d;
    cin >> q;
    while(q--){
        scanf("%d %d %d %d",&a,&b,&c,&d);
        if( (sa[b] - sa[a-1])%3 == (ta[d]-ta[c-1])%3) cout << "YES" <<'\n';
        else cout << "NO" << '\n';
    }
    return 0;
}



/*
 
 문자열은 a와b로 표현된다.
 
 3가지 기능
    a->bb변경
    b->aa변경
    aaa,bbb삭제
 
'한가지 문자로 표현해보자'가 핵심이다.
 
 부분 문자열을 모두 a형태로 표현한다.
 
 ex) abab -> a(aa)a(aa) 
 
 그렇게 되면 aaa를 삭제 가능 하므로 빈 문자열이 된다.
 
 즉 a로만 이루어진 문자열은 총 3가지 형태로만 나오게 된다.
 ' ', 'a', 'aa',
 
 즉, 어떤 부분문자열의 a개수만 알 수 있다면 %3으로 위의 3가지중 하나를 만들 수 있다.
 

*/