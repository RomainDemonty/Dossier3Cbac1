/*
Romain
Demonty
2102
10-05-2022
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Date{
    short Jour;
    short Mois;
    short Annee;
};

struct patients{
    char NumRegNat[16];
    char Nom [25];
    char Prenom[15];
    struct Date DateNaissance;
    char VIPO[5];
    char Rue[40];
    int CodePostal;
    char Ville[15];
    char Numero[5];
    char telephone[15];
};

struct Examens {
    long NumNomenclature ;
    char Intitule[30] ;
    float MntMutuelVipo ;
    float MntMutuelAO ;
    float TMAO ;
} ;

struct SubiExamens {
    long Nomenclature;
    char NumRegNat[16];
    struct Date DateExamen;
    char Facture[3];
} ;

struct IndexPatients{
    char NumRegNat[16] ;
    char Nom [25];
    char Prenom[15];
    short Position;
};

struct IndexExamen{
    long NumNomenclature;
    short Position;
};
//patient
int NEW(int,int);
int MODIF(void);
void SUPP(struct IndexPatients*,short);
void AFT(struct IndexPatients *,short );
void CRINDEX(struct IndexPatients*);
void TRIINDEX(struct IndexPatients*);
void AffIndex(struct IndexPatients*);
void AJOUTINDEXPATIENT(struct IndexPatients*,int);
int RECHERCHE (char*,char *E);

//Examen
void NEWEXAMEN(struct IndexExamen*);
void CRINDEXEXAMEN(struct IndexExamen*);
void AFFICHEXAMEN(struct IndexExamen*);
void TRIINDEXEXAMEN(struct IndexExamen*);

//Examen subis
void NEWEXAMENSUBI(struct IndexPatients*,struct IndexExamen*,short,short,short);
void AFFICHEXAMENSUBI(short);
void SUPPEXAMENSUBI(struct IndexPatients*,struct IndexExamen*,short,short,short);

//general
void DATE(struct Date*);
int VERIFLETTRE(char*,int);
int VERIFNUM(char*);

int main()
{
    int N;
    short choix,Recommencer,i1,i2,i3;
    struct IndexPatients Table[100];
    struct IndexExamen IEX[30];
    struct patients Base1[9];
    struct Examens Base2 [8];
    struct SubiExamens Base3[9];
    struct patients FICHE;
    struct SubiExamens SUBEX;
    struct Examens EXA;
    FILE *P,*PE,*PES;
    P = fopen("Fiche","ab");
    if(P==NULL)
    {
        printf("Impossible d ouvrir le fichier");
    }
    else
    {
        fseek (P, 0, SEEK_END);
        i1= ftell(P)/sizeof(FICHE);
        if(i1==0)
        {
            struct patients Base1[9]=
            {
                {"45.01.27-123.45","Duras","Louise",27,1,1945,"OUI","allee des bouvreils",4031,"Angleur","11","04/33356682"}
                ,{"53.03.02-135.88","Robert","Marc",2,3,1953,"OUI","allee du Bois",4121,"Neuville","5","04/5553222"}
                ,{"59.12.25-147.25","Lahaut","Christophe",25,12,1959,"NON","Rue de l universite",4000,"Liege","12","04/6502121"}
                ,{"69.03.01-258.36","Simons","Marie",1,3,1969,"NON","bld d Avroy",4000,"Liege","115","04/5306698"}
                ,{"35.11.12-456.78","Peters","Nicolas",12,11,1935,"OUI","avenue du Chene",4031,"Angleur","36","04/6502244"}
                ,{"69.01.06-336.98","Colin","Eric",6,1,1969,"NON","bld d Avroy",4000,"Liege","17a","04/2104456"}
                ,{"65.09.16-258.96","Darcis","Justine",16,9,1965,"OUI","rue des Eglantiers",4537,"Verlaine","2","04/5201212"}
                ,{"70.06.01-147.89","Dotton","Pierre",1,6,1970,"NON","route de Liege",4280,"Hannut","25a","04/5809977"}
                ,{"66.12.04-45.678","Leduc","Laura",4,12,1966,"OUI","rue Saint Gilles",4000,"Liege","27","04/2301145"}
            };
            fwrite(&Base1,sizeof(Base1),1,P);
        }
        fclose(P);
        CRINDEX(&Table[0]);
        TRIINDEX(&Table[0]);
    }

    PE = fopen("Examens","ab");
    if(PE==NULL)
    {
        printf("Impossible d ouvrir le fichier");
    }
    else
    {
        fseek (PE, 0, SEEK_END);
        i2= ftell(PE)/sizeof(EXA);
        if(i2==0)
        {
            struct Examens Base2[8]=
            {
                {470750,"ECG",15.48,13.16,2.32}
                ,{475812,"ECG effort",30.58,26,4.58}
                ,{469814,"Echo coulur",62.32,59.84,2.48}
                ,{475893,"Controle VVI",30.16,25.64,4.52}
                ,{477893,"Controle defibrilateur",100.54,91.86,8.68}
                ,{475650,"Dopler bilateral",15.08,12.82,2.26}
                ,{475532,"Epreuve de stress",25.13,21.37,3.76}
                ,{476210,"Holter",65.23,56.55,8.68}
            };
            fwrite(&Base2,sizeof(Base2),1,PE);
            fclose(PE);
        }
        CRINDEXEXAMEN(&IEX[0]);
        TRIINDEXEXAMEN(&IEX[0]);
    }

    PES = fopen("ExamensSubi","ab");
    if(PES==NULL)
    {
        printf("Impossible d ouvrir le fichier");
    }
    else
    {
        fseek (PES, 0, SEEK_END);
        i3= ftell(PES)/sizeof(SUBEX);
        if(i1==0&&i2==0&&i3==0)
        {
            struct SubiExamens Base3[9]=
            {
                {470750,"45.01.27-123.45",1,12,2015,"NON"}
                ,{475893,"53.03.02-135.88",25,11,2019,"OUI"}
                ,{469814,"59.12.25-147.25",01,12,2019,"NON"}
                ,{469814,"35.11.12-456.78",02,12,2019,"NON"}
                ,{477893,"69.03.01-258.36",03,12,2019,"OUI"}
                ,{469814,"69.03.02-258.36",04,01,2020,"OUI"}
                ,{470750,"45.01.27-123.45",04,01,2020,"OUI"}
                ,{476210,"65.09.16-258.96",04,01,2020,"NON"}
                ,{475532,"66.12.04-456.78",05,01,2020,"OUI"}
            };
            fwrite(&Base3,sizeof(Base3),1,PES);
        }
        fclose(PES);
    }


    do
    {
        do
        {
            system("cls");
            //AffIndex(&Table[0]);
            printf("__________MENU__________");
            printf("\nQue voulez vous faire ?\n");
            printf("1)Entrer un nouveau patient\n");
            printf("2)Modifier les donees d un patient\n");
            printf("3)Supprimer un patient\n");
            printf("4)Afficher tout les patients\n");
            printf("5)Ajouter un examen\n");
            printf("6)Afficher les examens\n");
            printf("7)Supprimer un examen\n");
            printf("8)Ajouter un examen subis\n");
            printf("9)Afficher tout les examens subis\n");
            printf("Que voulez vous faire ?\n");

            printf("Votre choix: ");
            fflush(stdin);
            scanf("%hd",&choix);
            if(choix > 9 || choix < 1)
            {
                printf("\nChoix pas valide, recommencer:\n");
            }
        }while(choix > 9 || choix < 1);

        P = fopen("Fiche","rb");
        if(P==NULL)
        {
        printf("Impossible d ouvrir le fichier");
        }
        else
        {
            fseek (P, 0, SEEK_END);
            i1= ftell(P)/sizeof(FICHE);
            fclose(P);
        }
        PE = fopen("Examens","rb");
        if(PE==NULL)
        {
            printf("Impossible d ouvrir le fichier");
        }
        else
        {
            fseek (PE, 0, SEEK_END);
            i2= ftell(PE)/sizeof(EXA);
            fclose(PE);
        }
        PES = fopen("ExamensSubi","rb");
        if(PES==NULL)
        {
            printf("Impossible d ouvrir le fichier");
        }
        else
        {
            fseek (PES, 0, SEEK_END);
            i3= ftell(PES)/sizeof(SUBEX);
            fclose(PES);
        }
        CRINDEXEXAMEN(&IEX[0]);
        TRIINDEXEXAMEN(&IEX[0]);
        CRINDEX(&Table[0]);
        TRIINDEX(&Table[0]);
        switch(choix){
        case 1:
            N=NEW(0,1);
            AJOUTINDEXPATIENT(&Table[0],N);
            TRIINDEX(&Table[0]);
        break;
        case 2:
            N=MODIF();
        break;
        case 3:
            SUPP(&Table[0],i3);
        break;
        case 4:
            system("cls");
            AFT(&Table[0],i1);
        break;
        case 5:
            system("cls");
            NEWEXAMEN(&IEX[0]);
        break;
        case 6:
            system("cls");
            AFFICHEXAMEN(&IEX[0]);
        break;
        case 7:
            system("cls");
            SUPPEXAMENSUBI(&Table[0],&IEX[0],i1,i2,i3);
        break;
        case 8:
            system("cls");
            NEWEXAMENSUBI(&Table[0],&IEX[0],i1,i2,i3);
        break;
        case 9:
            system("cls");
            AFFICHEXAMENSUBI(i3);
        break;
        };

        do{
            printf("\nQue voulez vous faire?\n1)Quitter\n2)Continuer\nVotre choix: ");
            fflush(stdin);
            scanf("%hd",&Recommencer);
            if(Recommencer!=1 && Recommencer!=2)
            {
                printf("\nChoix pas valide, recommencer\n");
            }
        }while(Recommencer!=1 && Recommencer!=2);
    }while(Recommencer==2);

    return 0;
}
/*
input:L'adresse de debut du fichier
output: /
process: écrire dans un fichier des structures de patient a l'aide du pointeur d'adresse.
*/
int NEW(int position,int mode)
{
    int Q,i=0,N,Vipo,N2;
    struct patients FICHE;
    struct patients FICHE2;
    char FIN[7];
    char REC[5];
    char PRE[5];
    char NUM[11];
    char D[11];
    int DAT;
    char NBR[3];
    NBR[3]='\0';

    strcpy(REC,"VIDE");
    REC[4]='\0';
    strcpy(PRE,"VIDE");
    PRE[4]='\0';
    system("cls");
    FILE *P;

    //si il n'existe pas comme ça il sera créer
    P = fopen("Fiche","ab");
    if(P==NULL)
    {
        printf("Impossible d ouvrir le fichier");
    }
    else
    {
        //mode 0 pour modifier une personne et ça position est renvoyée de la fonction modif
        if(mode==0)
        {
            N=position;
        }
        else
        {
            N=RECHERCHE(REC,PRE);
            fseek (P, 0, SEEK_END);
            i= ftell(P)/sizeof(FICHE);
            printf("\n___NEW PATIENT___\n");
        }
        fclose(P);

        //permet de vérifier si il ,n'y as pas trop d'élément et si il y en a 100 ce n'est pas grave car on en modifie un donc mode 0
        if(i!=100||mode==0)
        {
            P = fopen("Fiche","r+b");
            if(P==NULL)
            {
                printf("Impossible d ouvrir le fichier");
            }
            else
            {
                if(N==-1)
                {
                    fseek(P,0,SEEK_END);
                }
                else
                {
                    fseek(P,N*sizeof(struct patients),SEEK_SET);
                }

                do
                {
                    printf("\nEntrez un nom: ");
                    fflush(stdin);
                    gets(FICHE.Nom);
                }
                while(strlen(FICHE.Nom)<2||VERIFLETTRE(&FICHE.Nom[0],0)!=0);

                do
                {
                    printf("Entrez un prenom: ");
                    fflush(stdin);
                    gets(FICHE.Prenom);

                }while(strlen(FICHE.Prenom)<2||VERIFLETTRE(&FICHE.Prenom[0],0)!=0);


                DATE(&FICHE.DateNaissance);

                char TMP2[10],TEMP[10];
                int T= FICHE.DateNaissance.Annee;
                T=T%100;
                if(T<10&&T!=0)
                {
                    strcpy(FICHE.NumRegNat,"0");
                }
                if(T==0)
                {
                    strcpy(FICHE.NumRegNat,"00");
                }
                else
                {
                    sprintf(TEMP, "%d",T);
                    strcat(FICHE.NumRegNat,TEMP);
                }
                strcat(FICHE.NumRegNat,".");

                if(FICHE.DateNaissance.Mois<10)
                {
                    strcat(FICHE.NumRegNat,"0");
                }
                sprintf(TMP2,"%d",FICHE.DateNaissance.Mois);
                strcat(FICHE.NumRegNat,TMP2);

                strcat(FICHE.NumRegNat, ".");

                if(FICHE.DateNaissance.Jour<10)
                {
                    strcat(FICHE.NumRegNat,"0");
                }
                sprintf(TEMP, "%d",FICHE.DateNaissance.Jour);
                strcat(FICHE.NumRegNat,TEMP);

                strcat(FICHE.NumRegNat,"-");

                printf("\nGeneration automatique du debut de votre numero de registre nationnal: ");
                puts(FICHE.NumRegNat);

                do
                {
                    printf("Introduire la fin de votre numero de registre nationnal sous le format 123.45: ");
                    fflush(stdin);
                    gets(FIN);
                    if(FIN[3]!='.')
                    {
                        printf("Pas valide, il manque le . , recommencez:\n");
                    }
                    if(strlen(FIN)!=6)
                    {
                        printf("La taille n est pas bonne, recommencez:\n");
                    }
                }
                while(FIN[3]!='.'||strlen(FIN)!=6||VERIFNUM(&FIN[0])==1);
                strcat(FICHE.NumRegNat,FIN);
                printf("Votre numero de registre nationnal est: ");
                puts(FICHE.NumRegNat);

                printf("\nIntroduire l adresse: ");
                do
                {
                    printf("\nCode postal: ");
                    fflush(stdin);
                    scanf("%d",&FICHE.CodePostal);

                    if(FICHE.CodePostal<1000||FICHE.CodePostal>10000)
                    {
                        printf("Code pas valide, recommencez:\n");
                    }
                }while(FICHE.CodePostal<1000||FICHE.CodePostal>10000);

                do
                {
                    printf("Rue: ");
                    fflush(stdin);
                    gets(FICHE.Rue);
                }while(strlen(FICHE.Rue)<2||VERIFLETTRE(&FICHE.Rue[0],1)!=0);

                do
                {
                    printf("Introduire la ville: ");
                    fflush(stdin);
                    gets(FICHE.Ville);
                }while(strlen(FICHE.Ville)<2||VERIFLETTRE(&FICHE.Ville[0],0)!=0);

                printf("Introduire le numero de maison: ");
                fflush(stdin);
                gets(FICHE.Numero);

                do
                {
                    printf("Vipo:\n1)Oui\n2)Non\nVotre choix: ");
                    fflush(stdin);
                    scanf("%d",&Vipo);
                }
                while(Vipo!=1&&Vipo!=2);

                if(Vipo==1)
                {
                    strcpy(FICHE.VIPO,"OUI");
                }
                else
                {
                    strcpy(FICHE.VIPO,"NON");
                }
                FICHE.VIPO[4]='\0';

                strcpy(FICHE.telephone,"04/");

                do
                {
                    printf("Entrez le numero de telephone: 04/");
                    fflush(stdin);
                    gets(NUM);
                }
                while(VERIFNUM(&NUM[0])==1);

                strcat(FICHE.telephone,NUM);

                N2=RECHERCHE(FICHE.Nom,FICHE.Prenom);
                //vérifie si le nom n'est pas déja dans le fichier
                fseek(P,N2*sizeof(struct patients),SEEK_SET);
                fread(&FICHE2,sizeof(struct patients),1,P);
                if(strcmp(FICHE.NumRegNat,FICHE2.NumRegNat)==0&&mode!=0)
                {
                    printf("Ce passient existe deja, il n a pas ete rajoute.\n");
                }
                else
                {
                    //si pas de place  vide
                    if(N==-1)
                    {
                        fseek(P,0,SEEK_END);
                        N=i-1;
                    }
                    else
                    {
                        fseek(P,N*sizeof(struct patients),SEEK_SET);
                    }
                    fwrite(&FICHE,sizeof(FICHE),1,P);
                    fclose(P);
                }

            }
        }
    }
    return (N);
}

