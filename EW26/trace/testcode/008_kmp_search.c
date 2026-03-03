#include "test_config.h"
#ifdef TEST_008_KMPSEARCH

#include <stddef.h>

#define MAX_TEST	3000
#define PATTERN_LENGTH 20

static const char text0[]="1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234AB56789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890";
static const char pattern0[]="AB";
static const char text1[]="123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890ABCDEFGHIJKLMN01234567890";
static const char pattern1[]="ABCDEFGHIJKLMN";
static const char text2[]="123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890ABCDEFGHIJKLMN01234567890";
static const char pattern2[]="ABCDEFGHIJKLMN012345";


static const char *kmp_search(const char *text, const char *pattern);

int test_008(void)
{
	volatile const char *result;
	unsigned long j;


	static char c;
	for(j=0;j<MAX_TEST;j++){
    	result = kmp_search(text0, pattern0);
        //if(result== NULL) {
        //if(*result != 'A') {
        c = result[0];
        if(c != 'A') {
		  	for(;;);
		}
    	result = kmp_search(text1, pattern1);
		//if(result== NULL) {
        if(*result!= 'A') {
		  	for(;;);
		}
    	result = kmp_search(text2, pattern2);
		//if(result== NULL) {
        if(*result!= 'A') {
		  	for(;;);
		}
	}
        return 0;
}

const char *kmp_search(const char *text, const char *pattern)
{
    int table[PATTERN_LENGTH + 1] = {0, 0};
    int text_index = 1, pattern_index = 0;
    int i = 0;

    while((pattern[text_index]) != '\0') {
        if(pattern[text_index] == pattern[pattern_index]) {	
            table[++text_index] = ++pattern_index;
        }
		else if(pattern_index == 0) {
            table[++text_index] = 0;
        }
		else {

            pattern_index = table[pattern_index];
        }
    }

    while((*text) != '\0') {
        if((*text) == pattern[i]) {
            text++;
            if(pattern[++i] == '\0') {
                return text - PATTERN_LENGTH;
            }
        }
        else if(i == 0) {
            text++;
        } else {
            i = table[i];
        }
    }
    return( NULL );
}

#endif