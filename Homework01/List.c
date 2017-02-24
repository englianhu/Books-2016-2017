#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define StdSearch 1024
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

/*
	->Tries opening given file for Reading. If file can' t open,
	->Prints an error message and returns -1.
*/
int openGivenFile(FILE *inputFile, char fileName[]);

int searchOpenedFile(FILE *openedFile, char stringTaken[]);

int main(int argv, char * argc[])
{
	FILE *FileWillSearchen;
	/*Usage part of the tool.*/
	if (argv == 1)
	{
		fprintf(stderr, "Usage of the 'List': \n");
		fprintf(stderr, "\t->List \"String\" <Filename>\n");
		fprintf(stderr, "\t->This tool takes a String and File Name,\n");
		fprintf(stderr, "\t\tsearches the String inside of the taken File.\n");
		fprintf(stderr, "\t->Each time if found it, prints where it found\n");
		fprintf(stderr, "\t\tlike;\n\t->Times of Found: ~, Row: ~, Column: ~\n");
		return -1;
	}
	/*Error situation.*/
	else if(argv != 3)
	{
		fprintf(stderr, "Invalid input for tool.\n");
		fprintf(stderr, "Please use like this: \n");
		fprintf(stderr, "\t->List \"String\" <Filename>\n");
		return -1;
	}
	/*Working part of the tool.*/
	else
	{
		if (openGivenFile(FileWillSearchen, argc[2]) == 0)
			searchOpenedFile(FileWillSearchen, argc[1]);
		else
			return -1;
	}
	return 0;
}

int openGivenFile(FILE *inputFile, char fileName[])
{
	inputFile = fopen(fileName, "r");
	if (inputFile == NULL)
	{
		fprintf(stderr, "Error while openning file.\n");
		fclose(inputFile);
		return -1;
	}
	else if (feof(inputFile))
	{
		printf("The file is empty.\n");
		fclose(inputFile);
		return -1;
	}
	return 0;
}

int searchOpenedFile(FILE *openedFile, char stringTaken[])
{
	char oneCharFromFile, spaceSymbol = ' ';
	int rowinFile = 1, /*Sat�r*/
		columninFile = 1,/*S�tun*/
		everyFoundPart = 0, 
		unexpectedTokens = 0, 
		foundTimes = 0;
	do{
		
		/*
			Dosyadan ilk harf okunuyor.
		*/
		fscanf(openedFile, "%c", &oneCharFromFile);
		
		/*
			E�er yeni sat�r karakteri gelirse,
			rowinLine de�i�keni artt�r�l�p,
			columninFile 1 ile de�i�tiriliyor.
		*/
		if (oneCharFromFile == '\n')
		{
			++rowinFile;
			columninFile = 1;
		}
		
		/*
			E�er okunan karakter,
			aranan karakter ile ayn� ise;
			Aranan kelimenin b�t�n� var m� diye
			kontrol etmeye gidiyor.
		*/
		else if (oneCharFromFile == stringTaken[everyFoundPart])
		{

			/*
				Aranan ilk harf bulundu�una g�re,
				Aranan kelime, dosya i�inde harf harf bak�l�yor.
				Whitespace karakterleri yok say�l�yor.
					->Ayn� olan k�s�m kelimenin son harfine kadar taran�yor,
					->'\0' karakteri kontrol edilmiyor.
			*/
			while (oneCharFromFile == stringTaken[everyFoundPart]
				&& everyFoundPart < strlen(stringTaken) - 1)
			{
				/*
					Bir sonraki harf aran�yor.
				*/
				fscanf(openedFile, "%c", &oneCharFromFile);
				
				/*
					yeni sat�r, tab, bo�luk sembol� geldi�i zaman;
					Beklenmeyen i�aret de�i�keni artt�r�l�p,
					sembol yok say�l�yor.
				*/
				if (oneCharFromFile == spaceSymbol
					|| oneCharFromFile == '\n'
					|| oneCharFromFile == '\t')
					++unexpectedTokens;
				
				/*
					Al�nan harf sonras� dosya sonuna gelindiyse,
					fonksiyondan ��k�l�yor.
				*/
				else if (feof(openedFile))
					return 0;

				/*
					Bulunan her harf i�in,
					aranacak kelime i�indeki bir sonraki harfe ge�iliyor.
				*/
				else
					++everyFoundPart;
			}
			
			/*
				Bulunan harf say�s�, aranan kelimedeki harf say�s�na e�itse;
				Kelimenin bulunma say�s�n� 1 artt�r�yoruz,
				��eri�i ekrana bas�yoruz.
			*/
			if (everyFoundPart == strlen(stringTaken) - 1)
			{
				++foundTimes;
				printf("Times of Found: %d, ", foundTimes);
				printf("Row: %d, ", rowinFile);
				printf("Column: %d.\n", columninFile);
			}

			/*
				Dosya i�inde harfler tek tek tarand�ktan sonra,
				tamam� bulunsa da bulunmasa da, taranan t�m harflerden 1 az� kadar
				geri gidiliyor.
			*/
			fseek(openedFile, SEEK_CUR, -(everyFoundPart + unexpectedTokens) + 1);
			everyFoundPart = 0;
			unexpectedTokens = 0;
		}
		++columninFile;
	} while (foundTimes == 0);
	return 0;
}