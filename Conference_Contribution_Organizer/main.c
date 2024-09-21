#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <malloc.h>

#define PD 0
#define UD 1
#define PP 2
#define UP 3
#define true 1
#define false 0

typedef int bool;

typedef struct
{
    char *firstName;
    char *secondName;
    char *prefix;
} author_name;

typedef struct
{
    int type;
    char id[9];
    char name[151];
    author_name *autors;
    int autorsLength;
    char date[13];
} elem;

typedef struct _unit
{
    elem currentBlock;
    struct _unit *next;
} unit;

elem scanElem(FILE *file);
char *typeToString(int type);
int stringToType(const char *type);
elem createElem(char *input);
void printElem(elem currentBlock);

void n(unit **array);
void v(unit **array);
void p(unit **array);
void z(unit **array);
void a(unit **array);
void r(unit **array);
void k(unit **array);

void appendElem(elem currentBlock, unit **array);
void insertElem(elem currentBlock, int index, unit **array);
void swapElems(int first, int second, unit **array);
void deleteElem(int index, unit **array);
void clearArray(unit **array);
void clearUnit(unit **unit);
unit *scanArray(FILE *file);

char *concatFn(char *href, char *second)
{
    int firstLen = strlen(href);
    int length = firstLen + strlen(second);
    char *output = (char *)malloc(sizeof(char) * (length + 1));

    for (int i = 0; i < length; i++)
    {
        if (i < firstLen)
        {
            output[i] = href[i];
        }
        else
        {
            output[i] = second[i - firstLen];
        }
    }
    output[length] = 0;
    free(href);

    return output;
}

void clearArray(unit **array)
{
    if (array == NULL)
        return;

    // clear each unit
    unit *pointer = *array;
    while (pointer != NULL)
    {
        unit *previous = pointer;
        pointer = pointer->next;
        clearUnit(&previous);
    }
    // set the array pointer to null for other functions
    *array = NULL;
}

void n(unit **array)
{
    FILE *file = fopen("KonferencnyZoznam2.txt", "r");
    if (!file)
    {
        printf("Zaznamy neboli nacitane!\n");
        return;
    }

    if (*array != NULL)
        clearArray(array);

    *array = scanArray(file);

    int length = 0;
    unit *pointer = *array;
    while (pointer != NULL)
    {
        pointer = pointer->next;
        length++;
    }
    printf("Nacitalo sa %d zaznamov\n", length);

    fclose(file);
}

void v(unit **array)
{
    if (*array == NULL)
        printf("Prazdny zoznam zaznamov.\n");

    unit *current = *array;
    int c = 1;
    while (current != NULL)
    {
        printf("%d.\n", c);
        c++;
        printElem(current->currentBlock);
        current = current->next;
    }
}

void printElem(elem currentBlock)
{
    printf("ID prispevku: %s%s\n", currentBlock.id, typeToString(currentBlock.type));
    printf("Nazov prispevku: %s\n", currentBlock.name);
    printf("Mena autorov:\n");
    for (int i = 0; i < currentBlock.autorsLength; i++)
    {
        printf("\t%d: ", i + 1);

        printf("%s %s ", currentBlock.autors[i].firstName, currentBlock.autors[i].secondName);
        printf("(%s)\n", currentBlock.autors[i].prefix);
    }
    printf("Datum a Cas: ");

    char bufer[5];
    bufer[4] = 0;

    strncpy(bufer, currentBlock.date, 4);
    printf("%s.", bufer);

    strncpy(bufer, currentBlock.date + 4, 2);
    bufer[2] = 0;
    printf("%s.", bufer);

    strncpy(bufer, currentBlock.date + 6, 2);
    printf("%s ", bufer);

    strncpy(bufer, currentBlock.date + 8, 2);
    printf("%s:", bufer);

    strncpy(bufer, currentBlock.date + 10, 2);
    printf("%s\n", bufer);
}

void p(unit **array)
{
    getchar(); // flush \n
    int index;
    scanf("%d", &index);
    getchar(); // flush \n
    insertElem(scanElem(stdin), index, array);
}

void insertElem(const elem currentBlock, const int index, unit **array)
{
    if (array == NULL)
        return;

    unit *newElem = (unit *)malloc(sizeof(unit));
    newElem->currentBlock = currentBlock;
    unit **pointer = array;
    int currentIndex = 1;
    while (currentIndex < index && *pointer != NULL)
    {
        currentIndex++;
        pointer = &((*pointer)->next);
    }

    unit *temp = *pointer;
    *pointer = newElem;
    newElem->next = temp;
}

