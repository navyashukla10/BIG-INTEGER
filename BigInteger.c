#include <stdio.h>
#include <stdlib.h>
#include "BigInteger.h"

 struct BigInteger {
    int data;
    struct BigInteger *next;
};

 struct BigInteger* Initialize(int element)
 {
    struct  BigInteger *temp;
    temp=(struct BigInteger*)malloc(sizeof(struct BigInteger));
    temp->data=element;
    temp->next=NULL;
    return temp;
 }
 struct BigInteger* add(struct BigInteger* n1, struct BigInteger* n2) {
    struct BigInteger* h = Initialize(0), *itr = h;
    int carry = 0;

    while (n1 || n2) {
        int a = n1 ? n1->data : 0;
        int b = n2 ? n2->data : 0;
        int sum = a + b + carry;

        carry = sum / 10;
        itr->next = Initialize(sum % 10);
        itr = itr->next;

        if (n1){
        n1 = n1->next;}

        if(n2)
        {n2 = n2->next;
        }
    }

    if (carry > 0) {
        itr->next = Initialize(carry);
    }

    return h->next;
}

 struct BigInteger* sub(struct BigInteger* n1, struct BigInteger* n2) {
    struct BigInteger* h = (struct BigInteger*)malloc(sizeof(struct BigInteger));
    struct BigInteger* itr = h;
    int borrow = 0;

    while (n1 || n2) {
        int a = n1 ? n1->data : 0;
        int b = n2 ? n2->data : 0;
        int diff = a - b - borrow;

        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        itr->next = (struct BigInteger*)malloc(sizeof(struct BigInteger));
        itr->next->data = diff;
        itr->next->next = NULL;
        itr = itr->next;

        if (n1) n1 = n1->next;
        if (n2) n2 = n2->next;
    }

    struct BigInteger* res = h->next;
    free(h);
    return res;
}

struct BigInteger* mul(struct BigInteger* n1, struct BigInteger* n2) {
    struct BigInteger* res = Initialize(0);

    while (n1) {
        struct BigInteger* itr = res;
        int carry = 0;
        struct BigInteger* n2_copy = n2;

        while (n2_copy || carry) {
            int a = n1->data;
            int b = n2_copy ? n2_copy->data : 0;
            int product = a * b + carry;

            if (itr->next) {
                product += itr->next->data;
                itr->next->data = product % 10;
            } else {
                itr->next = Initialize(product % 10);
            }

            carry = product/10;

            if (n2_copy) n2_copy = n2_copy->next;
            if (!itr->next) {
                itr->next = Initialize(0);
            }

            itr = itr->next;
        }

        n1 = n1->next;
        res = add(res, Initialize(0));
    }

    return res;
}
 struct BigInteger* div1(struct BigInteger* dividend, struct BigInteger* divisor) {
    if (divisor == NULL || divisor->data== 0) {
        printf("Error");
        return NULL;
    }

    struct BigInteger* res = Initialize(0);
    struct BigInteger* itr = res;
    struct BigInteger* temp;

    while (dividend != NULL) {
        int quotient = 0;
        while (dividend != NULL && dividend>= divisor) {
            dividend = sub(dividend, divisor);
            quotient++;
        }

        itr->data = quotient;
        if (dividend != NULL) {
            temp = Initialize(0);
            itr->next = temp;
            itr = itr->next;
        }
    }

    return res;
}
void disp(struct BigInteger* head) {
    struct BigInteger *prev=NULL, *curr= head, *next=NULL;
    while (curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
        head = prev;
        while (head != NULL) {
        printf("%d", head->data);
        head = head->next;
    }

    printf("\n");
}

