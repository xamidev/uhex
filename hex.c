#include <stdio.h>
#include <ctype.h>
#include <sys/ioctl.h>
#include <unistd.h>

// TODO: Skip repeating lines

#define BYTES 1024
//#define BYTES_PER_LINE 10
#define round(x) (int)(x < 0 ? (x -0.5) : x + 0.5)

void print_hex(unsigned char* buf, int byteno, int pos, int BYTES_PER_LINE)
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
          if (isprint(buf[j])) printf("\x1b[33m%c\x1b[0m", buf[j]);
          else printf(".");
        }
      }
      puts("");
      // Here, we could print positions in hex but I prefer using integers. printf("%04X  ", i); 
      if (pos == 0) printf("\x1b[1;34m%06d:\x1b[0m   ", i);
      else printf("\x1b[1;34m%06d:\x1b[0m   ", pos);
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

  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  int BYTES_PER_LINE = round((w.ws_col-14)/4);

  FILE* f = fopen(argv[1], "rb+");
  if (!f)
  {
    printf("Error opening file %s\n", argv[1]);
    return -1;
  }
  unsigned char buf[BYTES];
  int byteno = fread(buf, 1, BYTES, f);
  print_hex(buf, byteno, 0, BYTES_PER_LINE);
  
  for (;;)
  {
    char cmd;
    int loc;
     
    scanf(" %c", &cmd);
    if (cmd == 'p' || cmd == 'e') scanf("%d", &loc);

    switch(cmd)
    {
      case 'p': 
        print_hex(buf + loc, BYTES_PER_LINE, loc, BYTES_PER_LINE);
        break;
      case 'e':
        int value;
        scanf("%x", &value);
        if (loc < byteno) buf[loc] = (unsigned char)value;
        break;
      case 's':
        fseek(f, 0, SEEK_SET);
        fwrite(buf, 1, byteno, f);
        fclose(f);
        return 0;
        break;
      case 'q':
        return 0;
    }
  }
}
