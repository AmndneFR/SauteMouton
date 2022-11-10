#include <stdio.h>
#include <stdlib.h>

const char MOUTON1 = '>';
const char MOUTON2 = '<';
const char VIDE = ' ';

void initialisation(char t[], int dim)// Initialise le plateau de jeu au début
{
	int i;
	for (i = 0; i < dim/2; i++)
	{
		t[i] = MOUTON1;
	}
	for (i = dim/2+1; i <= dim-1; i++)
	{
		t[i] = MOUTON2;
	}
	t[dim / 2] = VIDE;
}

void affichage(char t[], int dim)// Affiche le plateau de jeu
{
	int i;
	
	for (i = 0; i < dim; i++)
	{
		printf(" %d", i);
	}
	printf("\n");

	printf("|");
	for (i = 0; i < dim; i++)
	{
		printf("%c|", t[i]);
	}
	printf("\n");
}

void mouvement(char t[], int dim)
{
	int x;
	do
	{
		printf("\nQuel pion voulez-vous deplacer? \n");
		scanf_s("%d", &x);
	} while (x<0 || x>dim);

	if (t[x]==MOUTON1)
	{
		if (x + 1 < dim && t[x + 1] == VIDE)
		{
			t[x + 1] = t[x];
			t[x] = VIDE;
		}
		else
		{
			if (x + 2 < dim && t[x+1] == MOUTON2 && t[x + 2] == VIDE)
			{
				t[x + 2] = t[x];
				t[x] = VIDE;
			}
			else
			{
				printf("\nMouvement imposible\n");
			}
		}
	}
	else
	{
		if (t[x]==MOUTON2)
		{
			if (x - 1 >= 0 && t[x - 1] == VIDE)
			{
				t[x - 1] = t[x];
				t[x] = VIDE;
			}
			else
			{
				if (x - 2 >= 0 && t[x - 1] == MOUTON1 && t[x - 2]==VIDE)
				{
					t[x - 2] = t[x];
					t[x] = VIDE;
				}
				else
				{
					printf("\nMouvement imposible\n");
				}
			}
		}
		else
		{
			printf("\nPas de mouvement\n");
		}
	}
}

int gagnant(char t[], int dim)
{
	int i, x, y;
	int gain = 0; //Si gain = 0 gagnant sinon perdu

	// On verifie si la partie est gagnee sinon elle continue
	for (i = 0; i < dim/2; i++)
	{
		if (t[i] == MOUTON2)
		{
			gain = gain + 0;
		}
		else
		{
			gain = gain + 1;
		}
	}
	for (i = dim / 2 + 1; i < dim; i++)
	{
		if (t[i]==MOUTON1)
		{
			gain = gain + 0;
		}
		else
		{
			gain = gain + 1;
		}
	}
	if (t[dim / 2] != VIDE)
	{
		gain = gain + 1;
	}
	if (gain == 0)
	{
		return gain;
	}

	// On verifie si la partie est perdue sinon elle continue
	for (i = 0; i < dim-1; i++) //On s'arrete a i = 5
	{
		x = i - 1;
		y = i + 2;

		//On verifie que les bornes ne sont pas depassee
		if (x < 0)
		{
			x = 0;
		}
		if (y > dim - 1)
		{
			y = dim - 1;
		}

		//On compare à la combinaison est perdante
		if (t[x]==MOUTON1 && t[i]==MOUTON1 && t[i+1]==MOUTON2 && t[y]==MOUTON2)
		{
			gain = -1;
		}
	}

	return gain;
}



int main(int argc, char* argv[])
{
	const int TAILLE = 7;
	char plateau[7];
	int gagne, perdu=0;

	// initialisation du plateau
	initialisation(plateau, TAILLE);

	printf("Bienvenue dans le jeu du Saute Mouton\n"
		"Le but : Passer chaque mouton de l'autre cote\n"
		"3 regles :\n"
		"- Un mouton ne peut pas reculer\n"
		"- Un mouton avance d'un cran si la place est libre\n"
		"- Un mouton saute par dessus un autre s'il va dans l'autre sens et si la case derriere est libre\n\n");

	do
	{
	// affichage du plateau de jeu
	affichage(plateau, TAILLE);

	// demande et execute un mouvement
	mouvement(plateau, TAILLE);

	// vérifie si la partie est gagnante, si elle est perdante ou si elle continue
	gagne = gagnant(plateau, TAILLE);

	} while (gagne != 0 && gagne !=-1);

	if (gagne == 0)
	{
		affichage(plateau, TAILLE);
		printf("\nBravo vous avez reussi\n");
	}
	else
	{
		affichage(plateau, TAILLE);
		printf("\nVous avez bloque des moutons, le jeu est perdu\n");
	}
}