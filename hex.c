#include <stdio.h>
#include <ctype.h>

// TODO: ASCII/Position printing 
// TODO: Stop appending garbage at file end
// TODO: Simplify/clean some code (useless condition/loop guard brackets)

#define BYTES 1024
#define BYTES_PER_LINE 20

void print_hex(unsigned char* buf, int byteno)
{ 
  for (int i=0; i<byteno; i++)
  {
    if (i % BYTES_PER_LINE == 0)
    {
      if (i != 0)
      {
        printf("  ");
        for (int j=i-BYTES_PER_LINE; j<i; j++)
        {
          if (isprint(buf[j])) 
          {
            printf("%c", buf[j]);
          }
          else {
            printf(".");    
          }
        }
      }
      puts("");
    }
    printf("%.2X ", buf[i]);
  }

  // ASCII: last line 
  int padding = BYTES_PER_LINE - (byteno % BYTES_PER_LINE);
  if (padding < BYTES_PER_LINE)
  {
    for (int i=0; i<padding; i++)
    {
      printf("   ");
    }
    printf("  ");
  }

  int start = byteno - (byteno % BYTES_PER_LINE);
  for (int j = start; j < byteno; j++) {
    if (isprint(buf[j])) {
      printf("%c", buf[j]);
    }
    else {
      printf(".");
    }
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
    int loc = 0;
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
        if (!f) {
          perror("Error opening file for writing");
          return -1;
        }
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