/*
input:L'adresse de debut du fichier
output: /
process: Modifier le contenu (adresse) d'un patient
*/
int MODIF(void)
{
    struct patients FICHE;
    int choix,N;
    char REC[25],PRE[25];
    system("cls");

    printf("\nDe qui voulez vous modifier les donnees?\n");

    do
    {
        printf("Nom: ");
        fflush(stdin);
        gets(REC);
    }
    while(VERIFLETTRE(REC,0)!=0);
    do
    {
        printf("Prenom: ");
        fflush(stdin);
        gets(PRE);
    }
    while(VERIFLETTRE(PRE,0)!=0);
    N=RECHERCHE(REC,PRE);

    NEW(N,0);
    return(N);
}

/*
input:L'adresse de debut du fichier
output: /
process: Supprimer un patient
*/
void SUPP(struct IndexPatients *DEBUTINDEX,short T3)
{
    struct patients FICHE;
    struct SubiExamens SubiExamen;
    char REC[25],PRE[25];
    int N,i=0;
    FILE *P,*PES;
    P = fopen("Fiche","r+b");
    system("cls");
    if(P==NULL)
    {
        printf("Impossible d ouvrir le fichier");
    }
    else
    {
        printf("\nQuel patient voulez vous supprimer ?\n");
        do
        {
            printf("Nom: ");
            fflush(stdin);
            gets(REC);
        }
        while(VERIFLETTRE(REC,0)!=0);
        do
        {
            printf("Prenom: ");
            fflush(stdin);
            gets(PRE);
        }
        while(VERIFLETTRE(PRE,0)!=0);
        fclose(P);
        N=RECHERCHE(REC,PRE);

        P = fopen("Fiche","r+b");
        if(P==NULL)
        {
            printf("Impossible d ouvrir le fichier");
        }
        else
        {
            if(N==-1)
            {
                printf("Patient pas trouve\n");
            }
            else
            {
                while(N!=DEBUTINDEX->Position)
                {
                    DEBUTINDEX++;
                }
                strcpy(DEBUTINDEX->NumRegNat,"VIDE");
                strcpy(DEBUTINDEX->Nom,"VIDE");
                strcpy(DEBUTINDEX->Prenom,"VIDE");
                fseek(P,N*sizeof(struct patients),SEEK_SET);
                fread(&FICHE,sizeof(struct Examens),1,P);
                PES = fopen("ExamensSubi","r+b");
                if(PES==NULL)
                {
                    printf("Impossible d ouvrir le fichier");
                }
                else
                {
                    i=0;
                    do
                    {
                        fread(&SubiExamen,sizeof(struct SubiExamens),1,PES);
                        if(strcmp(FICHE.NumRegNat,SubiExamen.NumRegNat)==0)
                        {
                            printf("%d",i);
                            fseek(PES,i*sizeof(struct SubiExamens),SEEK_SET);
                            SubiExamen.Nomenclature=1;
                            fwrite(&SubiExamen,sizeof(SubiExamen),1,PES);
                        }
                        i++;
                    }
                    while(i!=T3);
                    fclose(PES);
                }
                fseek(P,N*sizeof(struct patients),SEEK_SET);
                strcpy(FICHE.Nom,"VIDE");
                FICHE.Nom[4]='\0';
                strcpy(FICHE.Prenom,"VIDE");
                FICHE.Prenom[4]='\0';
                fwrite(&FICHE,sizeof(FICHE),1,P);
                printf("\nPersonne bien supprimee !\n\n");


            }
                    fclose(P);
                }
    }
}

