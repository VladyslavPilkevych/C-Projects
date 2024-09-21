#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// I'm not sure if I need this feature, but other compilers (except VS Code) have asked me to remove the strrev method. I found this solution on the Internet at the first link: -->  https://stackoverflow.com/questions/8534274/is-the-strrev-function-not-available-in-linux
char *strrev(char *str)
{
    char *p1, *p2;

    if (!str || !*str)
        return str;
    for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
    {
        *p1 ^= *p2;
        *p2 ^= *p1;
        *p1 ^= *p2;
    }
    return str;
}

// As an example, I used this site to write the following function size_t countLines() -->   https://www.cyberforum.ru/c-beginners/thread397516.html
size_t countLines(const char *filePath)
{
    size_t linesQuantity = 0u;
    FILE *fp;
    if ((fp = fopen(filePath, "r")) == NULL)
        return 0u;
    while (!feof(fp))
    {
        fscanf(fp, "%*[^\n]%*c");
        linesQuantity++;
    }
    fclose(fp);
    return linesQuantity;
}

// I also partially found this function on the Internet, and after reading the explanation and some manipulations, I ideally understood the principle of its operation and inserted it into my project. -->  https://metanit.com/cpp/c/7.4.php
char *readFile(char *studentStringInfo, int studentCount, const char *filePath)
{
    FILE *fp;
    fp = fopen(filePath, "r");
    if (fp == NULL)
    {
        perror("Error occured while opening file");
        return 0;
    }
    int line = 0;
    while (fgets(studentStringInfo, 200, fp))
    {
        line++;
        if (line == studentCount)
            break;
    }
    fclose(fp);
    return studentStringInfo;
}

typedef struct
{
    int year;
    int month;
    int day;
} birthDate;
typedef struct
{
    char *name;
    birthDate birthday;
    char *birthData;
    char *sex;
    char *origin;
    float marks[6];
    float bestTest;
    int bestTestIndex;
    float worstTest;
    float avarageGrade;
} studentStruct;

birthDate parseBirthDate(char *birthData)
{
    int year, month, day, counter = 0;
    char *parseDate = strtok(birthData, "/");
    while (parseDate != NULL)
    {
        switch (counter)
        {
        case 0:
            year = atoi(parseDate);
            break;
        case 1:
            month = atoi(parseDate);
            break;
        case 2:
            day = atoi(parseDate);
            break;
        default:
            break;
        }
        counter++;
        parseDate = strtok(NULL, "/");
    }
    birthDate studentBirthDate = {year, month, day};
    return studentBirthDate;
}

studentStruct createStruct(int studentIndex, const char *filePath)
{
    int linesQuantity = countLines(filePath);
    char *studentString;
    studentStruct studentData;
    char studentStringInfo[200];
    for (int i = 1; i <= linesQuantity; i++)
    {
        studentString = readFile(studentStringInfo, i, filePath);
        char *parseDate[10];
        memset(parseDate, 0, 10);
        int year, month, day, separationCount = 0;
        char *parseString = strtok(studentString, ";");
        while (parseString != NULL)
        {
            switch (separationCount)
            {
            case 0:
                studentData.name = parseString;
                break;
            case 1:
                if (*parseString == 'm')
                {
                    studentData.sex = "muz";
                }
                else if (*parseString == 'f')
                {
                    studentData.sex = "zena";
                }
                break;
            case 2:
                studentData.birthData = parseString;
                break;
            case 3:
                studentData.origin = parseString;
                break;
            default:
                studentData.marks[separationCount - 4] = atof(parseString);
                break;
            }
            separationCount++;
            parseString = strtok(NULL, ";");
        }
        if (i == studentIndex)
            break;
    }
    studentData.birthday = parseBirthDate(studentData.birthData);
    float arr[6];
    for (int k = 0; k < 6; k++)
    {
        arr[k] = studentData.marks[k];
    }
    int cisloNajlepsehoTestu = 0;
    for (int n = 1; n < 6; ++n)
    {
        if (arr[0] < arr[n])
        {
            arr[0] = arr[n];
            cisloNajlepsehoTestu = n;
        }
    }
    studentData.bestTest = arr[0];
    studentData.bestTestIndex = cisloNajlepsehoTestu + 1;
    for (int n = 1; n < 6; ++n)
    {
        if (arr[0] > arr[n])
        {
            arr[0] = arr[n];
        }
    }
    studentData.worstTest = arr[0];
    studentData.avarageGrade = (studentData.marks[0] + studentData.marks[1] + studentData.marks[2] + studentData.marks[3] + studentData.marks[4] + studentData.marks[5]) / 6;
    return studentData;
}

