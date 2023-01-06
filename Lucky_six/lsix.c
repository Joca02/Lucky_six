#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<ctype.h>
#include <conio.h>

#include<stdbool.h>		//ako VS2010 nece da ucita biblioteku, komentarisati ovu liniju koda i "uncommentovati" 3 linije ispod

//typedef int bool;
//#define false 0
//#define true 1



struct kuglica {
	char boja[21];
	int broj;
};
typedef struct kuglica Kuglica;

char* kreiraj_nalog();	//poziva se iz glavne funkcije ili iz funkcije login(),korisnik kreira nalog i broj pobeda/poraza se setuje na 0/0 -vraca string korisnicko_ime
char* login();	//poziva se iz glavnog programa ili iz funkcije kreiraj_nalog() -vraca string korisnicko_ime
void kraj_programa();	//poziva se iz glavne funkcije ili iz funkcije login() ako korisnik nije uspeo da unese tacnu sifru za uneto korisnicko ime vise puta

void print_izbor_igara();	//poziva se iz glavne funkcije i prikazuje igre koje korisnik moze da igra
void setovanje_kuglica(Kuglica kuglice[]);	//poziva se iz glavne funkcije i postavlja brojeve i boju za svaku kuglicu u nizu od 48 kuglica
Kuglica* izvlacenje(Kuglica kuglice[]);	 //poziva se iz glavne funkcije, kreira niz od nasumicno izvucenih kuglica koji vraca
float opcije_za_kladjenje(Kuglica* izvuceni_brojevi);	//poziva se iz glavne funkcije, u njoj korisnik bira koje igre zeli da odigra i vraca kvotu

//funckije koje su indeksirane se pozivaju iz funkcije opcije_za_kladjenje(), sve vracaju svoju kvotu, a kolicnik svih pozvanih kvota vraca opcija_za_kladjenje()
/*1.*/ float lucky_six(Kuglica* izvuceni_brojevi);	  //proverava da li se korisnicko-unetih 6 brojeva kuglica nalazi u 35 random izvucenih kuglica
bool provera_izvucene_kuglice(int korisnikove_kuglice[], int broj);		//poziva se iz lucky_six() -vraca true ako se korisnikovih 6 kuglica nalaze u nasumicno izvucenih 35
float odredi_kvotu(int mesto_dobitka);	//poziva se iz lucky_six(), vraca razlicite kvote u zavisnosti kada je korisnik uspeo da pogodi 6 izvucenih kuglica
/*2.*/ float broj_u_prvih_5(Kuglica* izvuceni_brojevi);   //proverava da li se korisnikov broj nalazi u prvih 5 izvucenih kuglica
/*3.*/ float suma_prvih_5(Kuglica* izvuceni_brojevi);	//korisnik unosi da li je suma prvih 5 kuglica veca ili manja od 122.5 i to program proverava
/*4.*/ float parnost_prve_kugle(Kuglica* izvuceni_brojevi);  //korisnik pogadja da li prva kugla ima paran ili neparan broj
/*5.*/ float boja_prve_kugle(Kuglica* izvuceni_brojevi);	//korisnik pogadja boju prve kugle gde moze uneti 1 ili 4 boja za pogadjanje od mogucih 8 boja
bool provera_da_se_boja_ponavlja(char boje[4][16], char* boja, int n); //poziva se iz boja_prve_kugle() -vraca false ako uneta boja nije prethodno uneta, u suprotnom vraca true
/*6.*/ float broj_prve_kugle_veci_manji(Kuglica* izvuceni_brojevi);  //korisnik pogadja da li je broj prve kugle veci ili manji od 24.5
/*7.*/ float vise_par_nepar_u_prvih_5(Kuglica* izvuceni_brojevi);  //korisnik pogadja da li ima vise parnih ili neparnih brojeva u prvih 5 izvucenih kuglica

void print_izvlacenje(Kuglica* izvuceni_brojevi);	//poziva se iz glavne funkcije i simulira izvlacenje 35 kuglica
void delay(unsigned timeout);	//poziva se iz funkcije print_izvlacenje()
					//preko ove funkcije se na svakih timeout milisekundi prikaze informacija o jednoj izvucenoj kuglici

void prikazi_isplatu(float kvota, float uplata, char* korisnik);	//poziva se iz glavne funkcije i izbacuje obavestenje korisniku o uspesnosti njegovog tiketa

void kopira_dat1_u_dat2(char* korisnik, char* izvor, char* cilj, bool pobeda); //poziva se iz prikazi_isplatu()
//kopira binarnu datoteku izvor u binarnu datoteku cilj, ako se string korisnik poklopi sa korisnickim imenom iz datoteke "izvor"
//inkrementuje broj_pobeda ili broj_poraza u zavisnosti od stanja bool pobeda npr pobeda=true-->broj_pobeda++, pa se azuriran podatak upisuje u datoteku "cilj"

