#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*******************************************
 * Completez le programme a partir d'ici.
 *******************************************/
// Chaines de caractères à utiliser pour les affichages:
/*

été jeté

d'un

n'est

L'oeuvre

bibliothèque

détruit

*/

class Auteur
{
	private:
		string nom;
		bool prime;
	public:
		Auteur(string nom, bool prime = false)
		: nom(nom), prime(prime)
		{}
		Auteur(Auteur const&) = delete;
		string getNom() const { return nom; }
		bool getPrix() const { return prime; }
};

class Oeuvre
{
	private:
		string titre;
		Auteur const& ecrivain;
		string langue;
	public:
		Oeuvre(string titre, Auteur const& ecrivain, string langue)
		: titre(titre), ecrivain(ecrivain), langue(langue)
		{}
		Oeuvre(Oeuvre const&) = delete;
		~Oeuvre()
		{
			cout << "L'oeuvre \"" << titre << ", " << ecrivain.getNom() << ", en " << langue << "\" n'est plus disponible" << endl;
		}
		string getTitre() const { return titre; }
		Auteur const& getAuteur() const { return ecrivain; }
		string getLangue() const { return langue; }
		void affiche() const 
		{
			cout << titre << ", " << ecrivain.getNom() << ", en " << langue << endl;
		}
};

class Exemplaire
{
	private:
		Oeuvre const& creation;
	public:
		Exemplaire(Oeuvre const& creation)
		: creation(creation)
		{
			cout << "Nouvel exemplaire de : ";
			creation.affiche();
		}
		Exemplaire(Exemplaire const& _other)
		: creation(_other.creation)
		{
			cout << "Copie d'un exemplaire de : ";
			_other.affiche();
		}
		~Exemplaire()
		{
			cout << "Un exemplaire de \"";
			creation.affiche();
			cout << "\" a été jeté !" << endl;
		}
		Oeuvre const& getOeuvre() const { return creation; }
		void affiche() const
		{
			cout << "Exemplaire de : " << creation.getTitre() << ", " << creation.getAuteur().getNom() << ", en " << creation.getLangue();
		}
};

//class Bibliotheque
//{
	//private:
		//string nom;
		//vector<Exemplaire *> ensemble;
	//public:
		//Bibliotheque() { cout << "La bibliothèque " << nom << "est ouverte !" << endl; }
		//string getNom() const { return nom; }
		//void stocker(Oeuvre const& creation, int n = 1)
		//{
			//while( n != 0 )
			//{
				//ensemble.push_back(creation);
				//--n;
			//}
		//}
//};
/*******************************************
 * Ne rien modifier apres cette ligne.
 *******************************************/

int main()
{
  Auteur a1("Victor Hugo"),
         a2("Alexandre Dumas"),
         a3("Raymond Queneau", true);

  Oeuvre o1("Les Misérables"           , a1, "français" ),
         o2("L'Homme qui rit"          , a1, "français" ),
         o3("Le Comte de Monte-Cristo" , a2, "français" ),
         o4("Zazie dans le métro"      , a3, "français" ),
         o5("The Count of Monte-Cristo", a2, "anglais" );

  //Bibliotheque biblio("municipale");
  //biblio.stocker(o1, 2);
  //biblio.stocker(o2);
  //biblio.stocker(o3, 3);
  //biblio.stocker(o4);
  //biblio.stocker(o5);

  //cout << "La bibliothèque " << biblio.getNom()
       //<< " offre les exemplaires suivants :" << endl;
  //biblio.lister_exemplaires();

  //const string langue("anglais");
  //cout << " Les exemplaires en "<< langue << " sont :" << endl;
  //biblio.lister_exemplaires(langue);

  //cout << " Les auteurs à succès sont :" << endl;
  //biblio.afficher_auteurs(true);

  //cout << " Il y a " << biblio.compter_exemplaires(o3) << " exemplaires de "
       //<< o3.getTitre() << endl;

  //return 0;
}