int sum(FILE *fileStudents, const char *filePath)
{
    int linesQuantity = countLines(filePath);
    studentStruct studentData;
    for (int i = 1; i <= linesQuantity; i++)
    {
        studentData = createStruct(i, filePath);
        printf("\n\n%s, nar. %d, %s, Kraj: %s\nVysledky testov:%.2f;%.2f;%.2f;%.2f;%.2f;%.2f", studentData.name, studentData.birthday.year, studentData.sex, studentData.origin, studentData.marks[0], studentData.marks[1], studentData.marks[2], studentData.marks[3], studentData.marks[4], studentData.marks[5]);
    }
    return 0;
}

int who(FILE *fileStudents, const char *filePath)
{
    int linesQuantity = countLines(filePath);
    char userName[20];
    studentStruct studentData;
    printf("Write user name: ");
    scanf("%s", &userName);
    int userNameLength = strlen(userName);
    strrev(userName);

    int numberOfTrue = 0;
    int exactUser = 0;

    for (int i = 1; i <= linesQuantity; i++)
    {
        studentData = createStruct(i, filePath);
        char *reverseUserName = studentData.name;
        strrev(reverseUserName);
        for (int n = 0; n < userNameLength; n++)
        {
            if (userName[n] == reverseUserName[n])
            {
                numberOfTrue++;
            }
            else
            {
                numberOfTrue = 0;
                break;
            }
            if (numberOfTrue == userNameLength)
            {
                exactUser = i;
                break;
            }
        }
    }
    if (exactUser != 0)
    {
        studentData = createStruct(exactUser, filePath);
        printf("\n%s\nnar. %d, %s\nKraj: %s\n\nVysledky testov: %.2f,%.2f,%.2f,%.2f,%.2f,%.2f\nNajlepsi test: %.2f\nNajhorsi test: %.2f\nPriemerny test: %.2f", studentData.name, studentData.birthday.year, studentData.sex, studentData.origin, studentData.marks[0], studentData.marks[1], studentData.marks[2], studentData.marks[3], studentData.marks[4], studentData.marks[5], studentData.bestTest, studentData.worstTest, studentData.avarageGrade);
    }
    else
    {
        printf("Sorry, we don't have student with this surname, please call the function 'w' and try again.");
    }

    return 0;
}

int best(FILE *fileStudents, const char *filePath)
{
    int linesQuantity = countLines(filePath);
    studentStruct studentData;
    float najlepsiTest = 0;
    int cisloNajlepsehoTestu, id;
    for (int i = 1; i <= linesQuantity; i++)
    {
        studentData = createStruct(i, filePath);
        if (najlepsiTest < studentData.bestTest)
        {
            najlepsiTest = studentData.bestTest;
            id = i;
        }
    }
    studentStruct bestStudentStruct = createStruct(id, filePath);
    printf("Najlepsi test: %.2f\nStudent: %s\nCislo testu: %d", bestStudentStruct.bestTest, bestStudentStruct.name, bestStudentStruct.bestTestIndex);
    return 0;
}

int gender(FILE *fileStudents, const char *filePath)
{
    int linesQuantity = countLines(filePath);
    studentStruct studentData;
    float najlepsiTest = 0;
    char *studentName, *sex, studentSex;
    int cisloNajlepsehoTestu, id;
    printf("Write sex: ");
    scanf("%s", &studentSex);
    while (!(studentSex == 'm' || studentSex == 'f'))
    {
        printf("-------------------------------\nThere are only two genders, write please one 'm', if student is male, or write 'f', if student is female:\n");
        printf("Write student sex (m/f): ");
        scanf("%s", &studentSex);
    }
    if (studentSex == 'm')
    {
        sex = "muz";
    }
    else if (studentSex == 'f')
    {
        sex = "zena";
    }
    for (int i = 1; i <= linesQuantity; i++)
    {
        studentData = createStruct(i, filePath);
        if (sex == studentData.sex && najlepsiTest < studentData.bestTest)
        {
            najlepsiTest = studentData.bestTest;
            id = i;
        }
    }
    studentStruct bestStudentStruct = createStruct(id, filePath);
    printf("\nNajlepsi test: %.2f\nStudent: %s\nCislo testu: %d", bestStudentStruct.bestTest, bestStudentStruct.name, bestStudentStruct.bestTestIndex);
    return 0;
}

