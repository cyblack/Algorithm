//
//  main.cpp
//  92.A
//
//  Created by 신원식 on 2018. 3. 25..
//  Copyright (c) 2018년 신원식. All rights reserved.
//

#include <cstdio>

int main(int argc, const char * argv[]) {
    
    int a,b,c,d;
    
    scanf("%d %d %d %d",&a,&b,&c,&d);
    
    if(a>b) a=b;
    if(c>d) c=d;
    
    printf("%d\n",a+c);
    
    return 0;
}