void provera_otvaranja_datoteke(FILE* fptr); //poziva se iz funkcije kopira_dat1_u_dat2() i proverava otvaranje datoteke
void broj_pobeda_poraza(int* pobeda_gubitak);  //poziva se iz kopira_dat1_u_dat2() i prikazuje informacije o procentu pobede za ulogovanog korisnika
								//kao i ukupan broj pobeda i gubitaka za taj nalog





main()
{
	int izbor;
	char* korisnik=NULL;
	float  uplata,kvota;
	float isplata;
	Kuglica kuglice[48];
	Kuglica* izvuceni_brojevi;

	printf("1. Kreiraj nalog\n2. Uloguj se u nalog\n3. Izadji iz aplikacije");
	do
	{
		printf("\nUnesi svoj izbor: ");
		scanf("%d", &izbor);
		if (izbor < 1 || izbor>3)
			printf("\nOpcija mora biti 1, 2 ili 3");
	} while (izbor < 1 || izbor>3);

	switch (izbor)
	{
	case 1:
		korisnik = kreiraj_nalog();
		break;
	case 2:
		korisnik = login();
		break;
	case 3:
		kraj_programa();
		break;
	}
	
	
	
	print_izbor_igara();
	
	setovanje_kuglica(kuglice);
	izvuceni_brojevi = izvlacenje(kuglice);
	
	kvota = opcije_za_kladjenje(izvuceni_brojevi);

	system("cls");

	do {
		printf("\nUnesite uplatu u dinarima: ");
		scanf("%f", &uplata);
		if (uplata < 20)
			printf("\nNajmanja uplata mora biti bar 20din!");
		else if (uplata > 100000000)
			printf("\nNajveca uplata koju mozete uneti je 100.000.000din!");

	} while (uplata<20 || uplata>100000000);

	print_izvlacenje(izvuceni_brojevi);
	
	prikazi_isplatu(kvota, uplata, korisnik);
	
	free(izvuceni_brojevi);
	free(korisnik);

	return 0;
}

char* kreiraj_nalog()
{
	char korisnicko_ime[51], poredi[51], sifra[51];
	int l;
	int lokacija;
	char c;
	bool provera = true;
	int i;
	int broj_pobeda_poraza[2] = { 0,0 };
	FILE* fptr;
	
	fptr = fopen("baza.bin", "rb");
	if (fptr == NULL)
		//ako baza.bin ne postoji nece biti provere da li je korisnicko ime vec zauzeto, vec ce se otvoriti za upis od pocetka 
	{

		do
		{
			printf("\nUnesi svoje korisnicko ime za nov nalog: ");

			scanf("%s", korisnicko_ime);
			l = strlen(korisnicko_ime);
			for (i = 0; i < l; i++)
			{
				if (isalnum(korisnicko_ime[i]) != 0)
					continue;
				else
				{
					i--;
					break;
				}

			}
			if (i != l)
				printf("\nKorisnicko ime mora da sadrzi samo slova i karaktere!\n");
		} while (i != l);
			//petlja iznad proverava korektan unos korisnickog imena

		fptr = fopen("baza.bin", "wb");
		fwrite(korisnicko_ime, sizeof(char), l, fptr);

		fputc('-', fptr);
			//fputc koristim kao razmak izmedju korisnickog_imena - lozinke - broj_pobeda_poraza
		do
		{
			printf("\nUnesi sifru za nov nalog: ");
			scanf("%s", sifra);
			l = strlen(sifra);
			if (l < 3 || l>15)
				printf("\nSifra mora da sadrzi najmanje 3 karaktera a najvise 15!\n");
			else if (sifra[l - 1] == '-')
				printf("\nSifra se NE sme zavrsiti sa karakterom '-' \n");
		} while (l < 3 || l>15 ||sifra[l-1]=='-');
			
		fwrite(sifra, sizeof(char), l, fptr);
		fputc('-', fptr);
		
		fwrite(broj_pobeda_poraza, sizeof(int), 2, fptr);
			//pri kreaciji naloga setuje broj pobeda i poraza na 0 0

		fputc('\n', fptr);
		fclose(fptr);
		printf("\nUspesno ste se napravili nalog! Molimo vas da se ulogujete.");
		return login();
			//kreiraj_nalog funkcija ce uvek da vrati string koji vraca funkcija login
	}
	else {
		while (provera)
		{
			provera = true;
			do
			{
				printf("\nUnesi svoje korisnicko ime za nov nalog: ");

				scanf("%s", korisnicko_ime);
				l = strlen(korisnicko_ime);
				for (i = 0; i < l; i++)
				{
					if (isalnum(korisnicko_ime[i]) != 0)
						continue;
					else
					{
						i--; //smanjujem i za 1 da bih pokrio slucaj kada je poslednji karakter znak
						break;
					}

				}
				if (i != l)
					printf("\nKorisnicko ime mora da sadrzi samo slova i karaktere!\n");
			} while (i != l);

			while (1) {

				if ((c = fgetc(fptr)) == EOF)
				{
					lokacija = ftell(fptr) - 1;
					fclose(fptr);
					fptr = fopen("baza.bin", "ab");
					fseek(fptr, lokacija, SEEK_SET);
					fwrite(korisnicko_ime, sizeof(char), l, fptr);
					fputc('-', fptr);

					do
					{
						printf("\nUnesi sifru za nov nalog: ");
						scanf("%s", sifra);
						l = strlen(sifra);
						if (l < 3 || l>15)
							printf("\nSifra mora da sadrzi najmanje 3 karaktera a najvise 15!\n");
						else if (sifra[l - 1] == '-')
							printf("\nSifra se NE sme zavrsiti sa karakterom '-' \n");
					} while (l < 3 || l>15 || sifra[l - 1] == '-');

					
					fwrite(sifra, sizeof(char), l, fptr);
					fputc('-', fptr);
					fwrite(broj_pobeda_poraza, sizeof(int), 2, fptr);

					fputc('\n', fptr);

					provera = false;
					system("cls");
					fclose(fptr);

					printf("\nUspesno ste se napravili nalog! Molimo vas da se ulogujete.");
					return login();
					break;
				}
					//kupi karakter, ako je EOF znaci da nema vise zauzetih korisnickih imena

				fseek(fptr, -1, SEEK_CUR);
					//u slucaju da karakter nije EOF, fptr se vraca 1 mesto nazad radi provere sledeceg korisnickog imena
				

				fread(poredi, sizeof(char), l + 1, fptr);
				if (poredi[l] == '-')
						//ako je l-ti karakter '-' znaci da je uneta rec iste duzine kao i rec sa kojom se poredi
					poredi[l] = NULL;
				if (strcmp(poredi, korisnicko_ime) == 0)
				{
					printf("\nKorisnicko ime vec postoji!");
					rewind(fptr);
					break;
				}

				while (1)
				{
					c = fgetc(fptr);
					if (c == '\n')
						break;
				}


			}
		}
	}
}

