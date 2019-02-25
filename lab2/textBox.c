#include "textBox.h"

#include <stdio.h>
#include <string.h>

void processBackspace(struct textBox * textBox)
{
  if (textBox->cursor != 0)
  {
    char newText[TEXTBOX_SIZE]; //Buffer where the next state of the textbox is stored
    memset(newText, 0, TEXTBOX_SIZE);
    int newCurs = 0;  //Keep track of current location in new text

    for (int oldCurs=0; oldCurs<TEXTBOX_SIZE; oldCurs++)
    {
      if (oldCurs != (textBox->cursor - 1))
      {
        //This character should not be removed. Copy over to new text
        newText[newCurs] = textBox->text[oldCurs];
        newCurs++;
      }   
    }

    memcpy(textBox->text, newText, TEXTBOX_SIZE);  //Overwrite text
    textBox->cursor = textBox->cursor - 1;  //Decriment cursor position
  }

}
