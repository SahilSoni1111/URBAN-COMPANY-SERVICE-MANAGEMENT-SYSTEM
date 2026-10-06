#ifndef CUSTOMER_H
#define CUSTOMER_H
#include "common.h"
typedef struct CUSTOMER_NODE{
    int customerId;
    char name[NAME_SIZE];
    int pincode;
    char phone[PHONE_SIZE];

    struct CUSTOMER_NODE* next;
}CustomerNode;
CustomerNode* CreateCustomer(int, const char*, int , const char*);
CustomerNode* InsertCustomer(CustomerNode* head,CustomerNode*Cnode);
CustomerNode* FindCustomer(CustomerNode*head, int id);
CustomerNode* RegisterCustomer();
#endif