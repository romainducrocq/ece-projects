#include <stdio.h>
#include <time.h>

unsigned long long multiplicationEgyptienneRecursive(unsigned long long  x, unsigned long long y)
{
	if (x == 0)
		return 0;
	else if (x % 2 == 0)
		return multiplicationEgyptienneRecursive(x / 2, 2*y);
	else if (x % 2 == 1)
		return multiplicationEgyptienneRecursive(x - 1, y) + y;
	else
		return y;
}

unsigned long long multiplicationEgyptienneIterative(unsigned long long x, unsigned long long y)
{
	unsigned long long res=0;
	while(y>0)
	{
		if(y%2==0)
		{
			x=2*x;
			y=y/2;
		}
		else
		{
			res=res+x;
			y=y-1;
		}
	}
	return res;
}

unsigned long long multiplicationClassique(unsigned long long x, unsigned long long y)
{
	unsigned long long res=0, i;
	if(x<y)
	{
		unsigned long long tmp;
		tmp=x;
		x=y;
		y=tmp;
	}
	for(i=0; i<y; i++)
	{
		res = res + x;
	}
	return res;
}

void tempsExecution(char mul[], unsigned long long x, unsigned long long y, unsigned long long(*multiplier)(unsigned long long, unsigned long long))
{
    clock_t start, end;
	start=clock();
	printf("%s : %llu * %llu = %llu", mul, x, y, multiplier(x,y));
	end=clock();
   	printf(" - Temps : %f\n", (double)(end-start)/CLOCKS_PER_SEC);
}

int main()
{
	unsigned long long x, y;
	printf("Entrez 2 nombres positifs tres grands mais pas trop grands quand meme SVP : \n");
	scanf("%llu %llu",&x,&y);

	tempsExecution("Multiplication egyptienne recursive", x, y, multiplicationEgyptienneRecursive);
	tempsExecution("Multiplication egyptienne iterative", x, y, multiplicationEgyptienneIterative);
	tempsExecution("Multiplication classique", x, y, multiplicationClassique);

return 0;
}
