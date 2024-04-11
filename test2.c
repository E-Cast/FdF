#include <stdlib.h>

int	main(void)
{
	char	*mem;

	mem = calloc(1, sizeof(char));
	return (free(mem), 1);
}
