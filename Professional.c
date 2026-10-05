#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "professional.h"
#include "common.h"
ProfessionalNode* CreateProfessional(int id,const char* name,int pcode,const char* contact){
    ProfessionalNode* Pnode=(ProfessionalNode*)malloc(sizeof(ProfessionalNode));
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
    return Pnode;
}

ProfessionalNode* RegisterProfessional(ProfessionalNode*head,ProfessionalNode*Pnode){
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
ProfessionalNode* AddServicetoProfessional(ProfessionalNode*Pnode,ServiceNode*Snode){
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