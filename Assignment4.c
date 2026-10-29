#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    int regNo;
    char name[50];
    struct Node *next;
} Node;

Node* createHead(void);
Node* createNode(int regNo, const char* name);
void addStudent(Node* head);
void displayList(Node* head);
void countParticipants(Node* head);
void sortList(Node* head);
void reverseList(Node* head);
void addAtPosition(Node* head);
void deleteAtPosition(Node* head);
void freeList(Node* head);

int main(void)
{
    Node* head = createHead();
    int choice, r, c;

    while (1)
    {
        r = scanf("%d", &choice);

        if (r == EOF)
        {
            freeList(head);
            return 0;
        }

        if (r != 1)
        {
            printf("Invalid input! Please enter a number.\n");

            while ((c = getchar()) != '\n' && c != EOF)
                ;

            continue;
        }

        switch (choice)
        {
            case 1:
                addStudent(head);
                break;

            case 2:
                displayList(head);
                break;

            case 3:
                countParticipants(head);
                break;

            case 4:
                sortList(head);
                break;

            case 5:
                reverseList(head);
                break;

            case 6:
                addAtPosition(head);
                break;

            case 7:
                deleteAtPosition(head);
                break;

            case 8:
                freeList(head);
                printf("All student records deleted. Exiting program...\n");
                return 0;

            default:
                printf("Invalid choice! Please select between 1 and 8.\n");
        }
    }
}

Node* createHead(void)
{
    Node* head = malloc(sizeof(Node));

    if (head == NULL)
        exit(1);

    head->next = NULL;
    return head;
}

Node* createNode(int regNo, const char* name)
{
    Node* newNode = malloc(sizeof(Node));

    if (newNode == NULL)
        exit(1);

    newNode->regNo = regNo;
    strncpy(newNode->name, name, 49);
    newNode->name[49] = '\0';
    newNode->next = NULL;

    return newNode;
}

/* Add students at the end */
void addStudent(Node* head)
{
    Node* temp = head;
    Node* newNode;
    int regNo, ch = 1;
    char name[50];

    while (temp->next != NULL)
        temp = temp->next;

    while (ch == 1)
    {
        if (scanf("%d", &regNo) != 1)
            break;

        if (scanf(" %49[^\n]", name) != 1)
            break;

        newNode = createNode(regNo, name);
        temp->next = newNode;
        temp = newNode;

        printf("Student added successfully.\n");

        if (scanf("%d", &ch) != 1)
            ch = 0;
    }
}

void displayList(Node* head)
{
    Node* temp = head->next;

    if (temp == NULL)
    {
        printf("No students registered.\n");
        return;
    }

    printf("\n--- Registered Students ---\n");
    printf("%-15s %-30s\n", "Reg No", "Name");
    printf("--------------------------------------------\n");

    while (temp != NULL)
    {
        printf("%-15d %-30s\n", temp->regNo, temp->name);
        temp = temp->next;
    }
}

void countParticipants(Node* head)
{
    Node* temp = head->next;
    int count = 0;

    while (temp != NULL)
    {
        count++;
        temp = temp->next;
    }

    printf("Total registered students: %d\n", count);
}

/* Sort by registration number using bubble sort */
void sortList(Node* head)
{
    Node* temp;
    int swapped, tempReg;
    char tempName[50];

    if (head->next == NULL || head->next->next == NULL)
    {
        printf("List sorted successfully (or already contains 0 or 1 item).\n");
        return;
    }

    do
    {
        swapped = 0;
        temp = head->next;

        while (temp->next != NULL)
        {
            if (temp->regNo > temp->next->regNo)
            {
                tempReg = temp->regNo;
                temp->regNo = temp->next->regNo;
                temp->next->regNo = tempReg;

                strcpy(tempName, temp->name);
                strcpy(temp->name, temp->next->name);
                strcpy(temp->next->name, tempName);

                swapped = 1;
            }

            temp = temp->next;
        }
    } while (swapped == 1);

    printf("Students are sorted in ascending order of Registration Number.\n");
}

/* Reverse using pointers */
void reverseList(Node* head)
{
    Node* prev = NULL;
    Node* current = head->next;
    Node* nextNode;

    if (current == NULL)
    {
        printf("No students registered to reverse.\n");
        return;
    }

    while (current != NULL)
    {
        nextNode = current->next;
        current->next = prev;
        prev = current;
        current = nextNode;
    }

    head->next = prev;

    printf("Student records reversed successfully.\n");
}

void addAtPosition(Node* head)
{
    Node* temp = head;
    Node* newNode;
    int pos, regNo, i;
    char name[50];

    if (scanf("%d", &pos) != 1)
        return;

    if (scanf("%d", &regNo) != 1)
        return;

    if (scanf(" %49[^\n]", name) != 1)
        return;

    if (pos < 1)
    {
        printf("Invalid position!\n");
        return;
    }

    for (i = 1; i < pos; i++)
    {
        if (temp->next == NULL)
        {
            printf("Invalid position!\n");
            return;
        }

        temp = temp->next;
    }

    newNode = createNode(regNo, name);
    newNode->next = temp->next;
    temp->next = newNode;

    printf("Student added successfully.\n");
}

void deleteAtPosition(Node* head)
{
    Node* temp = head;
    Node* deleted;
    int pos, i;

    if (head->next == NULL)
    {
        printf("List is empty. No students to remove.\n");
        return;
    }

    if (scanf("%d", &pos) != 1)
        return;

    if (pos < 1)
    {
        printf("Invalid position!\n");
        return;
    }

    for (i = 1; i < pos; i++)
    {
        if (temp->next == NULL)
            break;

        temp = temp->next;
    }

    if (temp->next == NULL)
    {
        printf("Invalid position!\n");
        return;
    }

    deleted = temp->next;
    temp->next = deleted->next;
    free(deleted);

    printf("Student record deleted successfully.\n");
}

void freeList(Node* head)
{
    Node* temp;

    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}