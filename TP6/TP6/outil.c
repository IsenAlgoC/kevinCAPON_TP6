#include <stdio.h>   /* pour les entrées-sorties */
#include <string.h>  /* pour les manipulations de chaînes de caractères */
#include <conio.h>
#include <ctype.h>
#include <stdlib.h>
#include <locale.h>
#include "rep.h"

#define VERSION 3.0
#define SQUELET
/**************************************************************************/
/* Compléter votre nom ici                                                */
/*   Nom : BETRY                  Prénom : Steeven                        */
/**************************************************************************/

extern bool modif;


/**********************************************************************/
/*  Ajout d'un contact dans le répertoire stocké en mémoire           */
/**********************************************************************/

int ajouter_un_contact_dans_rep(Repertoire* rep, Enregistrement enr)
{
#ifdef IMPL_TAB
	// compléter code ici pour tableau
	int idx;

	if (rep->nb_elts < MAX_ENREG)
	{
		
		rep->tab[rep->nb_elts] = enr;
		rep->nb_elts++;
		if (rep->nb_elts >= 2)
		{
			rep->est_trie = false;
		}
		

	}
	else {
		return(ERROR);
	}


#else
#ifdef IMPL_LIST

	bool inserted = false;
	if (rep->nb_elts == 0) {
		if (InsertElementAt(rep->liste, rep->liste->size, enr) != 0) {
			rep->nb_elts += 1;
			modif = true;
			rep->est_trie = true;
			return(OK);
		}

	}
	else {
		

		if (InsertElementAt(rep->liste, rep->nb_elts, enr) != 0) {

			rep->nb_elts++;
			modif = true;
			rep->est_trie = true;
			return(OK);
		}


	}


#endif

#endif


	return(OK);

} /* fin ajout */
  /**********************************************************************/
  /* supprime du répertoire l'enregistrement dont l'indice est donné en */
  /*   paramètre       et place modif = true                            */
  /**********************************************************************/
#ifdef IMPL_TAB
void supprimer_un_contact_dans_rep(Repertoire* rep, int indice) {

	// compléter code ici pour tableau
	if (rep->nb_elts >= 1)		/* s'il y a au moins un element ds le tableau */
	{						/* et que l'indice pointe a l'interieur */

		for (size_t i = indice; i < rep->nb_elts - 1; i++)
		{
			rep->tab[i] = rep->tab[i + 1];
		}

		rep->nb_elts -= 1;
		modif = true;
	}

	return;
} /* fin supprimer */

#else
#ifdef IMPL_LIST
  /************************************************************************/
  /* supprime du répertoire l'enregistrement contenu dans le maillon elem */
  /*                   et fixe modif à vrai                              */
  /************************************************************************/
  // complet

int supprimer_un_contact_dans_rep_liste(Repertoire* rep, SingleLinkedListElem* elem) {

	int ret = DeleteLinkedListElem(rep->liste, elem);
	if (ret == 1) {
		rep->nb_elts--;
		modif = true;
	}

	return (0);
}
#endif
#endif


/**********************************************************************/
/*  fonction d'affichage d'un enregistrement sur une ligne à l'écran  */
/* ex Dupont, Jean                 0320304050                         */
/**********************************************************************/
void affichage_enreg(Enregistrement enr)
{
	printf("%s, %s		%s\n", enr.nom, enr.prenom, enr.tel);

} /* fin affichage_enreg */
  /**********************************************************************/
  /*  fonction d'affichage d'un enregistrement avec alignement des mots */
  /* pour les listes                                                    */
  /* ex | Dupont                |Jean                  |0320304050      */
  /**********************************************************************/
void affichage_enreg_frmt(Enregistrement enr)
{
	// code à compléter ici
	// comme fonction affichage_enreg, mais avec présentation alignées des infos

	int espaceM = 30;
	int espace;
	int caracNom = strlen(enr.nom);
	int caracPrenom = strlen(enr.prenom);
	int caracTel = strlen(enr.tel);

	printf("|%s", enr.nom);

	espace = espaceM - caracNom;

	for (int i = 0; i < espace; i++)
	{
		printf(" ");
	}

	printf("|%s", enr.prenom);

	espace = espaceM - caracPrenom;

	for (int i = 0; i < espace; i++)
	{
		printf(" ");
	}

	printf("|%s", enr.tel);

	espace = espaceM - caracTel;

	for (int i = 0; i < espace; i++)
	{
		printf(" ");
	}

	printf("\n");



} /* fin affichage_enreg */


  /**********************************************************************/
  /* test si dans l'ordre alphabetique, un enregistrement est apres     */
  /* un autre                                                           */
  /**********************************************************************/
