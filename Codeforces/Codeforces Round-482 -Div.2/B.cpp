#include <cstdio>
#include <cstring>
char str[2001];
char ans[2001];
int main(int argc, const char * argv[]) {
    
    int n,p;
    
    scanf("%d %d",&n,&p);
    
    scanf("%s",str);
    bool ok =true;
    for(int i=0;i+p<n;i++){
        if(str[i]=='.'){
            if(str[i+p]=='.'){
                str[i]='0';
                str[i+p]='1';
            }else if(str[i+p]=='0'){
                str[i]='1';
            }else if(str[i+p]=='1'){
                str[i]='0';
            }
            ok= false;
            break;
        }else if(str[i+p]=='.'){
            if(str[i]=='0') str[i+p]='1';
            else if(str[i]=='1') str[i+p]='0';
            ok=false;
            break;
        }else if(str[i]!=str[i+p]){
            ok=false;
            break;
        }
    }
    for(int i=0;i<n;i++){
        if(str[i]!='.') ans[i]=str[i];
        else ans[i]='0';
    }
    if(ok) printf("No\n");
    else printf("%s",ans);
    
    return 0;
}

/*
 
 i점이 . 이라면 (i+p)이 '.' '1' '0' 에 대해서 결정이 됨
 
 i+p이 . 이라면 i는 무조건 숫자다 -> i+p에는반대값
 
 i와 i+p가 둘다 숫자인데 다르다면 결과값은 동일
 
 세조건 중 하나라도 만족하지 않다면 .에 어떤값이 들어와도 i == i+p를 만족함
 
 
 */