/*
input:L'adresse de debut du fichier
output: /
process: Afficher la totalité des patients mais dans l'ordre alphabétique
*/
void AFT(struct IndexPatients *I,short T1)
{
    struct patients FICHE;
    int i,n,Q,V,CP=0,N;
    FILE *P;
    P = fopen("Fiche","rb");
    system("cls");
    if(P==NULL)
    {
        printf("Impossible d ouvrir le fichier");
    }
    else
    {
        printf("\nAffichage de tous les patients:\n");
        n=0;
        Q=1;
        if(i==0)
        {
            printf("\nAucun patients ne sont present dans le fichier");
        }
        while(n<T1)
        {
            N=I->Position;
            fseek(P,N*sizeof(struct patients),SEEK_SET);
            fread(&FICHE,sizeof(struct patients),1,P);
            if(strcmp(FICHE.Nom,"VIDE")!=0)
            {
                printf("____________________\n");
                printf("\nPersonne %d:\n",Q);
                printf("\nNom: %s",FICHE.Nom);
                printf("\nPrenom: %s",FICHE.Prenom);
                printf("\n\nNumerro de registre nationnal: %s",FICHE.NumRegNat);
                printf("\n\nCode postal: %d",FICHE.CodePostal);
                printf("\nVille: %s",FICHE.Ville);
                printf("\nRue: %s",FICHE.Rue);
                printf("\nNumero: %s",FICHE.Numero);
                printf("\n\nDate de naissance: %d/%d/%d\n",FICHE.DateNaissance.Jour,FICHE.DateNaissance.Mois,FICHE.DateNaissance.Annee);
                printf("Vipo: %s\n",FICHE.VIPO);
                printf("Numero de telephone: %s\n",FICHE.telephone);
                printf("____________________\n");
                Q++;
            }
            else
            {
                CP++;
            }
            n++;
            I++;
        }
        if(CP==i)
        {
            printf("Pas de passient enregistre\n");
        }
        fclose(P);
    }
}

