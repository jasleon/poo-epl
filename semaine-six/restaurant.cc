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
    Produit(string nom, string unite = "") : nom(nom), unite(unite) {}

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

    /**
     * This method returns the current object
     */ 
    virtual const Produit* adapter(double n = 0.0) const { return (this); }
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
    Ingredient(const Produit& produit, double quantite) : produit(produit), quantite(quantite) {}

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
      // return string(to_string(getQuantite()) + " " + produit_ptr->getUnite() + " de " + produit_ptr->toString());
      return "";
    }
};

class Recette
{
  private:
    string nom;
    double nbFois_;
    vector<Ingredient> liste;

  public:
    
    /**
     * Superclass constructor
     */ 
    Recette(string nom, double replication = 1.0 ) : nom(nom), nbFois_(replication) {}

    /**
     * This method constructs an ingredient based on the given parameters, and adds it to the ingredient list of the recipe
     */ 
    void ajouter(const Produit& p, double quantite) 
    {
      liste.push_back(Ingredient(p, quantite * nbFois_));
    }

    /**
     * This method returns a new recipe corresponding to the current recipe replicated n times
     */ 
    Recette adapter(double n)
    {
      Recette duplicate(nom, n);
      for(auto i : liste)
      {
        double quantite = (i.getQuantite() / nbFois_);
        duplicate.ajouter(i.getProduit(), quantite);
      }
      return duplicate;
    }
    
    /**
     * This method produces a string representation of this recipe
     */ 
    string toString() const
    {
      string description("Recette \"" + nom + "\" x " + to_string(nbFois_) + ":\n");
      const size_t ingredientSize(liste.size()); 
      size_t nombre(1U);
      for(auto i : liste)
      {
        const string tail((nombre < ingredientSize) ? "\n" : "");
        description.append(to_string(nombre++) + ". " + i.descriptionAdaptee() + tail);
      }
      return description;
    }
};

class ProduitCuisine : public Produit
{
  private:
    Recette recette;

  public:
    
    /**
     * Subclass constructor
     */ 
    ProduitCuisine(string nom, string unite = "portion(s)") : Produit(nom, unite), recette(nom) {}
    
    /**
     * A method to add an ingredient to the product's recipe
     */ 
    void ajouterARecette(const Produit& produit, double quantite)
    {
      recette.ajouter(produit, quantite);
    }

    /**
     * A method to produce a representation in a specific format
     */ 
    string toString() const override
    {
      return (Produit::toString() + '\n' + recette.toString());
    }

    /**
     * This method returns a pointer to a new cooked product corresponding to the current product 
     * whose recipe has been adapted n times
     */ 
    // virtual const ProduitCuisine* adapter(double n) const override { return (this); }
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

int main()
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

  // Recette recette("tourte glacée au chocolat");
  // recette.ajouter(oeufs, 5);
  // recette.ajouter(farine, 150);
  // recette.ajouter(beurre, 100);
  // recette.ajouter(amandesMoulues, 50);
  // recette.ajouter(glacageParfume, 2);

  // cout << "===  Recette finale  =====" << endl;
  // cout << recette.toString() << endl;
  // afficherQuantiteTotale(recette, beurre);
  // cout << endl;

  // // double recette
  // Recette doubleRecette = recette.adapter(2);
  // cout << "===  Recette finale x 2 ===" << endl;
  // cout << doubleRecette.toString() << endl;

  // afficherQuantiteTotale(doubleRecette, beurre);
  // afficherQuantiteTotale(doubleRecette, oeufs);
  // afficherQuantiteTotale(doubleRecette, extraitAmandes);
  // afficherQuantiteTotale(doubleRecette, glacage);
  // cout << endl;

  // cout << "===========================\n" << endl;
  // cout << "Vérification que le glaçage n'a pas été modifié :\n";
  // cout << glacage.toString() << endl;

  return 0;
}
