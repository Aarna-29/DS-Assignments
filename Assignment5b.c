#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int coef;
    int exp;
    struct node *next;
} pnode;

pnode *new_poly(void) {
    pnode *head = malloc(sizeof(pnode));

    if (head == NULL)
        exit(1);

    head->next = head;

    return head;
}

void insert_term(pnode *head, int coef, int exp) {
    pnode *prev = head;
    pnode *value = head->next;
    pnode *newNode;

    if (coef == 0)
        return;

    while (value != head && value->exp > exp) {
        prev = value;
        value = value->next;
    }

    if (value != head && value->exp == exp) {
        value->coef = value->coef + coef;

        if (value->coef == 0) {
            prev->next = value->next;
            free(value);
        }

        return;
    }

    newNode = malloc(sizeof(pnode));

    if (newNode == NULL)
        exit(1);

    newNode->coef = coef;
    newNode->exp = exp;

    newNode->next = value;
    prev->next = newNode;
}

pnode *read_poly(void) {
    pnode *head = new_poly();
    int choice, coef, exp;

    while (1) {
        if (scanf("%d", &choice) != 1 || choice != 1)
            break;

        if (scanf("%d %d", &coef, &exp) != 2)
            break;

        insert_term(head, coef, exp);
    }

    return head;
}

pnode *poly_add(pnode *h1, pnode *h2) {
    pnode *sum = new_poly();
    pnode *value;

    value = h1->next;

    while (value != h1) {
        insert_term(sum, value->coef, value->exp);
        value = value->next;
    }

    value = h2->next;

    while (value != h2) {
        insert_term(sum, value->coef, value->exp);
        value = value->next;
    }

    return sum;
}

void free_poly(pnode *head) {
    pnode *value = head->next;
    pnode *nextNode;

    while (value != head) {
        nextNode = value->next;
        free(value);
        value = nextNode;
    }

    free(head);
}

void print_poly(pnode *head) {
    pnode *p = head->next;

    if (p == head) {
        printf("0\n");
        return;
    }

    while (p != head) {
        printf("%+dx^%d", p->coef, p->exp);
        p = p->next;

        if (p != head)
            printf(" ");
    }

    printf("\n");
}

int main(void) {
    pnode *p1 = read_poly();
    pnode *p2 = read_poly();
    pnode *sum = poly_add(p1, p2);

    printf("P1 = ");
    print_poly(p1);

    printf("P2 = ");
    print_poly(p2);

    printf("SUM = ");
    print_poly(sum);

    free_poly(p1);
    free_poly(p2);
    free_poly(sum);

    return 0;
}
