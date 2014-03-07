//
//  shell.c
//  
//
//  Created by Saikat Maitra on 04/03/14.
//
//

#include <stdio.h>
#define _GNU_SOURCE     /* Get declaration of strsignal() from <string.h> */
#include <string.h>
#include <signal.h>
#include <fcntl.h>

int
main(int argc, char *argv[])
{
	printf("%s",argv[1]);

}
