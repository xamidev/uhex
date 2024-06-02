#include <stdio.h>

// TODO: ASCII/Position printing 
// TODO: Stop appending garbage at file end

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

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    printf("Usage: %s <file>\n", argv[0]);
    return -1;
  }

  FILE* f = fopen(argv[1], "r");
  unsigned char buf[BYTES];
  int byteno = fread(buf, 1, BYTES, f);
  print_hex(buf, byteno);
  
  for (;;)
  {
    char cmd;
    int loc;
    scanf("%c%d", &cmd, &loc);
    switch(cmd)
    {
      case 'p':
      case 'P':
        print_hex(buf + loc, BYTES_PER_LINE);
        break;
      case 'e':
      case 'E':
        scanf("%hhx", buf + loc);
        break;
      case 's':
      case 'S':
        fclose(f);
        f = fopen(argv[1], "w");
        fwrite(buf, 1, BYTES, f);
        fclose(f);
        break;
      case 'q':
      case 'Q':
        return 0;
        break;
    }
  }
}
