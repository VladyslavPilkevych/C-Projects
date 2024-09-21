#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void bubbleSort(double *arr, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void j_function(char **pole_ID_MM, char **pole_Typ_MV, double *hodnota, int velkost_pole)
{
    char ID_modulu[6];
    int num = 0;
    int i = 0;

    printf("Zadajte ID mer. modulu (velke pismeno A-Z, tri cisla 001-999, maly znak a-z): ");
    scanf("%5s", ID_modulu);

    printf("Your ID is: %s\n", ID_modulu);

    i = 1;
    while (isdigit(ID_modulu[i]) && i <= 3)
    {
        num = num * 10 + (ID_modulu[i] - '0');
        i++;
    }

    if (!(ID_modulu[0] >= 'A' && ID_modulu[0] <= 'Z'))
    {
        printf("\nChyba: Prvy znak musi byt velke pismeno A-Z.\n");
    }

    if (num < 1 || num > 999 || i != 4)
    {
        printf("\nChyba: Cislo modulu musi byt v rozmedzi 001-999.\n");
    }

    if (!(ID_modulu[i] >= 'a' && ID_modulu[i] <= 'z'))
    {
        printf("\nChyba: Posledny znak musi byt maly znak a-z.\n");
    }

    while (!(ID_modulu[0] >= 'A' && ID_modulu[0] <= 'Z') || num < 1 || num > 999 || i != 4 || !(ID_modulu[i] >= 'a' && ID_modulu[i] <= 'z'))
    {
        printf("\nSkus este krat: ");
        scanf("%5s", ID_modulu);

        i = 1;
        while (isdigit(ID_modulu[i]) && i <= 3)
        {
            num = num * 10 + (ID_modulu[i] - '0');
            i++;
        }

        if (!(ID_modulu[0] >= 'A' && ID_modulu[0] <= 'Z'))
        {
            printf("\nChyba: Prvy znak musi byt velke pismeno A-Z.\n");
        }

        if (num < 1 || num > 999 || i != 4)
        {
            printf("\nChyba: Cislo modulu musi byt v rozmedzi 001-999.\n");
        }

        if (!(ID_modulu[i] >= 'a' && ID_modulu[i] <= 'z'))
        {
            printf("\nChyba: Posledny znak musi byt maly znak a-z.\n");
        }
    }
    printf("\nSpravne zadane ID mer. modulu: %s\n", ID_modulu);

    char typ_mer_veliciny[3];
    printf("\nZadajte typ mer. veliciny (RD, RM, RO, PI, PE, PA): ");
    scanf("%s", typ_mer_veliciny);

    while (!(strcmp(typ_mer_veliciny, "RD") == 0 || strcmp(typ_mer_veliciny, "RM") == 0 || strcmp(typ_mer_veliciny, "RO") == 0 ||
             strcmp(typ_mer_veliciny, "PI") == 0 || strcmp(typ_mer_veliciny, "PE") == 0 || strcmp(typ_mer_veliciny, "PA") == 0))
    {
        printf("Zadajte typ mer. veliciny (RD, RM, RO, PI, PE, PA): ");
        scanf("%s", typ_mer_veliciny);
    }
    printf("\nSpravne zadany typ mer. veliciny: %s\n", typ_mer_veliciny);

    printf("\nVypocitavam....\n");

    char **uniqueStrings = malloc(velkost_pole * sizeof(char *));
    char **uniqueTypes = malloc(velkost_pole * sizeof(char *));
    int *counts = malloc(velkost_pole * sizeof(int));
    double **minMaxArray = malloc(velkost_pole * sizeof(double *));
    double *arr = malloc(velkost_pole * sizeof(double *));

    for (int i = 0; i < velkost_pole; ++i)
    {
        minMaxArray[i] = malloc(2 * sizeof(double));
    }

    int uniqueCount = 0;
    int arrLength = 0;
    for (int i = 0; i < velkost_pole; ++i)
    {
        int isDuplicate = 0;
        for (int j = 0; j < uniqueCount; ++j)
        {
            if (strcmp(pole_ID_MM[i], uniqueStrings[j]) == 0 && strcmp(pole_Typ_MV[i], uniqueTypes[j]) == 0)
            {
                if (minMaxArray[j][0] > hodnota[i])
                    minMaxArray[j][0] = hodnota[i];
                else if (minMaxArray[j][1] < hodnota[i])
                    minMaxArray[j][1] = hodnota[i];
                isDuplicate = 1;
                counts[j]++;
                if (strcmp(pole_ID_MM[i], ID_modulu) == 0 && strcmp(pole_Typ_MV[i], typ_mer_veliciny) == 0)
                {
                    arr[arrLength] = hodnota[i];
                    arrLength++;
                }
            }
        }

        if (!isDuplicate)
        {
            minMaxArray[uniqueCount][0] = hodnota[i];
            minMaxArray[uniqueCount][1] = hodnota[i];
            if (strcmp(pole_ID_MM[i], ID_modulu) == 0 && strcmp(pole_Typ_MV[i], typ_mer_veliciny) == 0)
            {
                arr[arrLength] = hodnota[i];
                arrLength++;
            }

            uniqueStrings[uniqueCount] = strdup(pole_ID_MM[i]);
            uniqueTypes[uniqueCount] = strdup(pole_Typ_MV[i]);
            counts[uniqueCount] = 1;
            uniqueCount++;
        }
    }
    if (uniqueCount == 0)
    {
        printf("Ziadne zaznamy pre typy RD, RM, RO.\n");
        return;
    }

    bubbleSort(arr, arrLength);

    printf("\nTyp mer. vel.  Pocetnost    Minimum  Maximum    Type    Mediana      min_percent   max_percent\n");
    for (int i = 0; i < uniqueCount; ++i)
    {
        if (strcmp(uniqueStrings[i], ID_modulu) == 0 && strcmp(uniqueTypes[i], typ_mer_veliciny) == 0)
        {
            printf("   %s          %d          %.2f   %.2f      %s     %.2f       %.2f         %.2f\n", uniqueStrings[i], counts[i], minMaxArray[i][0], minMaxArray[i][1], uniqueTypes[i], arr[arrLength / 2], (minMaxArray[i][0] * 100 / arr[arrLength / 2]) - 100, (minMaxArray[i][1] * 100 / arr[arrLength / 2]) - 100);
            if ((minMaxArray[i][0] * 100 / arr[arrLength / 2]) - 100 < -15 || (minMaxArray[i][1] * 100 / arr[arrLength / 2]) - 100 > 15)
            {
                printf("\n\n%s prekracuje limit povoleneho rozmedzenia\n");
            }
            else
            {
                printf("\n\n%s je v standartnej odchylke\n");
            }

            free(uniqueStrings[i]);
            free(uniqueTypes[i]);
        }
    }
}