int over(FILE *fileStudents, const char *filePath)
{
    int linesQuantity = countLines(filePath);
    studentStruct studentData;
    float overNumber;
    printf("Write min: ");
    scanf("%f", &overNumber);
    for (int i = 1; i <= linesQuantity; i++)
    {
        studentData = createStruct(i, filePath);
        if (studentData.bestTest > overNumber)
        {
            int counter = 0;
            float testy[6];
            for (int j = 0; j < 6; j++)
            {
                if (studentData.marks[j] > overNumber)
                {
                    counter++;
                }
            }
            if (counter == 1)
            {
                printf("\n%s - 1 test", studentData.name, counter);
            }
            else
            {
                printf("\n%s - %d testy", studentData.name, counter);
            }
            for (int j = 0; j < 6; j++)
            {
                if (studentData.marks[j] > overNumber)
                {
                    printf(", %d (%.2f)", j + 1, studentData.marks[j]);
                }
            }
        }
    }
    return 0;
}

int region(FILE *fileStudents, const char *filePath)
{
    int linesQuantity = countLines(filePath);
    studentStruct studentData;
    float najlepsiTest = 0;
    int cisloNajlepsehoTestu, id, studentCounterInEachRegion = 0;
    char *userName, *kraj[8] = {"bratislavsky", "trnavsky", "trenciansky", "nitriansky", "zilinsky", "banskobystricky", "presovsky", "kosicky"};
    for (int j = 0; j < 8; j++)
    {
        for (int i = 1; i <= linesQuantity; i++)
        {
            studentData = createStruct(i, filePath);
            if (!strcmp(studentData.origin, kraj[j]) && najlepsiTest < studentData.bestTest)
            {
                najlepsiTest = studentData.bestTest;
                id = i;
                studentCounterInEachRegion++;
            }
        }
        if (studentCounterInEachRegion != 0)
        {
            studentStruct bestStudentStruct = createStruct(id, filePath);
            printf("\nKraj: %s\nNajlepsi test: %.2f\nStudent: %s\nCislo testu: %d\n", bestStudentStruct.origin, bestStudentStruct.bestTest, bestStudentStruct.name, bestStudentStruct.bestTestIndex);
        }

        studentCounterInEachRegion = 0;
        najlepsiTest = 0;
    }
    return 0;
}

int year(FILE *fileStudents, const char *filePath)
{
    int linesQuantity = countLines(filePath);
    studentStruct studentData;
    float najlepsiTest = 0;
    int studentBirthYear, cisloNajlepsehoTestu, year, id;
    char *studentName, *sex;
    printf("Write year: ");
    scanf("%d", &studentBirthYear);
    for (int i = 1; i <= linesQuantity; i++)
    {
        studentData = createStruct(i, filePath);
        if (studentBirthYear < studentData.birthday.year && najlepsiTest < studentData.bestTest)
        {
            year = studentData.birthday.year;
            id = i;
        }
    }
    studentStruct bestStudentStruct = createStruct(id, filePath);

    printf("\n%s\nnar. %d\nNajlepsi test: %.2f\nCislo testu: %d", bestStudentStruct.name, bestStudentStruct.birthday.day, bestStudentStruct.bestTest, bestStudentStruct.bestTestIndex);
    return 0;
}

int average(FILE *fileStudents, const char *filePath)
{
    int linesQuantity = countLines(filePath);
    studentStruct studentData;
    float avarageTest = 0;
    char *studentNameQWEPOI = "";
    int id;
    for (int i = 1; i <= linesQuantity; i++)
    {
        studentData = createStruct(i, filePath);
        printf("\n%s - %.2f", studentData.name, studentData.avarageGrade);
        if (avarageTest < studentData.avarageGrade)
        {
            avarageTest = studentData.avarageGrade;
            id = i;
        }
    }
    studentStruct bestStudentStruct = createStruct(id, filePath);

    printf("\n\nNajlepsie:\n%s - %.2f", bestStudentStruct.name, bestStudentStruct.avarageGrade);
    return 0;
}