char * login()
{
	char *korisnicko_ime, poredi[51], sifra[51],nov_nalog[51];
	int l, brojac_neuspelih_loginova = 3;
	int pobeda_gubitak[2];
	char c;
	bool provera = true;

	FILE* fptr;

	korisnicko_ime = malloc(21 * sizeof(char));	
	if (korisnicko_ime == NULL)
	{
		printf("\nGreska pri dinamickoj dodeli memorije.");
		exit(1);
	}

	fptr = fopen("baza.bin", "rb");
	if (fptr == NULL)
	{
		printf("\nU bazi ne postoji ni jedan nalog.");
		return kreiraj_nalog();
	}
	else
	{
		while (provera)
		{
			provera = true;
		
			printf("\nUnesi svoje korisnicko ime: ");
			scanf("%s", korisnicko_ime);
			
			l = strlen(korisnicko_ime);

			while (1) {

				fread(poredi, sizeof(char), l+1, fptr);
				//citam l+1 karakter kako bih potvrdio da su korisnicko ime sa tastature i iz baze iste duzine
				//ovim pokrivam slucaj da "koris" ne bi mogao da se uloguje na nalog "korisnik" jer koris_ime sme da ima samo slova i brojeve
				if (poredi[l] == '-')
					poredi[l] = NULL;
				if (strcmp(poredi, korisnicko_ime) == 0)
				{
					while (1) {

						
						printf("\nUnesite sifru: ");
						scanf("%s", sifra);						
						
						l = strlen(sifra);
					
						fread(poredi, sizeof(char), l+1, fptr);
						if (poredi[l] == '-')
							poredi[l] = NULL;

						if (strcmp(poredi, sifra) == 0)
						{
							system("cls");
							printf("\nUspesno ste se ulogovali!\n");
							
							c = fgetc(fptr);//kupi '-' koji razdvaja lozinku od broja pobeda i poraza
							fread(pobeda_gubitak, sizeof(int), 2, fptr);
							fclose(fptr);
							provera = false;
							return korisnicko_ime;
							break;
						}
						else
						{
							if (brojac_neuspelih_loginova == 0)
							{
								printf("\nNiste uspeli da se prijavite kao korisnik %s\n", korisnicko_ime);
								kraj_programa();
							}
							printf("\nNetacna sifra za nalog %s. Imate jos %d pokusaja.",korisnicko_ime,brojac_neuspelih_loginova);
							brojac_neuspelih_loginova--;
							fseek(fptr, -(l+1), SEEK_CUR);	
								//vracam fptr za l+1 mesta unazad jer sam citao string sifru i jos 1 ekstra znak '-'

						}
					}
				}
				if (!provera)break;
				while (1)
				{
					c = fgetc(fptr);
					if (c == '\n')
						break;
				}
					//kupi po 1 karakter posle citanja korisnickog imena sve dok ne dodje do novog reda 


				if ((c = fgetc(fptr)) == EOF)
				{
					printf("Nalog sa unetim korisnickim imenom ne postoji, zelite li da napravite novi nalog? (da, ne) ---> ");
					do
					{
						scanf("%s", nov_nalog);
						nov_nalog[0] = tolower(nov_nalog[0]);
						nov_nalog[1] = tolower(nov_nalog[1]);
						if (strcmp(nov_nalog, "da") == 0)
						{
							return kreiraj_nalog();
							break;
						}
						else if (strcmp(nov_nalog, "ne") == 0)
						{
							fclose(fptr);
							kraj_programa();
						}
						else
						{
							printf("\nMolimo vas da odgovorite sa opcijom 'da' ili 'ne'.");
							printf("\nDa li zelite da napravite novi nalog? ---> ");
						}

					} while (1);
					
				}
				fseek(fptr, -1, SEEK_CUR);
			}
		}
	
	}
} 

