#include <stdio.h>

typedef struct{
	int capacity;
	int durability;
	int flavour;
	int texture;
	int calories;
}ingredient;

//global ingredients

ingredient sprinkles = {5, -1, 0, 0, 5};
ingredient peanutbutter = {-1, 3, 0, 0, 1};
ingredient frosting = {0, -1, 4, 0, 6};
ingredient sugar = {-1, 0, 0, 2, 8};

int getCookieValue(int spr, int pb, int fro, int sug);
int getCookieValue2(int spr, int pb, int fro, int sug);

int main()
{

	int best = 0;
	int best2 = 0;

	for(int spr=0; spr <= 100; spr++)
	{
		for(int pb=0; pb <= 100; pb++)
		{
			for(int fro=0; fro <= 100; fro++)
			{ //[spr,pb,fro,100-(spr+pb+fro)]
				if(spr+pb+fro <= 100)
				{
					int tmp = getCookieValue(spr, pb, fro, 100-(spr+pb+fro));
					if(tmp > best)
						best = tmp;
					tmp = getCookieValue2(spr, pb, fro, 100-(spr+pb+fro));
					if(tmp > best2)
						best2 = tmp;
				}
			}
		}
	}
	printf("best (part 1): %d\n", best);
	printf("best (part 2): %d\n", best2);
}

int getCookieValue(int spr, int pb, int fro, int sug)
{
	int capacity = spr*sprinkles.capacity +
		pb*peanutbutter.capacity +
		fro*frosting.capacity +
		sug*sugar.capacity;

	int durability = spr*sprinkles.durability +
		pb*peanutbutter.durability +
		fro*frosting.durability +
		sug*sugar.durability;

	int flavour = spr*sprinkles.flavour +
		pb*peanutbutter.flavour +
		fro*frosting.flavour +
		sug*sugar.flavour;

	int texture = spr*sprinkles.texture +
		pb*peanutbutter.texture +
		fro*frosting.texture +
		sug*sugar.texture;


	if(capacity < 0)
		capacity = 0;

	if(durability < 0)
		durability = 0;

	if(flavour < 0)
		flavour = 0;

	if(texture < 0)
		texture = 0;

	return capacity * durability * flavour * texture;
}


int getCookieValue2(int spr, int pb, int fro, int sug)
{
	int calories = spr*sprinkles.calories +
		pb*peanutbutter.calories +
		fro*frosting.calories +
		sug*sugar.calories;

	if (calories != 500)
		return -1;

	int capacity = spr*sprinkles.capacity +
		pb*peanutbutter.capacity +
		fro*frosting.capacity +
		sug*sugar.capacity;

	int durability = spr*sprinkles.durability +
		pb*peanutbutter.durability +
		fro*frosting.durability +
		sug*sugar.durability;

	int flavour = spr*sprinkles.flavour +
		pb*peanutbutter.flavour +
		fro*frosting.flavour +
		sug*sugar.flavour;

	int texture = spr*sprinkles.texture +
		pb*peanutbutter.texture +
		fro*frosting.texture +
		sug*sugar.texture;


	if(capacity < 0)
		capacity = 0;

	if(durability < 0)
		durability = 0;

	if(flavour < 0)
		flavour = 0;

	if(texture < 0)
		texture = 0;

	return capacity * durability * flavour * texture;
}
