#ifndef _TEXTBOX_H
#define _TEXTBOX_H

#include "usbkeyboard.h"

#define TEXTBOX_SIZE 64


struct textBox
{
  int cursor;
  char text[TEXTBOX_SIZE];
  uint8_t oldKeycode;
};

void initTextBox(struct textBox * textBox);
void tbBackspace(struct textBox * textBox);
void tbDelete(struct textBox * textBox);
void tbInsert(struct textBox * textBox, char character);
void tbLeftArrow(struct textBox * texBox);
void tbRghtArrow(struct textBox * textBox);
void tbKeypress(struct textBox * textBox, struct usb_keyboard_packet * packet);


#endif