void kraj_programa()
{
	printf("\n\nKRAJ PROGRAMA\n\n");
	exit(0);
}



void print_izbor_igara()
{

	printf("\nUnesite redne brojeve igara koje zelite da odigrate na tiketu\n ");
	printf("\n////////////////////////////////////////////////////////////");
	printf("\nUneti 0 za nastavak ka uplati\n");
	printf("\n1. Klasican LUCKY SIX");
	printf("\n2. Kugla u prvih 5 izvucenih (broj kugle)");
	printf("\n3. Suma prvih 5 VECA ili MANJA od 122.5");
	printf("\n4. Parnost prve kugle ");
	printf("\n5. Boja prve kugle");
	printf("\n6. Broj prve kugle VECI ili MANJI od 24.5");
	printf("\n7. Vise parnih/neparnih u prvih 5 izvucenih");
	printf("\n////////////////////////////////////////////////////////////\n");
}
        
void setovanje_kuglica(Kuglica kuglice[])
{
	int br = 1;
	int i;
	for (i = 0; i < 48; i++) {
		kuglice[i].broj = i + 1;
		switch (br) {
		case 1:
			strcpy(kuglice[i].boja, "crvena");
			br++;
			break;
		case 2:
			strcpy(kuglice[i].boja, "braon");
			br++;
			break;
		case 3:
			strcpy(kuglice[i].boja, "zelena");
			br++;
			break;
		case 4:
			strcpy(kuglice[i].boja, "plava");
			br++;
			break;
		case 5:
			strcpy(kuglice[i].boja, "pink");
			br++;
			break;
		case 6:
			strcpy(kuglice[i].boja, "zuta");
			br++;
			break;
		case 7:
			strcpy(kuglice[i].boja, "narandzasta");
			br++;
			break;
		case 8:
			strcpy(kuglice[i].boja, "crna");
			br = 1;
			break;

		}
	}
}

Kuglica* izvlacenje(Kuglica kuglice[])
{
	Kuglica* izvuceni_brojevi;
	int i, j;
	int rnd;
	bool provera;
	int br;
	izvuceni_brojevi = malloc(35 * sizeof(Kuglica));
	if (izvuceni_brojevi == NULL)
	{
		printf("\nGreska pri dinamickoj dodeli memorije!");
		exit(1);
	}
	srand(time(NULL));
	for (j = 0; j < 35; j++)
	{
		
		provera = true;
		br = 0;

		while (provera)
		{
			rnd = rand() % 48 + 1;

			for (i = 0; i < j; i++)
			{
				br = 0;
				if (izvuceni_brojevi[i].broj == rnd)
				{
					br++;
					break;
				}
			}
			if (!br) provera = false;
		}
			//while petlja ce generisati novi random broj sve dok se ne izvuce nov broj 1-48

		izvuceni_brojevi[j].broj = rnd;
		strcpy(izvuceni_brojevi[j].boja, kuglice[rnd - 1].boja);
	}
	return izvuceni_brojevi;
}

