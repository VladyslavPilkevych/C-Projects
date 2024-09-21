#include <stdio.h>
#include <stdlib.h>

void v(char ***dataArray, int *numPeople, int *isFileOpen)
{

    if (*isFileOpen == 1)
        for (int i = 0; i < (*numPeople); ++i)
        {
            printf("%s\n%s\n%s\n%s\n%s\n%s\n\n",
                   dataArray[i][0],  // dataID
                   dataArray[i][1],  // dataModulePosition
                   dataArray[i][2],  // dataType
                   dataArray[i][3],  // dataNumber
                   dataArray[i][4],  // dataTime
                   dataArray[i][5]); // dataDate
        }
    else
    {
        FILE *file = fopen("dataloger.txt", "r");
        if (file == NULL)
        {
            printf("Neotvoreny subor.\n");
            return;
        }
        char line[100];
        *isFileOpen = 1;
        int lineCount = 1;
        while (fgets(line, sizeof(line), file) != NULL)
        {
            printf("%s", line);
            lineCount++;
        }
        *numPeople = lineCount / 7;
    }
}

void n(char ****dataArray, int *numPeople, int isFileOpen, int *isArrayCreated)
{
    if (isFileOpen == 0)
    {
        printf("Neotvoreny subor.\n");
        return;
    }

    FILE *file = fopen("dataloger.txt", "r");
    if (file == NULL)
    {
        printf("Neotvoreny subor.\n");
        return;
    }
    if (*dataArray)
    {
        for (int i = 0; i < *numPeople; ++i)
        {
            for (int j = 0; j < 6; ++j)
            {
                free((*dataArray)[i][j]);
            }
            free((*dataArray)[i]);
        }
        free(*dataArray);
        (*dataArray) = NULL;
    }

    *numPeople = 10;
    *dataArray = malloc(*numPeople * sizeof(char **));

    for (int i = 0; i < *numPeople; ++i)
    {
        (*dataArray)[i] = malloc(6 * sizeof(char *));
        for (int j = 0; j < 6; ++j)
        {
            (*dataArray)[i][j] = malloc(100 * sizeof(char));
            fscanf(file, "%s", (*dataArray)[i][j]);
        }
    }
    *isArrayCreated = 1;
    fclose(file);
}

