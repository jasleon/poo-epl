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

ostream& operator<<(ostream& sortie, Brique const& brique_)
{
  return brique_.afficher(sortie);
}

class Construction
{
  friend class Grader;

  private:
    vector<vector<vector<Brique>>> contenu;

  public:
    
    Construction(const Brique& brique) : contenu({{{brique}}}) {}

    ostream& afficher(ostream& sortie) const
    {
      if (!contenu.empty())
      {
        const int couches = static_cast<int>(contenu.size()) - 1;
        for(int height = couches; 0 <= height; height--)
        {
          sortie << "Couche " << height << " :\n";
          for(size_t depth = 0U; depth < contenu[height].size(); depth++)
          {
            for(size_t width = 0U; width < contenu[height][depth].size(); width++)
            {
              sortie << contenu[height][depth][width] << "\n";
            }
          }
        }
      }
      return sortie;
    }

    void ajouter(vector<vector<Brique>> const& couche)
    {
      contenu.push_back(couche);
    }

    vector<vector<Brique>> obtenir(const size_t couche_id) const
    {
      return contenu[couche_id];
    }

    Construction& operator^=(Construction const& batiment)
    {
      for(size_t height = 0U; height < batiment.contenu.size(); height++)
      {
        this->contenu.push_back(batiment.contenu[height]);
      }
      return *this;
    }

    Construction& operator-=(Construction const& batiment)
    {
      if (this->contenu.size() > batiment.contenu.size())
      {
        for(size_t height = 0U; height < batiment.contenu.size(); height++)
        {
          for(size_t depth = 0U; depth < batiment.contenu[height].size(); depth++)
          {
            this->contenu[height].push_back(batiment.contenu[height][depth]);
          }
        }
      }
      return *this;
    }
};

ostream& operator<<(ostream& sortie, Construction const& construction_)
{
  return construction_.afficher(sortie);
}

// const Construction operator^(Construction a, Construction const& b)
// {
//   a.ajouter(b.obtenir(0U));
//   return a;
// }

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
