#ifndef _APIGSM_H
#define _APIGSM_H

#include "Sim900D.h"

//Abstarct Layer for USER

//*******************************************************************************************************************
//************************************************   GENERAL   ******************************************************
//*******************************************************************************************************************
//Etat du GSM


//***** MODE GSM ***************************************************************
//******************************************************************************

//Definition des modes
#define GSM_MODE_NORMAL	0
#define GSM_MODE_SLEEP	1
#define GSM_MODE_OFF	2

//Fonctions/macros :

/*----------------------------------------------------------------------------
Changer le mode de fonctionnement du GSM :
------------------------------------------------------------------------------
parametres :
	- unsigned char mode : Mode d�sir� (GSM_MODE_NORMAL ou GSM_MODE_SLEEP ou GSM_MODE_OFF)
------------------------------------------------------------------------------
Return :
	- none
----------------------------------------------------------------------------*/
extern void SetGsmMode(unsigned char mode);


/*----------------------------------------------------------------------------
Connaitre le mode de fonctionnement actuel :
------------------------------------------------------------------------------
parametres :
	- none
------------------------------------------------------------------------------
Return :
	- unsigned char		mode actuel (GSM_MODE_NORMAL ou GSM_MODE_SLEEP ou GSM_MODE_OFF)
----------------------------------------------------------------------------*/
extern unsigned char GetGsmMode(void);

//***** ETAT GSM ***************************************************************
//******************************************************************************

/*----------------------------------------------------------------------------
 Connaitre l'�tat  actuel du module :
------------------------------------------------------------------------------
parametres :
	- none
------------------------------------------------------------------------------
Return :
	- unsigned char		eat actuel du module
						0 GSM_ST_POWER_OFF,	//module eteint (pas d'alimentation)
						1 GSM_ST_POWER_ON,	//phase d'alimentation du module
						2 GSM_ST_CONFIG,		//phase d'init
						3 GSM_ST_PRET,		//Connect� au r�seau
						4 GSM_ST_NO_SIGNAL,	//Deconnect�
						5 GSM_ST_SLEEP,		//Mode veille actif
						6 GSM_ST_ERROR		//ERREUR - (pas d'alimentation)
----------------------------------------------------------------------------*/
extern unsigned char GetGsmState(void);


/*----------------------------------------------------------------------------
 Connaitre l'erreur rencontr�e dans le cas ou le GSM est en etat "ERROR"
------------------------------------------------------------------------------
parametres :
	- none
------------------------------------------------------------------------------
Return :
	- unsigned char		erreur actuelle
						0 NO_ERROR,			//Pas d'erreur
						1 CCID_ERROR,			//Le CCID n'a pu �tre lu
						2 SIM_ERROR,			//Erreur carte SIM
						3 PIN_CODE_ERROR		//Code PIN erron�
----------------------------------------------------------------------------*/
extern unsigned char GetGsmError(void);


/*----------------------------------------------------------------------------
Connaitre la qualit� du signal (RSSI) :
------------------------------------------------------------------------------
parametres :
	- none
------------------------------------------------------------------------------
Return :
	- unsigned char		entier sur 8 bits image de la qualit� du signal (RSSI) d�fini comme suit:
								0 			-115 dBm or less
								1 			-111 dBm
								2...30 		-110... -54 dBm
								31 			-52 dBm or greater
								99 			not known or not detectable
----------------------------------------------------------------------------*/




//*******************************************************************************************************************
//*********************************************   SMS INTERFACE   ***************************************************
//*******************************************************************************************************************

//***** Envoi d'un SMS *********************************************************
//******************************************************************************


/*----------------------------------------------------------------------------
Envoyer un sms avec comme param�tre d'entr�e des chaines en rom (flash memory):
------------------------------------------------------------------------------
parametres :
	- unsigned char *PnoneNumber	- pointeur sur le 1er carcact�re du buffer en RAM contenant le numero de telephone
	- unsigned char *SmsText		- pointeur sur le 1er carcact�re du buffer en RAM contenant le texte du SMS

------------------------------------------------------------------------------
Return :
	- unsigned char  	1 si sms plac� dans la boite d'envoi
						0 sinon (2 causes possibles, un sms est d�ja en attente d'envoi ou le 
								nombre maximum de sms envoy� � d�pass� le seuil param�tr�).
----------------------------------------------------------------------------*/
extern unsigned char SMSSend (unsigned char *PnoneNumber,unsigned char *SmsText,unsigned char FlagAuto);


/*----------------------------------------------------------------------------
Permet de savoir si le sms � �t� envoy� (Boite d'envoi vide)
------------------------------------------------------------------------------
parametres :
	- none
------------------------------------------------------------------------------
Return :
	- unsigned char  	1 si sms envoy� et boite d'envoi libre
						0 si sms en attente d'envoi (boite d'envoi occup�e)
----------------------------------------------------------------------------*/
#define SmsSent() 			(~SMSSortant.ATraiter&0x01)