void c(char ****dataArray, int *numPeople, int isArrayCreated)
{
    if (isArrayCreated == 0)
    {
        printf("Polia nie su vytvorene.\n");
        return;
    }

    char ***filteredArray = NULL;
    int newSize = 0;
    int j = 0;

    int mounth;
    printf("mesiac (number pls): ");
    scanf(" %d", &mounth);
    while (mounth < 1 || mounth > 12)
    {
        printf("0 > mesiac (number pls) < 12 ==> : ");
        scanf(" %d", &mounth);
    }

    char ***ciachovanieArray = NULL;
    int numCiachovanie = 6;
    FILE *file = fopen("ciachovanie.txt", "r");
    if (file == NULL)
    {
        printf("Error.\n");
        return;
    }
    ciachovanieArray = malloc(numCiachovanie * sizeof(char **));

    for (int i = 0; i < numCiachovanie; ++i)
    {
        ciachovanieArray[i] = malloc(2 * sizeof(char *));
        for (int k = 0; k < 2; ++k)
        {
            ciachovanieArray[i][k] = malloc(100 * sizeof(char));
            fscanf(file, "%s", ciachovanieArray[i][k]);
        }
    }

    fclose(file);

    for (int i = 0; i < *numPeople; ++i)
    {
        int additionalCounterIfInFileExist = 0;
        for (int k = 0; k < numCiachovanie; ++k)
        {
            if (strcmp((*dataArray)[i][0], ciachovanieArray[k][0]) == 0)
            {
                char modifiedString[100];
                char modifiedStringC[100];

                strncpy(modifiedString, (*dataArray)[i][5] + 4, strlen((*dataArray)[i][5]) - 6);
                modifiedString[strlen((*dataArray)[i][5]) - 6] = '\0';
                strncpy(modifiedStringC, ciachovanieArray[k][1] + 4, strlen(ciachovanieArray[k][1]));
                modifiedStringC[strlen(ciachovanieArray[k][1]) - 6] = '\0';

                int mNumberData = atoi(modifiedString);
                int mNumberCiachovanie = atoi(modifiedStringC);
                additionalCounterIfInFileExist++;
                if (mNumberData - mNumberCiachovanie > mounth)
                {
                    newSize++;
                }
            }
        }
        if (additionalCounterIfInFileExist == 0)
        {
            newSize++;
        }
    }

    if (newSize == 0)
    {
        printf("Polia nie su vytvorene\n");
        return;
    }

    filteredArray = malloc(newSize * sizeof(char *));
    for (int i = 0; i < newSize; ++i)
    {
        filteredArray[i] = malloc(6 * sizeof(char *));
        for (int k = 0; k < 6; ++k)
        {
            filteredArray[i][k] = malloc(100 * sizeof(char));
        }
    }
    for (int i = 0; i < *numPeople; ++i)
    {
        int additionalCounterIfInFileExist = 0;
        for (int k = 0; k < numCiachovanie; ++k)
        {
            if (strcmp((*dataArray)[i][0], ciachovanieArray[k][0]) == 0)
            {
                char modifiedString[100];
                char modifiedStringC[100];

                strncpy(modifiedString, (*dataArray)[i][5] + 4, strlen((*dataArray)[i][5]) - 6);
                modifiedString[strlen((*dataArray)[i][5]) - 6] = '\0';
                strncpy(modifiedStringC, ciachovanieArray[k][1] + 4, strlen(ciachovanieArray[k][1]));
                modifiedStringC[strlen(ciachovanieArray[k][1]) - 6] = '\0';

                int mNumberData = atoi(modifiedString);
                int mNumberCiachovanie = atoi(modifiedStringC);
                additionalCounterIfInFileExist++;
                if (mNumberData - mNumberCiachovanie > mounth)
                {
                    for (int n = 0; n < 6; n++)
                    {
                        strcpy(filteredArray[j][n], (*dataArray)[i][n]);
                    }
                    printf("ID. mer. modulu [%s] ma %d mesiacov po ciachovani\n", filteredArray[j][0], mNumberData - mNumberCiachovanie);
                    j++;
                }
            }
        }
        if (additionalCounterIfInFileExist == 0)
        {
            for (int n = 0; n < 6; n++)
            {
                strcpy(filteredArray[j][n], (*dataArray)[i][n]);
            }
            printf("ID. mer. modulu [%s] nie je ciachovany.\n", filteredArray[j][0]);
            j++;
        }
    }

    for (int i = 0; i < newSize; ++i)
    {
        for (int j = 0; j < 6; ++j)
        {
            free(filteredArray[i][j]);
        }
        free(filteredArray[i]);
    }
    free(filteredArray);
    filteredArray = NULL;
}

int compareStrings(const void *a, const void *b)
{
    return atoi(*(const char **)a) - atoi(*(const char **)b);
}