void z(unit **array)
{
    getchar(); // flush \n
    char bufer[512];
    fgets(bufer, 511, stdin); // allows to enter more than one word
    // get rid of the line break
    for (int i = 0; bufer[i] != 0; i++)
    {
        if (bufer[i] == '\n')
        {
            bufer[i] = 0;
            break;
        }
    }
    // convert input query to lowercase to achieve consistency
    for (int i = 0; bufer[i] != 0; i++)
    {
        bufer[i] = tolower(bufer[i]);
    }
    unit **pointer = array;
    int index = 1;
    // iterate through each unit
    while (*pointer != NULL)
    {
        bool skip = false; // indicates if we should skip iteration step
        // iterate through each author
        for (int i = 0; i < (*pointer)->currentBlock.autorsLength; i++)
        {
            // skip currentBlock if currentBlock's not actually author
            if (strcmp((*pointer)->currentBlock.autors[i].prefix, "A") != 0)
                continue;

            // make full name out of first and second names
            char *fullName = strdup((*pointer)->currentBlock.autors[i].firstName);
            fullName = concatFn(fullName, " ");
            fullName = concatFn(fullName, (*pointer)->currentBlock.autors[i].secondName);

            // convert to lower for consistency with bufer
            for (int i = 0; fullName[i] != 0; i++)
            {
                fullName[i] = tolower(fullName[i]);
            }

            // compare the two names
            if (strcmp(fullName, bufer) == 0)
            {
                free(fullName); // clear up!
                printf("Prispevok s nazvom %s bol vymazany.\n", (*pointer)->currentBlock.name);
                deleteElem(index, array);
                skip = true;
                break;
            }
            free(fullName); // clear up!
        }
        if (skip)
        {
            skip = false;
            continue;
        }

        // only step forward if a unit was not deleted
        // if currentBlock was, the pointer points at the next unit of the deleted one
        pointer = &((*pointer)->next);
        index++;
    }
}

void a(unit **array)
{
    getchar(); // flush \n
    // bufer string for input
    char bufer[512];
    while (true)
    {
        // fgets because currentBlock eats the \n character right away
        fgets(bufer, 511, stdin);
        // get rid of the line break
        for (int i = 0; bufer[i] != 0; i++)
        {
            if (bufer[i] == '\n')
            {
                bufer[i] = 0;
                break;
            }
        }

        int id = 0; // numerical id
        for (int i = 0; i < 8; i++)
        {
            id *= 10;
            id += bufer[i] - '0';
        }

        // input validation
        // could be done by checking if the second number is 0 or 5 and the sum
        // can be divided by 3, but there's no difference, since we still
        // need to iterate over the string
        if (
            id % 15 != 0 ||
            (bufer[8] != 'P' && bufer[8] != 'U') ||
            (bufer[9] != 'P' && bufer[9] != 'D'))
        {
            printf("Zadane udaje nie su korektne, zadaj novy retazec: ");
            continue;
        }

        // iterate over the array, search for given id
        unit *pointer = *array;
        while (pointer != NULL)
        {
            // compare first 8 characters only
            if (strncmp(bufer, pointer->currentBlock.id, 8) != 0)
            {
                pointer = pointer->next;
                continue;
            }
            // confirm change
            int previousBlock = pointer->currentBlock.type;
            pointer->currentBlock.type = stringToType(bufer + 8);
            printf("Prispevok s nazvom %s sa bude prezentovat %s [%s].\n",
                   pointer->currentBlock.name,
                   typeToString(pointer->currentBlock.type),
                   typeToString(previousBlock));
            return;
        }
        printf("Zadane udaje nie su korektne, zadaj novy retazec: ");
    }
}

void r(unit **array)
{
    getchar(); // flush \n
    int first, second;
    scanf("%d%d", &first, &second);
    swapElems(first, second, array);
}

void k(unit **array)
{
    printf("Koniec");
    clearArray(array);
}

elem scanElem(FILE *file)
{
    char bufer[512]; // this will be enough to store whole structure
    int length = 0;
    for (int i = 0; i < 4; i++)
    {
        fgets(bufer + length, 512 - length, file);
        while (bufer[length] != '\n' && bufer[length] != 0)
            length++;
        length++;
    }
    bufer[length] = 0;
    return createElem(bufer);
}

elem createElem(char *input)
{
    elem result;
    char *current = input;
    result.type = stringToType(current);

    current += 2;
    int length = 0;

    strncpy(result.id, current, 8);
    result.id[8] = 0;

    current += strcspn(current, "\n") + 1;
    length = strcspn(current, "\n");

    strncpy(result.name, current, length);
    result.name[length] = 0;

    current += strcspn(current, "\n") + 1;

    // author names parsing
    length = strcspn(current, "\n");

    int authorLength = 0;
    result.autors = NULL;
    while (*current != '\n')
    {
        author_name *previousBlock = result.autors;
        // expand the array
        result.autors = (author_name *)malloc(sizeof(author_name) * (authorLength + 1));
        // copy over previousBlock data
        for (int i = 0; i < authorLength; i++)
        {
            result.autors[i] = previousBlock[i];
        }
        free(previousBlock); // free previousBlock array
        // copy to first name until first space
        result.autors[authorLength].firstName = strtok(strdup(current), " ");
        // move the current pointer to the end of first name + 1
        current = strpbrk(current, " ") + 1;
        // copy the rest of the name to second name
        result.autors[authorLength].secondName = strtok(strdup(current), "#");
        // move the current pointer to the end of the whole name + 1
        current = strpbrk(current, "#") + 1;

        // do the same for prefix
        result.autors[authorLength].prefix = strtok(strdup(current), "#");
        current = strpbrk(current, "#") + 1;
        authorLength++;
    }

    result.autorsLength = authorLength;

    current += strcspn(current, "\n") + 1;

    strncpy(result.date, current, 12);
    result.date[12] = 0;

    return result;
}

