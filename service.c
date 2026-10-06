#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "service.h"
#include "common.h"
ServiceNode* CreateService(int id, const char* name, float price){
    ServiceNode*Snode=NULL;
    if(id<=0){
        printf("Invalid Service ID");
    }
    else{
        Snode=(ServiceNode*)malloc(sizeof(ServiceNode));
        if(Snode!=NULL){
            Snode->serviceId=id;
            Snode->basePrice=price;
            strcpy(Snode->serviceName, name);
            Snode->next=NULL;
        }
    }
    return Snode;
}
ServiceNode* InsertService(ServiceNode* head, ServiceNode* Snode){
    ServiceNode*temp=head;
    if(head==NULL){
        head=Snode;
    }
    else if(head->serviceId>Snode->serviceId){
        Snode->next=head;
        head=Snode;
    }
    else{
        int dublicate=0;
        ServiceNode*prev=NULL;
        while(temp!=NULL && temp->serviceId<Snode->serviceId){
            prev=temp;
            temp=temp->next;
        }
        if(temp!=NULL && temp->serviceId==Snode->serviceId){
            dublicate=1;
        }
        else{
            prev->next=Snode;
            Snode->next=temp;
        }
        if(dublicate==1){
            printf("Service ID already exists.\n");
            free(Snode);
        }
    }
    return head;
}
ServiceNode* FindService(ServiceNode*head,int id){
    ServiceNode*temp=head, *retval=NULL;
    Bool found=FALSE;

    while(temp!=NULL && !found){
        if(temp->serviceId==id){
            retval=temp;
            found=TRUE;
        }
        temp=temp->next;
    }

    return retval;
}
void DisplayService(ServiceNode*head){
    ServiceNode*temp=head;
    if(head==NULL){
        printf("------------------------------------------\n");
        printf("No Service Available\n");
        printf("-------------------------------------------\n");
    }
    else{
        printf("-------------------------------------\n"); 
        printf("\nAvailable Services:\n");
        printf("-------------------------------------\n");
        while(temp!=NULL){
            printf("Service ID: %d\n",temp->serviceId);
            printf("Service Name: %s\n",temp->serviceName);
            printf("Base Price: %f\n",temp->basePrice);
            printf("--------------------------------------\n");
            temp=temp->next;
        }
    }
}
ServiceNode* InputService(ServiceNode*head){
    int id;
    float price;
    char name[NAME_SIZE];
    ServiceNode*Snode;
    printf("Enter Service ID: ");
    scanf("%d",&id);

    printf("Enter Service Name: ");
    scanf(" %[^\n]",name);

    printf("Enter Base Price: ");
    scanf("%f",&price);

    Snode=CreateService(id,name,price);

    if(Snode!=NULL){
        head=InsertService(head,Snode);
        printf("Service added successfully.\n");
    }

    return head;
}