/*
input:L'adresse de debut de la chaine de caractère recherchée
output: N (Nombre de strcut à se déplacer) ou -1 si pas trouvé
process: parcourir lefichier et si on le trouve on renvoi le nombre de structure à se déplacer et si non on renvoie -1
*/
int RECHERCHE(char *R,char *E)
{
    int N,i,C;
    char REC[25],PRE[25],TMP[25],TMP2[25];
    struct patients FICHE;
    FILE *P;
    system("cls");
    P = fopen("Fiche","rb");
    if(P==NULL)
    {
        printf("Impossible d ouvrir le fichier");
    }
    else
    {
        strcpy(REC,R);
        strcpy(PRE,E);
        fseek(P,0,SEEK_END);
        i=ftell(P)/sizeof(struct patients);
        fseek(P,0,SEEK_SET);
        N=0;

        C=0;
        while(strlen(REC)>=C)
        {
            REC[C]=toupper(REC[C]);
            C++;
        }
        C=0;
        while(strlen(PRE)>=C)
        {
            PRE[C]=toupper(REC[C]);
            C++;
        }

        do
        {
            fread(&FICHE,sizeof(struct patients),1,P);
            N++;
            C=0;
            strcpy(TMP,FICHE.Nom);
            while(strlen(FICHE.Nom)>=C)
            {
                TMP[C]=toupper(TMP[C]);
                C++;
            }
            C=0;
            strcpy(TMP2,FICHE.Nom);
            while(strlen(FICHE.Nom)>=C)
            {
                TMP2[C]=toupper(TMP2[C]);
                C++;
            }
        }
        while(strcmp(TMP,REC)!=0&&strcmp(TMP2,PRE)!=0&&N<=i);
        N--;
        if(strcmp(TMP,REC)!=0&&strcmp(TMP2,PRE)!=0)
        {
            N=-1;
        }
        fclose(P);
    }
    return(N);
}

/*
input:adresse de la chaine de caractère à vérifier et le nombre d'espace permis 0 si un nom et 1 phrase (On peut avoir des espaces dans les phrases de rue masi pas en plein millieu d'un mot)
output: return t pour savoir si elle est valide ou pas et si on doit recommencer si T=0 c'est juste aussi non on recommence
process: parcourir caractère par caractère et les vérifier et si il y a des espaces vérifier si il n'y en a pas deux qui se suivent ou si il y en a un en pleins millieu
*/
int VERIFLETTRE(char*C,int O)
{
    int T=0,i=0,l;
    char tmp[25];
    char E;
    if(strlen(C)<2)
    {
        printf("\nTrop petit, recommencez:");
        T++;
    }
    l=strlen(C);
    while(l>i&&T==0)
    {
        if(i==0)
        {
            strcpy(tmp,C);
            tmp[0]=toupper(tmp[0]);
            strcpy(C,tmp);
        }

        //si ce n'est pas une lettre majuscucle ou une lettre minuscule renvoie 0
        if(isalpha(*C)==0)
        {
            if(*C==' ')
            {
                if(*(C+1)==' '||O!=1)
                {
                    T++;
                    printf("\nTrop d espace, recommencez:");
                }
                else
                {
                    C++;
                }
            }
            else
            {
                T++;
                printf("\nSeules les letrres sont autorises, recommencez:");
            }
        }
        else
        {
            C++;
        }
        i++;
    }
    return(T);
}

