#define TEXTBOX_SIZE 64


struct textBox
{
  int cursor;
  char text[TEXTBOX_SIZE];
};

void initTextBox(struct textBox * textBox);
void processBackspace(struct textBox * textBox);
void processDelete(struct textBox * textBox);
void insertCharacter(struct textBox * textBox, char character);
/*
 * Decriment cursor position on leftArrow
 */
void leftArrow(struct textBox * textBox);

/*
 * Incriment cursor position on rightArrow
 */
void rightArrow(struct textBox * textBox);
