#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct student
{
    int roll;
    char name[50];
    int attendance[10];
    char date[10][20];
};

struct student s[100];

int count = 0;
int days = 0;

void saveToFile()
{
    FILE *fp = fopen("data.txt", "w");

    if (fp == NULL)
    {
        printf("Error saving file!\n");
        return;
    }

    fprintf(fp, "%d %d\n", count, days);

    for (int i = 0; i < count; i++)
    {
        fprintf(fp, "%d %s\n", s[i].roll, s[i].name);

        for (int j = 0; j < days; j++)
        {
            fprintf(fp, "%s %d\n",
                    s[i].date[j],
                    s[i].attendance[j]);
        }
    }

    fclose(fp);
}

void loadFromFile()
{
    FILE *fp = fopen("data.txt", "r");

    if (fp == NULL)
    {
        return;
    }

    fscanf(fp, "%d %d", &count, &days);

    for (int i = 0; i < count; i++)
    {
        fscanf(fp, "%d %s", &s[i].roll, s[i].name);

        for (int j = 0; j < days; j++)
        {
            fscanf(fp, "%s %d",
                   s[i].date[j],
                   &s[i].attendance[j]);
        }
    }

    fclose(fp);
}

void addStudent()
{
    printf("Enter Roll No: ");
    scanf("%d", &s[count].roll);

    printf("Enter Name: ");
    scanf("%s", s[count].name);

    printf("Student Added Successfully!\n");

    count++;

    saveToFile();
}

void markAttendance()
{
    if (count == 0)
    {
        printf("No students available!\n");
        return;
    }

    if (days >= 10)
    {
        printf("Maximum attendance days reached!\n");
        return;
    }

    char today[20];

    printf("Enter date (DD/MM/YYYY): ");
    scanf("%s", today);

    printf("\nMarking attendance for %s\n", today);

    for (int i = 0; i < count; i++)
    {
        printf("Is %s present? (1=Yes, 0=No): ", s[i].name);

        scanf("%d", &s[i].attendance[days]);

        strcpy(s[i].date[days], today);
    }

    days++;

    saveToFile();
}

void display()
{
    if (count == 0)
    {
        printf("No records available!\n");
        return;
    }

    for (int i = 0; i < count; i++)
    {
        printf("\nRoll: %d", s[i].roll);
        printf("\nName: %s\n", s[i].name);

        for (int j = 0; j < days; j++)
        {
            printf("Date: %s -> Attendance: %d\n",
                   s[i].date[j],
                   s[i].attendance[j]);
        }

        printf("\n");
    }
}

void deleteStudent()
{
    int roll;
    int found = 0;

    printf("Enter Roll No to delete: ");
    scanf("%d", &roll);

    for (int i = 0; i < count; i++)
    {
        if (s[i].roll == roll)
        {
            for (int j = i; j < count - 1; j++)
            {
                s[j] = s[j + 1];
            }

            count--;

            found = 1;

            printf("Student deleted successfully!\n");

            saveToFile();

            break;
        }
    }

    if (!found)
    {
        printf("Student not found!\n");
    }
}

int main()
{
    int choice;

    loadFromFile();

    printf("\n====================================");
    printf("\n   ATTENDANCE MANAGEMENT SYSTEM");
    printf("\n====================================\n");

    printf("\nProject Based Learning (PBL)");
    printf("\nUsing C Programming");
    printf("\n------------------------------------\n");

    while (1)
    {
        printf("\n====================================\n");
        printf("             MAIN MENU\n");
        printf("====================================\n");

        printf("1. Add Student\n");
        printf("2. Mark Attendance\n");
        printf("3. Display Records\n");
        printf("4. Delete Student\n");
        printf("5. Exit\n");

        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input!\n");

            while (getchar() != '\n');

            continue;
        }

        switch (choice)
        {
        case 1:
            addStudent();
            break;

        case 2:
            markAttendance();
            break;

        case 3:
            display();
            break;

        case 4:
            deleteStudent();
            break;

        case 5:
            printf("Exiting program...\n");
            return 0;

        default:
            printf("Invalid choice!\n");
        }
    }
}