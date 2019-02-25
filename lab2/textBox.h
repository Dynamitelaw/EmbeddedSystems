#define TEXTBOX_SIZE 64


struct textBox
{
  int cursor;
  char text[TEXTBOX_SIZE];
};

void processBackspace(struct textBox * textBox);

