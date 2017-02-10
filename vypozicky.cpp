#define _CRT_SECURE_NO_WARNINGS
#include "vypozicky.h"
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>


int readLoansFromFile(Vypozicky *loans)
{
	FILE *fl;							//vytvorenie smernika na binarny subor so zoznamom vypoziciek
	fl=fopen("vypozicky.dat","rb");		//otvorenie binarneho suboru so zoznamom vypoziciek
	int i = 0;							//vytvorenie premennej, ktora bude pocitat kolko vypoziciek obsahuje binarny subor
	while(fread(&loans[i], sizeof(Vypozicky), 1 , fl))//nacitavanie informacii z binarneho suboru
	{
		i++;							//zvysovanie poctu vypoziciek, kym sa neskonci cyklus
	}
	fclose(fl);							// prikaz na zatvorenie binarneho suboru so zoznamom vypoziciek
	return i;							// vratenie poctu vypozciek
}