/*
input:Adresse de la chaine de caractère à vérifier
output: Si elle est valide ou pas si T=0 valide aussi non pas valide
process: Parcourir cacartère par caractère sauf le point pour vérifier si c'est bien des nombres et pas des lettres
*/
int VERIFNUM(char*C)
{
    int i=0,T=0;
    while(strlen(C)>=i)
    {
        if(i!=3&&i!=6)
        {
            if(isdigit(*C)==0)
            {
                T++;
                printf("\nCe n est pas valide, ce ne sont pas que des nombres, recommencez: \n");
            }
        }
        i++;
        C++;
    }
    return(T);
}

//input : l'adresse de l'index des patients
//process: parcoure le fichhier éléments par élement et les inscrit dasn l'index
//output: //
void CRINDEX(struct IndexPatients *DEBUTINDEX)
{
    short N,n;
    FILE *P;
    struct patients FICHE;
    P = fopen("Fiche","rb");
    if(P==NULL)
    {
        printf("Impossible d ouvrir le fichier");
    }
    else
    {
        fseek(P,0,SEEK_END);
        n=ftell(P)/sizeof(struct patients);
        fseek(P,0,SEEK_SET);
        for(N=0;N<n;N++,DEBUTINDEX++)
        {
            fread(&FICHE,sizeof(struct patients),1,P);
            strcpy(DEBUTINDEX->NumRegNat,FICHE.NumRegNat);
            strcpy(DEBUTINDEX->Nom,FICHE.Nom);
            strcpy(DEBUTINDEX->Prenom,FICHE.Prenom);
            DEBUTINDEX->Position=N;
        }
        fclose(P);
    }
}

//input : l'index des patients pour pouvoir le trier
//process: inverser si il est plus petit alphabétiquement que l'autre pui l'écrire dans l'index
//output: //
void TRIINDEX(struct IndexPatients *I)
{
    short n,i;
    char TMP[25];
    int t;
    struct patients FICHE;
    FILE *P;

    P = fopen("Fiche","rb");
    if(P==NULL)
    {
        printf("Impossible d ouvrir le fichier");
    }
    else
    {
        fseek(P,0,SEEK_END);
        n=ftell(P)/sizeof(struct patients);
        while(n>1)
        {
            for(i=0;i<(n-1);i++)
            {
                if((strcmp(I->Nom,(I+1)->Nom))==1)
                {
                    if((strcmp(I->Prenom,(I+1)->Prenom))==1)
                    {
                        strcpy(TMP,I->Nom);
                        strcpy((I->Nom),(I+1)->Nom );
                        strcpy((I+1)->Nom,TMP);

                        strcpy(TMP,I->Prenom);
                        strcpy((I->Prenom),(I+1)->Prenom);
                        strcpy((I+1)->Prenom,TMP);

                        strcpy(TMP,I->NumRegNat);
                        strcpy((I->NumRegNat),(I+1)->NumRegNat );
                        strcpy((I+1)->NumRegNat,TMP);

                        t=I->Position;
                        I->Position=(I+1)->Position;
                        (I+1)->Position=t;
                    }

                }
                I++;
            }
            n--;
            I-=i;
        }
        fclose(P);
    }
}

//juste une fonction pour m'aider à verifier
void AffIndex(struct IndexPatients *I)
{
    int n,N;
    struct patients FICHE;
    FILE *P;
    P = fopen("Fiche","rb");
    if(P==NULL)
    {
        printf("Impossible d ouvrir le fichier");
    }
    else
    {
        fseek(P,0,SEEK_END);
        N=ftell(P)/sizeof(struct patients);
        for(n=0;n<N;n++,I++)
        {
            printf("\n\n");
            printf("%s\n",I->Nom);
            printf("%s\n",I->Prenom);
            printf("%s\n",I->NumRegNat);
            printf("%hd\n",I->Position);
        }
        fclose(P);
    }
}

//input : l'index pour voir si il existe deja
//process: remplir la fiche examen puis verifier si il n'y en a pas deja 30 et si il n'y est pas déja puis ecrire si un vide ou sinon à la fin
//output: //
void NEWEXAMEN(struct IndexExamen *IE)
{
    struct Examens Examens;
    struct Examens TMP;
    int N,i,NE=0,stop=0;
    float test;
    FILE *PE;
    system("cls");
    printf("___Nouvel Examen___");
    do
    {
        printf("\nEntrez l intitule du nouvel examen: ");
        fflush(stdin);
        gets(Examens.Intitule);
    }
    while(VERIFLETTRE(&Examens.Intitule[0],1)!=0);

    do
    {
        printf("Entrez la nomenclature: ");
        fflush(stdin);
        scanf("%ld",&Examens.NumNomenclature);

        if(Examens.NumNomenclature<=99999||Examens.NumNomenclature>=1000000)
        {
            printf("\nLe numero doit contenir 6 chiffres\n");
        }
    }
    while(Examens.NumNomenclature<=99999||Examens.NumNomenclature>=1000000);

    do
    {
        printf("Entrez le montant mutuelle AO: ");
        fflush(stdin);
        scanf("%f",&Examens.MntMutuelAO);

        N=(int)(Examens.MntMutuelAO*100);
        test=N/100.0;

        if(Examens.MntMutuelAO<=0)
        {
            printf("\nLe montant ne peut pas etre nul ou négatif!\n");
        }
    }
    while(Examens.MntMutuelAO<=0);

    do
    {
        printf("Introduire le montant du ticket modérateur: ");
        fflush(stdin);
        scanf("%f",&Examens.TMAO);

        if(Examens.MntMutuelAO<=Examens.TMAO)
        {
            printf("\nLe montant doit etre inférieure à %.2f\n",Examens.MntMutuelAO);
        }
    }
    while(Examens.MntMutuelAO<=Examens.TMAO);

    PE = fopen("Examens","r+b");
    if(PE==NULL)
    {
        printf("Impossible d ouvrir le fichier");
    }
    else
    {
        fseek(PE,0,SEEK_END);
        i=ftell(PE)/sizeof(struct Examens);
        while(IE->NumNomenclature!=Examens.NumNomenclature&&NE<i)
        {
            if(IE->NumNomenclature==Examens.NumNomenclature)
            {
                printf("\nL'examen existe deja!");
                stop=1;
            }
            IE++;
            NE++;
        }
        IE-=i;
        if(stop!=1)
        {
            while(IE->NumNomenclature!=1&&NE<i)
            {
                IE++;
                NE++;
            }
            if(NE==30)
            {
                printf("Impossible d ecrire il y 30 examens");
            }
            else
            {
                fseek(PE,NE*sizeof(struct Examens),SEEK_CUR);
                fwrite(&Examens,sizeof(Examens),1,PE);
                IE->NumNomenclature=Examens.NumNomenclature;
                IE->Position=NE;
            }
        }
        fclose(PE);
    }
}
//Ne marche pas comme voulu si je modifie et supprime des éléments du coup je ne préfère pas l'utiliser et je cree a chaque fois de nouveau l'index
void AJOUTINDEXPATIENT(struct IndexPatients*I,int N)
{
    int i,c=0;
    FILE *P;
    struct patients FICHE;
    P = fopen("Fiche","r+b");
    if(P==NULL)
    {
        printf("Impossible d ouvrir le fichier");
    }
    else
    {
        fseek(P,0,SEEK_END);
        i=ftell(P)/sizeof(struct patients);
        fseek(P,N*sizeof(struct patients),SEEK_SET);
        fread(&FICHE,sizeof(struct patients),1,P);
        while(strcmp(I->NumRegNat,"VIDE")!=0&&i-1!=c)
        {
            I++;
            c++;
        }
        I->Position=N;
        strcpy(I->NumRegNat,FICHE.NumRegNat);
        strcpy(I->Nom,FICHE.Nom);
        strcpy(I->Prenom,FICHE.Prenom);
        fclose(P);
    }
}

