#ifndef _FBPUTCHAR_H
#define _FBPUTCHAR_H

#include "textBox.h"

#define FBOPEN_DEV -1          /* Couldn't open the device */
#define FBOPEN_FSCREENINFO -2  /* Couldn't read the fixed info */
#define FBOPEN_VSCREENINFO -3  /* Couldn't read the variable info */
#define FBOPEN_MMAP -4         /* Couldn't mmap the framebuffer memory */
#define FBOPEN_BPP -5          /* Unexpected bits-per-pixel */

#define TRUE 1
#define FALSE 0

enum color {BLACK, WHITE, RED, GREEN, BLUE, PURPLE, YELLOW, CYAN};

extern int fbopen(void);
extern void fbputchar(char, int, int, enum color color, int invert);
extern void fbputs(const char *, int, int, enum color color);
extern void fbDrawLine(int row, enum color color);

/*
 * Prints the given textbox on the second to last line 
 */
void fbPrintTextBox(struct textBox * textBox, enum color color);

extern void fbClear();
void fbScrollUp();

#endif
