#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "professional.h"
#include "common.h"
#include "customer.h"
#include "request.h"
ProfessionalNode* CreateProfessional(int id,const char* name,int pcode,const char* contact){
    ProfessionalNode*Pnode=NULL;
    if(id<=0){
        printf("Invalid Professional ID\n");
    }
    else{
        Pnode=(ProfessionalNode*)malloc(sizeof(ProfessionalNode));

        if(Pnode!=NULL){
            Pnode->professionalId=id;
            Pnode->pincode=pcode;
            strcpy(Pnode->name,name);
            strcpy(Pnode->contact,contact);
            Pnode->Status=AVAILABLE;
            Pnode->serviceCount=0;

            for(int i=0;i<MAX_SERVICES;i++){
                Pnode->services[i]=NULL;
            }

            Pnode->next=NULL;
        }
        else{
            printf("Professional not assigned. Memory allocation failed.\n");
        }
    }

    return Pnode;
}
ProfessionalNode* InsertProfessional(ProfessionalNode*head,ProfessionalNode*Pnode){
    ProfessionalNode*temp=head;
    int dublicate=0;

    if(head==NULL){
        head=Pnode;
    }
    else if(head->professionalId>Pnode->professionalId){
        Pnode->next=head;
        head=Pnode;
    }
    else{
        ProfessionalNode*prev=NULL;
        while(temp!=NULL && temp->professionalId<Pnode->professionalId){
            prev=temp;
            temp=temp->next;
        }
        if(temp!=NULL && temp->professionalId==Pnode->professionalId){
            dublicate=1;
        }
        else{
            prev->next=Pnode;
            Pnode->next=temp;
        }
        if(dublicate==1){
            printf("Professional ID already exists.\n");
            free(Pnode);
        }
    }
    return head;
}
ProfessionalNode* FindProfessional(ProfessionalNode*head,int id){
    ProfessionalNode*temp=head,*retval=NULL;
    Bool found=FALSE;
    while(temp!=NULL && !found){
        if(temp->professionalId==id){
            retval=temp;
            found=TRUE;
        }
        temp=temp->next;
    }
    return retval;
}
Bool AddServicetoProfessional(ProfessionalNode*Pnode,ServiceNode*Snode){
    Bool added=FALSE;

    if(Pnode!=NULL && Snode!=NULL){
        if(ProfessionalProvideService(Pnode,Snode)==FALSE &&
           Pnode->serviceCount<MAX_SERVICES){
            Pnode->services[Pnode->serviceCount]=Snode;
            Pnode->serviceCount++;
            added=TRUE;
        }
    }

    return added;
}
ProfessionalNode* RegisterProfessional(ProfessionalNode*head,ServiceNode*serviceHead){
    int id,pcode,serviceId,numberOfServices;
    char name[NAME_SIZE],contact[PHONE_SIZE];
    ProfessionalNode*Pnode=NULL;
    ServiceNode*Snode=NULL;
    Bool valid=TRUE;

    printf("Enter Professional ID: ");
    scanf("%d",&id);

    if(id<=0){
        printf("Invalid Professional ID.\n");
    }
    else if(FindProfessional(head,id)!=NULL){
        printf("Professional ID already exists.\n");
    }
    else if(serviceHead==NULL){
        printf("No services available. Add services first.\n");
    }
    else{
        printf("Enter Professional Name: ");
        scanf(" %49[^\n]",name);

        printf("Enter Pincode: ");
        scanf("%d",&pcode);

        printf("Enter Contact Number: ");
        scanf("%14s",contact);

        Pnode=CreateProfessional(id,name,pcode,contact);

        if(Pnode!=NULL){
            DisplayService(serviceHead);

            printf("Enter number of services: (max limit 5) ");
            scanf("%d",&numberOfServices);

            if(numberOfServices<1 || numberOfServices>MAX_SERVICES){
                printf("Invalid number of services.\n");
                free(Pnode);
                Pnode=NULL;
            }
            else{
                for(int i=0;i<numberOfServices;i++){
                    printf("Enter Service ID: ");
                    scanf("%d",&serviceId);

                    Snode=FindService(serviceHead,serviceId);

                    if(Snode==NULL){
                        printf("Invalid Service ID. Enter again.\n");
                        i--;
                    }
                    else if(ProfessionalProvideService(Pnode,Snode)==TRUE){
                        printf("Service already selected. Enter another Service ID.\n");
                        i--;
                    }
                    else if(AddServicetoProfessional(Pnode,Snode)==FALSE){
                        printf("Service could not be added. Enter again.\n");
                        i--;
                    }
                    else{
                        printf("Service added successfully.\n");
                    }
                }

                if(Pnode!=NULL){
                    head=InsertProfessional(head,Pnode);
                    printf("Professional added successfully.\n");
                }
            }
        }
    }

    return head;
}
Bool ProfessionalProvideService(ProfessionalNode*pnode, ServiceNode*Snode){
    Bool found=FALSE;
    if(pnode!=NULL && Snode!=NULL){
        for(int i=0; i<pnode->serviceCount && !found; i++){
            if(pnode->services[i]==Snode){
                found=TRUE;
            }
        }
    }
    return found;
}
ProfessionalNode* FindcorrectProfessional(CustomerNode*customer,ServiceNode*service,ProfessionalNode*head){
    ProfessionalNode*temp=head;
    ProfessionalNode*samepincode=NULL;
    ProfessionalNode*diffpincode=NULL;
    ProfessionalNode*retval=NULL;

    if(customer!=NULL && service!=NULL){
        while(temp!=NULL){
            if(temp->Status==AVAILABLE &&
               ProfessionalProvideService(temp,service)==TRUE){
                if(temp->pincode==customer->pincode){
                    if(samepincode==NULL){
                        samepincode=temp;
                    }
                }
                else{
                    if(diffpincode==NULL){
                        diffpincode=temp;
                    }
                }
            }
            temp=temp->next;
        }
        if(samepincode!=NULL){
            retval=samepincode;
        }
        else{
            retval=diffpincode;
        }
    }

    return retval;
}
void FindProfessionalsByService(ProfessionalNode*Phead,ServiceNode*Shead){
    int id;
    ServiceNode*Snode=NULL;
    ServiceNode*nptr=Shead;
    ProfessionalNode*temp=Phead;

    printf("List of Services\n");

    while(nptr!=NULL){
        printf("Service ID: %d  Name: %s\n",nptr->serviceId,nptr->serviceName);
        nptr=nptr->next;
    }

    printf("Enter Service ID: ");
    scanf("%d",&id);

    Snode=FindService(Shead,id);

    if(Snode==NULL){
        printf("Service ID does not exist\n");
    }
    else{
        printf("Professionals providing Service %d:\n",Snode->serviceId);

        while(temp!=NULL){
            if(ProfessionalProvideService(temp,Snode)==TRUE){
                printf("Professional ID: %d\n",temp->professionalId);
                printf("Professional Name: %s\n",temp->name);
                printf("Pincode: %d\n",temp->pincode);
                printf("Contact: %s\n",temp->contact);
                printf("--------------------------------\n");
            }
            temp=temp->next;
        }
    }
}
void FindServicesByProfessional(ProfessionalNode*Phead){
    int id;
    ProfessionalNode*Pnode=NULL;
    ProfessionalNode*nptr=Phead;

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
        printf("Services provided by Professional %d:\n",Pnode->professionalId);

        for(int i=0;i<Pnode->serviceCount;i++){
            printf("Service ID: %d\n",Pnode->services[i]->serviceId);
            printf("Service Name: %s\n",Pnode->services[i]->serviceName);
            printf("Base Price: %.2f\n",Pnode->services[i]->basePrice);
            printf("--------------------------------\n");
        }
    }
}