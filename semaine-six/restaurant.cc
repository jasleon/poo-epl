#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

/*****************************************************
  * Compléter le code à partir d'ici
 *****************************************************/
class Produit
{
  private:
    string nom;
    string unite;
  
  public:
    
    /**
     * Superclass constructor
     */ 
    Produit(string name, string unit = "") : nom(name), unite(unit) {}

    /**
     * This method returns the name of the product
     */ 
    string getNom() const { return nom; }

    /**
     * This method returns the units of the product
     */ 
    string getUnite() const { return unite; }

    /**
     * This method returns the name of the product without any change
     */ 
    virtual string toString() const { return nom; }
};

class Ingredient
{
  private:
    Produit produit;
    double quantite;
  
  public:
    
    /**
     * Class constructor
     */ 
    Ingredient(const Produit& product, double quantity) : produit(product), quantite(quantity) {}

    /**
     * This method returns a constant reference to the ingredient's product
     */ 
    const Produit& getProduit() const { return produit; }

    /**
     * This method returns the quantity of the ingredient
     */ 
    double getQuantite() const { return quantite; }

    /**
     * This method is a bit complex
     */ 
    string descriptionAdaptee() const
    {
      return string(to_string(getQuantite()) + " " + produit.getUnite() + " de " + produit.toString());
    }
};

class Recette
{
  private:
    string nom;
    double nbFois_;
    vector<Ingredient> liste;

  public:
    
    Recette(string name, double replication = 1.0 ) : nom(name), nbFois_(replication) {}

    void ajouter(const Produit& p, double quantite) 
    {
      liste.push_back(Ingredient(p, quantite * nbFois_));
    }

    // Recette adapter(double n) { return Recette(""); }

    string toString() const
    {
      cout << "Recette \"" << nom << "\" x " << nbFois_ << ":" << endl;
      unsigned int nombre(1U);
      for(auto i : liste)
      {
        cout << nombre++ << ". ";
        i.descriptionAdaptee();
      }
    }
};

class ProduitCuisine : public Produit
{
  private:
    Recette r;
  public:
    
    ProduitCuisine(string name, string portion = "") : Produit(name, portion), r(name) {}
    
    void ajouterARecette(const Produit& produit, double quantite)
    {
      r.ajouter(produit, quantite);
    }

    string toString() const override
    {
      return "helloWorld";
    }
};

/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/
/* void afficherQuantiteTotale(const Recette& recette, const Produit& produit)
{
  string nom = produit.getNom();
  cout << "Cette recette contient " << recette.quantiteTotale(nom)
       << " " << produit.getUnite() << " de " << nom << endl;
} */

/* int main()
{
  // quelques produits de base
  Produit oeufs("oeufs");
  Produit farine("farine", "grammes");
  Produit beurre("beurre", "grammes");
  Produit sucreGlace("sucre glace", "grammes");
  Produit chocolatNoir("chocolat noir", "grammes");
  Produit amandesMoulues("amandes moulues", "grammes");
  Produit extraitAmandes("extrait d'amandes", "gouttes");

  ProduitCuisine glacage("glaçage au chocolat");
  // recette pour une portion de glaçage:
  glacage.ajouterARecette(chocolatNoir, 200);
  glacage.ajouterARecette(beurre, 25);
  glacage.ajouterARecette(sucreGlace, 100);
  cout << glacage.toString() << endl;

  ProduitCuisine glacageParfume("glaçage au chocolat parfumé");
  // besoin de 1 portions de glaçage au chocolat et de 2 gouttes
  // d'extrait d'amandes pour 1 portion de glaçage parfumé

  glacageParfume.ajouterARecette(extraitAmandes, 2);
  glacageParfume.ajouterARecette(glacage, 1);
  cout << glacageParfume.toString() << endl;

  Recette recette("tourte glacée au chocolat");
  recette.ajouter(oeufs, 5);
  recette.ajouter(farine, 150);
  recette.ajouter(beurre, 100);
  recette.ajouter(amandesMoulues, 50);
  recette.ajouter(glacageParfume, 2);

  cout << "===  Recette finale  =====" << endl;
  cout << recette.toString() << endl;
  afficherQuantiteTotale(recette, beurre);
  cout << endl;

  // double recette
  Recette doubleRecette = recette.adapter(2);
  cout << "===  Recette finale x 2 ===" << endl;
  cout << doubleRecette.toString() << endl;

  afficherQuantiteTotale(doubleRecette, beurre);
  afficherQuantiteTotale(doubleRecette, oeufs);
  afficherQuantiteTotale(doubleRecette, extraitAmandes);
  afficherQuantiteTotale(doubleRecette, glacage);
  cout << endl;

  cout << "===========================\n" << endl;
  cout << "Vérification que le glaçage n'a pas été modifié :\n";
  cout << glacage.toString() << endl;

  return 0;
} */
