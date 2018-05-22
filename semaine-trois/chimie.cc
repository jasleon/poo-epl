#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class Flacon
{
private:
  string nom;
  double volume;
  double pH;

public:
  /*****************************************************
    Compléter le code à partir d'ici
  *******************************************************/
  Flacon(string nom, double volume, double pH)
  : nom(nom), volume(volume), pH(pH)
  {}
  string getNom() const { return nom; }
  double getVolume() const { return volume; }
  double getPH() const { return pH; }
  ostream& etiquette(ostream& sortie) const
  {
	  sortie << getNom() << " : " << static_cast<long>(getVolume()) << " ml, pH " << getPH();
	  return sortie;
  }
};
ostream& operator<<(ostream& sortie, Flacon const& flask)
{
	return flask.etiquette(sortie);
}
const Flacon operator+(Flacon f1, Flacon const& f2)
{
	const string nom1(f1.getNom());
	const string nom2(f2.getNom());
	const double volume1(f1.getVolume());
	const double volume2(f2.getVolume());
	const string nom3(nom1 + " + " + nom2);
	const double volume3(volume1 + volume2);
	const double pH1(f1.getPH());
	const double pH2(f2.getPH());
	const double pH3(-log10((volume1*pow(10.0, -pH1) + volume2*pow(10.0, -pH2))/(volume1 + volume2)));
	Flacon f3(nom3, volume3, pH3);
	return f3;
}
/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

void afficher_melange(Flacon const& f1, Flacon const& f2)
{
  cout << "Si je mélange " << endl;
  cout << "\t\"" << f1 << "\"" << endl;
  cout << "avec" << endl;
  cout << "\t\"" << f2 << "\"" << endl;
  cout << "j'obtiens :" << endl;
  cout << "\t\"" << (f1 + f2) << "\"" << endl;
}

int main()
{
  Flacon flacon1("Eau", 600.0, 7.0);
  Flacon flacon2("Acide chlorhydrique", 500.0, 2.0);
  Flacon flacon3("Acide perchlorique",  800.0, 1.5);

  afficher_melange(flacon1, flacon2);
  afficher_melange(flacon2, flacon3);

  return 0;

}