float opcije_za_kladjenje(Kuglica* izvuceni_brojevi)
{
	float kvota = 1;
	int i, j;
	bool postoji = false;

	int* izbor = malloc(8 * sizeof(int));
	if (izbor == NULL)
	{
		printf("\nGreska pri dinamickoj dodeli memorije!");
		exit(1);
	}
	for (i = 0; i < 8; i++)
	{
		if (i == 0)
			izbor[i] = 0;
		else
			izbor[i] = -1;
	}
		//u nizu izbor mi se pamte izabrane igre, radi provere vrednosti sam setovao prvi element na 0 a ostale na -1

	i = 0;

	do
	{
		postoji = false;
		printf("\n%d. igra: ", i + 1);
		scanf("%d", &izbor[i]);
		if (i == 0 && izbor[i] == 0)
		{
			printf("Morate uneti redni broj bar jedne igre!\n");
			continue;
		}
		else if (izbor[i] > 7||izbor[i]<0)
		{
			printf("Dostupne su opcije od 0 do 7!\n");
			continue;
		}
		for (j = 0; j < i; j++)
		{
			if (izbor[i] == izbor[j])
				postoji = true;
		}

		if (postoji && izbor[0] != 0) {
			printf("Vec ste uneli trazenu igru!\n");
			continue;
		}
		else if (izbor[i] == 0)
		{
			printf("Uspesno ste uneli kombinacije.\n");
		}
		else
		{
			printf("Igra pod rednim brojem %d. je dodata u tiket. Unesite '0' ako ste zavrsili sa unosom igara.\n", izbor[i]);

		}
		i++;

	} while (izbor[0] == 0 || (izbor[i - 1] != 0));

	izbor = realloc(izbor, i * sizeof(int));
	
	if (izbor == NULL)
	{
		printf("\nDoslo je do greske pri dinamickoj dodeli memorije!");
		exit(1);
	}

	system("cls");

	for (j = 0; j < i - 1; j++)
	{
		switch (izbor[j])
		{
		case 1:
			kvota *= lucky_six(izvuceni_brojevi);
			break;
		case 2:
			kvota *= broj_u_prvih_5(izvuceni_brojevi);
			break;
		case 3:
			kvota *= suma_prvih_5(izvuceni_brojevi);
			break;
		case 4:
			kvota *= parnost_prve_kugle(izvuceni_brojevi);
			break;
		case 5:
			kvota *= boja_prve_kugle(izvuceni_brojevi);
			break;
		case 6:
			kvota *= broj_prve_kugle_veci_manji(izvuceni_brojevi);
			break;
		case 7:
			kvota *= vise_par_nepar_u_prvih_5(izvuceni_brojevi);
			break;
		}
	}
		//korisnik unosi svoje predikcije za igre, u redosledu po kojem ih je birao

	free(izbor);
	return kvota;
}



float lucky_six(Kuglica* izvuceni_brojevi)
{
	int korisnik_kuglice[6];
	int izvucenih_brojeva = 0;
	int mesto_dobitka = 0;
	int i, j;
	bool pamti_mesto = false, nema_ponavljanja_korisnikovog_broja, broj_van_opsega;
	do {
		nema_ponavljanja_korisnikovog_broja = true;
		broj_van_opsega = false;
		printf("\nUnesite brojeve 6 kuglica za izvlacenje (1-48): ");
		scanf("%d%d%d%d%d%d", &korisnik_kuglice[0], &korisnik_kuglice[1], &korisnik_kuglice[2], &korisnik_kuglice[3], &korisnik_kuglice[4], &korisnik_kuglice[5]);
		for (i = 0; i < 5; i++)
		{
			if (!nema_ponavljanja_korisnikovog_broja)
				break;

			for (j = i + 1; j < 6; j++)
			{
				if (korisnik_kuglice[i] == korisnik_kuglice[j])
				{
					nema_ponavljanja_korisnikovog_broja = false;
					break;
				}
			}

		}	//ovaj deo proverava da korisnik ne unese bar 2 ista broja u svojih 6 unetih
			

		for (i = 0; i < 6; i++)
		{
			if (korisnik_kuglice[i] < 1 || korisnik_kuglice[i]>48)
			{
				broj_van_opsega = true;
				break;
			}
		}


		if (!nema_ponavljanja_korisnikovog_broja)
			printf("\nMorate uneti 6 razlicitih brojeva kuglica!\n");
		if (broj_van_opsega)
			printf("\nBrojevi svih 6 kuglica moraju biti u opsegu 1-48!\n");
	} while (!nema_ponavljanja_korisnikovog_broja || broj_van_opsega);


	for (i = 0; i < 35; i++)
	{
		if (provera_izvucene_kuglice(korisnik_kuglice, izvuceni_brojevi[i].broj))
			izvucenih_brojeva++;
				//inkrement svaki put kada je korisnik pogodio broj kuglice -->moze ici do 6 jer se unosi 6 brojeva

		if (izvucenih_brojeva == 6 && !pamti_mesto)
		{
			pamti_mesto = true;
			mesto_dobitka = i + 1;
			break;
		}
	}

	return odredi_kvotu(mesto_dobitka);
}

bool provera_izvucene_kuglice(int korisnikove_kuglice[], int broj)
{
	bool postoji = false;
	int i;
	for (i = 0; i < 6; i++)
	{
		if (korisnikove_kuglice[i] == broj)
		{
			postoji = true;
			break;
		}
	}
	return postoji;
}