void s(char ****dataArray, int *numPeople, int isArrayCreated)
{
    if (isArrayCreated == 0)
    {
        printf("Polia nie su vytvorene.\n");
        return;
    }
    char ***filteredArray = NULL;
    int newSize = 0;
    int j = 0;

    char id[7];
    char type[3];
    printf("id & type: ");
    scanf(" %s %s", id, type);

    for (int i = 0; i < *numPeople; ++i)
    {
        if (strcmp((*dataArray)[i][0], id) == 0 && strcmp((*dataArray)[i][2], type) == 0)
        {
            newSize++;
        }
    }

    if (newSize == 0)
    {
        printf("Pre dany vstup neexistuju zaznamy\n");
        return;
    }

    filteredArray = malloc(newSize * sizeof(char *));
    for (int i = 0; i < newSize; ++i)
    {
        filteredArray[i] = malloc(6 * sizeof(char *));
        for (int k = 0; k < 6; ++k)
        {
            filteredArray[i][k] = malloc(100 * sizeof(char));
        }
    }

    for (int i = 0; i < *numPeople; ++i)
    {
        if (strcmp((*dataArray)[i][0], id) == 0 && strcmp((*dataArray)[i][2], type) == 0)
        {
            for (int k = 0; k < 6; k++)
            {
                strcpy(filteredArray[j][k], (*dataArray)[i][k]);
            }
            j++;
        }
    }

    char **arrayDateTime = NULL;
    char temp[40];
    for (int i = 0; i < newSize; i++)
    {
        arrayDateTime = malloc(12 * sizeof(int));

        strcpy(temp, filteredArray[i][5]);
        strcat(temp, filteredArray[i][4]);
        arrayDateTime[i] = temp;
    }


    qsort(arrayDateTime, newSize, sizeof(char *), compareStrings);

    char ***sortedArray = NULL;
    sortedArray = malloc(newSize * sizeof(char *));
    for (int i = 0; i < newSize; ++i)
    {
        sortedArray[i] = malloc(6 * sizeof(char *));
        for (int k = 0; k < 6; ++k)
        {
            sortedArray[i][k] = malloc(100 * sizeof(char));
        }
    }

    for (int i = 0; i < newSize; i++)
    {
        for (int k = 0; k < newSize; k++)
        {
            strcpy(temp, filteredArray[k][5]);
            strcat(temp, filteredArray[k][4]);
            if (arrayDateTime[i] == temp)
            {
                for (int n = 0; n < 6; n++)
                {
                    strcpy(sortedArray[i][n], filteredArray[k][n]);
                }
            }
        }
    }

    FILE *file = fopen("vystup_S.txt", "w");

    if (file == NULL)
    {
        printf("Cannot open.\n");
        return;
    }

    for (int i = 0; i < newSize; ++i)
    {
        char *plusPtr1 = strchr(filteredArray[i][1], '+');
        char *one;
        char *two;
        if (plusPtr1)
        {
            char *plusPtr2 = strchr(plusPtr1 + 1, '+');
            if (plusPtr2)
            {
                *plusPtr2 = '\0';
                one = plusPtr1 + 1;
                two = plusPtr2 + 1;
            }
        }
        printf("%s%s         %s         +%s   +%s\n", filteredArray[i][5], filteredArray[i][4], filteredArray[i][3], one, two);
        fprintf(file, "%s%s         %s         +%s   +%s\n", filteredArray[i][5], filteredArray[i][4], filteredArray[i][3], one, two);
    }

    fclose(file);

    for (int i = 0; i < newSize; ++i)
    {
        for (int j = 0; j < 6; ++j)
        {
            free(filteredArray[i][j]);
        }
        free(filteredArray[i]);
    }
    free(filteredArray);
    filteredArray = NULL;
    for (int i = 0; i < newSize; ++i)
    {
        for (int j = 0; j < 6; ++j)
        {
            free(sortedArray[i][j]);
        }
        free(sortedArray[i]);
    }
    free(sortedArray);
    sortedArray = NULL;
}

void h(char ***dataArray, int numPeople, int isArrayCreated)
{
    if (isArrayCreated == 0)
    {
        printf("Polia nie su vytvorene.\n");
        return;
    }
    char **uniqueStrings = malloc(numPeople * sizeof(char *));
    int *counts = malloc(numPeople * sizeof(int));
    double **minMaxArray = malloc(numPeople * sizeof(double *));
    for (int i = 0; i < numPeople; ++i)
    {
        minMaxArray[i] = malloc(2 * sizeof(double));
    }

    int uniqueCount = 0;

    for (int i = 0; i < numPeople; ++i)
    {
        int isDuplicate = 0;
        for (int j = 0; j < uniqueCount; ++j)
        {
            if (strcmp(dataArray[i][2], uniqueStrings[j]) == 0)
            {
                if (minMaxArray[j][0] > strtod(dataArray[i][3], NULL))
                    minMaxArray[j][0] = strtod(dataArray[i][3], NULL);
                else if (minMaxArray[j][1] < strtod(dataArray[i][3], NULL))
                    minMaxArray[j][1] = strtod(dataArray[i][3], NULL);
                isDuplicate = 1;
                counts[j]++;
            }
        }

        if (!isDuplicate)
        {
            minMaxArray[uniqueCount][0] = strtod(dataArray[i][3], NULL);
            minMaxArray[uniqueCount][1] = strtod(dataArray[i][3], NULL);

            uniqueStrings[uniqueCount] = strdup(dataArray[i][2]);
            counts[uniqueCount] = 1;
            uniqueCount++;
        }
    }
    if (uniqueCount == 0)
    {
        printf("Ziadne zaznamy pre typy RD, RM, RO.\n");
        return;
    }

    printf("Typ mer. vel.  Pocetnost  Minimum  Maximum\n");
    for (int i = 0; i < uniqueCount; ++i)
    {
        printf("%s             %d          %.2f   %.2f\n", uniqueStrings[i], counts[i], minMaxArray[i][0], minMaxArray[i][1]);
        free(uniqueStrings[i]);
    }
}

