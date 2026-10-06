#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "customer.h"
#include "common.h"
CustomerNode* CreateCustomer(int id, const char* name, int pcode, const char* phone){
    CustomerNode*Cnode=NULL;
    if(id<=0){
        printf("Invalid Customer ID\n");
    }
    else{
        Cnode=(CustomerNode*)malloc(sizeof(CustomerNode));
        if(Cnode!=NULL){
            Cnode->customerId=id;
            Cnode->pincode=pcode;
            strcpy(Cnode->name, name);
            strcpy(Cnode->phone, phone);
            Cnode->next=NULL;
        }
    }
    return Cnode;
}
CustomerNode* InsertCustomer(CustomerNode* head, CustomerNode*Cnode){
    CustomerNode*temp=head;
    int dublicate=0;
    if(head==NULL){
        head=Cnode;
    }
    else if(head->customerId>Cnode->customerId){
        Cnode->next=head;
        head=Cnode;
    }
    else{
        CustomerNode*prev=NULL;
        while(temp!=NULL && temp->customerId<Cnode->customerId){
            prev=temp;
            temp=temp->next;
        }
        if(temp!=NULL && temp->customerId==Cnode->customerId){
            dublicate=1;
        }
        else{
            prev->next=Cnode;
            Cnode->next=temp;
        }
        if(dublicate==1){
            printf("Customer ID already exists.\n");
            free(Cnode);
        }
    }
    return head;
}
CustomerNode* FindCustomer(CustomerNode*head, int id){
    CustomerNode*temp=head, *retval=NULL;
    Bool found=FALSE;
    while(temp!=NULL && !found){
        if(temp->customerId==id){
            retval=temp;
            found=TRUE;
        }
        temp=temp->next;
    }
    return retval;
}
CustomerNode* RegisterCustomer(CustomerNode*head){
    int id,pcode;
    char name[NAME_SIZE],phone[PHONE_SIZE];
    CustomerNode*Cnode;

    printf("Enter Customer ID: ");
    scanf("%d",&id);

    printf("Enter Customer Name: ");
    scanf(" %[^\n]",name);

    printf("Enter Pincode: ");
    scanf("%d",&pcode);

    printf("Enter Contact Number: ");
    scanf("%s",phone);

    Cnode=CreateCustomer(id,name,pcode,phone);

    if(Cnode!=NULL){
        head=InsertCustomer(head,Cnode);
        printf("Customer added successfully.\n");
    }

    return head;
}