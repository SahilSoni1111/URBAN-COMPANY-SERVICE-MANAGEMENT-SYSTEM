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
RequestNode* CompleteRequest(RequestNode*Rhead, ProfessionalNode*Phead){
    int id;
    RequestNode*Rnode=NULL;
    RequestNode*nptr=Rhead;
    ProfessionalNode*professional=NULL;
    RequestNode*samePincode=NULL;
    RequestNode*diffPincode=NULL;
    int count=0;
    printf("List of Requests still pending\n");

    while(nptr!=NULL){
        if(nptr->Rstatus==PENDING){
            count++;
            printf("(%d) %d\n",count ,nptr->requestId);
        }
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
            nptr=Rhead;
            while(nptr!=NULL){
                if(nptr->Rstatus==PENDING){
                    if(ProfessionalProvideService(professional,nptr->service)==TRUE){
                        if(nptr->customer->pincode==professional->pincode){
                            if(samePincode==NULL){
                                samePincode=nptr;
                            }
                        }
                        else{
                            if(diffPincode==NULL){
                                diffPincode=nptr;
                            }
                        }
                    }
                }
                nptr=nptr->next;
            }
    
            if(samePincode!=NULL){
                samePincode->professional=professional;
                samePincode->Rstatus=ASSIGNED;
                professional->Status=UNAVAILABLE;
                printf("Pending request assigned successfully\n");
            }
            else if(diffPincode!=NULL){
                diffPincode->professional=professional;
                diffPincode->Rstatus=ASSIGNED;
                professional->Status=UNAVAILABLE;
                printf("Pending request assigned successfully\n");
            }
            else{
                printf("No suitable pending request available\n");
            }
        }
    }
    return Rhead;
}