void swapElems(int first, int second, unit **array)
{
    // first is guaranteed to be less or equal to second
    if (first > second)
    {
        int t = first;
        first = second;
        second = t;
    }

    if (first == second || first < 1 || second < 1 || array == NULL || *array == NULL)
        return;

    // now first < second for sure

    unit **firstPointer = array;
    int current = 1;

    // find first's position
    while (current < first && *firstPointer != NULL)
    {
        current++;
        firstPointer = &((*firstPointer)->next);
    }

    // first is out of bounds, do nothing
    if (*firstPointer == NULL)
        return;

    // special case for when first and second are neighbours
    if (second - first == 1)
    {
        // case when first is the last unit in array
        if ((*firstPointer)->next == NULL)
            return;
        unit *aUnit = *firstPointer;
        unit *bUnit = (*firstPointer)->next;
        *firstPointer = bUnit;
        aUnit->next = bUnit->next;
        bUnit->next = aUnit;
        return;
    }

    // find second's location
    unit **secondPointer = firstPointer;
    while (current < second && *secondPointer != NULL)
    {
        current++;
        secondPointer = &((*secondPointer)->next);
    }

    // second is out of bounds, do nothing
    if (*secondPointer == NULL)
        return;

    // swap first and second
    unit *aUnit = *firstPointer, *bUnit = *secondPointer;

    *firstPointer = bUnit;
    *secondPointer = aUnit;

    unit *t = aUnit->next;
    aUnit->next = bUnit->next;
    bUnit->next = t;
}

void deleteElem(int index, unit **array)
{
    unit **pointer = array;
    // index out of bounds
    if (index < 1)
        return;

    // go through the array, find the unit location
    for (int i = 1; i < index && *pointer != NULL; i++)
    {
        pointer = &((*pointer)->next);
    }

    // deleting the elem
    unit *deleted = *pointer;
    *pointer = (*pointer)->next; // replace the next link
    clearUnit(&deleted);         // actually remove the elem from memory
}

void clearUnit(unit **unit)
{
    // free all author units
    for (int i = 0; i < (*unit)->currentBlock.autorsLength; i++)
    {
        free((*unit)->currentBlock.autors[i].firstName);
        free((*unit)->currentBlock.autors[i].secondName);
        free((*unit)->currentBlock.autors[i].prefix);
    }
    // free the rest
    free((*unit)->currentBlock.autors);
    free(*unit);
    *unit = NULL;
}

void appendElem(elem currentBlock, unit **array)
{
    if (*array == NULL)
    {
        *array = (unit *)malloc(sizeof(unit));
        (*array)->currentBlock = currentBlock;
        (*array)->next = NULL;
        return;
    }
    unit *pointer = *array;
    while (pointer->next != NULL)
        pointer = pointer->next;
    pointer->next = (unit *)malloc(sizeof(unit));
    pointer->next->currentBlock = currentBlock;
    pointer->next->next = NULL;
}


unit *scanArray(FILE *file)
{
    unit *array = NULL;

    char bufer[512];

    while (fgets(bufer, 511, file) != NULL)
    {
        appendElem(scanElem(file), &array);
    }

    return array;
}

char *typeToString(int type)
{
    switch (type)
    {
    case PD:
        return "PD";
    case PP:
        return "PP";
    case UD:
        return "UD";
    case UP:
        return "UP";
    }
    return "";
}
int stringToType(const char *type)
{
    if (type[0] == 'P')
    {
        if (type[1] == 'P')
        {
            return PP;
        }
        else
        {
            return PD;
        }
    }
    else
    {
        if (type[1] == 'P')
        {
            return UP;
        }
        else
        {
            return UD;
        }
    }
}

int main()
{
    unit *array = NULL;
    while (true)
    {
        switch (getchar())
        {
        case 'n':
            n(&array);
            break;
        case 'v':
            v(&array);
            break;
        case 'p':
            p(&array);
            break;
        case 'z':
            z(&array);
            break;
        case 'a':
            a(&array);
            break;
        case 'r':
            r(&array);
            break;
        case 'k':
            k(&array);
            return 0;
        }
    }
    return 0;
}
