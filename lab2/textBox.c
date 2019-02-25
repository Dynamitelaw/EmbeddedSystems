#include "textBox.h"

#include <stdio.h>
#include <string.h>


void initTextBox(struct textBox * textBox)
{
  memset(textBox->text, 0, TEXTBOX_SIZE);
  textBox->cursor = 0;
}


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


void processDelete(struct textBox * textBox)
{
  char newText[TEXTBOX_SIZE]; //Buffer where the next state of the textbox is stored
  memset(newText, 0, TEXTBOX_SIZE);
  int newCurs = 0;  //Keep track of current location in new text

  for (int oldCurs=0; oldCurs<TEXTBOX_SIZE; oldCurs++)
  {
    if (oldCurs != (textBox->cursor + 1))
    {
      //This character should not be removed. Copy over to new text
      newText[newCurs] = textBox->text[oldCurs];
      newCurs++;
    }   
  }

  memcpy(textBox->text, newText, TEXTBOX_SIZE);  //Overwrite text
}


void insertCharacter(struct textBox * textBox, char character)
{
  char newText[TEXTBOX_SIZE]; //Buffer where the next state of the textbox is stored
  memset(newText, 0, TEXTBOX_SIZE);
  int oldCurs = 0;  //Keep track of current location in old text

  for (int newCurs=0; newCurs<TEXTBOX_SIZE; newCurs++)
  {
    if (newCurs == textBox->cursor)
    {
      //The character should be insterted here. Add to new text
      newText[newCurs] = character;
    }
    else
    {
      newText[newCurs] = textBox->text[oldCurs];
      oldCurs++;
    }   
  }

  memcpy(textBox->text, newText, TEXTBOX_SIZE);  //Overwrite text
}


/*
 * Decriment cursor position on leftArrow
 */
void leftArrow(struct textBox * textBox)
{
  if (textBox->cursor != 0)
  {
    textBox->cursor = textBox->cursor - 1;
  }
}


/*
 * Incriment cursor position on rightArrow
 */
void rightArrow(struct textBox * textBox)
{  
  if (textBox->cursor < TEXTBOX_SIZE)
  {
    textBox->cursor = textBox->cursor + 1;
  }
}