bool est_sup(Enregistrement enr1, Enregistrement enr2)
{
	// code à compléter ici

	int resultNom = strcmp(enr1.nom, enr2.nom);
	int resultPrenom = strcmp(enr1.prenom, enr2.prenom);

	if (resultNom < 0)
	{
		return true;
	}
	else if (resultNom == 0)
	{
		if (resultPrenom < 0)
		{
			return true;
		}
	}


	


	return(false);

}

/*********************************************************************/
/*   Tri Alphabetique du tableau d'enregistrements                   */
/*********************************************************************/

void trier(Repertoire* rep)
{

#ifdef IMPL_TAB
	// ajouter code ici pour tableau

	Enregistrement temp;
	for (int i = 0; i < rep->nb_elts; i++)
	{
		for (int j = 0; j < rep->nb_elts; j++) {
			if (est_sup(rep->tab[i], rep->tab[j]) == true)
			{
				temp = rep->tab[i];
				rep->tab[i] = rep->tab[j];
				rep->tab[j] = temp;
			}
		}
	}

#else
#ifdef IMPL_LIST
	// ajouter code ici pour Liste
	// la liste est toujours triée
#endif
#endif


	rep->est_trie = true;

} /* fin trier */

  /**********************************************************************/
  /* recherche dans le répertoire d'un enregistrement correspondant au  */
  /*   nom à partir de l'indice ind                                     */
  /*   retourne l'indice de l'enregistrement correspondant au critère ou*/
  /*   un entier négatif si la recherche est négative				    */
  /**********************************************************************/

int rechercher_nom(Repertoire* rep, char nom[], int ind)
{
	int i = ind;						/* position (indice) de début de recherche dans tableau/liste rep */
	int ind_fin = rep->nb_elts;			/* position (indice) de fin de tableau/liste rep */

	char tmp_nom[MAX_NOM];					/* 2 variables temporaires dans lesquelles */
	char tmp_nom2[MAX_NOM];					/* on place la chaine recherchee et la chaine lue dans le */
											/* tableau, afin de les convertir en majuscules et les comparer */
	bool trouve = false;

	
	for (int j = 0; j < MAX_NOM; j++)
	{
		tmp_nom[j] = toupper(nom[j]);
	}


#ifdef IMPL_TAB
	// ajouter code ici pour tableau

	bool continu = true;

	while (i < ind_fin && continu == true)
	{

		for (int o = 0; o < MAX_NOM; o++)
		{
			tmp_nom2[o] = toupper(rep->tab[i].nom[o]);
		}

		if (strcmp(tmp_nom, tmp_nom2) == 0)
		{
			trouve = true;
			continu = false;
		}
		else {
			i++;
		}
	}

#else
#ifdef IMPL_LIST
	// ajouter code ici pour Liste

	
	bool continu = true;

	ind_fin = rep->liste->size;
	SingleLinkedListElem* tmp = rep->liste->head;
	int j = 0;

	for (size_t k = 0; k <= i; k++)
	{
		tmp = &tmp->next;
	}

	while (i < ind_fin && continu == true) {

		strncpy_s(tmp_nom2, _countof(tmp_nom2), GetElementAt(rep->liste, i)->pers.nom, _TRUNCATE);
		_strupr_s(tmp_nom2, strlen(tmp_nom) + 1);

		if (strcmp(tmp_nom, tmp_nom2) == 0)
		{
			trouve = true;
			continu = false;
		}
		else {
			tmp = &tmp->next;
			i++;
		}

	}

	

#endif
#endif

	return((trouve) ? i : -1);
} /* fin rechercher_nom */

  /*********************************************************************/
  /* Supprimer tous les caracteres non numériques de la chaines        */
  /*********************************************************************/
void compact(char* s)
{
	// compléter code ici

	

	int i = 0;

	while (s[i] != '\0') {

		if (isalpha(s[i]) == 0)
		{
			for (size_t j = i; j < MAX_NOM; j++)
			{
				s[j] = s[j + 1];
			}
		}
		else {
			i++;
		}
	}

	

	return;
}