/*----------------------------------------------------------------------------
Permet de savoir si le SMS qui � �t� envoy� � g�n�r� une erreur
------------------------------------------------------------------------------
parametres :
	- none
------------------------------------------------------------------------------
Return :
	- unsigned char  	1 si le dernier sms envoy� � g�n�r� une erreur
						0 si le SMS � �t� envoy� avec succ�s
----------------------------------------------------------------------------*/
#define SmsSendingError()	(SMSSortant.SendingError&0x01)


/*----------------------------------------------------------------------------
Permet de savoir si le nombre de SMS envoy� � d�pass� le nombre maximum
de SMS pouvant �tre envoy�s
------------------------------------------------------------------------------
parametres :
	- none
------------------------------------------------------------------------------
Return :
	- unsigned char  	1 si le nb de SMS envoy� est > au maximum (impossible d'envoyer un SMS)
						0 sinon
----------------------------------------------------------------------------*/
//#define NbMaxSmsReach()		(CptSmsSent>=MaxSmsSent)

//Variables globales :
//extern unsigned int MaxSmsSent;	//Nombre maximum de SMS pouvant �tre envoy�s

extern unsigned int CptSmsSent; //Compteur de SMS envoy�s (incr�ment� par le moteur GSM � chaque envoi)


//***** Reception d'un SMS *****************************************************
//******************************************************************************

//Fonctions/macros :

/*----------------------------------------------------------------------------
Permet de savoir si un SMS est en attente de traitement
------------------------------------------------------------------------------
parametres :
	- none
------------------------------------------------------------------------------
Return :
	- unsigned char  	1 si un sms est en attente de traitement
						0 sinon
----------------------------------------------------------------------------*/
#define SmsReady()			(SMSEntrant.ATraiter&0x01)


/*----------------------------------------------------------------------------
Permet d'acquiter le sms entrant - autorisation d'�craser le sms
------------------------------------------------------------------------------
parametres :
	- none
------------------------------------------------------------------------------
Return :
	- none
----------------------------------------------------------------------------*/
#define SmsAck()			{SMSEntrant.ATraiter=0;SMSEntrant.AEffacer=1;}

//Variables globales :
#define SmsTxt				SMSEntrant.BuffTxt	//Buffer contenant le texte du SMS recu
#define SmsTxtLen			SMSEntrant.TxtLengt	//nombre de caract�re dans le buffer "SmsTxt"
#define SmsPN				SMSEntrant.BuffNum 	//Buffer contenant le num�ro de telephone de l'emetteur  du SMS recu
#define SmsDate				SMSEntrant.BuffDate	//Buffer contenant la date du SMS recu (AA/MM/DD)
#define SmsHeure			SMSEntrant.BuffHeure//Buffer contenant l'heure du SMS recu (HH/MM/SS)


//*******************************************************************************************************************
//*********************************************   AUDIO INTERFACE  ***************************************************
//*******************************************************************************************************************

/*----------------------------------------------------------------------------
Permet de choisir le canal audio est de le parametrer
------------------------------------------------------------------------------
parametres :
	- ChannelNumber	 	1 = canal gsm non li� au HP et au micro
						2 =canal gsm li� au HP et au micro

	- MicLvl			entier de 0 � 15 (niveau du microphone)
	- SpkLvl			entier de 0 � 100 (niveau du HP)
------------------------------------------------------------------------------
Return :
	- unsigned char		1	Si tout les param�tres sont corrects et que la demande � �t� prise en compte
						0	Sinon

----------------------------------------------------------------------------*/
extern unsigned char  SetAudioChannel (unsigned char ChannelNumber , unsigned char MicLvl , unsigned char SpkLvl);


//*******************************************************************************************************************
//**************************************   APPEL VOIX FONCTIONS COMMUNES ********************************************
//*******************************************************************************************************************
//Etat des appels
#define APPEL_AUCUN			0	//Pas d'appel en cours
#define APPEL_TRAITEMENT	1	//Appel en cours de traitement 
#define APPEL_ALERT			2	//Appel en alerte (attend le d�crochage ou l'autorisation de d�crocher)
#define APPEL_ACTIF			3	//Appel actif (connection �tablie le corrspondant � d�croch�)
#define APPEL_DISCONNECT	6	//Appel deconnecte (Tombe sur un disque numero non atribue)

/*----------------------------------------------------------------------------
arreter toutes les connexions existantes (raccrocher)
------------------------------------------------------------------------------
parametres :
	- none
------------------------------------------------------------------------------
Return :
	- unsigned char		1	si la demande d�arret des communications � �t� prise en compte
						0	sinon (GSM en mode SLEEP ou OFF)
----------------------------------------------------------------------------*/
extern unsigned char HangUp(void);

/*----------------------------------------------------------------------------
Savoir s�il y a un appel en cours :
------------------------------------------------------------------------------
parametres :
	- none
------------------------------------------------------------------------------
Return :
	- unsigned char		1 	Si un appel est en cours (entrant ou sortant)
						0	sinon 
----------------------------------------------------------------------------*/
extern unsigned char VoiceCallInProgress(void);

