

#include <stdlib.h>
#include <unistd.h>

int main(int ac, char **av)
{
	char code[] = "cabdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	for (int i=0; i < atoi(av[1]); i++)
	{
		write(1,&code[i%62], 1);
	}
}
