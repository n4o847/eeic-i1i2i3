/* 
 * p05.c
 */

/* 
 * usage:
 *   ./a.out
 * 
 * Intended behavior
 *   It reads the contents of this file and print it.
 */

/* 
 * fix:
 *   "pO5.c" を "p05.c" に直す
 */

#include <assert.h>
#include <stdio.h>
int main()
{
  FILE * fp = fopen("p05.c", "rb");
  char buf[100];
  while (1) {
    int n = fread(buf, 1, 100, fp);
    if (n == 0) break;
    fwrite(buf, 1, n, stdout);
  }
  return 0;
}

