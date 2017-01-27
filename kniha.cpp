#define _CRT_SECURE_NO_WARNINGS
#include "kniha.h"
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>


int readBooksFromFile(Kniha *books)
{
	FILE *fb;							//vytvorenie smernika na binarny subor so zoznamom knih
	fb=fopen("knihy.dat","rb");			//otvorenie binarneho suboru so zoznamom knih
	int i = 0;							//vytvorenie premennej, ktora bude pocitat kolko knih obsahuje binarny subor
	while(fread(&books[i], sizeof(Kniha), 1 , fb))//nacitavanie informacii z binarneho suboru
	{
		i++;							//zvysovanie poctu citatelov, kym sa neskonci cyklus
	}
	fclose(fb);							// prikaz na zatvorenie binarneho suboru so zoznamom knih
	return i;							// vratenie poctu knih
}