int newstudent(FILE *fileStudents, const char *filePath)
{
    FILE *fp;
    fp = fopen(filePath, "a");
    char name[30], birthData[10], origin[15], sex[5], marks[45], grades[45];
    birthDate studentBirthDate;
    printf("Write new student name (FirstName SecondName): ");
    scanf(" %[^\n]", name);
    fprintf(fp, "\n%s;", name);
    printf("Write new student sex (m/f): ");
    scanf(" %s", sex);
    while (!(!strcmp(sex, "m") || !strcmp(sex, "f")))
    {
        printf("-------------------------------\nThere are only two genders, write please one 'm', if student is male, or write 'f', if student is female:\n");
        printf("Write new student sex (m/f): ");
        scanf(" %s", sex);
    }
    fprintf(fp, "%s;", sex);
    printf("Write new student birthay (yyyy/mm/dd): ");
    scanf(" %s", birthData);
    studentBirthDate = parseBirthDate(birthData);
    while (studentBirthDate.year > 2023 || studentBirthDate.year < 1000 || studentBirthDate.month > 12 || studentBirthDate.month <= 0 || studentBirthDate.day >= 32 || studentBirthDate.month <= 0)
    {
        printf("-------------------------------\nPlease, format student birthday '2023-1000/13-0/32-0' (yyyy/mm/dd)\n");
        printf("Write new student birthay (yyyy/mm/dd): ");
        scanf(" %s", birthData);
        studentBirthDate = parseBirthDate(birthData);
    }
    fprintf(fp, "%d/%d/%d;", studentBirthDate.year, studentBirthDate.month, studentBirthDate.day);
    printf("Write new student origin: ");
    scanf(" %s", origin);
    while (strcmp(origin, "bratislavsky") && strcmp(origin, "trnavsky") && strcmp(origin, "trenciansky") && strcmp(origin, "nitriansky") && strcmp(origin, "zilinsky") && strcmp(origin, "banskobystricky") && strcmp(origin, "presovsky") && strcmp(origin, "kosicky"))
    {
        printf("-------------------------------\nWrite one of each regions: : 'bratislavsky', 'trnavsky', 'trenciansky', 'nitriansky', 'zilinsky', 'banskobystricky', 'presovsky', 'kosicky'\n");
        printf("Write new student origin: ");
        scanf(" %s", origin);
    }
    fprintf(fp, "%s", origin);
    printf("Write new student marks (n;n;n;n;n;n): ");
    scanf(" %s", marks);
    strcpy(grades, marks);
    int boolValue = 0, counters = 0;
    char *parseString = strtok(marks, ";");
    while (parseString != NULL)
    {
        if (0 > atof(parseString) || atof(parseString) > 100)
        {
            boolValue = 1;
        }
        counters++;
        parseString = strtok(NULL, ";");
    }
    while (boolValue || counters != 6)
    {
        printf("\nWrite new student marks (n;n;n;n;n;n): ");
        scanf(" %s", marks);
        memset(grades, 0, strlen(grades));
        strcpy(grades, marks);
        boolValue = 0;
        counters = 0;
        parseString = strtok(marks, ";");
        while (parseString != NULL)
        {
            if (0 > atof(parseString) || atof(parseString) > 100)
            {
                boolValue = 1;
            }
            counters++;
            parseString = strtok(NULL, ";");
        }
    }
    parseString = strtok(grades, ";");
    while (parseString != NULL)
    {
        fprintf(fp, ";%.2f", atof(parseString));
        parseString = strtok(NULL, ";");
    }
    fclose(fp);
    sum(fileStudents, filePath);
    return 0;
}

