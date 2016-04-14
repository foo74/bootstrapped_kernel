/**************************************************************************
 * Attribute byte code. first 4 bits are background, next 4 are foreground.
 * 0 = BLACK            8 = DARK GREY
 * 1 = BLUE             9 = LIGHT BLUE
 * 2 = GREEN           10 = LIGHT GREEN
 * 3 = CYAN            11 = LIGHT CYAN
 * 4 = RED             12 = LIGHT RED
 * 5 = MAGENTA         13 = LIGHT MAGENTA
 * 6 = BROWN           14 = LIGHT BROWN
 * 7 = LIGHT GREY      15 = WHITE
 **************************************************************************/

#define CHAR_COLOR 0x02
#define VIDEO_MEMORY 0xb8000
#define VIDEO_ADDRESS 0xb8000
#define MAX_COLS 80
#define MAX_ROWS 25

/* Attribute byte for our default color scheme. */
#define GREEN_ON_BLACK 0x02

/* Screen device I/O ports. */
#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5

void clear_screen(char *);
void print_char(char character, int col, int row, char attribute_byte);
unsigned char port_byte_in(unsigned short port);
void port_byte_out(unsigned short port, unsigned char data);
unsigned short port_word_in(unsigned short port);
void port_word_out(unsigned short port, unsigned short data);
void print_message(char* video_memory, char s[]);
void set_cursor();

void main()
{
   /* Create a pointer to a char, and point it to the first text cell
    * of video memory (i.e. the top-left of the screen). */
   char* video_memory = VIDEO_MEMORY;
   char hello[] = "HELLO";
   int i;

   /* At the address pointed to by video_memory, store the character 'X'
    * (i.e. display 'X' in the top-left of the screen). */

   /*
   for (i=0; hello[i] != 0; i++)
   {
      *video_memory++ = hello[i];
      *video_memory++ = CHAR_COLOR;
     
      *video_memory++ = 'X';
      *video_memory++ = CHAR_COLOR;
      video_memory = video_memory + 0x100;
      *video_memory++ = 'Y';
      *video_memory++ = CHAR_COLOR;
   }
      */

   clear_screen(video_memory);

   /* last char of line is 0x9E in hex 
   video_memory += (80 * 2);
   *video_memory++ = 'X';
   *video_memory++ = CHAR_COLOR;
*/
   print_message(video_memory, hello);
   set_cursor();
   
}

void print_message(char* video_memory, char s[])
{
   int i;
   for (i=0; s[i] != 0; i++)
   {
      *video_memory++ = s[i];
      *video_memory++ = CHAR_COLOR;
   }
}

void clear_screen(char* video_memory)
{
   int i, j;
   for (i=0; i<25; i++)
   {
      for (j=0; j<80; j++)
      {
         *video_memory++ = ' ';
         *video_memory++ = CHAR_COLOR;
      }
   }
}

void set_cursor()
{
   port_byte_out(REG_SCREEN_CTRL, 14);
   port_byte_out(REG_SCREEN_DATA, 0x00);
   port_byte_out(REG_SCREEN_CTRL, 15);
   port_byte_out(REG_SCREEN_DATA, 0x50);
}

/*
void get_cursor(int offset)
{
   offset /= 2;
   port_byte_out(REG_SCREEN_CTRL, 14);
   offset = port_byte_in(REG_SCREEN_DATA) << 8;
   port_byte_out(REG_SCREEN_CTRL, 15);
   offset += port_byte_in(REG_SCREEN_DATA);
}


get_screen_offset()
{
}

handle_scrolling()
{
}
void print_char(char character, int col, int row, char attribute_byte)
{
   unsigned char *vidmem = (unsigned char *)VIDEO_ADDRESS;

   if (!attribute_byte)
      attribute_byte = GREEN_ON_BLACK;

   int offset;
   if (col >= 0 && row >= 0)
      offset = get_screen_offset(col, row);
   else
      offset = get_cursor();

   if (character == '\n')
   {
      int rows = offset / (2*MAX_COLS);
      offset = get_screen_offset(79, rows);
   }
   else
   {
      vidmem[offset] = character;
      vidmem[offset+1] = attribute_byte;
   }

   offset = handle_scrolling(offset);
   set_cursor(offset);
}
*/
/*****************************************************************************
 * A C wrapper function that reads a byte from the specified port
 * "=a" (result) means: put AL register in variable RESULT when finished
 * "d" (port) means: load EDX with port.
 *****************************************************************************/
unsigned char port_byte_in(unsigned short port)
{
   unsigned char result;
   __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
   return result;
}

void port_byte_out(unsigned short port, unsigned char data)
{
   __asm__("out %%al, %%dx" : :"a" (data), "d" (port));
}

unsigned short port_word_in(unsigned short port)
{
   unsigned short result;
   __asm__("in %%dx, %%ax" : "=a" (result) : "d" (port));
   return result;
}

void port_word_out(unsigned short port, unsigned short data)
{
   __asm__("out %%ax, %%dx" : :"a" (data), "d" (port));
}
