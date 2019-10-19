#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Pour simplifier
typedef string Forme   ;
typedef string Couleur ;

class Brique
{
private:
  Forme   forme   ;
  Couleur couleur ;

public:
  /*****************************************************
    Compléter le code à partir d'ici
  *******************************************************/
  Brique(Forme shape, Couleur color) : forme(shape), couleur(color) {}

  /**
   * This method prints the object in the format "(shape, color)"
   */
  ostream& afficher(ostream& sortie) const
  {
    if (couleur.empty())
    {
      sortie << forme;
    }
    else
    {
      sortie << "(" << forme << ", " << couleur << ")";
    }
    return sortie;
  }

private:
  
  Brique() {}
};

ostream& operator<<(ostream& sortie, Brique const& brique)
{
  return brique.afficher(sortie);
}

// class Construction
// {
//   friend class Grader;

// };

// const Construction operator*(unsigned int n, Construction const& a)
// {
// }

// const Construction operator/(unsigned int n, Construction const& a)
// {
// }

// const Construction operator%(unsigned int n, Construction const& a)
// {
// }

/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

int main()
{
  // Modèles de briques
  Brique toitD("obliqueD", "rouge");
  Brique toitG("obliqueG", "rouge");
  Brique toitM(" pleine ", "rouge");
  Brique mur  (" pleine ", "blanc");
  Brique vide ("                 ", "");

  // unsigned int largeur(4);
  // unsigned int profondeur(3);
  // unsigned int hauteur(3); // sans le toit

  // // on construit les murs
  // Construction maison( hauteur / ( profondeur % (largeur * mur) ) );

  // // on construit le toit
  // Construction toit(profondeur % ( toitG + 2*toitM + toitD ));
  // toit ^= profondeur % (vide + toitG + toitD);

  // // on pose le toit sur les murs
  // maison ^= toit;

  // // on admire notre construction
  // cout << maison << endl;

  return 0;
}
