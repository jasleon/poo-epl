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
    virtual const Produit* adapter(double n) const { return (this); }

    /**
     * This method returns 1.0 if the product is named nomProduit and 0.0 otherwise
     */
    virtual double quantiteTotale(const string& nomProduit) const
    {
      return ((nomProduit == getNom()) ? 1.0 : 0.0);
    }
};

class Ingredient
{
  private:
    const Produit* produit_ptr;
    double quantite;
  
  public:
    
    /**
     * Class constructor
     */ 
    Ingredient(const Produit& produit, double quantite) : produit_ptr(&produit), quantite(quantite) {}

    /**
     * This method returns a constant reference to the ingredient's product
     */ 
    const Produit& getProduit() const { return (*produit_ptr); }

    /**
     * This method returns the quantity of the ingredient
     */ 
    double getQuantite() const { return quantite; }

    /**
     * This method is returns a description of the ingredient adapted to the quantity
     */ 
    string descriptionAdaptee() const
    {
      const Produit* produit_adapte_ptr = getProduit().adapter(getQuantite());
      const string description = to_string(getQuantite()) + " " + produit_adapte_ptr->getUnite() + " de " + produit_adapte_ptr->toString();
      return description;
    }

    /**
     * This method returns the ingredient’s quantity multiplied by the total quantity obtained in the ingredient’s product
     */
    double quantiteTotale(const string& nomProduit) const
    {
      return (produit_ptr->quantiteTotale(nomProduit) * getQuantite());
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
      Recette duplicate(nom, (n * nbFois_));
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
      string description("Recette \"" + nom + "\" x " + GetBonReplication(nbFois_) + ":\n");
      const size_t ingredientSize(liste.size()); 
      size_t nombre(1U);
      for(auto i : liste)
      {
        const string tail((nombre < ingredientSize) ? "\n" : "");
        description.append(to_string(nombre++) + ". " + i.descriptionAdaptee() + tail);
      }
      return description;
    }

    /**
     * This method computes the total necessary quantity of a given product in a recipe
     */
    double quantiteTotale(const string& nomProduit) const
    {
      double result(0.0);
      for(auto i : liste)
      {
        result += i.quantiteTotale(nomProduit);
      }
      return result;
    }

    /**
     * This method returns a string with a nice format (for marking only)
     */
    static string GetBonReplication(double replication)
    {
      string conversion = to_string(replication);
      const size_t point_pos = conversion.find('.');
      if (string::npos != point_pos)
      {
        const size_t decimal_pos = point_pos + 1U;
        if ('0' == conversion[decimal_pos])
        {
          conversion.assign(to_string(static_cast<int>(replication)));
        }
        else
        {
          conversion.resize(decimal_pos + 1U);
        }
      }
      return conversion;
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
    const ProduitCuisine* adapter(double n) const override
    {
      ProduitCuisine* produit_cuisine_ptr = new ProduitCuisine(*this);
      produit_cuisine_ptr->recette = produit_cuisine_ptr->recette.adapter(n);
      return produit_cuisine_ptr;
    }

    /**
     * This method returns 1.0 if the cooked product is named nomProduit and otherwise, 
     * the total quantity of the given product in the recipe of the specific cooked product
     */
    double quantiteTotale(const string& nomProduit) const override
    {
      return ((nomProduit == getNom()) ? 1.0 : recette.quantiteTotale(nomProduit));
    }
};

/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/
void afficherQuantiteTotale(const Recette& recette, const Produit& produit)
{
  string nom = produit.getNom();
  cout << "Cette recette contient " << recette.quantiteTotale(nom)
       << " " << produit.getUnite() << " de " << nom << endl;
}

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
}
