#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct PaƟent
{
    int paƟent_id;
    char name[100];
    int age;
    char gender[10];
    char condiƟon[100];
    struct PaƟent *next;
};
struct PaƟent *createPaƟent(int paƟent_id, char name[], int age, char gender[], char condiƟon[])
{
    struct PaƟent *newPaƟent = (struct PaƟent *)malloc(sizeof(struct PaƟent));
    newPaƟent->paƟent_id = paƟent_id;
    strcpy(newPaƟent->name, name);
    newPaƟent->age = age;
    strcpy(newPaƟent->gender, gender);
    strcpy(newPaƟent->condiƟon, condiƟon);
    newPaƟent->next = NULL;
    return newPaƟent;
}
void addPaƟent(struct PaƟent **head, int paƟent_id, char name[], int age, char gender[], char condiƟon[])
{
    struct PaƟent *newPaƟent = createPaƟent(paƟent_id, name, age, gender, condiƟon);
    if (*head == NULL)
    {
        *head = newPaƟent;
    }
    else
    {
        struct PaƟent *current = *head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newPaƟent;
    }
}
struct PaƟent *searchPaƟent(struct PaƟent *head, int paƟent_id)
{
    struct PaƟent *current = head;
    while (current != NULL)
    {
        if (current->paƟent_id == paƟent_id)
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}
void removePaƟent(struct PaƟent **head, int paƟent_id)
{
    if (*head == NULL)
    {
        return;
    }
    struct PaƟent *current = *head;
    if (current->paƟent_id == paƟent_id)
    {
        *head = current->next;
        free(current);
        return;
    }
    struct PaƟent *prev = NULL;
    while (current != NULL)
    {
        if (current->paƟent_id == paƟent_id)
        {
            prev->next = current->next;
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}
void displayPaƟents(struct PaƟent *head)
{
    struct PaƟent *current = head;
    while (current != NULL)
    {
        prinƞ("PaƟent ID: %d\n", current->paƟent_id);
        prinƞ("Name: %s\n", current->name);
        prinƞ("Age: %d\n", current->age);
        prinƞ("Gender: %s\n", current->gender);
        prinƞ("Medical CondiƟon: %s\n", current->condiƟon);
        prinƞ("--------------------\n");
        current = current->next;
    }
}
void savePaƟentsToFile(struct PaƟent *head)
{
    FILE *file = fopen("paƟents.txt", "w");
    if (file == NULL)
    {
        prinƞ("Error opening file.\n");
        return;
    }
    struct PaƟent *current = head;
    while (current != NULL)
    {
        fprinƞ(file, "%d;%s;%d;%s;%s\n", current->paƟent_id, current->name, current->age, current - > gender, current->condiƟon);
        current = current->next;
    }
    fclose(file);
}
struct PaƟent *loadPaƟentsFromFile()
{
    FILE *file = fopen("paƟents.txt", "r");
    if (file == NULL)
    {
        prinƞ("Error opening file.\n");
        return NULL;
    }
    struct PaƟent *head = NULL;
    char line[256];
    while (fgets(line, sizeof(line), file))
    {
        int paƟent_id, age;
        char name[100], gender[10], condiƟon[100];
        sscanf(line, "%d;%[^;];%d;%[^;];%[^\n]", &paƟent_id, name, &age, gender, condiƟon);
        addPaƟent(&head, paƟent_id, name, age, gender, condiƟon);
    }
    fclose(file);
    return head;
}
void freePaƟents(struct PaƟent *head)
{
    struct PaƟent *current = head;
    while (current != NULL)
    {
        struct PaƟent *next = current->next;
        free(current);
        current = next;
    }
}
int main()
{
    struct PaƟent *paƟentList = NULL;
    // Load paƟents from file
    paƟentList = loadPaƟentsFromFile();
    int choice;
    while (1)
    {
        prinƞ("\n--- Hospital Management System ---\n");
        prinƞ("1. Add PaƟent\n");
        prinƞ("2. Search PaƟent\n");
        prinƞ("3. Delete PaƟent\n");
        prinƞ("4. Display PaƟents\n");
        prinƞ("5. Exit\n");
        prinƞ("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
        {
            int paƟent_id, age;
            char name[100], gender[10], condiƟon[100];
            prinƞ("Enter PaƟent ID: ");
            scanf("%d", &paƟent_id);
            prinƞ("Enter Name: ");
            scanf(" %[^\n]s", name);
            prinƞ("Enter Age: ");
            scanf("%d", &age);
            prinƞ("Enter Gender: ");
            scanf(" %[^\n]s", gender);
            prinƞ("Enter Medical CondiƟon: ");
            scanf(" %[^\n]s", condiƟon);
            addPaƟent(&paƟentList, paƟent_id, name, age, gender, condiƟon);
            savePaƟentsToFile(paƟentList);
            prinƞ("PaƟent added successfully.\n");
            break;
        }
        case 2:
        {
            int paƟent_id;
            prinƞ("Enter PaƟent ID to search: ");
            scanf("%d", &paƟent_id);
            struct PaƟent *paƟent = searchPaƟent(paƟentList, paƟent_id);
            if (paƟent != NULL)
            {
                prinƞ("PaƟent found:\n");
                prinƞ("PaƟent ID: %d\n", paƟent->paƟent_id);
                prinƞ("Name: %s\n", paƟent->name);
                prinƞ("Age: %d\n", paƟent->age);
                prinƞ("Gender: %s\n", paƟent->gender);
                prinƞ("Medical CondiƟon: %s\n", paƟent->condiƟon);
            }
            else
            {
                prinƞ("PaƟent not found.\n");
            }
            break;
        }
        case 3:
        {
            int paƟent_id;
            prinƞ("Enter PaƟent ID to delete: ");
            scanf("%d", &paƟent_id);
            removePaƟent(&paƟentList, paƟent_id);
            savePaƟentsToFile(paƟentList);
            prinƞ("PaƟent with ID %d removed.\n", paƟent_id);
            break;
        }
        case 4:
            displayPaƟents(paƟentList);
            break;
        case 5:
            prinƞ("ExiƟng program...\n");
            freePaƟents(paƟentList);
            exit(0);
        default:
            prinƞ("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