int delstudent(FILE *fileStudents, const char *filePath)
{
    int linesQuantity = countLines(filePath);
    char userName[20];
    studentStruct studentData;
    printf("Write user name: ");
    scanf("%s", &userName);
    int userNameLength = strlen(userName);
    strrev(userName);

    int numberOfTrue = 0;
    int exactUser = 0;

    for (int i = 1; i <= linesQuantity; i++)
    {
        studentData = createStruct(i, filePath);
        char *reverseUserName = studentData.name;
        strrev(reverseUserName);
        for (int n = 0; n < userNameLength; n++)
        {
            if (userName[n] == reverseUserName[n])
            {
                numberOfTrue++;
            }
            else
            {
                numberOfTrue = 0;
                break;
            }
            if (numberOfTrue == userNameLength)
            {
                exactUser = i;
                break;
            }
        }
    }
    if (exactUser != 0)
    {
        FILE *myFile, *bufferFile;
        const char *bufferFilePath = "./bufferFile.csv";
        myFile = fopen(filePath, "r");
        bufferFile = fopen(bufferFilePath, "w");

        int byt;

        byt = fgetc(myFile);

        while (byt != EOF)
        {
            fprintf(bufferFile, "%c", byt);
            byt = fgetc(myFile);
        }

        fclose(bufferFile);
        fclose(myFile);

        remove(filePath);

        myFile = fopen(filePath, "w");
        bufferFile = fopen(bufferFilePath, "r");

        char studentInfo[200];

        for (int i = 1; i <= linesQuantity; i++)
        {
            if (i != exactUser)
            {
                byt = fgetc(bufferFile);
                while ((byt >= 48 && byt <= 57) || (byt >= 65 && byt <= 90) || (byt >= 97 && byt <= 122) || (char)byt == '.' || (char)byt == ' ' || (char)byt == ';' || (char)byt == '/' || (char)byt == '-')
                {
                    fprintf(myFile, "%c", byt);
                    byt = fgetc(bufferFile);
                }
                if (i != linesQuantity && !(i == linesQuantity - 1 && exactUser == linesQuantity))
                    fprintf(myFile, "\n");
            }
            else
            {
                byt = fgetc(bufferFile);
                while ((byt >= 48 && byt <= 57) || (byt >= 65 && byt <= 90) || (byt >= 97 && byt <= 122) || (char)byt == '.' || (char)byt == ' ' || (char)byt == ';' || (char)byt == '/' || (char)byt == '-')
                {
                    byt = fgetc(bufferFile);
                }
            }
        }

        fclose(bufferFile);
        fclose(myFile);

        remove(bufferFilePath);

        strrev(userName);
        printf("\nStudent s menom '%s' bol vymazany.", userName);
    }
    return 0;
}

int getFunctionName(char *text)
{
    const char *filePath = "./studenti.csv";
    FILE *fileStudents;
    if ((fileStudents = fopen(filePath, "r")) == NULL)
    {
        perror("Error occured while opening file");
        return 0;
    }
    char functionName;
    printf("%s", text);
    scanf(" %c", &functionName);
    studentStruct studentData;
    switch (functionName)
    {
    case 's':
        sum(fileStudents, filePath);
        getFunctionName("\n\n-------------------------------------------------\nWrite function letter: ");
        break;
    case 'w':
        who(fileStudents, filePath);
        getFunctionName("\n\n-------------------------------------------------\nWrite function letter: ");
        break;
    case 'b':
        best(fileStudents, filePath);
        getFunctionName("\n\n-------------------------------------------------\nWrite function letter: ");
        break;
    case 'g':
        gender(fileStudents, filePath);
        getFunctionName("\n\n-------------------------------------------------\nWrite function letter: ");
        break;
    case 'r':
        region(fileStudents, filePath);
        getFunctionName("\n\n-------------------------------------------------\nWrite function letter: ");
        break;
    case 'y':
        year(fileStudents, filePath);
        getFunctionName("\n\n-------------------------------------------------\nWrite function letter: ");
        break;
    case 'a':
        average(fileStudents, filePath);
        getFunctionName("\n\n-------------------------------------------------\nWrite function letter: ");
        break;
    case 'o':
        over(fileStudents, filePath);
        getFunctionName("\n\n-------------------------------------------------\nWrite function letter: ");
        break;
    case 'n':
        newstudent(fileStudents, filePath);
        getFunctionName("\n\n-------------------------------------------------\nWrite function letter: ");
        break;
    case 'd':
        delstudent(fileStudents, filePath);
        getFunctionName("\n\n-------------------------------------------------\nWrite function letter: ");
        break;
    case 'x':
        printf("\n\n\n------------==============______________End______________==============------------\n\n\n\n");
        break;
    default:
        printf("\n\n-------------------------------------------------\nThe letter is incorrect, try one more time:");
        getFunctionName("\nWrite function letter: ");
        break;
    }
    return 0;
}

int main()
{
    // I will call it feature
    getFunctionName("\nWrite function letter\n(for fast usage you can write couple of commands together, for example 'sba' for sum() && best() && avarage())\n========================: ");
    return 0;
}
