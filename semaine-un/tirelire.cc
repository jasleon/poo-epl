#include <iostream>
using namespace std;

/*******************************************
 * Complétez le programme à partir d'ici.
 *******************************************/
class Tirelire
{
	private:
		double montant;
	public:
		double getMontant() const{ return montant; };
		void afficher()
		{
			if(montant == 0.0) cout << "Vous etes sans le sou." << endl;
			else cout << "Vous avez : " << montant << " euros dans votre tirelire." << endl;
		};
		void secouer()
		{
			if(montant > 0) cout << "Bing bing" << endl;
		};
		void remplir(double pieces)
		{
			if(pieces > 0) montant += pieces;
		};
		void vider(){ montant = 0.0; };
		void puiser(double casser)
		{
			if(casser > montant) vider();
			else if(casser <= montant && casser > 0) montant -= casser; 
		};
		bool montant_suffisant(double budget, double& solde)
		{
			if(budget <= 0)
			{
				solde = montant;
				return true;
			}
			else
			{
				if(budget <= montant)
				{
					solde = montant - budget;
					return true; 
				}
				else
				{
					solde = budget - montant;
					return false;
				}
			}
		};
		double calculerSolde(double budget)
		{
			if(budget <= 0) return montant;
			else return (montant - budget);
		};
};
/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

int main()
{
  Tirelire piggy;

  piggy.vider();
  piggy.secouer();
  piggy.afficher();

  piggy.puiser(20.0);
  piggy.secouer();
  piggy.afficher();

  piggy.remplir(550.0);
  piggy.secouer();
  piggy.afficher();

  piggy.puiser(10.0);
  piggy.puiser(5.0);
  piggy.afficher();

  cout << endl;

  // le budget de vos vacances de rève.
  double budget;

  cout << "Donnez le budget de vos vacances : ";
  cin >> budget;

  // ce qui resterait dans la tirelire après les
  // vacances
  double solde(0.0);

  if (piggy.montant_suffisant(budget, solde)) {
    cout << "Vous êtes assez riche pour partir en vacances !"
         << endl
         << "Il vous restera " << solde << " euros"
         << " à la rentrée." << endl << endl;
    piggy.puiser(budget);
  } else {
    cout << "Il vous manque " << solde << " euros"
         << " pour partir en vacances !" << endl << endl;
  }
  return 0;
}
