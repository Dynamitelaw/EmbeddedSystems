/*
 *
 * CSEE 4840 Lab 2 for 2019
 *
 * Name/UNI: Jose Rubianes (jer2201)
 *           Varun Varahabhotla (vv2282)
 */

#include "fbputchar.h"
#include "textBox.h"
#include "keyBindings.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "usbkeyboard.h"
#include <pthread.h>

/* Update SERVER_HOST to be the IP address of
 * the chat server you are connecting to
 */
/* micro36.ee.columbia.edu */

#define SERVER_HOST "128.59.148.182"
#define SERVER_PORT 42000

#define BUFFER_SIZE 128


/*
 * References:
 *
 * http://beej.us/guide/bgnet/output/html/singlepage/bgnet.html
 * http://www.thegeekstuff.com/2011/12/c-socket-programming/
 *
 */

int sockfd; /* Socket file descriptor */

struct libusb_device_handle *keyboard;
uint8_t endpoint_address;

pthread_t network_thread;
void *network_thread_f(void *);

int main()
{
  int err;

  struct sockaddr_in serv_addr;

  struct usb_keyboard_packet packet;
  int transferred;
  char keystate[12];

  if ((err = fbopen()) != 0) {
    fprintf(stderr, "Error: Could not open framebuffer: %d\n", err);
    exit(1);
  }

  /* Open the keyboard */
  if ( (keyboard = openkeyboard(&endpoint_address)) == NULL ) {
    fprintf(stderr, "Did not find a keyboard\n");
    exit(1);
  }

  /* Create a TCP communications socket */
  if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) {
    fprintf(stderr, "Error: Could not create socket\n");
    exit(1);
  }

  /* Get the server address */
  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(SERVER_PORT);
  if ( inet_pton(AF_INET, SERVER_HOST, &serv_addr.sin_addr) <= 0) {
    fprintf(stderr, "Error: Could not convert host IP \"%s\"\n", SERVER_HOST);
    exit(1);
  }

  /* Connect the socket to the server */
  if ( connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
    fprintf(stderr, "Error: connect() failed.  Is the server running?\n");
    exit(1);
  }

  /* Start the network thread */
  pthread_create(&network_thread, NULL, network_thread_f, NULL);

  //Instantiate textbox
  struct textBox textBox;
  initTextBox(&textBox);
  fbDrawLine(21, WHITE);  //Draw line to seperate textbox

  /* Look for and handle keypresses */
  for (;;) {
    libusb_interrupt_transfer(keyboard, endpoint_address,
			      (unsigned char *) &packet, sizeof(packet),
			      &transferred, 0);
    if (transferred == sizeof(packet)) {
      sprintf(keystate, "%02x %02x %02x", packet.modifiers, packet.keycode[0],
	      packet.keycode[1]);
      //printf("=>%s\n", keystate);
      //printf("=> [%d, %d, %d, %d, %d, %d]\n", packet.keycode[0], packet.keycode[1], packet.keycode[2], packet.keycode[3], packet.keycode[4], packet.keycode[5]);
      
      //Send message if ENTER is pressed
      if(packet.keycode[0]== KEY_ENTER)
      {
        int n = write(sockfd, textBox.text, TEXTBOX_SIZE);
        //Write exception later
        if(n<0)
        {
          fprintf(stderr, "Write Failed N<0. Check Network.");
          fbputs("Write Failed N<0. Check Network.",20, 0, RED, 1);
        }
        fbScrollUp();
        fbputs(textBox.text, 20, 0, GREEN, 1);
        printf("%s\n", textBox.text);
      }

      tbKeyboardPacket(&textBox, &packet);  //Process keypress in textbox
      fbPrintTextBox(&textBox, CYAN);  //Refresh textbox on screen
      if (packet.keycode[0] == 0x29) { /* ESC pressed? */
	       break;
      }
    }
  }

  //Clear frame buffer
  fbClear();

  /* Terminate the network thread */
  pthread_cancel(network_thread);

  /* Wait for the network thread to finish */
  pthread_join(network_thread, NULL);

  return 0;
}

void *network_thread_f(void *ignored)
{
  char recvBuf[BUFFER_SIZE];
  int n;
  /* Receive data */
  while ( (n = read(sockfd, &recvBuf, BUFFER_SIZE - 1)) > 0 ) {
    recvBuf[n] = '\0';
    printf("%s\n", recvBuf);
    fbScrollUp();
    enum color color = (recvBuf[0] == '#') ? YELLOW : WHITE;
    fbputs(recvBuf, 20, 0, color, 1);
  }

  return NULL;
}