//input : l'index
//process: ecrire fiche par fiche pas dans lordre
//output: //
void CRINDEXEXAMEN(struct IndexExamen* DEBUTEXAMEN)
{
    struct Examens Examens;
    int i,N=0;
    FILE *PE;
    PE = fopen("Examens","rb");
    if(PE==NULL)
    {
        printf("Impossible d ouvrir le fichier");
    }
    else
    {
        fseek(PE,0,SEEK_END);
        i=ftell(PE)/sizeof(struct Examens);
        fseek(PE,N*sizeof(struct Examens),SEEK_SET);
        while(i!=N)
        {
            fread(&Examens,sizeof(struct Examens),1,PE);
            DEBUTEXAMEN->NumNomenclature=Examens.NumNomenclature;
            DEBUTEXAMEN->Position=N;
            DEBUTEXAMEN++;
            N++;
        }
        fclose(PE);
    }
}

//input : l'index pour écrire dedans
//process: comparer les éléments et les inverser si plus petit
//output: //
void TRIINDEXEXAMEN(struct IndexExamen*I)
{
    short n,i;
    long t;
    struct Examens Examens;
    FILE *PE;

    PE = fopen("Examens","r+b");
    if(PE==NULL)
    {
        printf("Impossible d ouvrir le fichier");
    }
    else
    {
        fseek(PE,0,SEEK_END);
        n=ftell(PE)/sizeof(struct Examens);
        while(n>1)
        {
            for(i=0;i<(n-1);i++)
            {
                if(I->NumNomenclature>(I+1)->NumNomenclature)
                {
                    t=I->Position;
                    I->Position=(I+1)->Position;
                    (I+1)->Position=t;

                    t=I->NumNomenclature;
                    I->NumNomenclature=(I+1)->NumNomenclature;
                    (I+1)->NumNomenclature=t;
                }
                I++;
            }
            n--;
            I-=i;
        }
        fclose(PE);
    }
}

//input : l'index des examens trié
//process: parcourir l'index et recuperer la position et l'afficher
//output: //
void AFFICHEXAMEN(struct IndexExamen* I)
{
    short i,N,c;
    struct Examens Examens;
    FILE *PE;

    PE = fopen("Examens","rb");
    if(PE==NULL)
    {
        printf("Impossible d ouvrir le fichier");
    }
    else
    {
        fseek(PE,0,SEEK_END);
        i=ftell(PE)/sizeof(struct Examens);

        printf("\nAffichage de tout les examens:\n");
        while(i!=c)
        {
            if(I->NumNomenclature!=1);
            N=I->Position;
            fseek(PE,N*sizeof(struct Examens),SEEK_SET);
            fread(&Examens,sizeof(struct Examens),1,PE);
            printf("Nomenclature: %ld\n",Examens.NumNomenclature);
            printf("Intitule: %s\n",Examens.Intitule);
            printf("Montant mutuel vipo: %f\n",Examens.MntMutuelVipo);
            printf("Montant mutuel AO: %f\n",Examens.MntMutuelAO);
            printf("TMAO: %f\n\n\n",Examens.TMAO);
            c++;
            I++;
        }
        fclose(PE);
    }
}