void t(char **pole_ID_MM, int velkost_pole)
{
    char **uniqueStrings = malloc(velkost_pole * sizeof(char *));
    int *counts = malloc(velkost_pole * sizeof(int));

    int uniqueCount = 0;

    for (int i = 0; i < velkost_pole; ++i)
    {
        int isDuplicate = 0;
        for (int j = 0; j < uniqueCount; ++j)
        {
            if (strcmp(pole_ID_MM[i], uniqueStrings[j]) == 0)
            {
                isDuplicate = 1;
                counts[j]++;
            }
        }

        if (!isDuplicate)
        {
            uniqueStrings[uniqueCount] = strdup(pole_ID_MM[i]);
            counts[uniqueCount] = 1;
            uniqueCount++;
        }
    }

    printf("Typ mer. vel.  Pocetnost\n");
    for (int i = 0; i < uniqueCount; ++i)
    {
        printf("%s             %d\n", uniqueStrings[i], counts[i]);
        free(uniqueStrings[i]);
    }
}

#define Pocet_Zaznamov 30 // nemenit
int main()
{
    char **pole_ID_MM = NULL;  // ID mer. modul
    char **pole_Typ_MV = NULL; // typ mer. veliciny
    char **pole_DM = NULL;     // Datum merania
    char **pole_CM = NULL;     // cas merania
    double *hodnota;
    char *pole[] = {"0905", "0915", "0925", "0935", "0945", "1005", "1405", "1505", "1605", "1905"};
    char *pole1[] = {"20201030", "20201030", "20211030", "20211030", "20211130", "20211130", "20211130", "20211212", "20211212", "20211212"};

    int i = 0, j = 0, r = 1;

    hodnota = (double *)malloc(Pocet_Zaznamov * sizeof(double));
    for (i = 0; i < Pocet_Zaznamov; i++)
    {
        if (i < Pocet_Zaznamov / 3)
            hodnota[i] = 100.255 + (i * 8.358);
        else if (i < Pocet_Zaznamov * 2 / 3)
            hodnota[i] = 10.255 + (i * 17.358);
        else
            hodnota[i] = (i * 11.358);
        ;
    }

    pole_ID_MM = (char **)malloc(Pocet_Zaznamov * sizeof(char *));
    for (i = 0; i < Pocet_Zaznamov; i++)
    {
        pole_ID_MM[i] = (char *)malloc(6 * sizeof(char));
        if (i < Pocet_Zaznamov / 3)
            strcpy(*(pole_ID_MM + i), "A111a");
        else if (i < Pocet_Zaznamov * 2 / 3)
            strcpy(*(pole_ID_MM + i), "A211b");
        else
            strcpy(*(pole_ID_MM + i), "B111a");
    }

    pole_Typ_MV = (char **)malloc(Pocet_Zaznamov * sizeof(char *));
    for (i = 0; i < Pocet_Zaznamov; i++)
    {
        pole_Typ_MV[i] = (char *)malloc(3 * sizeof(char));
        if (r == 1)
        {
            strcpy(*(pole_Typ_MV + i), "RM");
            r = 2;
        }
        else if (r == 2)
        {
            strcpy(*(pole_Typ_MV + i), "RO");
            r = 3;
        }
        else
        {
            strcpy(*(pole_Typ_MV + i), "RD");
            r = 1;
        }
    }

    pole_DM = (char **)malloc(Pocet_Zaznamov * sizeof(char *));
    for (i = 0, j = 0; i < Pocet_Zaznamov; i++)
    {
        pole_DM[i] = (char *)malloc(9 * sizeof(char));
        if (i < Pocet_Zaznamov / 3)
        {
            strcpy(*(pole_DM + i), pole1[j]);
            j++;
        }
        else if (i < Pocet_Zaznamov * 2 / 3)
        {
            j--;
            strcpy(*(pole_DM + i), pole1[j]);
        }
        else
        {
            strcpy(*(pole_DM + i), pole1[j]);
            j++;
        }
    }

    pole_CM = (char **)malloc(Pocet_Zaznamov * sizeof(char *));
    for (i = 0, j = 0; i < Pocet_Zaznamov; i++)
    {
        pole_CM[i] = (char *)malloc(5 * sizeof(char));
        if (i < Pocet_Zaznamov / 3)
        {
            strcpy(*(pole_CM + i), pole[j]);
            j++;
        }
        else if (i < Pocet_Zaznamov * 2 / 3)
        {
            j--;
            strcpy(*(pole_CM + i), pole[j]);
        }
        else
        {
            strcpy(*(pole_CM + i), pole[j]);
            j++;
        }
    }

    // vypis
    for (i = 0; i < Pocet_Zaznamov; i++)
    {
        printf("\n%3d %s %s %s %s \t%f", i, pole_ID_MM[i], pole_Typ_MV[i], pole_DM[i], pole_CM[i], hodnota[i]);
    }

    // vase riesenia / your solution

    char klavesa;
    printf("\nStlacte 'j' alebo 't' pre spustenie merania: ");
    scanf(" %c", &klavesa);

    if (klavesa == 'j')
    {
        j_function(pole_ID_MM, pole_Typ_MV, hodnota, Pocet_Zaznamov);
    }
    else if (klavesa == 't')
    {
        t(pole_ID_MM, Pocet_Zaznamov);
    }
    else
    {
        printf("Nespravny vstup. Program konci.\n");
    }

    // uvolnenie poli
    for (i = 0; i < Pocet_Zaznamov; i++)
    {
        free(*(pole_ID_MM + i));
        *(pole_ID_MM + i) = NULL;
        free(*(pole_Typ_MV + i));
        *(pole_Typ_MV + i) = NULL;
        free(*(pole_DM + i));
        *(pole_DM + i) = NULL;
        free(*(pole_CM + i));
        *(pole_CM + i) = NULL;
    }
    free(pole_ID_MM);
    pole_ID_MM = NULL;
    free(pole_Typ_MV);
    pole_Typ_MV = NULL;
    free(pole_DM);
    pole_DM = NULL;
    free(pole_CM);
    pole_CM = NULL;
    free(hodnota);
    hodnota = NULL;

    return 0;
}