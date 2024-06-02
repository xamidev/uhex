#include <stdio.h>

// TODO: Error checking

#define BYTES 1024
#define BYTES_PER_LINE 10

void print_hex(unsigned char* buf, int byteno)
{
  for (int i=0; i<byteno; i++)
  {
    if (i % BYTES_PER_LINE == 0)
    {
      puts("");
    }
    printf("%.2X ", buf[i]);
  }
  puts("");
}

void main(int argc, char** argv)
{
  FILE* f = fopen(argv[1], "r");
  unsigned char buf[BYTES];
  int byteno = fread(buf, 1, BYTES, f);
  print_hex(buf, byteno);
  
  for (;;)
  {
    char cmd;
    int loc;
    scanf("%c%d", &cmd, &loc);

    if (cmd == 'p') print_hex(buf + loc, BYTES_PER_LINE);
    if (cmd == 'e') scanf("%x", buf + loc);
    if (cmd == 's') break;
  }

  fclose(f);
  f = fopen(argv[1], "w");
  fwrite(buf, 1, BYTES, f);
  fclose(f);
}
