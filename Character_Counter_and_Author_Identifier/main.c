#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Pocet_Zaznamov 10
#define ALL_SYMBOLS_LENGTH 256

int x(char **IDprispevku_1, int velkost_pola)
{
    char c;
    int k = 0, l = 0, resultArrLength = 0;
    int counterArray[ALL_SYMBOLS_LENGTH] = {0};
    char resultArraySymbols[ALL_SYMBOLS_LENGTH];
    int resultArrayCounter[ALL_SYMBOLS_LENGTH];
    printf("Napiste dva cisla 'k' a 'l', kde k<l, k<=9 a l<=10:\n");
    scanf("%d %d", &k, &l);
    if (k <= 0 || l <= 0 || k >= l || k > 9 || l > 10)
    {
        printf("Validacia nie je spravna, musi byt takto: 0<k<=9, k<l, 1<l<=10\n");
        return 0;
    }
    for (int i = 0; i < velkost_pola; i++)
    {
        char *id = IDprispevku_1[i];
        for (int j = 0; id[j] != '\0'; j++)
        {
            c = id[j];
            counterArray[c]++;
        }
    }
    printf("-------------------\nvystup:\n-------------------\n");
    for (c = 'A'; c <= 'Z'; c++)
    {
        resultArraySymbols[resultArrLength] = c;
        resultArrayCounter[resultArrLength] = counterArray[c];
        resultArrLength++;
    }
    for (c = 'a'; c <= 'z'; c++)
    {
        resultArraySymbols[resultArrLength] = c;
        resultArrayCounter[resultArrLength] = counterArray[c];
        resultArrLength++;
    }
    for (c = '0'; c <= '9'; c++)
    {
        resultArraySymbols[resultArrLength] = c;
        resultArrayCounter[resultArrLength] = counterArray[c];
        resultArrLength++;
    }
    printf("znaky :     ");
    for (int i = 0; i < resultArrLength - 1; i++)
    {
        if (resultArrayCounter[i] > 0)
        {
            resultArrayCounter[i] < 10
                ? printf(" %c |", resultArraySymbols[i])
                : printf("  %c |", resultArraySymbols[i]);
        }
    }
    printf("\npocetnost : ");
    for (int i = 0; i < resultArrLength - 1; i++)
    {
        if (resultArrayCounter[i] > 0)
        {
            printf(" %d |", resultArrayCounter[i]);
        }
    }
    printf("\n-------------------\n");
    return 1;
}

char **e(char **MenaAutorov, int velkost_pola, char ZNAK, int *VelkostMENA)
{
    int count = 0;
    char **MENAx = malloc(sizeof(char *) * velkost_pola);

    for (int i = 0; i < velkost_pola; i++)
    {
        char *a = strstr(MenaAutorov, "#A#");
        if (a != NULL)
        {
            // strcpy(a, "#Q#");
            // strcpy(a, "\n");
            count++;
        }
        char *k = strstr(MenaAutorov, "#K#");
        if (k != NULL)
        {
            // strcpy(k, "#Q#");
            // strcpy(k, "\n");
            count++;
        }
    }
    if (count != 0)
    {
        for (int i = 0; i < count; i++)
        {
            printf("%s\n", MENAx[i]);
        }
    }

    return MENAx;
}