float odredi_kvotu(int mesto_dobitka)
{
	float kvota = 0;
	switch (mesto_dobitka) {
	case 6:
		kvota = 25000;
		break;
	case 7:
		kvota = 15000;
		break;
	case 8:
		kvota = 7500;
		break;
	case 9:
		kvota = 3000;
		break;
	case 10:
		kvota = 1250;
		break;
	case 11:
		kvota = 700;
		break;
	case 12:
		kvota = 350;
		break;
	case 13:
		kvota = 250;
		break;
	case 14:
		kvota = 175;
		break;
	case 15:
		kvota = 125;
		break;
	case 16:
		kvota = 100;
		break;
	case 17:
		kvota = 90;
		break;
	case 18:
		kvota = 80;
		break;
	case 19:
		kvota = 70;
		break;
	case 20:
		kvota = 60;
		break;
	case 21:
		kvota = 50;
		break;
	case 22:
		kvota = 35;
		break;
	case 23:
		kvota = 25;
		break;
	case 24:
		kvota = 20;
		break;
	case 25:
		kvota = 15;
		break;
	case 26:
		kvota = 12;
		break;
	case 27:
		kvota = 10;
		break;
	case 28:
		kvota = 8;
	case 29:
		kvota = 7;
		break;
	case 30:
		kvota = 6;
		break;
	case 31:
		kvota = 5;
		break;
	case 32:
		kvota = 4;
		break;
	case 33:
		kvota = 3;
		break;
	case 34:
		kvota = 2;
		break;
	case 35:
		kvota = 1;
		break;
	default:
		kvota = 0;
		break;


		
	}
	return kvota;
}

float broj_u_prvih_5(Kuglica* izvuceni_brojevi)
{
	float kvota = 0;
	int broj;
	int i;
	do
	{
		printf("\nUnesi broj koji mislis da ce biti izvucen u prvih 5 izvlacenja kuglica: ");
		scanf("%d", &broj);
		if (broj < 1 || broj>48)
			printf("\nBroj mora biti u opsegu brojeva kuglica: 1-48! ");
	} while (broj < 1 || broj>48);

	for (i = 0; i < 5; i++)
	{
		if (broj == izvuceni_brojevi[i].broj)
		{
			kvota = 8;
			break;
		}
	}
	return kvota;

}

float suma_prvih_5(Kuglica* izvuceni_brojevi)
{
	float kvota = 0;
	char izbor[16];
	int i = 0, j;
	int sum = 0;
	printf("\nUkucajte 'veci' ako mislite da ce zbir brojeva prvih 5 kuglica biti veca od 122.5 ili 'manji' ako ce suma biti manja: ");

	scanf("%s", izbor);

	while (izbor[i] != NULL)
	{
		izbor[i] = tolower(izbor[i]);
		i++;
	}

	for (j = 0; j < 5; j++)
		sum += izvuceni_brojevi[j].broj;

	if (strcmp(izbor, "veci") == 0)
	{
		if (sum >= 123)
			kvota = 1.8;
		return kvota;
	}
	else if (strcmp(izbor, "manji") == 0)
	{
		if (sum <= 123)
			kvota = 1.8;
		return kvota;
	}
	else return kvota = suma_prvih_5(izvuceni_brojevi);
}

float parnost_prve_kugle(Kuglica* izvuceni_brojevi)
{
	float kvota = 0;
	char parnost[16];
	bool parna;
	int i = 0;
	printf("\nUnesite 'par' za parni broj prve kuglice ili 'nepar' za neparan broj prve kuglice: ");

	scanf("%s", parnost);

	while (parnost[i] != NULL)
	{
		parnost[i] = tolower(parnost[i]);
		i++;
	}
	if (izvuceni_brojevi[0].broj % 2 == 0)
		parna = true;
	else
		parna = false;
	if (strcmp(parnost, "par") == 0)
	{
		if (parna)
			kvota = 1.8;
		return kvota;
	}
	else if (strcmp(parnost, "nepar") == 0)
	{
		if (!parna)
			kvota = 1.8;
		return kvota;
	}
	else return kvota = parnost_prve_kugle(izvuceni_brojevi);
}

