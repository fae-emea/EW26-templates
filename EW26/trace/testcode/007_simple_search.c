#include "test_config.h"
#ifdef TEST_007_SIMPLESEARCH


#include <stddef.h>

#define MAX_TEST	2000	


const char text0[]="1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234AB56789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890";
const char pattern0[]="AB";
const char text1[]="123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890ABCDEFGHIJKLMN01234567890";
const char pattern1[]="ABCDEFGHIJKLMN";
const char text2[]="123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890ABCDEFGHIJKLMN01234567890";
const char pattern2[]="ABCDEFGHIJKLMN012345";

const char *simple_search(const char *text, const char *pattern);

volatile unsigned long j;

int test_007(void)
{
  const char *ans;
	//volatile unsigned long i,j;
	//static volatile unsigned long j;

	
	
	for(j=0;j<MAX_TEST;j++){
		ans = simple_search(text0,pattern0);
		if( ans==NULL ){
			for(;;);
		}
		ans = simple_search(text1,pattern1);
		if( ans==NULL ){
			for(;;);
		}
		ans = simple_search(text2,pattern2);
		if( ans==NULL ){
			for(;;);
		}
	}
	return 0;
}

const char *simple_search(const char *text,const char *pattern)
{
    int i;
	
    while((*text) != '\0') {

        for(i = 0; pattern[i] != '\0'; i++) {
            if(pattern[i] != text[i]) {
                break;              
            }
        }
        if(pattern[i] == '\0') {    
            return text;
        }
        text++;
    }
    return( NULL );
}

#endif