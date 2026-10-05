#ifndef CUSTOMER_H
#define CUSTOMER_H
#include "common.h"
typedef struct CUSTOMER_NODE{
    int customerId;
    char name[NAME_SIZE];
    int pincode;
    char phone[PHONE_SIZE];

    struct CUSTOME_NODE* next;
}CustomerNode;

CustomerNode* Create_Customer(int, const char*, int , const char*);
CustomerNode* InsertCustomer(CustomerNode* head,CustomerNode*Cnode);
CustomerNode* FindCustomer(CustomerNode*head, int id);
#endif