//*******************************************************************************************************************
//*******************************************   APPEL VOIX ENTRANTS *************************************************
//*******************************************************************************************************************

#define REPONSE_AUTO		0
#define REPONSE_MANUELLE	1
/*----------------------------------------------------------------------------
Choix du mode de r�ponse � un appel entrant :
------------------------------------------------------------------------------
parametres :
	- mode 	 		REPONSE_AUTO
			 		REPONSE_MANUELLE
------------------------------------------------------------------------------
Return :
	- none
----------------------------------------------------------------------------*/
extern void SetAnsweringMode (unsigned char mode);

/*----------------------------------------------------------------------------
Connaitre le mode de r�ponse � un appel entrant actuel:
------------------------------------------------------------------------------
parametres :
	- none	
------------------------------------------------------------------------------
Return :
	- unsigned char 	REPONSE_AUTO
			 			REPONSE_MANUELLE
----------------------------------------------------------------------------*/
extern unsigned char GetAnsweringMode (void);


/*----------------------------------------------------------------------------
Connaitre l��tat d�un appel entrant :
------------------------------------------------------------------------------
parametres :
	- none	
------------------------------------------------------------------------------
Return :
	- unsigned char 	APPEL_AUCUN
						APPEL_TRAITEMENT
						APPEL_ALERT	
						APPEL_ACTIF
----------------------------------------------------------------------------*/
extern unsigned char GetIncommingCallStat(void);

/*----------------------------------------------------------------------------
Donner l�autorisation de d�crocher au moteur gsm (cas du mode de reponse manuel):
------------------------------------------------------------------------------
parametres :
	- none	
------------------------------------------------------------------------------
Return :
	- unsigned char 	1  Si la demande d�autorisation � �t� prise en compte
						0	Sinon (pas d�appel entrant en cours ou mode r�ponse auto actif)
----------------------------------------------------------------------------*/
extern unsigned char AnswerIncommingCall(void);

/*----------------------------------------------------------------------------
Connaitre la dur�e de l�appel entrant :
------------------------------------------------------------------------------
parametres :
	- none	
------------------------------------------------------------------------------
Return :
	- unsigned int	   entier 16bits � dur�e de l�appel entrant en secondes.
----------------------------------------------------------------------------*/
extern unsigned int GetIncommingCallTime(void);


//Variables globales :
#define IncomCallPN			AppelEntrant.BuffNum
#define IncomCallPNLengt	AppelEntrant.NumLengt


//*******************************************************************************************************************
//*******************************************   APPEL VOIX SORTANTS *************************************************
//*******************************************************************************************************************
/*----------------------------------------------------------------------------
Savoir si il est possible d��mettre un appel :
------------------------------------------------------------------------------
parametres :
	- none	
------------------------------------------------------------------------------
Return :
	- unsigned char	   	1	Si il est actuellement possible de passer un appel
						0	Sinon (non connect� au r�seau ou un appel est d�j� en cours)
----------------------------------------------------------------------------*/
extern unsigned char IsVoiceCallReady(void);

/*----------------------------------------------------------------------------
Demande d��mission d�un appel (param�tres en RAM) :
------------------------------------------------------------------------------
parametres :
	- 	PnoneNumber � pointeur sur un buffer contenant le num�ro de t�l�phone de l�interlocuteur
		
------------------------------------------------------------------------------
Return :
	- unsigned char	   	1	Si la demande d�appel � �t� prise en compte
						0	Sinon (parametres erron�s ou impossible de passer un appel actuellement).
----------------------------------------------------------------------------*/
extern unsigned char MakeVoiceCall (unsigned char *PnoneNumber,unsigned char Tpa);


/*----------------------------------------------------------------------------
Connaitre l��tat d�un appel sortant :
------------------------------------------------------------------------------
parametres :
	- none	
------------------------------------------------------------------------------
Return :
	- unsigned char 	APPEL_AUCUN
						APPEL_TRAITEMENT
						APPEL_ALERT	
						APPEL_ACTIF
----------------------------------------------------------------------------*/
//extern unsigned char GetOutgoingCallStat(void);

/*----------------------------------------------------------------------------
Connaitre la dur�e de l�appel sortant :
------------------------------------------------------------------------------
parametres :
	- none	
------------------------------------------------------------------------------
Return :
	- unsigned int	   entier 16bits � dur�e de l�appel entrant en secondes.
----------------------------------------------------------------------------*/
extern unsigned int GetOutgoingCallTime(void);

//Variables globales :
#define OutgoingCallPN		    AppelSortant.BuffNum




extern unsigned char SendDTMF(unsigned char * BuffData, unsigned char Lengt , unsigned char Time);
extern unsigned char GetDTMFError (void);
extern unsigned char GetDTMFStatus (void);

#endif