//input : les index pour vérifier si le numero de registre est présent et si le num nomenclature existe et la taille des différents fichier pour les boucles
//process: parcourir les index pour verifier puis parcourir le fichier pour trouver une place vide ou mettre à la fin
//output: //
void NEWEXAMENSUBI(struct IndexPatients*PATIENTS,struct IndexExamen*EXAMEN,short T1,short T2,short T3)
{
    char NOM[25],PRENOM[25];
    struct SubiExamens NewSubiExamen;
    struct SubiExamens TMPNewSubiExamen;
    FILE *PES;
    int i,choix,OK=0;
    do
    {
        do
        {
            printf("Entrez un numero de nomenclature: ");
            fflush(stdin);
            scanf("%ld",&NewSubiExamen.Nomenclature);
            i=0;
            while(EXAMEN->NumNomenclature!=NewSubiExamen.Nomenclature&&i<T2)
            {
                EXAMEN++;
                i++;
            }
            if(EXAMEN->NumNomenclature!=NewSubiExamen.Nomenclature||NewSubiExamen.Nomenclature==1)
            {
                printf("Le numero de nomenclature n existe pas! Recommencez:\n");
                EXAMEN-=i;
            }
        }
        while(EXAMEN->NumNomenclature!=NewSubiExamen.Nomenclature||NewSubiExamen.Nomenclature==1);

        i=0;
        do
        {
            if(i!=0)
            {
                PATIENTS-=i;
                i=0;
            }
            printf("Donnees du patient:");
            do
            {
                printf("\nNom: ");
                fflush(stdin);
                gets(NOM);
            }
            while(VERIFLETTRE(NOM,0)!=0);
            do
            {
                printf("Prenom: ");
                fflush(stdin);
                gets(PRENOM);
            }
            while(VERIFLETTRE(PRENOM,0)!=0);
            while(OK!=1&&T1>i)
            {
                OK=0;
                if(strcmp(NOM,PATIENTS->Nom)==0&&strcmp(PRENOM,PATIENTS->Prenom)==0)
                {
                    printf("\nCe patient correspond a ce numero national: %s\n",PATIENTS->NumRegNat);
                    do
                    {
                        printf("Es-ce bien cette personne que vous voulez?\n1)Oui\n2)Non\nVotre choix: ");
                        fflush(stdin);
                        scanf("%d",&choix);
                        if(choix!=1&&choix!=2)
                        {
                            printf("\nChoix pas valide (Ni 1 ni 2),recommencez:\n");
                        }
                        if(choix==1)
                        {
                            OK=1;
                        }
                    }
                    while(choix!=1&&choix!=2);
                }
                else
                {
                    i++;
                    PATIENTS++;
                }
            }
            if(OK!=1)
            {
                printf("\nCette personne que vous cherchez n a pas ete trouve, recommencez:\n");
            }
            else
            {
                strcpy(NewSubiExamen.NumRegNat,PATIENTS->NumRegNat);
            }
        }
        while(OK!=1);
        //boucler jusquà ce que la bonne personne soit trouvée

        DATE(&NewSubiExamen.DateExamen);

        OK=0;
        i=0;
        PES = fopen("ExamensSubi","r+b");
        if(PES==NULL)
        {
            printf("Impossible d ouvrir le fichier");
        }
        else
        {
            do
            {
                fread(&TMPNewSubiExamen,sizeof(struct SubiExamens),1,PES);
            }
            while(i<T3&&strcmp(TMPNewSubiExamen.NumRegNat,NewSubiExamen.NumRegNat)!=0&&TMPNewSubiExamen.Nomenclature!=NewSubiExamen.Nomenclature
                  &&(TMPNewSubiExamen.DateExamen.Jour!=NewSubiExamen.DateExamen.Jour&&TMPNewSubiExamen.DateExamen.Mois!=NewSubiExamen.DateExamen.Mois
                  &&TMPNewSubiExamen.DateExamen.Annee!=NewSubiExamen.DateExamen.Annee));

            if(strcmp(TMPNewSubiExamen.NumRegNat,NewSubiExamen.NumRegNat)==0&&TMPNewSubiExamen.Nomenclature==NewSubiExamen.Nomenclature
            &&(TMPNewSubiExamen.DateExamen.Jour==NewSubiExamen.DateExamen.Jour&&TMPNewSubiExamen.DateExamen.Mois==NewSubiExamen.DateExamen.Mois
            &&TMPNewSubiExamen.DateExamen.Annee==NewSubiExamen.DateExamen.Annee))
            {
                OK=1;
                printf("\nL examen est deja present, il ne peut pas etre inscrit deux fois\n");
            }
            fclose(PES);
        }

    }
    while(OK==1);

    do
    {
        printf("A t-il ete facture ?\n1)OUI\n2)NON\nVotre choix: ");
        fflush(stdin);
        scanf("%d",&choix);

        if(choix!=1&&choix!=2)
        {
            printf("\nChoix pas valide, recommencez:\n");
        }
    }
    while(choix!=1&&choix!=2);

    if(choix==1)
    {
        strcpy(NewSubiExamen.Facture,"OUI");
    }
    else
    {
        strcpy(NewSubiExamen.Facture,"NON");
    }

    PES = fopen("ExamensSubi","r+b");
    if(PES==NULL)
    {
        printf("Impossible d ouvrir le fichier");
    }
    else
    {
        i=0;
        do
        {
            fread(&TMPNewSubiExamen,sizeof(struct SubiExamens),1,PES);
            i++;
        }
        while(TMPNewSubiExamen.Nomenclature!=1&&i<T3);
        fseek(PES,i*sizeof(struct SubiExamens),SEEK_SET);
        fwrite(&NewSubiExamen,sizeof(NewSubiExamen),1,PES);
        fclose(PES);
    }
}

//input : l'adresse à laquelle on doit mettre la date
//process: entrer en char convertir en int et verifier si valide
//output: //
void DATE(struct Date *PDATE)
{
    int Q,i;
    char NBR[4];
    char D[11];
    int DAT;
    do
    {
        Q=0;
        i=0;
        NBR[3]='\0';
        printf("Entrez la date sous se format:\nJJ.MM.AAAA: ");
        fflush(stdin);
        gets(D);
        if(D[2]!='.'||D[5]!='.'||strlen(D)<10)
        {
            printf("\nIl manque les points, recommencez\n");
            Q=1;
        }
        else
        {
            while(strlen(D)>i)
            {
                if(i!=2&&i!=5)
                {
                    if(isdigit(D[i])==0)
                    {
                        Q=1;
                        printf("\nCe n est pas valide, ce ne sont pas des nombres, recommencez: \n");
                    }
                }
                i++;
            }
            DAT=0;
            DAT=DAT*10+D[0]-48;
            DAT=DAT*10+D[1]-48;
            PDATE->Jour=DAT;

            DAT=0;
            DAT=DAT*10+D[3]-48;
            DAT=DAT*10+D[4]-48;
            PDATE->Mois=DAT;

            DAT=0;
            DAT=DAT*10+D[6]-48;
            DAT=DAT*10+D[7]-48;
            DAT=DAT*10+D[8]-48;
            DAT=DAT*10+D[9]-48;
            PDATE->Annee=DAT;
        }
        if(PDATE->Mois>12||PDATE->Jour>31||PDATE->Annee<1900||PDATE->Mois<=0||PDATE->Jour<=0)
        {
            Q=1;
        }
        if(PDATE->Mois==4||PDATE->Mois==6||PDATE->Mois==9||PDATE->Mois==11)
        {
            if(PDATE->Jour>30)
            {
                Q=1;
            }
        }
        if(PDATE->Mois==2)
        {
            if(PDATE->Jour>29)
            {
                Q=1;
            }
            else
            {
                if((PDATE->Annee%4==0&&PDATE->Annee%100!=0)||PDATE->Annee%400==0)
                {
                    Q=0;
                }
                else
                {
                    if(PDATE->Jour>=28)
                    {
                        Q=1;
                    }
                }
            }
        }
        if(Q==1)
        {
            printf("\nDate pas valide, recommencer: \n");
        }
    }
    while(Q==1);
}

