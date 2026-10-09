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
RequestNode* CreateServiceRequest(RequestNode*Rhead,ProfessionalNode*Phead,ServiceNode*Shead,CustomerNode*Chead){
    int id,customerId,serviceId;
    char date[DATE_SIZE],time[TIME_SIZE];
    CustomerNode*customer=NULL;
    CustomerNode*Ctemp=Chead;
    ServiceNode*service=NULL;
    ServiceNode*Snode=Shead;
    ProfessionalNode*professional=NULL;
    RequestNode*Rnode=NULL;

    printf("List of Customers\n");

    while(Ctemp!=NULL){
        printf("Customer ID: %d  Name: %s\n",Ctemp->customerId,Ctemp->name);
        Ctemp=Ctemp->next;
    }

    printf("Enter Customer ID: ");
    scanf("%d",&customerId);

    customer=FindCustomer(Chead,customerId);

    if(customer==NULL){
        printf("Customer ID does not exist.\n");
    }
    else{
        printf("Enter Request ID: ");
        scanf("%d",&id);

        if(id<=0){
            printf("Invalid Request ID.\n");
        }
        else if(FindRequest(Rhead,id)!=NULL){
            printf("Request ID already exists.\n");
        }
        else{
            printf("Available Services\n");

            while(Snode!=NULL){
                printf("Service ID: %d  Service Name: %s  Base Price: %.2f\n",
                       Snode->serviceId,Snode->serviceName,Snode->basePrice);
                Snode=Snode->next;
            }

            printf("Enter Service ID: ");
            scanf("%d",&serviceId);

            service=FindService(Shead,serviceId);

            if(service==NULL){
                printf("Service ID does not exist.\n");
            }
            else{
                printf("Enter Date (DD/MM/YYYY): ");
                scanf("%10s",date);

                printf("Enter Time (HH:MM): ");
                scanf("%9s",time);

                professional=FindcorrectProfessional(customer,service,Phead);
                Rnode=CreateRequest(id,customer,service,professional,date,time);

                if(Rnode!=NULL){
                    if(professional!=NULL){
                        professional->Status=UNAVAILABLE;
                        printf("Professional assigned successfully.\n");
                        printf("Professional Name: %s\n",professional->name);
                    }
                    else{
                        printf("No suitable professional available, request is pending.\n");
                    }

                    Rhead=InsertRequest(Rhead,Rnode);
                    printf("Service Request created successfully.\n");
                }
            }
        }
    }

    return Rhead;
}
RequestNode* AssignPendingRequest(RequestNode*Rhead,ProfessionalNode*professional){
    RequestNode*nptr=Rhead;
    RequestNode*samePincode=NULL;
    RequestNode*diffPincode=NULL;

    while(nptr!=NULL){
        if(nptr->Rstatus==PENDING &&
           ProfessionalProvideService(professional,nptr->service)==TRUE){
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
        nptr=nptr->next;
    }

    if(samePincode!=NULL){
        samePincode->professional=professional;
        samePincode->Rstatus=ASSIGNED;
        professional->Status=UNAVAILABLE;
        printf("Pending request assigned successfully.\n");
    }
    else if(diffPincode!=NULL){
        diffPincode->professional=professional;
        diffPincode->Rstatus=ASSIGNED;
        professional->Status=UNAVAILABLE;
        printf("Pending request assigned successfully.\n");
    }
    else{
        printf("No suitable pending request available.\n");
    }

    return Rhead;
}
RequestNode* CompleteRequest(RequestNode*Rhead,ProfessionalNode*Phead){
    int id,serviceId;
    int found=0,count=0;
    RequestNode*Rnode=NULL;
    RequestNode*nptr=Rhead;
    ProfessionalNode*Pnode=NULL;
    ProfessionalNode*temp=Phead;
    ServiceNode*Snode=NULL;

    printf("List of Professionals\n");

    while(temp!=NULL){
        printf("Professional ID: %d  Name: %s\n",temp->professionalId,temp->name);
        temp=temp->next;
    }

    printf("Enter Professional ID: ");
    scanf("%d",&id);

    Pnode=FindProfessional(Phead,id);

    if(Pnode==NULL){
        printf("Professional ID does not exist.\n");
    }
    else{
        printf("Services Offered by Professional %d\n",Pnode->professionalId);

        for(int i=0;i<Pnode->serviceCount;i++){
            printf("Service ID: %d  Service Name: %s\n",
                   Pnode->services[i]->serviceId,
                   Pnode->services[i]->serviceName);
        }

        printf("Enter Service ID to Complete: ");
        scanf("%d",&serviceId);

        for(int i=0;i<Pnode->serviceCount;i++){
            if(Pnode->services[i]->serviceId==serviceId){
                Snode=Pnode->services[i];
                found=1;
            }
        }

        if(found==0){
            printf("Professional does not provide this service.\n");
        }
        else if(Pnode->Status==AVAILABLE){
            printf("This professional has no active assigned request.\n");
        }
        else{
            printf("Assigned Requests for this Service\n");

            while(nptr!=NULL){
                if(nptr->professional==Pnode &&
                   nptr->service==Snode &&
                   nptr->Rstatus==ASSIGNED){
                    printf("Request ID: %d  Customer: %s\n",
                           nptr->requestId,nptr->customer->name);
                    count++;
                }
                nptr=nptr->next;
            }

            if(count==0){
                printf("No assigned requests available for this service.\n");
            }
            else{
                printf("Enter Request ID to Complete: ");
                scanf("%d",&id);

                Rnode=FindRequest(Rhead,id);

                if(Rnode==NULL ||
                   Rnode->professional!=Pnode ||
                   Rnode->service!=Snode ||
                   Rnode->Rstatus!=ASSIGNED){
                    printf("Invalid Request ID.\n");
                }
                else{
                    Rnode->Rstatus=COMPLETED;
                    Pnode->Status=AVAILABLE;

                    printf("Request completed successfully.\n");

                    Rhead=AssignPendingRequest(Rhead,Pnode);
                }
            }
        }
    }

    return Rhead;
}
RequestNode* CancelRequest(RequestNode*Rhead,CustomerNode*Chead){
    int id;
    int customerId;
    int count=0;
    RequestNode*Rnode=NULL;
    RequestNode*nptr=Rhead;
    RequestNode*temp=Rhead;
    CustomerNode*Cnode=NULL;
    CustomerNode*Ctemp=Chead;
    ProfessionalNode*professional=NULL;

    printf("List of Customers\n");

    while(Ctemp!=NULL){
        printf("Customer ID: %d  Name: %s\n",Ctemp->customerId,Ctemp->name);
        Ctemp=Ctemp->next;
    }

    printf("Enter Customer ID: ");
    scanf("%d",&customerId);

    Cnode=FindCustomer(Chead,customerId);

    if(Cnode==NULL){
        printf("Customer ID does not exist\n");
    }
    else{
        printf("Requests of Customer %d\n",Cnode->customerId);

        while(temp!=NULL){
            if(temp->customer==Cnode && temp->Rstatus!=CANCELLED && temp->Rstatus!=COMPLETED){
                count++;
                printf("(%d) Request ID: %d  Service: %s\n",count,temp->requestId,temp->service->serviceName);
            }
            temp=temp->next;
        }

        if(count==0){
            printf("No requests available for cancellation\n");
        }
        else{
            printf("Enter the Request ID which you want to Cancel: ");
            scanf("%d",&id);

            Rnode=FindRequest(Rhead,id);

            if(Rnode==NULL || Rnode->customer!=Cnode){
                printf("Invalid Request ID for this customer\n");
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