int main()
{
    char **IDprispevku = NULL;
    char **MenaAutorov = NULL;
    int i = 0, j = 0;
    char riad;
    int nameSize;

    IDprispevku = (char **)malloc(Pocet_Zaznamov * sizeof(char *));
    for (i = 0; i < Pocet_Zaznamov; i++)
    {
        IDprispevku[i] = (char *)malloc(11 * sizeof(char));
        switch (i)
        {
        case 0:
            strcpy(*(IDprispevku + i), "UP12345678");
            break;
        case 1:
            strcpy(*(IDprispevku + i), "UD12345678");
            break;
        case 2:
            strcpy(*(IDprispevku + i), "PD12345678");
            break;
        case 3:
            strcpy(*(IDprispevku + i), "PP12345678");
            break;
        case 4:
            strcpy(*(IDprispevku + i), "UP56556576");
            break;
        case 5:
            strcpy(*(IDprispevku + i), "UP12345678");
            break;
        case 6:
            strcpy(*(IDprispevku + i), "PP12345678");
            break;
        case 7:
            strcpy(*(IDprispevku + i), "UP98765432");
            break;
        case 8:
            strcpy(*(IDprispevku + i), "UD12345678");
            break;
        case 9:
            strcpy(*(IDprispevku + i), "UP76523567");
            break;
        default:
            strcpy(*(IDprispevku + i), "PP29384729");
        }
    }

    MenaAutorov = (char **)malloc(Pocet_Zaznamov * sizeof(char *));
    for (i = 0; i < Pocet_Zaznamov; i++)
    {
        switch (i)
        {
        case 0:
        {
            MenaAutorov[i] = (char *)malloc((strlen("Julius Novak#A#Marek Kovac#K#") + 1) * sizeof(char));
            strcpy(*(MenaAutorov + i), "Julius Novak#A#Marek Kovac#K#");
        }
        break;
        case 1:
        {
            MenaAutorov[i] = (char *)malloc((strlen("Lucia Ondrejkova#K#Lukas Hvizdal#A#") + 1) * sizeof(char));
            strcpy(*(MenaAutorov + i), "Lucia Ondrejkova#K#Lukas Hvizdal#A#");
        }
        break;
        case 2:
        {
            MenaAutorov[i] = (char *)malloc((strlen("MARCEL VON TAKAC#K#ANDREA NOVOTNA#A#") + 1) * sizeof(char));
            strcpy(*(MenaAutorov + i), "MARCEL VON TAKAC#K#ANDREA NOVOTNA#A#");
        }
        break;
        case 3:
        {
            MenaAutorov[i] = (char *)malloc((strlen("Ondrej Zatko#A#") + 1) * sizeof(char));
            strcpy(*(MenaAutorov + i), "Ondrej Zatko#A#");
        }
        break;
        case 4:
        {
            MenaAutorov[i] = (char *)malloc((strlen("Lucia Ondrejkova#A#Lukas Hvizdal#K#Janko Mrkvicka#S#") + 1) * sizeof(char));
            strcpy(*(MenaAutorov + i), "Lucia Ondrejkova#A#Lukas Hvizdal#K#Janko Mrkvicka#S#");
        }
        break;
        case 5:
        {
            MenaAutorov[i] = (char *)malloc((strlen("Janko Mrkvicka#A#Lena Von Der Brecht#S#") + 1) * sizeof(char));
            strcpy(*(MenaAutorov + i), "Janko Mrkvicka#A#Lena Von Der Brecht#S#");
        }
        break;
        case 6:
        {
            MenaAutorov[i] = (char *)malloc((strlen("Janko Mrkvicka#A#Hana Von Der Brecht#A#") + 1) * sizeof(char));
            strcpy(*(MenaAutorov + i), "Janko Mrkvicka#A#Hana Von Der Brecht#A#");
        }
        break;
        default:
        {
            MenaAutorov[i] = (char *)malloc((strlen("Neviem Neviem#A#") + 1) * sizeof(char));
            strcpy(*(MenaAutorov + i), "Neviem Neviem#A#");
        }
        }
    }

    while (scanf(" %c", &riad) == 1 && riad != 'k')
    {
        switch (riad)
        {
        case 'v':
        {
            for (i = 0; i < Pocet_Zaznamov; i++)
            {
                printf("%s \n", IDprispevku[i]);
            }

            for (i = 0; i < Pocet_Zaznamov; i++)
            {
                printf("%s \n", MenaAutorov[i]);
            }
        }
        break;
        case 'a':
        {
            printf("a:");
        }
        break;
        case 'x':
        {
            x(IDprispevku, Pocet_Zaznamov);
        }
        break;
        case 'e':
        {
            e(MenaAutorov, Pocet_Zaznamov, 'Q', &nameSize);
        }
        break;
        }
    }

    // uvolnenie poli
    for (i = 0; i < Pocet_Zaznamov; i++)
    {
        free(*(IDprispevku + i));
        *(IDprispevku + i) = NULL;
        free(*(MenaAutorov + i));
        *(MenaAutorov + i) = NULL;
    }
    free(IDprispevku);
    IDprispevku = NULL;
    free(MenaAutorov);
    MenaAutorov = NULL;

    return 0;
}
