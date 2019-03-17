#include <iostream>
#include <string>
using namespace std;

class Timbre
{
private:
  static constexpr unsigned int ANNEE_COURANTE = 2016;

  /*****************************************************
   * Compléter le code à partir d'ici
   *****************************************************/
  string nom;
	unsigned int annee;
	string pays;
	double valeur_faciale;

public:
  /**
   * Superclass constructor
   */ 
  Timbre(string code, unsigned int issue_year, string country = "Suisse", double denomination_value = 1.0)
    : nom(code), annee(issue_year), pays(country), valeur_faciale(denomination_value) {}
  
  /**
   * Determine the selling price of a stamp
   */ 
  double vente() const
  {
    return ((age() < 5U) ? valeur_faciale : (valeur_faciale * static_cast<double>(age()) * 2.5));
  }
  
  /**
   * Determine the current age of a stamp
   */ 
  unsigned int age() const { return (ANNEE_COURANTE - annee); }

  /**
   * Display basic information of a stamp
   */ 
  ostream& afficher(ostream& sortie) const
  {
    sortie << "de nom " << nom << " datant de " << annee << " (provenance " << pays << ") ayant pour valeur faciale " << valeur_faciale << " francs";
    return sortie;
  }
};

class Rare : public Timbre
{
  private:
    static constexpr unsigned int PRIX_BASE_TRES_RARE = 600U;
    static constexpr unsigned int PRIX_BASE_RARE = 400U;
    static constexpr unsigned int PRIX_BASE_PEU_RARE = 50U;
    unsigned int exemplaires;

  public:
    /**
     * Subclass constructor
     */
    Rare(string code, unsigned int issue_year, string country, double denomination_value, unsigned int copies = 100U)
      : Timbre(code, issue_year, country, denomination_value), exemplaires(copies) {} 
    
    /**
     * Determine the selling price of a rare stamp
     */ 
    double vente() const
    {
      unsigned int prix_base(0U);
      if(exemplaires < 100U)
      {
        prix_base = PRIX_BASE_TRES_RARE;
      }
      else if((100U <= exemplaires) && (exemplaires <= 1000U))
      {
        prix_base = PRIX_BASE_RARE;
      }
      else
      {
        prix_base = PRIX_BASE_PEU_RARE;
      }
      return (static_cast<double>(prix_base) * (static_cast<double>(age()) / 10.0));
    }
    
    /**
     * Access the number of stamp copies
     */
    unsigned int nb_exemplaires() const { return exemplaires; }
};

class Commemoratif : public Timbre
{
  public:
    /**
     * Subclass constructor
     */
    Commemoratif(string code, unsigned int issue_year, string country, double denomination_value)
      : Timbre(code, issue_year, country, denomination_value) {}

    /**
     * Determine the selling price of a commemorative stamp
     */ 
    double vente() const
    {
      return (2.0 * Timbre::vente());
    }
};

ostream& operator<<(ostream& sortie, Timbre const& stamp)
{
	sortie << "Timbre ";
	return stamp.afficher(sortie);
}

ostream& operator<<(ostream& sortie, Rare const& stamp)
{
	sortie << "Timbre rare (" << stamp.nb_exemplaires() << " ex.) ";
	return stamp.afficher(sortie);
}

ostream& operator<<(ostream& sortie, Commemoratif const& stamp)
{
	sortie << "Timbre commémoratif ";
	return stamp.afficher(sortie);
}

/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/
int main()
{
  /* Ordre des arguments :
  *  nom, année d'émission, pays, valeur faciale, nombre d'exemplaires
  */
  Rare t1( "Guarana-4574", 1960, "Mexique", 0.2, 98 );
  Rare t2( "Yoddle-201"  , 1916, "Suisse" , 0.8,  3 );

  /* Ordre des arguments :
  *  nom, année d'émission, pays, valeur faciale, nombre d'exemplaires
  */
  Commemoratif t3( "700eme-501"  , 2002, "Suisse", 1.5 );
  Timbre       t4( "Setchuan-302", 2004, "Chine" , 0.2 );

  /* Nous n'avons pas encore le polymorphisme :-(
   * (=> pas moyen de faire sans copie ici :-( )  */
  cout << t1 << endl;
  cout << "Prix vente : " << t1.vente() << " francs" << endl;
  cout << t2 << endl;
  cout << "Prix vente : " << t2.vente() << " francs" << endl;
  cout << t3 << endl;
  cout << "Prix vente : " << t3.vente() << " francs" << endl;
  cout << t4 << endl;
  cout << "Prix vente : " << t4.vente() << " francs" << endl;

  return 0;
}
