#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "professional.h"
#include "common.h"
ProfessionalNode* CreateProfessional(int id,const char* name,int pcode,const char* contact){
    ProfessionalNode*Pnode=NULL;
    if(id<=0){
        printf("Invalid Professional ID");
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
        if(Pnode->serviceCount<MAX_SERVICES){
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
    ProfessionalNode*Pnode;
    ServiceNode*Snode;
    
    printf("Enter Professional ID: ");
    scanf("%d",&id);

    Pnode=FindProfessional(head,id);

    if(Pnode!=NULL){
        printf("Professional ID already exists.\n");
    }
    else{
        printf("Enter Professional Name: ");
        scanf(" %[^\n]",name);

        printf("Enter Pincode: ");
        scanf("%d",&pcode);

        printf("Enter Contact Number: ");
        scanf("%s",contact);

        Pnode=CreateProfessional(id,name,pcode,contact);

        if(Pnode!=NULL){
            DisplayService(serviceHead);

            printf("Enter number of services: ");
            scanf("%d",&numberOfServices);

            if(numberOfServices<1 || numberOfServices>MAX_SERVICES){
                printf("Invalid number of services.\n");
                free(Pnode);
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
                    else{
                        if(AddServicetoProfessional(Pnode,Snode)==TRUE){
                            printf("Service added successfully.\n");
                        }
                        else{
                            printf("Not Inserted. Enter Again\n");
                            i--;
                        }
                    }
                }
                head=InsertProfessional(head,Pnode);
                printf("Professional added successfully.\n");
            }
        }
    }
    return head;
}