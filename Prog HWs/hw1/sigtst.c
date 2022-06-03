
#include <fcntl.h>
#include <errno.h>
/* program that prints out signals that is receives. This will loop forever until a kill -9 is sent to it */

void sighdl(); /* signal handler */
int fd = 0; /* global file descriptor */

main()
{
int i;

/* open the output file */
fd = open("sigtst.out",O_RDWR | O_CREAT, 0666);
if (fd < 0)
{
printf("Unable to open sigtst.out, errno = %d\n",errno);
exit(1);
}

/* give us a process number to signal */
printf("Process id is %d\n",getpid());

/* set up handlers for all signals */
for (i=1; i<32; i++)
{
signal(i,sighdl);
}

/* loop until kill -9 */
while (1)
sleep(1);
}

void
sighdl(sigcode)
int sigcode;
{
char buf[80]; /* temp buffer to write output */

if (fd <= 0)
{
printf("output file not open, using stdout\n");
printf("Received signal %d\n",sigcode);
return;
}

signal(sigcode,sighdl);

/* clear the buffer */
memset(buf,'\0',80);

/* setup the buffer */
sprintf(buf,"Received signal %d\n",sigcode);
write(fd,buf,sizeof(buf));
return;
}