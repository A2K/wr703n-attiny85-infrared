#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <memory.h>


int file = -1;
char* filename = "/dev/i2c-0";

void i2c_init()
{
  if ((file = open(filename, O_RDWR)) < 0)
  {
    perror("Failed to open the i2c bus");
  }
}

void i2c_reinit()
{
  close(file);
  i2c_init();
}

void i2c_write(char op)
{
  if (file < 0)
  {
    i2c_init();
  }

  if (file >= 0)
  {
    if (write(file, &op, 1) < 0)
    {
      i2c_reinit();
    }
  }
}

int main(int argc, char** argv)
{
  int sockfd, n;
  struct sockaddr_in servaddr, cliaddr;
  socklen_t len;
  char mesg;

  sockfd = socket(AF_INET, SOCK_DGRAM, 0);

  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(32000);
  bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

  for (;;)
  {
    n = recv(sockfd, &mesg, 1, 0);
    i2c_write(mesg);
  }
}

