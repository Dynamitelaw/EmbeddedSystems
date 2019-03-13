/*
 * Userspace program that communicates with the vga_ball device driver
 * through ioctls
 *
 * Stephen A. Edwards
 * Columbia University
 */

#include <stdio.h>
#include "vga_ball.h"
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define SCREENBORDER_X 155
#define SCREENBORDER_Y 115


int vga_ball_fd;

/* Read and print the background color */
void print_background_color() {
  vga_ball_arg_t vla;

  if (ioctl(vga_ball_fd, VGA_BALL_READ_BACKGROUND, &vla)) {
      perror("ioctl(VGA_BALL_READ_BACKGROUND) failed");
      return;
  }
  printf("%02x %02x %02x\n",
	 vla.background.red, vla.background.green, vla.background.blue);
}

/* Set the background color */
void set_background_color(const vga_ball_color_t *c)
{
  vga_ball_arg_t vla;
  vla.background = *c;
  if (ioctl(vga_ball_fd, VGA_BALL_WRITE_BACKGROUND, &vla)) {
      perror("ioctl(VGA_BALL_SET_BACKGROUND) failed");
      return;
  }
}

/* Set the ball position */
void set_ball_position(const vga_ball_position_t *pos)
{
  vga_ball_arg_t vla;
  vla.position = *pos;
  if (ioctl(vga_ball_fd, VGA_BALL_WRITE_POSITION, &vla)) {
      perror("ioctl(VGA_BALL_SET_POSITION) failed");
      return;
  }
}

int main()
{
  vga_ball_arg_t vla;
  int i;
  static const char filename[] = "/dev/vga_ball";

  static const vga_ball_color_t colors[] = {
    { 0xff, 0x00, 0x00 }, /* Red */
    { 0x00, 0xff, 0x00 }, /* Green */
    { 0x00, 0x00, 0xff }, /* Blue */
    { 0xff, 0xff, 0x00 }, /* Yellow */
    { 0x00, 0xff, 0xff }, /* Cyan */
    { 0xff, 0x00, 0xff }, /* Magenta */
    { 0x80, 0x80, 0x80 }, /* Gray */
    { 0x00, 0x00, 0x00 }, /* Black */
    { 0xff, 0xff, 0xff }  /* White */
  };

# define COLORS 9

  printf("VGA ball Userspace program started\n");

  if ( (vga_ball_fd = open(filename, O_RDWR)) == -1) {
    fprintf(stderr, "could not open %s\n", filename);
    return -1;
  }
  
  printf("initial state: ");
  print_background_color();

  //vga_ball_position_t position;
  //position.x = 0;
  //position.y = 0;
  //set_ball_position(&position);

  for (i = 0 ; i < 24 ; i++) {
    set_background_color(&colors[i % COLORS ]);
    print_background_color();
    usleep(4000);  
  }
  //return 0;
  //Move ball
  vga_ball_position_t position;
  position.x = 32;
  position.y = 80;
  set_ball_position(&position);

  printf("Bouncing ball...\n");

  int xVelocity = 3;
  int yVelocity = -10;

  int tempX;
  int tempY;

  while (1)
  {
    usleep(40000);

    //Check if ball will hit right or left of screen
    tempX = position.x + xVelocity;
    if ((tempX >= SCREENBORDER_X) || (tempX <= 4))
    {
      xVelocity = -1 * xVelocity;
      if (tempX >= SCREENBORDER_X) tempX = SCREENBORDER_X;
      else tempX = 4;
    }
    position.x = tempX;

    //Check if ball will hit top or bottom of screen 
    tempY = position.y + yVelocity;
    if ((tempY >= SCREENBORDER_Y) || (tempY <= 5))
    {
      yVelocity = -1 * yVelocity;
      if (tempY >= SCREENBORDER_Y) tempY = SCREENBORDER_Y;
      else tempY = 0;  
    }
    else
    {
      yVelocity = yVelocity + 1;  //Vertical acceleration to simulate gravity
    }
    position.y = tempY;
    

    //Update ball position
    set_ball_position(&position);
  }

  for (unsigned char pos = position.y; pos < SCREENBORDER_Y ; pos++)
  {
    position.y = pos;
    set_ball_position(&position);
    printf("Y = %i\n", pos);
    usleep(40000);
  }
  /*
  //perpetual while loop to bounce indefinetly
  while(1){
    //bounce down first, regardless of where it starts.
    for (int pos = position.y; pos > -1 ; pos--)
    {
      position.y = pos;
      set_ball_position(&position);
        printf("Y = %i\n", position.y);
        printf("X = %i\n", position.x);
        usleep(4000);
    }
    //picked 10 randomly because bounce movement seems unnatrual if it goes all the way back up.
    //could also do another loop which increments the bounce by 1 less which would eventually lead to the ball not bouncing then exit
    for(int pos = position.y; pos <10; pos++)
    {
      position.y = pos;
      set_ball_position(&position);
        printf("Y = %i\n", position.y);
        printf("X = %i\n", position.x);
        usleep(4000);
    }

  }
  */

  printf("VGA BALL Userspace program terminating\n");
  return 0;
}
