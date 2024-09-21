#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <malloc.h>

typedef int bool;

typedef struct
{
    char id[6];
    char modulePosition[17];
    int type[3];
    char number[151];
    char time[7];
    char date[9];
} item;

typedef struct _node
{
    item it;
    struct _node *next;
} node;

#define true 1
#define false 0

item scanElement(FILE *file);
item createElement(char *input);
void printElement(item it);

void appendElement(item it, node **list);
void insertElement(item it, int index, node **list);
void swapElements(int a, int b, node **list);
void deleteElement(int index, node **list);
void destroyList(node **list);
void destroyNode(node **node);
void printList(node **list);
node *scanList(FILE *file);

void n(node **list);
void v(node **list);
void p(node **list);
void u(node **list);
void z(node **list);
void r(node **list);
void k(node **list);

int main()
{
    node *list = NULL;
    while (true)
    {
        switch (getchar())
        {
        case 'n':
            n(&list);
            break;
        case 'v':
            v(&list);
            break;
        case 'p':
            p(&list);
            break;
        case 'z':
            z(&list);
            break;
        case 'u':
            u(&list);
            break;
        case 'r':
            r(&list);
            break;
        case 'k':
            k(&list);
            return 0;
        }
    }
    return 0;
}

void n(node **list)
{
    FILE *file = fopen("dataloger_V2.txt", "r");
    if (!file)
    {
        printf("Zaznamy neboli nacitane!\n");
        return;
    }

    if (*list != NULL)
        destroyList(list);

    *list = scanList(file);

    int length = 0;
    node *cursor = *list;
    while (cursor != NULL)
    {
        cursor = cursor->next;
        length++;
    }
    printf("Nacitalo sa %d zaznamov\n", length);

    fclose(file);
}

void v(node **list)
{
    if (*list == NULL)
        printf("Prazdny zoznam zaznamov.\n");
    printList(list);
}

void p(node **list)
{
    getchar(); // flush \n
    int index;
    scanf("%d", &index);
    getchar(); // flush \n
    insertElement(scanElement(stdin), index, list);
}

char *concatenate(char *destination, char *second)
{
    int firstLen = strlen(destination);
    int length = firstLen + strlen(second);
    char *output = (char *)malloc(sizeof(char) * (length + 1));

    for (int i = 0; i < length; i++)
    {
        if (i < firstLen)
        {
            output[i] = destination[i];
        }
        else
        {
            output[i] = second[i - firstLen];
        }
    }
    output[length] = 0;
    free(destination);

    return output;
}

void z(node **list)
{
    getchar();
    char buffer[512];
    fgets(buffer, 511, stdin);
    for (int i = 0; buffer[i] != 0; i++)
    {
        if (buffer[i] == '\n')
        {
            buffer[i] = 0;
            break;
        }
    }
    node **cursor = list;
    int index = 1;
    while (*cursor != NULL)
    {
        bool skip = false;
        if (strcmp((*cursor)->it.id, buffer) == 0)
        {
            printf("Prispevok s nazvom %s bol vymazany.\n", (*cursor)->it.id);
            deleteElement(index, list);
            skip = true;
            // break;
        }
        if (skip)
        {
            skip = false;
            continue;
        }

        cursor = &((*cursor)->next);
        index++;
    }
}

void filterByDateTime(node **list, int num)
{
    node **cursor = list;
    int minValueDate = 0;
    int minValueTime = 0;
    int minCount = 0;
    int index = 1;
    while (*cursor != NULL)
    {
        char buffer[14];
        char buffer1[14];
        if (index == 1)
        {
            strcpy(buffer, (*cursor)->it.date);
            strcpy(buffer1, (*cursor)->it.time);
            int intValueDate = atoi(buffer);
            int intValueTime = atoi(buffer1);

            minValueDate = intValueDate;
            minValueTime = intValueTime;
            minCount = index;
        }
        else if (num < index)
        {
            strcpy(buffer, (*cursor)->it.date);
            strcpy(buffer1, (*cursor)->it.time);
            int currentValueDate = atoi(buffer);
            int currentValueTime = atoi(buffer1);
            // printf("currentValueDate < minValueDate\n%d < %d\nnum:%d\nindex:%d\n\n", currentValueDate, minValueDate, num, index);
            if (currentValueDate < minValueDate || (currentValueDate == minValueDate && currentValueTime < minValueTime))
            {
                minValueDate = currentValueDate;
                minValueTime = currentValueTime;
                minCount = index;
            }
        }
        cursor = &((*cursor)->next);
        index++;
    }
    if (num != 1)
    {
        swapElements(num, minCount, list);
    }
}

void u(node **list)
{
    node **cursor = list;
    int index = 1;
    while (*cursor != NULL)
    {
        filterByDateTime(list, index);
        cursor = &((*cursor)->next);
        index++;
    }
}

void r(node **list)
{
    getchar(); // flush \n
    int a, b;
    scanf("%d%d", &a, &b);
    swapElements(a, b, list);
}

void k(node **list)
{
    destroyList(list);
}

