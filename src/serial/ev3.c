#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <sys/wait.h>
#include <sys/ioctl.h>
#include "lms2012\lms2012.h"
#include "C:\BricxCC\lms_api\ev3_output.h"
#include "C:\BricxCC\lms_api\ev3_command.h"
#include "C:\BricxCC\lms_api\ev3_lcd.h"
// Definition of Serial communication.
#define BAUDRATE 9600
#define MODEMDEVICE "/dev/ttyACM0"
// global variables.
struct termios oldTermio; // for keep original setting.
// Prototype of function.
int Serial_begin(int brate, char* devicePath);
void Serial_end(int fd);
int Serial_write(int fd, uint8_t pbyte);
uint8_t Serial_read(int fd);
int analogToCentimeter(int analogValue);
int main(int argc, char *argv[])
{
int fd = -1;
uint8_t rcvByte[16];
int data;
int i, j;
char disp[64];
OutputInit();
// Initialize serial port.
fd = Serial_begin(BAUDRATE, MODEMDEVICE);
if (fd < 0)
{
 printf("Serial port initialize Error.\n");
 exit(-1);
}
LcdInit();
LcdRefresh();
LcdScroll(10);
LcdSelectFont(1);
LcdText( 0, 2, 100, "Sart Serial Communication");
for (i = 0; i < 1000; i++)
{
 Serial_write(fd, 0x05);
 usleep(500000);
 for (j = 0; j < 4; j++)
 {
 rcvByte[j] = Serial_read(fd);
 }
 data = (int)( (((int)rcvByte[1]) << 8) | ((int)rcvByte[2]) );

 printf("%d\n", data);
 sprintf(disp, "%d %d", i, data);
 LcdScroll(10);
 LcdText( 1, 2, 100, disp);

 if (data > 300) {
 OnFwdEx(OUT_AB,70,0); //AB Port Motor Start Power 70
 Wait(100); //Wait 100msec
 Off(OUT_AB); //AB Port Motor Stop
 }
 usleep(500);
}
return 0;
}
int Serial_begin(int brate, char* devicePath)
{
int fd;
struct termios newTermio;
// open the device.
fd = open(devicePath, O_RDWR | O_NOCTTY);
if (fd < 0)
{
 // failed to open device.
 perror(devicePath);
 exit(-1);
}
// get original setting and keep it.
tcgetattr(fd, &oldTermio);
 // Initialize new_term_io' control code.
newTermio.c_iflag = 0;
newTermio.c_oflag = 0;
newTermio.c_cflag = 0;
newTermio.c_lflag = 0;
newTermio.c_line = 0;
memset(newTermio.c_cc, '\0', sizeof(newTermio.c_cc));
// Configure port.
// B9600 = 9600bps(default)
// CS8 = 8bit, no parity, 1 stopbit
// CLOCAL = local(non modem control)
// CREAD = enable read charactor
switch (brate)
{
case 300:
 newTermio.c_cflag = B300 | CS8 | CLOCAL | CREAD;
 break;
case 1200:
 newTermio.c_cflag = B1200 | CS8 | CLOCAL | CREAD;
 break;
case 2400:
 newTermio.c_cflag = B2400 | CS8 | CLOCAL | CREAD;
 break;
case 4800:
 newTermio.c_cflag = B4800 | CS8 | CLOCAL | CREAD;
 break;
case 9600:
 newTermio.c_cflag = B9600 | CS8 | CLOCAL | CREAD;
 break;
case 19200:
 newTermio.c_cflag = B19200 | CS8 | CLOCAL | CREAD;
 break;
case 38400:
 newTermio.c_cflag = B38400 | CS8 | CLOCAL | CREAD;
 break;
case 57600:
 newTermio.c_cflag = B57600 | CS8 | CLOCAL | CREAD;
 break;
case 115200:
 newTermio.c_cflag = B115200 | CS8 | CLOCAL | CREAD;
 break;
default:
 newTermio.c_cflag = B9600 | CS8 | CLOCAL | CREAD;
 break;
}
// Setting parity error is ignore.
newTermio.c_iflag = IGNPAR;
// Raw mode output.
newTermio.c_oflag = 0;
// Setting input mode. non-canonical, no echo,
newTermio.c_lflag = 0;
// inter-character timer
newTermio.c_cc[VTIME] = 0;
// Read block still received one char.
newTermio.c_cc[VMIN] = 1;
// Clear modem line.
tcflush(fd, TCIFLUSH);
// Apply new configure.
tcsetattr(fd, TCSANOW, &newTermio);
// Wait.
sleep(3);
// Return file descriptor.
return (fd);
}
void Serial_end(int fd)
{
if (fd >= 0)
{
 tcsetattr(fd, TCSANOW, &oldTermio);
 close(fd);
}
}
int Serial_write(int fd, uint8_t pbyte)
{
ssize_t res;
res = write(fd, &pbyte, 1);
return (int)res;
}
uint8_t Serial_read(int fd)
{
uint8_t c;
read(fd, (char *)&c, 1);
return c;
}