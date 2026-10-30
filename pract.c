
#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
};

struct Node *head = NULL;

struct Node *createNode(int data)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));

    if (newNode == NULL)
    {
        printf("Memory allocation failed\n");
        return NULL;
    }

    newNode->data = data;
    newNode->next = NULL;

    return newNode;
}

void insertBeginning(int data)
{
    struct Node *newNode = createNode(data);

    if (newNode == NULL)
        return;

    newNode->next = head;
    head = newNode;

    printf("Node inserted successfully\n");
}

void insertEnd(int data)
{
    struct Node *newNode = createNode(data);

    if (newNode == NULL)
        return;

    if (head == NULL)
    {
        head = newNode;
    }
    else
    {
        struct Node *temp = head;

        while (temp->next != NULL)
            temp = temp->next;

        temp->next = newNode;
    }

    printf("Node inserted successfully\n");
}

void insertPosition(int data, int position)
{
    if (position < 1)
    {
        printf("Invalid position\n");
        return;
    }

    if (position == 1)
    {
        insertBeginning(data);
        return;
    }

    struct Node *temp = head;
    int i;

    for (i = 1; i < position - 1 && temp != NULL; i++)
        temp = temp->next;

    if (temp == NULL)
    {
        printf("Invalid position\n");
        return;
    }

    struct Node *newNode = createNode(data);

    if (newNode == NULL)
        return;

    newNode->next = temp->next;
    temp->next = newNode;

    printf("Node inserted successfully\n");
}

void deleteBeginning(void)
{
    if (head == NULL)
    {
        printf("List is empty\n");
        return;
    }

    struct Node *temp = head;
    head = head->next;

    free(temp);

    printf("Node deleted successfully\n");
}

void deleteEnd(void)
{
    if (head == NULL)
    {
        printf("List is empty\n");
        return;
    }

    if (head->next == NULL)
    {
        free(head);
        head = NULL;
    }
    else
    {
        struct Node *temp = head;

        while (temp->next->next != NULL)
            temp = temp->next;

        free(temp->next);
        temp->next = NULL;
    }

    printf("Node deleted successfully\n");
}

void deleteKey(int key)
{
    if (head == NULL)
    {
        printf("List is empty\n");
        return;
    }

    struct Node *temp = head;
    struct Node *prev = NULL;

    while (temp != NULL && temp->data != key)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
    {
        printf("Key not found\n");
        return;
    }

    if (prev == NULL)
        head = temp->next;
    else
        prev->next = temp->next;

    free(temp);

    printf("Node deleted successfully\n");
}

void display(void)
{
    if (head == NULL)
    {
        printf("List is empty\n");
        return;
    }

    struct Node *temp = head;

    printf("Linked List: ");

    while (temp != NULL)
    {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }

    printf("NULL\n");
}

void freeList(void)
{
    struct Node *temp;

    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main(void)
{
    int choice, data, position, key;

    while (1)
    {
        printf("\n--- Singly Linked List Menu ---\n");
        printf("1. Insert at beginning\n");
        printf("2. Insert at end\n");
        printf("3. Insert at specific position\n");
        printf("4. Delete from beginning\n");
        printf("5. Delete from end\n");
        printf("6. Delete by key\n");
        printf("7. Display list\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input\n");
            break;
        }

        switch (choice)
        {
            case 1:
                printf("Enter data: ");
                if (scanf("%d", &data) != 1)
                    goto exit_program;
                insertBeginning(data);
                break;

            case 2:
                printf("Enter data: ");
                if (scanf("%d", &data) != 1)
                    goto exit_program;
                insertEnd(data);
                break;

            case 3:
                printf("Enter data: ");
                if (scanf("%d", &data) != 1)
                    goto exit_program;

                printf("Enter position (1-based): ");
                if (scanf("%d", &position) != 1)
                    goto exit_program;

                insertPosition(data, position);
                break;

            case 4:
                deleteBeginning();
                break;

            case 5:
                deleteEnd();
                break;

            case 6:
                printf("Enter key to delete: ");
                if (scanf("%d", &key) != 1)
                    goto exit_program;

                deleteKey(key);
                break;

            case 7:
                display();
                break;

            case 8:
                goto exit_program;

            default:
                printf("Invalid choice\n");
        }
    }

exit_program:
    freeList();
    printf("All allocated nodes freed. Exiting...\n");

    return 0;
}