void AFFICHEXAMENSUBI(short T3)
{
    int i=0;
    struct SubiExamens SubiExamen;
    FILE *PES;

    PES = fopen("ExamensSubi","rb");
    if(PES==NULL)
    {
        printf("Impossible d ouvrir le fichier");
    }
    else
    {
        printf("\nAffichage de tous les examens:");
        do
        {
            i++;
            fread(&SubiExamen,sizeof(struct SubiExamens),1,PES);
            if(SubiExamen.Nomenclature!=1)
            {
                printf("\nNumero de nomenclature: %ld",SubiExamen.Nomenclature);
                printf("\nNumero de registre national: %s",SubiExamen.NumRegNat);
                printf("\nDate examen: %hd/%hd/%hd",SubiExamen.DateExamen.Jour,SubiExamen.DateExamen.Mois,SubiExamen.DateExamen.Annee);
                printf("\nFacture: %s\n",SubiExamen.Facture);
            }

        }
        while(i<T3);
        fclose(PES);
    }
}
//input : les index pour vérifier si il est présent et la taille des différents fichier pour les boucles
//process: trouver l'examen et une fois trouvé le mettre à 1
//output: //
void SUPPEXAMENSUBI(struct IndexPatients*PATIENTS,struct IndexExamen*EXAMEN,short T1,short T2,short T3)
{
    char NOM[25],PRENOM[25];
    struct SubiExamens NewSubiExamen;
    struct SubiExamens TMPNewSubiExamen;
    FILE *PES;
    int i,choix,OK=0;
    do
    {
        do
        {
            printf("Entrez un numero de nomenclature: ");
            fflush(stdin);
            scanf("%ld",&NewSubiExamen.Nomenclature);
            i=0;
            while(EXAMEN->NumNomenclature!=NewSubiExamen.Nomenclature&&i<T2)
            {
                EXAMEN++;
                i++;
            }
            if(EXAMEN->NumNomenclature!=NewSubiExamen.Nomenclature||NewSubiExamen.Nomenclature==1)
            {
                printf("Le numero de nomenclature n existe pas! Recommencez:\n");
                EXAMEN-=i;
            }
        }
        while(EXAMEN->NumNomenclature!=NewSubiExamen.Nomenclature||NewSubiExamen.Nomenclature==1);

        i=0;
        do
        {
            if(i!=0)
            {
                PATIENTS-=i;
                i=0;
            }
            printf("Donnees du patient:");
            do
            {
                printf("\nNom: ");
                fflush(stdin);
                gets(NOM);
            }
            while(VERIFLETTRE(NOM,0)!=0);
            do
            {
                printf("Prenom: ");
                fflush(stdin);
                gets(PRENOM);
            }
            while(VERIFLETTRE(PRENOM,0)!=0);
            OK=0;
            while(OK!=1&&T1>i)
            {
                OK=0;
                if(strcmp(NOM,PATIENTS->Nom)==0&&strcmp(PRENOM,PATIENTS->Prenom)==0)
                {
                    printf("\nCe patient correspond a ce numero national: %s\n",PATIENTS->NumRegNat);
                    do
                    {
                        printf("Es-ce bien cette personne que vous voulez?\n1)Oui\n2)Non\nVotre choix: ");
                        fflush(stdin);
                        scanf("%d",&choix);
                        if(choix!=1&&choix!=2)
                        {
                            printf("\nChoix pas valide (Ni 1 ni 2),recommencez:\n");
                        }
                        if(choix==1)
                        {
                            OK=1;
                        }
                    }
                    while(choix!=1&&choix!=2);
                }
                else
                {
                    i++;
                    PATIENTS++;
                }
            }
            if(OK!=1)
            {
                printf("\nCette personne que vous cherchez n a pas ete trouve, recommencez:\n");
            }
            else
            {
                strcpy(NewSubiExamen.NumRegNat,PATIENTS->NumRegNat);
            }
        }
        while(OK!=1);
        //boucler jusquà ce que la bonne personne soit trouvée

        DATE(&NewSubiExamen.DateExamen);

        OK=0;
        i=0;
        PES = fopen("ExamensSubi","r+b");
        if(PES==NULL)
        {
            printf("Impossible d ouvrir le fichier");
        }
        else
        {
            do
            {
                fread(&TMPNewSubiExamen,sizeof(struct SubiExamens),1,PES);
            }
            while(i<T3&&strcmp(TMPNewSubiExamen.NumRegNat,NewSubiExamen.NumRegNat)!=0&&TMPNewSubiExamen.Nomenclature!=NewSubiExamen.Nomenclature
                  &&(TMPNewSubiExamen.DateExamen.Jour!=NewSubiExamen.DateExamen.Jour&&TMPNewSubiExamen.DateExamen.Mois!=NewSubiExamen.DateExamen.Mois
                  &&TMPNewSubiExamen.DateExamen.Annee!=NewSubiExamen.DateExamen.Annee));

            if(strcmp(TMPNewSubiExamen.NumRegNat,NewSubiExamen.NumRegNat)==0&&TMPNewSubiExamen.Nomenclature==NewSubiExamen.Nomenclature
            &&(TMPNewSubiExamen.DateExamen.Jour==NewSubiExamen.DateExamen.Jour&&TMPNewSubiExamen.DateExamen.Mois==NewSubiExamen.DateExamen.Mois
            &&TMPNewSubiExamen.DateExamen.Annee==NewSubiExamen.DateExamen.Annee))
            {
                OK=1;
                choix=2;
                printf("\nSuppression de l examen OK\n");
            }
            else
            {
                printf("\nL examen n a pas ete trouve\n");
                do
                {
                    printf("Voulez vous quitter?\n1)OUI\n2)NON\nVotre choix: ");
                    fflush(stdin);
                    scanf("%d",&choix);

                    if(choix!=1&&choix!=2)
                    {
                    printf("\nChoix pas valide, recommencez:\n");
                    }
                }
                while(choix!=1&&choix!=2);
            }
            fclose(PES);
        }
    }
    while(OK!=1&&choix==2);

    if(choix==2)
    {
        PES = fopen("ExamensSubi","r+b");
        if(PES==NULL)
        {
            printf("Impossible d ouvrir le fichier");
        }
        else
        {
            NewSubiExamen.Nomenclature=1;
            fseek(PES,i*sizeof(struct SubiExamens),SEEK_SET);
            fwrite(&NewSubiExamen,sizeof(NewSubiExamen),1,PES);
            fclose(PES);
        }
    }

}