float boja_prve_kugle(Kuglica* izvuceni_brojevi)
{
	float kvota = 0;
	int n;
	char boje[4][16];
	bool postoji = false;
	int br = 0;
	int i;
	printf("\nPogodi boju prve kuglice!");
	printf("\nBoje: crvena, braon, zelena, plava, pink, zuta, narandzasta, crvena");
	printf("\nUnesite koliko kombinacija boja zelite da unesete(1-4): ");

	do
	{
		scanf("%d", &n);
		if (n < 1 || n>4)
			printf("Morate uneti 1-4 kombinacije!");
	} while (n < 1 || n>4);


	for (i = 0; i < n; i++)
	{
		postoji = false;

		do {
			printf("\nUnesite vasu %d. boju: ", i + 1);
			scanf("%s", boje[i]);
			if (strcmp(boje[i], "crvena") == 0)
			{
				if (!provera_da_se_boja_ponavlja(boje, boje[i], i))
						//ako boja ne postoji onda..
					postoji = true;
				else
					printf("\n%s boja je vec uneta!", boje[i]);
			}

			else if (strcmp(boje[i], "braon") == 0)
			{
				if (!provera_da_se_boja_ponavlja(boje, boje[i], i))
					postoji = true;
				else
					printf("\n%s boja je vec uneta!", boje[i]);
			}

			else if (strcmp(boje[i], "zelena") == 0)
			{
				if (!provera_da_se_boja_ponavlja(boje, boje[i], i))
					postoji = true;
				else
					printf("\n%s boja je vec uneta!", boje[i]);
			}

			else if (strcmp(boje[i], "plava") == 0)
			{
				if (!provera_da_se_boja_ponavlja(boje, boje[i], i))
					postoji = true;
				else
					printf("\n%s boja je vec uneta!", boje[i]);
			}
			else if (strcmp(boje[i], "pink") == 0)
			{
				if (!provera_da_se_boja_ponavlja(boje, boje[i], i))
					postoji = true;
				else
					printf("\n%s boja je vec uneta!", boje[i]);
			}
			else if (strcmp(boje[i], "zuta") == 0)
			{
				if (!provera_da_se_boja_ponavlja(boje, boje[i], i))
					postoji = true;
				else
					printf("\n%s boja je vec uneta!", boje[i]);
			}
			else if (strcmp(boje[i], "narandzasta") == 0)
			{
				if (!provera_da_se_boja_ponavlja(boje, boje[i], i))
					postoji = true;
				else
					printf("\n%s boja je vec uneta!", boje[i]);
			}
			else if (strcmp(boje[i], "crna") == 0)
			{
				if (!provera_da_se_boja_ponavlja(boje, boje[i], i))
					postoji = true;
				else
					printf("\n%s boja je vec uneta!", boje[i]);
			}
			else
				printf("\nMorate uneti jednu od ponudjenih boja!");
		} while (!postoji);
	}
	postoji = false;
	for (i = 0; i < n; i++)
	{
		if (strcmp(izvuceni_brojevi[0].boja, boje[i]) == 0)
		{
			postoji = true;
			break;
		}
	}


	if (postoji)
	{
		switch (n)
		{
		case 1:
			kvota = 7;
			break;
		case 2:
			kvota = 3.5;
			break;
		case 3:
			kvota = 2.33;
			break;
		case 4:
			kvota = 1.75;
			break;
		}
	}
	return kvota;

}

bool provera_da_se_boja_ponavlja(char boje[4][16], char* boja, int n)
{
	bool boja_postoji = false;
	int i;
	for (i = 0; i < n; i++)
	{
		if (strcmp(boje[i], boja) == 0)
		{
			boja_postoji = true;
			break;
		}
	}
		//proverava da li je korisnik vec uneo datu boju

	return boja_postoji;
}

float broj_prve_kugle_veci_manji(Kuglica* izvuceni_brojevi)
{
	float kvota = 0;
	bool veci = false;
	char rec[11];
	int i;
	do {
		printf("\nUnesite 'veci' za broj veci od 24.5 ili 'manji' za prvi broj manji od 24.5: ");
		scanf("%s", rec);
		for (i = 0; i < strlen(rec); i++)
			rec[i] = tolower(rec[i]);
		if (strcmp(rec, "manji") == 0)
			break;
		else if (strcmp(rec, "veci") == 0)
		{
			veci = true;
			break;
		}
		else
			printf("\nMorate uneti 'veci' ili 'manji' !\n");
	} while (1);

	if (veci)
	{
		if (izvuceni_brojevi[0].broj > 24)
			kvota = 1.8;
	}
	else
	{
		if (izvuceni_brojevi[0].broj < 25)
			kvota = 1.8;
	}
	return kvota;
}

float vise_par_nepar_u_prvih_5(Kuglica* izvuceni_brojevi)
{
	float kvota = 0;
	char rec[11];
	bool par = true;
	int br_par = 0, br_nepar = 0;
	int i;
	do {
		printf("\nUnesite 'par' za vise parnih brojeva ili 'nepar' za vise neparnih brojeva u prvih 5 izvucenih kuglica: ");
		scanf("%s", rec);
		for (i = 0; i < strlen(rec); i++)
			rec[i] = tolower(rec[i]);
		if (strcmp(rec, "par") == 0)
			break;
		else if (strcmp(rec, "nepar") == 0)
		{
			par = false;
			break;
		}
		else
			printf("\nMorate uneti 'par' ili 'nepar' !\n");
	} while (1);

	for (i = 0; i < 5; i++)
	{
		if (izvuceni_brojevi[i].broj % 2 == 0)
			br_par++;
		else
			br_nepar++;
	}

	if (par)
	{
		if (br_par > br_nepar)
			kvota = 1.8;
	}
	else
	{
		if (br_par < br_nepar)
			kvota = 1.8;
	}
	return kvota;
}



