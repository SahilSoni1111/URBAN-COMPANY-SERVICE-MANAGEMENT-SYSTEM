#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "request.h"
#include "common.h"

RequestNode* CreateRequest(int id,CustomerNode*customer,ServiceNode*service,ProfessionalNode*professional,const char*date,const char*time){
    RequestNode*Rnode=NULL;
    if(id<=0){
        printf("Invalid Request ID\n");
    }
    else{
        Rnode=(RequestNode*)malloc(sizeof(RequestNode));
        if(Rnode!=NULL){
            Rnode->requestId=id;
            Rnode->customer=customer;
            Rnode->service=service;
            Rnode->professional=professional;
            strcpy(Rnode->date,date);
            strcpy(Rnode->time,time);

            if(professional==NULL){
                Rnode->Rstatus=PENDING;
            }
            else{
                Rnode->Rstatus=ASSIGNED;
            }
            Rnode->next=NULL;
        }
    }
    return Rnode;
}
RequestNode* InsertRequest(RequestNode*head,RequestNode*Rnode){
    RequestNode*temp=head;
    int dublicate=0;
    if(head==NULL){
        head=Rnode;
    }
    else{
        RequestNode*prev=NULL;
        while(temp!=NULL && !dublicate){
            if(temp->requestId==Rnode->requestId){
                dublicate=1;
            }
            prev=temp;
            temp=temp->next;
        }
        if(dublicate==1){
            printf("Request ID already exists.\n");
            free(Rnode);
        }
        else{
            prev->next=Rnode;
            Rnode->next=temp;
        }
    }
    return head;
}
RequestNode* FindRequest(RequestNode*head,int id){
    RequestNode*temp=head,*retval=NULL;
    Bool found=FALSE;

    while(temp!=NULL && !found){
        if(temp->requestId==id){
            retval=temp;
            found=TRUE;
        }
        temp=temp->next;
    }
    return retval;
}
RequestNode* CreateServiceRequest(RequestNode* Rhead, ProfessionalNode* Phead, ServiceNode* Shead, CustomerNode* Chead){
    int id, customerId, serviceId;
    char date[DATE_SIZE], time[TIME_SIZE];
    CustomerNode*customer=NULL;
    ServiceNode* service=NULL;
    ProfessionalNode*professional=NULL;
    RequestNode*Rnode=NULL;
    printf("Enter Request ID: ");
    scanf("%d",&id);

    if(FindRequest(Rhead,id)!=NULL){
        printf("Request ID already exists.\n");
    }
    else{
        printf("Enter Customer ID: ");
        scanf("%d",&customerId);
        customer=FindCustomer(Chead,customerId);
        if(customer==NULL){
            printf("Customer ID does not exist.\n");
        }
        else{
            printf("Enter Service ID:");
            scanf("%d",&serviceId);

            service=FindService(Shead,serviceId);

            if(service==NULL){
                printf("Service ID does not exist.\n");
            }
            else{
                printf("Enter Date:");
                scanf("%s",date);
                printf("Enter Time:");
                scanf("%s",time);
                professional=FindSuitableProfessional(customer,service,Phead);
                Rnode=CreateRequest(id,customer,service,professional,date,time);
                if(Rnode!=NULL){
                    if(professional!=NULL){
                        professional->Status=UNAVAILABLE;
                        printf("Professional assigned successfully.\n");
                    }
                    else{
                        printf("No suitable professional available. Request is pending.\n");
                    }
                    Rhead=InsertRequest(Rhead,Rnode);
                    printf("Service Request created successfully.\n");
                }
            }
        }
    }
    return Rhead;
}