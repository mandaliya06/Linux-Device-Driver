#include <stdio.h>

int * display()
{
	int a=10;
	int *ptr=&a;
	a=20;
	return ptr;

}

main()
{

	int *ptr1;
	ptr1=display();
	printf("%d \n",*ptr1);
}