void print_izvlacenje(Kuglica* izvuceni_brojevi)
{
	int j;
	for (j = 0; j < 35; j++)
	{
		printf("\n%d.\t  %s  %d", j + 1, izvuceni_brojevi[j].boja, izvuceni_brojevi[j].broj);
		delay(3000);
	}
}

void delay(unsigned timeout)
{
	timeout += clock();
	while (clock() < timeout) continue;
		//koristim funkciju da "ceka" timeout milisekundi do sledece naredbe
}



void prikazi_isplatu(float kvota, float uplata, char* korisnik)
{
	float isplata;

	if (uplata * kvota != 0)
	{

		isplata = kvota * uplata;
		printf("\n////////////////////////////////////////////////////////////\n");
		printf("\nCESTITAMO: osvojili ste %.2f dinara!\n", isplata);
		printf("\n////////////////////////////////////////////////////////////\n");
		kopira_dat1_u_dat2(korisnik, "baza.bin", "replika.bin", true);
			//ovde menjam rezultat kod korisnika u zavisnosti od true/false i upisujem izmenjenu datoteku u replika.bin

		kopira_dat1_u_dat2("-", "replika.bin", "baza.bin", true);
			//ovde ne menjam nista jer ne moze da postoji korisnik sa imenom "-" tako da samo kopiram iz replike sve u bazu
	}
	else
	{

		printf("\n////////////////////////////////////////////////////////////\n");
		printf("\nNiste ostvarili dobitak, vise srece u sledecoj rundi!\n");
		printf("\n////////////////////////////////////////////////////////////\n");
		kopira_dat1_u_dat2(korisnik, "baza.bin", "replika.bin", false);
		kopira_dat1_u_dat2("-", "replika.bin", "baza.bin", false);
	}
}


void kopira_dat1_u_dat2(char* korisnik, char* izvor, char* cilj,bool pobeda)
{
	FILE* ptrCilj = fopen(cilj, "w");
	FILE* ptrIzvor = fopen(izvor, "r");
	int i = 0,brojac_crta=0,pobeda_gubitak[2]={0,0};
	bool provera = false,rec_je_nadjena=false;
	char c, poredi_korisnicko_ime[21];

	provera_otvaranja_datoteke(ptrCilj);
	provera_otvaranja_datoteke(ptrIzvor);
	
	while ((c=fgetc(ptrIzvor))!=EOF)
		//petlja ce da kopira sve dok se ne dodje do kraja fajla
	{
		
		fputc(c, ptrCilj);
		if (c == '-')
		{
			brojac_crta++;
				//posle 2 crte u jednom redu se upisuje int br[2]

			poredi_korisnicko_ime[i] = NULL;
			i = 0;
			if (strcmp(korisnik, poredi_korisnicko_ime) == 0)
			{
				rec_je_nadjena = true;
				provera = true;
			}
		}
		else if (c == '\n')
			brojac_crta = 0;

		if (provera && brojac_crta == 2)
				//ako se korisnicko ime podudara onda ce se izmeniti rezultat u zavisnosti od bool pobeda
		{
			fread(pobeda_gubitak, sizeof(int), 2, ptrIzvor);
			if (pobeda)
				pobeda_gubitak[0]++;
			else
				pobeda_gubitak[1]++;

			fwrite(pobeda_gubitak, sizeof(int), 2, ptrCilj);

			broj_pobeda_poraza(pobeda_gubitak);
				//ispisuje opste informacije i % pobede za ulogovanog korisnika
		
			provera = false;
		}
		else if (brojac_crta == 2)
		{
			fread(pobeda_gubitak, sizeof(int), 2, ptrIzvor);
			fwrite(pobeda_gubitak, sizeof(int), 2, ptrCilj);
		}
		if(!provera && c!='\n' && c!='-'&&brojac_crta==0&&!rec_je_nadjena)
			poredi_korisnicko_ime[i++] = c;
	}
	fclose(ptrCilj);
	fclose(ptrIzvor);
}

void provera_otvaranja_datoteke(FILE* fptr)
{
	if (fptr == NULL)
	{
		printf("\nGreska pri otvaranju datoteke!");
		exit(1);
	}
}

void broj_pobeda_poraza(int* pobeda_gubitak)
{
	float procenat_pobede;
	procenat_pobede = (float)pobeda_gubitak[0] / (pobeda_gubitak[0] + pobeda_gubitak[1])*100;
	printf("\nImate prolaznost tiketa od %.2f%%", procenat_pobede);
	printf("\n\nStojite na %dW i %dL", pobeda_gubitak[0], pobeda_gubitak[1]);
}