/**********************************************************************/
/* sauvegarde le répertoire dans le fichier dont le nom est passé en  */
/* argument                                                           */
/* retourne OK si la sauvegarde a fonctionné ou ERROR sinon           */
/**********************************************************************/
int sauvegarder(Repertoire* rep, char nom_fichier[])
{
	FILE* fic_rep;					/* le fichier */
#ifdef IMPL_TAB
	// ajouter code ici pour tableau

	

	if (fopen_s(&fic_rep, nom_fichier, "w") != 0 || fic_rep == NULL)
	{
		return ERROR;
	}

	for (size_t i = 0; i < rep->nb_elts; i++)
	{
		fprintf(fic_rep, "%s", rep->tab[i].nom);
		fprintf(fic_rep, "%c", SEPARATEUR);
		fprintf(fic_rep, "%s", rep->tab[i].prenom);
		fprintf(fic_rep, "%c", SEPARATEUR);
		fprintf(fic_rep, "%s\n", rep->tab[i].tel);
	}

	if (feof(fic_rep))
	{
		fclose(fic_rep);
	}


	

#else
#ifdef IMPL_LIST
	// ajouter code ici pour Liste

	if (fopen_s(&fic_rep, nom_fichier, "w") != 0 || fic_rep == NULL)
	{
		return ERROR;
	}

	for (size_t i = 0; i < rep->nb_elts; i++)
	{
		fprintf(fic_rep, "%s", GetElementAt(rep->liste, i)->pers.nom);
		fprintf(fic_rep, "%c", SEPARATEUR);
		fprintf(fic_rep, "%s", GetElementAt(rep->liste, i)->pers.prenom);
		fprintf(fic_rep, "%c", SEPARATEUR);
		fprintf(fic_rep, "%s\n", GetElementAt(rep->liste, i)->pers.tel);
	}

	if (feof(fic_rep))
	{
		fclose(fic_rep);
	}

#endif
#endif

	return(OK);
} /* fin sauvegarder */


  /**********************************************************************/
  /*   charge dans le répertoire le contenu du fichier dont le nom est  */
  /*   passé en argument                                                */
  /*   retourne OK si le chargement a fonctionné et ERROR sinon         */
  /**********************************************************************/

int charger(Repertoire* rep, char nom_fichier[])
{
	FILE* fic_rep;					/* le fichier */
	errno_t err;
	int num_rec = 0;						/* index sur enregistrements */
	int long_max_rec = sizeof(Enregistrement);
	char buffer[sizeof(Enregistrement) + 1];
	int idx = 0;

	char* char_nw_line;

	_set_errno(0);
	if (((err = fopen_s(&fic_rep, nom_fichier, "r")) != 0) || (fic_rep == NULL))
	{
		return(err);
	}
	else
	{
		while (!feof(fic_rep) && (rep->nb_elts < MAX_ENREG))
		{
			if (fgets(buffer, long_max_rec, fic_rep) != NULL)
			{
				/* memorisation de l'enregistrement lu dans le tableau */
				buffer[long_max_rec] = 0;			/* en principe il y a deja un fin_de_chaine, cf fgets */

				if ((char_nw_line = strchr(buffer, '\n')) != NULL)
					*char_nw_line = '\0';			/* suppression du fin_de_ligne eventuel */

				idx = 0;								/* analyse depuis le debut de la ligne */
#ifdef IMPL_TAB
				if (lire_champ_suivant(buffer, &idx, rep->tab[num_rec].nom, MAX_NOM, SEPARATEUR) == OK)
				{
					idx++;							/* on saute le separateur */
					if (lire_champ_suivant(buffer, &idx, rep->tab[num_rec].prenom, MAX_NOM, SEPARATEUR) == OK)
					{
						idx++;
						if (lire_champ_suivant(buffer, &idx, rep->tab[num_rec].tel, MAX_TEL, SEPARATEUR) == OK)
							num_rec++;		/* element à priori correct, on le comptabilise */
					}
				}
#else
#ifdef IMPL_LIST
														// ajouter code implemention liste

				

				SingleLinkedListElem* tmp = rep->liste->head;

				if (lire_champ_suivant(buffer, &idx, tmp->pers.nom, MAX_NOM, SEPARATEUR) == OK)
				{
					idx++;
					if (lire_champ_suivant(buffer, &idx, tmp->pers.prenom, MAX_NOM, SEPARATEUR) == OK)
					{
						idx++;
						if (lire_champ_suivant(buffer, &idx, tmp->pers.tel, MAX_NOM, SEPARATEUR) == OK)
						{
							tmp = tmp->next;
						}
					}
				}

				
#endif
#endif




			}

		}
		rep->nb_elts = num_rec;
		fclose(fic_rep);
		return(OK);
	}


} /* fin charger */