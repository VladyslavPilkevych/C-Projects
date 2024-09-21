#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <malloc.h>

typedef int bool;

#define PD 0
#define UD 1
#define PP 2
#define UP 3

typedef struct {
    char* firstName;
    char* lastName;
    char* role;
} author_name;

typedef struct {
    int type;
    char id[9];
    char name[151];
    author_name* authors;
    int authorsLength;
    char date[13];
} item;

typedef struct _node {
    item it;
    struct _node *next;
} node;

#define true 1
#define false 0

item scanItem(FILE* file);
char *typeToString(int type);
int stringToType(const char *type);
item createItem(char *input);
void printItem(item it);

void appendItem(item it, node **list);
void insertItem(item it, int index, node **list);
void swapItems(int a, int b, node **list);
void deleteItem(int index, node **list);
void destroyList(node **list);
void destroyNode(node **node);
void printList(node **list);
node *scanList(FILE* file);

void n(node **list);
void v(node **list);
void p(node **list);
void z(node **list);
void a(node **list);
void r(node **list);
void k(node **list);

int main() {
    node* list = NULL;
    while(true) {
        switch (getchar()) {
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
            case 'a':
                a(&list);
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

void n(node **list) {
    FILE* file = fopen("KonferencnyZoznam2.txt", "r");
    if(!file) {
        printf("Zaznamy neboli nacitane!\n");
        return;
    }

    if(*list != NULL)
        destroyList(list);

    *list = scanList(file);

    int length = 0;
    node* cursor = *list;
    while(cursor != NULL) {
        cursor = cursor->next;
        // (*cursor).next
        length++;
    }
    printf("Nacitalo sa %d zaznamov\n", length);

    fclose(file);
}

void v(node **list) {
    printList(list);
}

void p(node **list) {
    getchar(); // flush \n
    int index;
    scanf("%d", &index);
    
    getchar(); // flush \n
    insertItem(scanItem(stdin), index, list);
}

void z(node **list) {
    getchar(); // flush \n
    char buffer[512];
    fgets(buffer, 511, stdin); // allows to enter more than one word
    // get rid of the line break
    for(int i = 0; buffer[i] != 0; i++) {
        if(buffer[i] == '\n') {
            buffer[i] = 0;
            break;
        }
    }
    // convert input query to lowercase to achieve consistency
    for (int i = 0; buffer[i] != 0; i++) {
        buffer[i] = tolower(buffer[i]);
    }
    node **cursor = list;
    int index = 1;
    // iterate through each node
    while(*cursor != NULL) {
        bool skip = false; // indicates if we should skip iteration step
        // iterate through each author
        for(int i = 0; i < (*cursor)->it.authorsLength; i++) {
            // skip it if it's not actually author
            if(strcmp((*cursor)->it.authors[i].role, "A") != 0)
                continue;

            // make full name out of first and last names
            char *fullName = strdup((*cursor)->it.authors[i].firstName);
            strcat(fullName, " ");
            strcat(fullName, (*cursor)->it.authors[i].lastName);
            // convert to lower for consistency with buffer
            for (int i = 0; fullName[i] != 0; i++) {
                fullName[i] = tolower(fullName[i]);
            }

            // compare the two names
            if(strcmp(fullName, buffer) == 0) {
                free(fullName); // clear up!
                printf("Prispevok s nazvom %s bol vymazany.\n", (*cursor)->it.name);
                deleteItem(index, list);
                skip = true;
                break;
            }
        }
        if(skip) {
            skip = false;
            continue;
        }

        // only step forward if a node was not deleted
        // if it was, the cursor points at the next node of the deleted one
        cursor = &((*cursor)->next);
        index++;
    }
}

void a(node **list) {
    getchar(); // flush \n
    // buffer string for input
    char buffer[512];
    while(true) {
        // fgets because it eats the \n character right away
        fgets(buffer, 11, stdin);
        // get rid of the line break
        for(int i = 0; buffer[i] != 0; i++) {
            if(buffer[i] == '\n') {
                buffer[i] = 0;
                break;
            }
        }
        
        int id = 0; // numerical id
        for(int i = 0; i < 8; i++) {
            id *= 10;
            id += buffer[i] - '0';
        }

        // input validation
        // could be done by checking if the last number is 0 or 5 and the sum
        // can be divided by 3, but there's no difference, since we still
        // need to iterate over the string
        if(
            id % 15 != 0 ||
            (buffer[8] != 'P' && buffer[8] != 'U') ||
            (buffer[9] != 'P' && buffer[9] != 'D')
        ) {
            printf("Zadane udaje nie su korektne, zadaj novy retazec: ");
            continue;
        }

        // iterate over the list, search for given id
        node* cursor = *list;
        while(cursor != NULL) {
            // compare first 8 characters only
            if(strncmp(buffer, cursor->it.id, 8) != 0) {
                cursor = cursor->next;
                continue;
            }
            // confirm change
            int old = cursor->it.type;
            cursor->it.type = stringToType(buffer + 8);
            printf("Prispevok s nazvom %s sa bude prezentovat %s [%s].\n",
                   cursor->it.name,
                   typeToString(cursor->it.type),
                   typeToString(old)
                   );
            return;
        }
        printf("Zadane udaje nie su korektne, zadaj novy retazec: ");
    }
}

void r(node **list) {
    getchar(); // flush \n
    int a, b;
    scanf("%d%d", &a, &b);
    swapItems(a, b, list);
}

void k(node **list) {
    destroyList(list);
}

item createItem(char *input) {
    item result;
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
    result.authors = NULL;
    while(*current != '\n') {
        author_name* old = result.authors;
        // expand the array
        result.authors = (author_name*) malloc(sizeof(author_name) * (authorLength + 1));
        // copy over old data
        for(int i = 0; i < authorLength; i++) {
            result.authors[i] = old[i];
        }
        free(old); // free old array
        // copy to first name until first space
        result.authors[authorLength].firstName = strtok(strdup(current), " ");
        // move the current pointer to the end of first name + 1
        current = strpbrk(current, " ") + 1;
        // copy the rest of the name to last name
        result.authors[authorLength].lastName = strtok(strdup(current), "#");
        // move the current pointer to the end of the whole name + 1
        current = strpbrk(current, "#") + 1;
        // do the same for role
        result.authors[authorLength].role = strtok(strdup(current), "#");
        current = strpbrk(current, "#") + 1;
        authorLength++;
    }

    result.authorsLength = authorLength;

    current += strcspn(current, "\n") + 1;

    strncpy(result.date, current, 12);
    result.date[12] = 0;

    return result;
}

void printItem(item it) {
    printf("ID prispevku: %s%s\n", it.id, typeToString(it.type));
    printf("Nazov prispevku: %s\n", it.name);
    printf("Mena autorov:\n");
    for(int i = 0; i < it.authorsLength; i++) {
        printf("\t%d: ", i + 1);

        printf("%s %s ", it.authors[i].firstName, it.authors[i].lastName);
        printf("(%s)\n", it.authors[i].role);
    }
    printf("Datum a Cas: ");

    char buffer[5];
    buffer[4] = 0;

    strncpy(buffer, it.date, 4);
    printf("%s.", buffer);

    strncpy(buffer, it.date + 4, 2);
    buffer[2] = 0;
    printf("%s.", buffer);

    strncpy(buffer, it.date + 6, 2);
    printf("%s ", buffer);

    strncpy(buffer, it.date + 8, 2);
    printf("%s:", buffer);

    strncpy(buffer, it.date + 10, 2);
    printf("%s\n", buffer);
}

item scanItem(FILE* file) {
    char buffer[512]; // this will be enough to store whole structure
    int length = 0;
    for (int i = 0; i < 4; i++) {
        fgets(buffer + length, 512 - length, file);
        while(buffer[length] != '\n' && buffer[length] != 0)
            length++;
        length++;
    }
    buffer[length] = 0;
    return createItem(buffer);
}

void appendItem(item it, node **list) {
    if(*list == NULL) {
        *list = (node*)malloc(sizeof(node));
        (*list)->it = it;
        (*list)->next = NULL;
        return;
    }
    node* cursor = *list;
    while(cursor->next != NULL)
        cursor = cursor->next;
    cursor->next = (node*)malloc(sizeof(node));
    cursor->next->it = it;
    cursor->next->next = NULL;
}

void insertItem(const item it, const int index, node **list) {
    if(list == NULL)
        return;

    node* newItem = (node*)malloc(sizeof(node));
    newItem->it = it;
    node **cursor = list;
    int currentIndex = 1;
    while(currentIndex < index && *cursor != NULL) {
        currentIndex++;
        cursor = &((*cursor)->next);
    }

    node* temp = *cursor;
    *cursor = newItem;
    newItem->next = temp;
}

void swapItems(int a, int b, node **list) {
    // a is guaranteed to be less or equal to b
    if(a > b) {
        int t = a;
        a = b;
        b = t;
    }

    if(a == b || a < 1 || b < 1 || list == NULL || *list == NULL)
        return;

    // now a < b for sure

    node **aCursor = list;
    int current = 1;

    // find a's position
    while(current < a && *aCursor != NULL) {
        current++;
        aCursor = &((*aCursor)->next);
    }

    // a is out of bounds, do nothing
    if(*aCursor == NULL)
        return;

    // special case for when a and b are neighbours
    if(b - a == 1) {
        // case when a is the last node in list
        if((*aCursor)->next == NULL)
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
    while(current < b && *bCursor != NULL) {
        current++;
        bCursor = &((*bCursor)->next);
    }

    // b is out of bounds, do nothing
    if(*bCursor == NULL)
        return;

    // swap a and b
    node *aNode = *aCursor, *bNode = *bCursor;

    *aCursor = bNode;
    *bCursor = aNode;

    node *t = aNode->next;
    aNode->next = bNode->next;
    bNode->next = t;
}

void deleteItem(int index, node **list) {
    node **cursor = list;
    // index out of bounds
    if(index < 1)
        return;

    // go through the list, find the node location
    for(int i = 1; i < index && *cursor != NULL; i++) {
        cursor = &((*cursor)->next);
    }

    // deleting the item
    node *deleted = *cursor;
    *cursor = (*cursor)->next; // replace the next link
    destroyNode(&deleted); // actually remove the item from memory
}

void destroyNode(node **node) {
    // free all author nodes
    for(int i = 0; i < (*node)->it.authorsLength; i++) {
        free((*node)->it.authors[i].firstName);
        free((*node)->it.authors[i].lastName);
        free((*node)->it.authors[i].role);
    }
    // free the rest
    free((*node)->it.authors);
    free(*node);
    *node = NULL;
}

void destroyList(node **list) {
    if(list == NULL)
        return;

    // destroy each node
    node *cursor = *list;
    while(cursor != NULL) {
        node *previous = cursor;
        cursor = cursor->next;
        destroyNode(&previous);
    }
    // set the list pointer to null for other functions
    *list = NULL;
}

void printList(node **list) {
    node* current = *list;
    int counter = 1;
    while(current != NULL) {
        printf("%d.\n", counter);
        counter++;
        printItem(current->it);
        current = current->next;
    }
}

node* scanList(FILE* file) {
    node* list = NULL;

    char buffer[512];

    while(fgets(buffer, 511, file) != NULL) {
        appendItem(scanItem(file), &list);
    }

    return list;
}

char *typeToString(int type) {
    switch(type) {
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
int stringToType(const char *type) {
    if(type[0] == 'P') {
        if(type[1] == 'P') {
            return PP;
        } else {
            return PD;
        }
    } else {
        if(type[1] == 'P') {
            return UP;
        } else {
            return UD;
        }
    }
}

