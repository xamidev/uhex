#include <stdio.h>
#include <ctype.h>

// TODO: Stop appending garbage at file end
// TODO: Skip repeating lines

#define BYTES 1024
#define BYTES_PER_LINE 20

void print_hex(unsigned char* buf, int byteno, int pos)
{
  for (int i=0; i<byteno; i++)
  {
    if (i % BYTES_PER_LINE == 0)
    {
      //printf("%03d:  ", lineno);
      if (i != 0)
      {
        printf("  ");
        for (int j=i-BYTES_PER_LINE; j<i; j++)
        {
          if (isprint(buf[j])) printf("\x1b[33m%c\x1b[0m", buf[j]);
          else printf(".");
        }
      }
      puts("");
      // Here, we could print positions in hex but I prefer using integers. printf("%04X  ", i); 
      if (pos == 0) printf("\x1b[1;34m%06d:\x1b[0m   ", i);
      else printf("\x1b[34m%06d:\x1b[0m   ", pos);
    }
    printf("%.2X ", buf[i]);
  }

  // ASCII: last line 
  int padding = BYTES_PER_LINE - (byteno % BYTES_PER_LINE);
  if (padding < BYTES_PER_LINE)
  {
    for (int i=0; i<padding; i++) printf("   ");
    printf("  ");
  }
  int start = byteno - (byteno % BYTES_PER_LINE);
  for (int j = start; j < byteno; j++) {
    if (isprint(buf[j])) {
      printf("\x1b[33m%c\x1b[0m", buf[j]);
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
    printf("Usage: %s <file>\nInline commands:\n\tpX - print position X\n\teX - edit position X\n\ts  - save modified buffer\n\tq  - quit\n", argv[0]);
    return -1;
  }

  FILE* f = fopen(argv[1], "r");
  unsigned char buf[BYTES];
  int byteno = fread(buf, 1, BYTES, f);
  print_hex(buf, byteno, 0);
  
  for (;;)
  {
    char cmd;
    int loc;
     
    scanf(" %c", &cmd);
    if (cmd == 'p' || cmd == 'P' || cmd == 'e' || cmd == 'E') scanf("%d", &loc);

    switch(cmd)
    {
      case 'p':
      case 'P':
        print_hex(buf + loc, BYTES_PER_LINE, loc);
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
    }
  }
}
