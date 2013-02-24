//
//  main.c
//  unix-netwk-prog
//
//  Created by Saikat Maitra on 06/02/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include <stdio.h>

int main (int argc, const char * argv[])
{

    printf ("Hello World!");
    printf("\n");
    int a=4;
    int b=5;
    int z = a+b;
    printf("The value of z : ");
    printf("%d",z);
    printf("\n");
    char label[] = "abcde";
    int i;
    for(i=0;i<sizeof(label);i++){
        printf("%c",label[i]);
        printf("\n");
    
    }
    return 0;
}