void z(char ****dataArray, int *numPeople, int isArrayCreated)
{
    if (isArrayCreated == 0)
    {
        printf("Polia nie su vytvorene.\n");
        return;
    }
    char ***filteredArray = NULL;
    int newSize = 0;
    int j = 0;

    char idToDelete[6];
    printf("id to delete: ");
    scanf(" %s", &idToDelete);

    for (int i = 0; i < *numPeople; ++i)
    {
        if (strcmp((*dataArray)[i][0], idToDelete) != 0)
        {
            newSize++;
        }
    }

    filteredArray = malloc(newSize * sizeof(char *));
    for (int i = 0; i < newSize; ++i)
    {
        filteredArray[i] = malloc(6 * sizeof(char *));
        for (int k = 0; k < 6; ++k)
        {
            filteredArray[i][k] = malloc(100 * sizeof(char));
        }
    }
    for (int i = 0; i < *numPeople; ++i)
    {
        if (strcmp((*dataArray)[i][0], idToDelete) != 0)
        {
            for (int k = 0; k < 6; k++)
            {
                strcpy(filteredArray[j][k], (*dataArray)[i][k]);
            }
            j++;
        }
    }

    for (int i = 0; i < *numPeople; ++i)
    {
        for (int j = 0; j < 6; ++j)
        {
            free((*dataArray)[i][j]);
        }
        free((*dataArray)[i]);
    }
    free(*dataArray);
    (*dataArray) = NULL;

    (*dataArray) = malloc(newSize * sizeof(char **));
    for (int i = 0; i < newSize; ++i)
    {
        (*dataArray)[i] = malloc(6 * sizeof(char *));
        for (int k = 0; k < 6; ++k)
        {
            (*dataArray)[i][k] = malloc(100 * sizeof(char));
            strcpy((*dataArray)[i][k], filteredArray[i][k]);
        }
    }
    printf("Vymazalo sa %d zaznamov!\n", (*numPeople) - newSize);
    (*numPeople) = newSize;

    for (int i = 0; i < newSize; ++i)
    {
        for (int j = 0; j < 6; ++j)
        {
            free(filteredArray[i][j]);
        }
        free(filteredArray[i]);
    }
    free(filteredArray);
    filteredArray = NULL;
}

void k(char ****dataArray, int *numPeople, int isArrayCreated)
{
    if (isArrayCreated == 0)
    {
        return;
    }
    
    for (int i = 0; i < *numPeople; ++i)
    {
        for (int j = 0; j < 6; ++j)
        {
            free((*dataArray)[i][j]);
        }
        free((*dataArray)[i]);
    }
    free(*dataArray);
}

int main()
{
    int numPeople = 10;
    char ***dataArray = NULL;
    int isFileOpen = 0;
    int isArrayCreated = 0;

    char command;
    while (1)
    {
        printf("Zadajte prikaz (v/n/c/s/h/z/k): ");
        scanf(" %c", &command);

        switch (command)
        {
        case 'v':
            v(dataArray, &numPeople, &isFileOpen);
            break;
        case 'n':
            n(&dataArray, &numPeople, isFileOpen, &isArrayCreated);
            break;
        case 'c':
            c(&dataArray, &numPeople, isArrayCreated);
            break;
        case 's':
            s(&dataArray, &numPeople, isArrayCreated);
            break;
        case 'h':
            h(dataArray, numPeople, isArrayCreated);
            break;
        case 'z':
            z(&dataArray, &numPeople, isArrayCreated);
            break;
        case 'k':
            k(&dataArray, &numPeople, isArrayCreated);
            exit(0);
            break;
        default:
            printf("Neplatny prikaz.\n");
            break;
        }
    }
    return 0;
}