item createElement(char *input)
{
    item result;

    char *current = input;

    strncpy(result.id, current, 5);
    result.id[5] = 0;

    current += strcspn(current, "\n") + 1;

    strncpy(result.modulePosition, current, 16);
    result.modulePosition[16] = 0;

    current += strcspn(current, "\n") + 1;

    strncpy(result.type, current, 2);
    result.type[2] = 0;

    current += strcspn(current, "\n") + 1;

    strncpy(result.number, current, 6);
    result.number[6] = 0;

    current += strcspn(current, "\n") + 1;

    strncpy(result.time, current, 6);
    result.time[6] = 0;

    current += strcspn(current, "\n") + 1;

    strncpy(result.date, current, 8);
    result.date[8] = 0;

    // printf("\n createElement: \n%s\n%s\n%s\n%s\n%s\n%s\n\n\n", result.id, result.modulePosition, result.type, result.number, result.time, result.date);
    return result;
}

void printElement(item it)
{
    printf("ID: %s  %.2s   %s\n", it.id, it.type, it.number);
    printf("Poz: %s\n", it.modulePosition);

    printf("DaC: ");

    char buffer[5];
    buffer[4] = 0;

    strncpy(buffer, it.date, 4);
    printf("%s.", buffer);

    strncpy(buffer, it.date + 4, 2);
    buffer[2] = 0;
    printf("%s.", buffer);

    strncpy(buffer, it.date + 6, 2);
    printf("%s ", buffer);

    strncpy(buffer, it.time, 2);
    printf("%s:", buffer);

    strncpy(buffer, it.time + 2, 2);
    printf("%s\n", buffer);
}

item scanElement(FILE *file)
{
    char buffer[512];
    int length = 0;
    for (int i = 0; i < 6; i++)
    {
        fgets(buffer + length, 512 - length, file);
        while (buffer[length] != '\n' && buffer[length] != 0)
            length++;
        length++;
    }
    buffer[length] = 0;
    return createElement(buffer);
}

void appendElement(item it, node **list)
{
    if (*list == NULL)
    {
        *list = (node *)malloc(sizeof(node));
        (*list)->it = it;
        (*list)->next = NULL;
        return;
    }
    node *cursor = *list;
    while (cursor->next != NULL)
        cursor = cursor->next;
    cursor->next = (node *)malloc(sizeof(node));
    cursor->next->it = it;
    cursor->next->next = NULL;
}

void insertElement(const item it, const int index, node **list)
{
    if (list == NULL)
        return;

    node *newItem = (node *)malloc(sizeof(node));
    newItem->it = it;
    node **cursor = list;
    int currentIndex = 1;
    while (currentIndex < index && *cursor != NULL)
    {
        currentIndex++;
        cursor = &((*cursor)->next);
    }

    node *temp = *cursor;
    *cursor = newItem;
    newItem->next = temp;
}

void swapElements(int a, int b, node **list)
{
    // a is guaranteed to be less or equal to b
    if (a > b)
    {
        int t = a;
        a = b;
        b = t;
    }

    if (a == b || a < 1 || b < 1 || list == NULL || *list == NULL)
        return;

    // now a < b for sure

    node **aCursor = list;
    int current = 1;

    // find a's position
    while (current < a && *aCursor != NULL)
    {
        current++;
        aCursor = &((*aCursor)->next);
    }

    // a is out of bounds, do nothing
    if (*aCursor == NULL)
        return;

    // special case for when a and b are neighbours
    if (b - a == 1)
    {
        // case when a is the last node in list
        if ((*aCursor)->next == NULL)
            return;
        node *aNode = *aCursor;
        node *bNode = (*aCursor)->next;
        *aCursor = bNode;
        aNode->next = bNode->next;
        bNode->next = aNode;
        return;
    }

    // find b's location
    node **bCursor = aCursor;
    while (current < b && *bCursor != NULL)
    {
        current++;
        bCursor = &((*bCursor)->next);
    }

    // b is out of bounds, do nothing
    if (*bCursor == NULL)
        return;

    // swap a and b
    node *aNode = *aCursor, *bNode = *bCursor;

    *aCursor = bNode;
    *bCursor = aNode;

    node *t = aNode->next;
    aNode->next = bNode->next;
    bNode->next = t;
}

void deleteElement(int index, node **list)
{
    node **cursor = list;
    // index out of bounds
    if (index < 1)
        return;

    // go through the list, find the node location
    for (int i = 1; i < index && *cursor != NULL; i++)
    {
        cursor = &((*cursor)->next);
    }

    // deleting the item
    node *deleted = *cursor;
    *cursor = (*cursor)->next; // replace the next link
    destroyNode(&deleted);     // actually remove the item from memory
}

void destroyNode(node **node)
{
    free(*node);
    *node = NULL;
}

void destroyList(node **list)
{
    if (list == NULL)
        return;

    // destroy each node
    node *cursor = *list;
    while (cursor != NULL)
    {
        node *previous = cursor;
        cursor = cursor->next;
        destroyNode(&previous);
    }
    // set the list pointer to null for other functions
    *list = NULL;
}

void printList(node **list)
{
    node *current = *list;
    int counter = 1;
    while (current != NULL)
    {
        printf("%d.\n", counter);
        counter++;
        printElement(current->it);
        current = current->next;
    }
}

node *scanList(FILE *file)
{
    node *list = NULL;

    char buffer[512];

    while (fgets(buffer, 511, file) != NULL)
    {
        appendElement(scanElement(file), &list);
    }

    return list;
}
