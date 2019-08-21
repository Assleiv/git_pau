
#ifndef CMD_TRAITEMENT_H
#define	CMD_TRAITEMENT_H


#define SET_MSQ(c,msq) (c)|=(msq) // positionne le bit b de l'octet p � 1
#define RESET_MSQ(c,msq) (c)&=~(msq) // positionne le bit b de l'octet p � 1
#define SZ_NUM_TEL ((unsigned char) 15)
extern int ValeurVariableLCR(unsigned char *ChaineRecue,unsigned char* NomVar,unsigned char *ValVar,int SzVar);
extern unsigned char CodePinValide(unsigned char *CodePin);

/*
unsigned char DecodeChaine(unsigned char *cmd, unsigned char sep, unsigned char *data, unsigned char *stop)
Fonction destin�e � simplifier le traitement d'une commande DT
Extrait une valeur numerique d'une chaine jusqu'a la fin de cette chaine ou un s�parateur
ENTREE : cmd  = pointeur sur la chaine a traiter
         sep  = caract�re s�parateur
         
SORTIE : data = Valeur numerique represent� par la chaine
         stop = d�calage entre la chaine cmd d'entree et le sparateur si existant (Retour = 1)

Retour   1 si s�parateur ou fin de chaine atteind
         0 si caract�re non num�rique et different du s�parateur rencontr�
*/
extern unsigned char DecodeChaine(unsigned char *cmd, unsigned char sep, unsigned char *data, unsigned char *stop);

#endif	/* XC_HEADER_TEMPLATE_H */

