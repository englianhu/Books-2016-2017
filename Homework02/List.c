/*
Yap�lacaklar:
*Uygulamay� a�
*Dosya ismi al
*Dosyay� okumak i�in a�
*Dosyada aranacak kelime, harf al.
*Her sat�r� tek tek oku
E�er bulunduysa:
*Bulundu�u sat�r, sat�r ba��na uzakl�k olarak  bir log dosyas�na yaz.
Bulunamad�ysa:
*Program� bitir.
*Dosyan�n sonuna aranan kelimeden az kald�ysa bitir.
*Dosya sonu gelince, dosyay� kapat.
*Kulland���n de�i�kenleri temizle.
*Program� kapat.
*/
#include "List.h"
char makeCharLover(char inputChar)
{
	if (inputChar >= 'A' && inputChar <= 'Z')
		inputChar += 'a' - 'A';
	else;
	return inputChar;
}

char *makeStrLover(char *inputStr)
{
	int charCounter = 0;
	while (charCounter < strlen(inputStr))
	{
		inputStr[charCounter] = makeCharLover(inputStr[charCounter]);
		++charCounter;
	}
	return inputStr;
}

int doesStringFound(FILE *openedFile, const char stringtaken[])
{
	int readCharactersFromFile = 0, sameParts = 1, error = 0;
	char charfromFile;
	fpos_t pos;
	fgetpos(openedFile, &pos);
	while (sameParts != strlen(stringtaken) && error != 1)
	{
		charfromFile = fgetc(openedFile);
		charfromFile = makeCharLover(charfromFile);
		++readCharactersFromFile;
		if (charfromFile == '\n' || charfromFile == '\t' || charfromFile == ' ');
		else if (charfromFile == stringtaken[sameParts])
			++sameParts;	
		else if (charfromFile == EOF || charfromFile != stringtaken[sameParts])
			error = 1;
	}
	fsetpos(openedFile, &pos);
	if (error == 0)
		return 1;
	return 0;
}

int searchOpenedFile(FILE *openedFile, const char stringTaken[])
{
	char oneCharFromFile;
	int rowinFile = 1, /*Sat�r*/
		columninFile = 1,/*S�tun*/
		foundTimes = 0;
	do{
		/*
			Dosyadan ilk harf okunuyor.
		*/
		oneCharFromFile = makeCharLover(fgetc(openedFile));
		/*
			E�er yeni sat�r karakteri gelirse,
			rowinLine de�i�keni artt�r�l�p,
			columninFile 1 ile de�i�tiriliyor.
		*/
		if (oneCharFromFile == '\n')
		{
			++rowinFile;
			columninFile = 0;
		}
		/*
			E�er okunan karakter,
			aranan karakter ile ayn� ise;
			Aranan kelimenin b�t�n� var m� diye
			kontrol etmeye gidiyor.
		*/
		else if (oneCharFromFile == stringTaken[0])
		{
			if (doesStringFound(openedFile, stringTaken) == 1)
			{
				++foundTimes;
				printf("[%d, %d] konumunda ilk harf bulundu.\n", rowinFile, columninFile);
			}
			else
				;
			}
		++columninFile;
	} while (oneCharFromFile != EOF);
	printf("\n\n%d adet %s bulundu.\n", foundTimes, stringTaken);
	return 0;
}