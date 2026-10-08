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
    printf("Enter Request ID:");
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
                professional=FindcorrectProfessional(customer,service,Phead);
                Rnode=CreateRequest(id,customer,service,professional,date,time);
                if(Rnode!=NULL){
                    if(professional!=NULL){
                        professional->Status=UNAVAILABLE;
                        printf("Professional assigned successfully.\n");
                    }
                    else{
                        printf("No suitable professional available ,request is pending.\n");
                    }
                    Rhead=InsertRequest(Rhead,Rnode);
                    printf("Service Request created successfully.\n");
                }
            }
        }
    }
    return Rhead;
}
RequestNode* CompleteRequest(RequestNode*Rhead){
    int id;
    int count=0;
    RequestNode*Rnode=NULL;
    RequestNode*nptr=Rhead;
    ProfessionalNode*professional=NULL;
    printf("List of Requests\n");

    while(nptr!=NULL){
        count++;
        printf("(%d) Request ID: %d  Service: %s\n",count,nptr->requestId,nptr->service->serviceName);
        nptr=nptr->next;
    }
    printf("Enter the Request which you want to Complete\n");
    scanf("%d",&id);

    Rnode=FindRequest(Rhead,id);

    if(Rnode==NULL){
        printf("Request ID does not exist\n");
    }
    else{
        if(Rnode->Rstatus!=ASSIGNED){
            printf("Request is not assigned\n");
        }
        else{
            professional=Rnode->professional;
            Rnode->Rstatus=COMPLETED;
            professional->Status=AVAILABLE;
            printf("Request completed successfully\n");
            Rhead=AssignPendingRequest(Rhead,professional);
        }
    }
    return Rhead;
}
RequestNode* CancelRequest(RequestNode*Rhead){
    int id;
    int count=0;
    RequestNode*Rnode=NULL;
    RequestNode*nptr=Rhead;
    ProfessionalNode*professional=NULL;
    printf("List of Requests\n");
    while(nptr!=NULL){
        count++;
        printf("(%d) Request ID: %d  Service: %s\n",count,nptr->requestId,nptr->service->serviceName);
        nptr=nptr->next;
    }
    printf("Enter the Request which you want to Cancel\n");
    scanf("%d",&id);

    Rnode=FindRequest(Rhead,id);

    if(Rnode==NULL){
        printf("Request ID does not exist\n");
    }
    else{
        if(Rnode->Rstatus==COMPLETED){
            printf("Completed request cannot be cancelled\n");
        }
        else if(Rnode->Rstatus==CANCELLED){
            printf("Request is already cancelled\n");
        }
        else{
            if(Rnode->Rstatus==ASSIGNED){
                professional=Rnode->professional;
                professional->Status=AVAILABLE;
            }

            Rnode->Rstatus=CANCELLED;
            printf("Request cancelled successfully\n");

            if(professional!=NULL){
                Rhead=AssignPendingRequest(Rhead,professional);
            }
        }
    }
    return Rhead;
}
void FindRequestsByCustomer(RequestNode*Rhead,CustomerNode*Chead){
    int id;
    CustomerNode*Cnode=NULL;
    CustomerNode*nptr=Chead;
    RequestNode*Rnode=Rhead;

    printf("List of Customers\n");

    while(nptr!=NULL){
        printf("Customer ID: %d  Name: %s\n",nptr->customerId,nptr->name);
        nptr=nptr->next;
    }

    printf("Enter Customer ID: ");
    scanf("%d",&id);

    Cnode=FindCustomer(Chead,id);

    if(Cnode==NULL){
        printf("Customer ID does not exist\n");
    }
    else{
        printf("Requests of Customer %d - %s\n",Cnode->customerId,Cnode->name);

        while(Rnode!=NULL){
            if(Rnode->customer==Cnode){
                printf("Request ID: %d\n",Rnode->requestId);
                printf("Service: %s\n",Rnode->service->serviceName);
                printf("Date: %s\n",Rnode->date);
                printf("Time: %s\n",Rnode->time);
                printf("--------------------------------\n");
            }
            Rnode=Rnode->next;
        }
    }
}
void DisplayPendingRequests(RequestNode*Rhead){
    RequestNode*nptr=Rhead;
    printf("Pending Requests\n");
    while(nptr!=NULL){
        if(nptr->Rstatus==PENDING){
            printf("Request ID: %d\n",nptr->requestId);
            printf("Customer: %s\n",nptr->customer->name);
            printf("Service: %s\n",nptr->service->serviceName);
            printf("Date: %s\n",nptr->date);
            printf("Time: %s\n",nptr->time);
            printf("--------------------------------\n");
        }
        nptr=nptr->next;
    }
}
void DisplayServiceHistory(RequestNode*Rhead,ProfessionalNode*Phead){
    int id;
    ProfessionalNode*Pnode=NULL;
    ProfessionalNode*nptr=Phead;
    RequestNode*Rnode=Rhead;
    printf("List of Professionals\n");
    while(nptr!=NULL){
        printf("Professional ID: %d  Name: %s\n",nptr->professionalId,nptr->name);
        nptr=nptr->next;
    }
    printf("Enter Professional ID: ");
    scanf("%d",&id);
    Pnode=FindProfessional(Phead,id);
    if(Pnode==NULL){
        printf("Professional ID does not exist\n");
    }
    else{
        printf("Service History of Professional %d:\n",Pnode->professionalId);
        while(Rnode!=NULL){
            if(Rnode->professional==Pnode && Rnode->Rstatus==COMPLETED){
                printf("Request ID: %d\n",Rnode->requestId);
                printf("Customer: %s\n",Rnode->customer->name);
                printf("Service: %s\n",Rnode->service->serviceName);
                printf("Date: %s\n",Rnode->date);
                printf("Time: %s\n",Rnode->time);
                printf("--------------------------------\n");
            }
            Rnode=Rnode->next;
        }
    }
}