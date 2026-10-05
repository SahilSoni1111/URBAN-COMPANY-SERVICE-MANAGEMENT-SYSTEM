#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "service.h"
#include "common.h"
ServiceNode* CreateService(int id, const char* name, float price){
    ServiceNode* Snode=(ServiceNode*)malloc(sizeof(ServiceNode));
    if(Snode!=NULL){
        Snode->serviceId=id;
        Snode->basePrice=price;
        strcpy(Snode->serviceName, name);
        Snode->next=NULL;
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