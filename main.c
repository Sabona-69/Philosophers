#include <libc.h>

void f(){
	system("leaks a.out");
}

int	main()
{
	atexit(f);
	int *a = malloc(5 * sizeof(int));
	a[0] = 1;
	a[1] = 2;
	a[2] = 3;
	a[3] = 4;
	a[4] = 5;
	free(a);
}
