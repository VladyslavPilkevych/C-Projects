#include <stdio.h>

int NacitajZnakPismeno(char N, char M, char V)
{
    char znak;
    printf("\nZadaj %s znak z intervalu <%c,%c>: ", (V == 'M') ? "maly" : "velky", N, M);
    scanf(" %c", &znak);
    if(V == 'M') {
        if (N >= 'a' && N <= 'z' && M >= 'a' && M <= 'z' && N < M && znak >= N && znak <= M) {
            return (int)znak;
        } else {
            return 0;
        }
    } else {
        if (N >= 'A' && N <= 'Z' && M >= 'A' && M <= 'Z' && N < M && znak >= N && znak <= M)
        {
            return (int)znak;
        } else {
            return 0;
        }
    }
    return 0;
}

int VykreslenieZC(int velkost) {
    if (velkost <= 0) {
        return 0;
    }
    printf("Velkost: %d \n", velkost);
    for (int square = velkost; square >= 1; square -= 2) {
        for (int riadok = 1; riadok <= square; riadok++) {
            for (int space = 0; space <= (velkost-square)/2; space++)
            {
                printf(" ");
            }
            
            for (int stlpec = 1; stlpec <= square; stlpec++) {
                if (riadok == 1 || riadok == square)
                {
                    printf("+");
                } else if (stlpec == 1 || stlpec == square)
                {
                    printf("+");
                } else {
                    printf("-");
                } 
            }
            printf("\n");
        }
        printf("\n");
    }
    return 1;
}

int main()
{
    char N, M, V;
    printf("Zadaj hodnotu N: ");
    scanf(" %c", &N);
    printf("Zadaj hodnotu M: ");
    scanf(" %c", &M);
    printf("Zadaj znak ('M' pre maly znak, 'V' pre velky znak): ");
    scanf(" %c", &V);

    int nacitanyZnak = NacitajZnakPismeno(N, M, V);
    if (nacitanyZnak != 0)
    {
        printf("Nacitanie prebehlo uspesne, z intervalu <%c,%c> vyberam %s znak: %c.\n", N, M, (V == 'M') ? "maly" : "velky", nacitanyZnak);
    } else {
        printf("Neuspesne nacitanie!\n");
    }

    int velkost;
    printf("Zadaj velkost pre tabulku ZC: ");
    scanf("%d", &velkost);
    int uspesnostZC = VykreslenieZC(velkost);
    if (uspesnostZC != 0) {
        printf("Vykreslenie prebehlo uspesne.\n");
    } else {
        printf("Neuspesne vykreslenie tabulky!\n");
    }
    
    return 0;
}
