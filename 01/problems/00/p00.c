/* 
 * p00.c
 */

/* 
 * usage:
 * 
 *   ./a.out
 *
 * Intented behavior:
 * It should print the content of this file.
 *
 */

/* 
 * fix:
 *   stdio.h を include する
 */

#include <stdio.h>

int main()
{
  FILE * fp = fopen("p00.c", "rb");
  while (1) {
    int c = fgetc(fp);
    if (c == EOF) break;
    fputc(c, stdout);
  }
  return 0;
}
