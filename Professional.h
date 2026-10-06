#ifndef PROFESSIONAL_H
#define PROFESSIONAL_H
#include "common.h"
#include "service.h"
typedef struct PROFESSIONAL_NODE{
    int professionalId;
    char name[NAME_SIZE];
    int pincode;
    char contact[PHONE_SIZE];
    Availability Status;
    ServiceNode* services[MAX_SERVICES];
    int serviceCount;

    struct PROFESSIONAL_NODE*next;

}ProfessionalNode;
ProfessionalNode* CreateProfessional(int id,const char* name,int pcode,const char* contact);
ProfessionalNode* InsertProfessional(ProfessionalNode*head,ProfessionalNode*Pnode);
ProfessionalNode* FindProfessional(ProfessionalNode*head,int id);
Bool AddServicetoProfessional(ProfessionalNode*Pnode, ServiceNode*Snode);
ProfessionalNode* RegisterProfessional(ProfessionalNode*head, ServiceNode*serviceHead);
Bool ProfessionalProvideService(ProfessionalNode*pnode, ServiceNode*Snode);
ProfessionalNode* FindcorrectProfessional(CustomerNode*customer, ServiceNode*service, ProfessionalNode*head)
#endif