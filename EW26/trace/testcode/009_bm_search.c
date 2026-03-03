#include "test_config.h"
#ifdef TEST_009_BMSEARCH

#include <stddef.h>

#define MAX_TEST	4000


#define PATTERN_LENGTH 4
static const char text0[]="1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234ABCD56789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890";
static const char pattern0[PATTERN_LENGTH + 1]="ABCD";
static const char text1[]="123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890ABCDEFGHIJKLMN01234567890";
static const char pattern1[]="KLMN";
static const char text2[]="123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890ABCDEFGHIJKLMN01234567890";
static const char pattern2[]="MN01";



const char *bm_search(const char *text,const char *pattern);


int test_009(void)
{
  volatile	const char *result;
  unsigned long j;
  
  
  
  for(j=0;j<MAX_TEST;j++){
    result = bm_search(text0, pattern0);
    //if(result== NULL) {
    if(*result != 'A') {
      for(;;);
    }
    result = bm_search(text1, pattern1);
    //if(result== NULL) {
    if(*result != 'K') {
      for(;;);
    }
    result = bm_search(text2, pattern2);
    //if(result== NULL) {
    if(*result != 'M') {
      for(;;);
    }
  }
  return 0;
}

const char *bm_search(const char *text,const char *pattern)
{
    int table[512];

    int text_index, pattern_index, text_len, i;

    for(i = 0; i < 256; i++) {
        table[i] = PATTERN_LENGTH;
    }
    for(i = 0; i < PATTERN_LENGTH - 1; i++) {
        table[pattern[i]] = PATTERN_LENGTH - i - 1;
    }

    for(text_len=0;text[text_len]!='\0';++text_len)
        ;

    text_index = PATTERN_LENGTH - 1;

    while(text_index < text_len) {
        pattern_index = PATTERN_LENGTH - 1;
        while(text[text_index] == pattern[pattern_index]) {
            if(pattern_index==0) {
                return text+text_index;
            }
            text_index--;
            pattern_index--;
        }

        if(table[text[text_index]] > PATTERN_LENGTH - pattern_index) {
            text_index += table[text[text_index]];
        } else {
            text_index += PATTERN_LENGTH - pattern_index;
        }
    }

    return NULL;
}

#endif