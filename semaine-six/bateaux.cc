#include <iostream>
#include <cmath>
using namespace std;

enum Pavillon { JollyRogers, CompagnieDuSenegal, CompagnieDOstende };

enum Etat { Intact, Endommage, Coule };

int sq(int x)
{
  return x*x;
}

class Coordonnees
{
public:
  Coordonnees(int un_x, int un_y) : x_(un_x), y_(un_y) {}
  int x() const {
    return x_;
  }
  int y() const {
    return y_;
  }
  void operator+=(Coordonnees const& autre); // à définir plus bas
private:
  int x_;
  int y_;
};

class Navire
{
  /*****************************************************
   * Compléter le code à partir d'ici
   *****************************************************/
  protected:
    Coordonnees position_;
    Pavillon pavillon_;
    Etat etat_;
    const int rayon_rencontre;

  public:

    /**
     * Superclass constructor
     */
    Navire(int x, int y, Pavillon pavillon) : position_(x, y), pavillon_(pavillon), etat_(Intact), rayon_rencontre(10) {}

    /**
     * This method returns the coordinates of the ship
     */
    Coordonnees position() const { return position_; }

    /**
     * This method moves the ship de_x units horizontally and de_y units vertically if it is not sunk (Coule)
     */
    void avancer(int de_x, int de_y)
    {
      if (Coule != etat_)
      {
        position_ += Coordonnees(de_x, de_y);
      }
    }

    /**
     * This method resets the ship to Intact state
     */
    void renflouer() { etat_ = Intact; }

    /**
     * This method displays the ship in this format: "<nom générique> en (<x>, <y>) battant pavillon <pavillon>, <etat>"
     */
    virtual ostream& afficher(ostream& sortie) const;
    
    /**
     * This method describes how a ship attacks another
     */
    virtual void attaque(Navire& _navire) const
    {
      (void)_navire;
    }
    
    /**
     * This method describes how a ship responds when it is attacked by another ship
     */
    virtual void replique(Navire& _navire) const
    {
      (void)_navire;
    }
    
    /**
     * This method describes what happens when a ship is hit
     */
    virtual void est_touche() { };
    
    /**
     * This method handles an encounter with another ship
     */
    virtual void rencontrer(Navire& navire_);
};

class Pirate : public virtual Navire
{
  public:
    
    /**
     * Subclass constructor
     */
    Pirate(int x, int y, Pavillon pavillon) : Navire(x, y, pavillon) {}

    /**
     * This method specialices the display method from its parent class by prepending "bateau pirate"
     */
    ostream& afficher(ostream& sortie) const override
    {
      sortie << "bateau pirate";
      return Navire::afficher(sortie);
    }
    
    void attaque(Navire& _navire) const override
    {
      if (Coule != etat_)
      {
        cout << "A l'abordage !" << endl;
        _navire.est_touche();
      }
    }

    void replique(Navire& _navire) const override
    {
      if (Coule != etat_)
      {
        cout << "Non mais, ils nous attaquent ! On riposte !!" << endl;
        attaque(_navire);
      }
    }

    virtual void est_touche() override
    {
      switch (etat_)
      {
        case Intact:
          etat_ = Endommage;
          break;
        case Endommage:
          etat_ = Coule;
        default:
          break;
      }
    }
};

class Marchand : public virtual Navire
{
  public:
    
    /**
     * Subclass constructor
     */
    Marchand(int x, int y, Pavillon pavillon) : Navire(x, y, pavillon) {}

    /**
     * This method specialices the display method from its parent class by prepending "navire marchand"
     */
    ostream& afficher(ostream& sortie) const override
    {
      sortie << "navire marchand";
      return Navire::afficher(sortie);
    }

    void attaque(Navire& _navire) const override
    {
      if (Coule != etat_)
      {
        cout << "On vous aura ! (insultes)" << endl;
      }
    }

    void replique(Navire& _navire) const override
    {
      if (Coule == etat_)
      {
        cout << "SOS je coule !" << endl;
      }
      else
      {
        cout << "Même pas peur !" << endl;
      }
    }

    void est_touche() override
    {
      etat_ = Coule;
    }
};

class Felon : public virtual Marchand, public virtual Pirate
{
  public:
    
    /**
     * Subclass constructor
     */
    Felon(int x, int y, Pavillon pavillon) :
      Navire(x, y, pavillon),
      Marchand(x, y, pavillon),
      Pirate(x, y, pavillon)
    {}

    /**
     * This method specialices the display method from its parent class by prepending "navire félon"
     */
    ostream& afficher(ostream& sortie) const override
    {
      sortie << "navire félon";
      return Navire::afficher(sortie);
    }

    void attaque(Navire& _navire) const override
    {
      Pirate::attaque(_navire);
    }

    void replique(Navire& _navire) const override
    {
      Marchand::replique(_navire);
    }

    void est_touche() override
    {
      Pirate::est_touche(); 
    }
};

void Coordonnees::operator+=(Coordonnees const& autre)
{
  // à définir ici
  this->x_ += autre.x();
  this->y_ += autre.y();
}

double distance(const Coordonnees& coordonnee1, const Coordonnees& coordonnee2)
{
  double dx = static_cast<double>(sq(coordonnee1.x() - coordonnee2.x()));
  double dy = static_cast<double>(sq(coordonnee1.y() - coordonnee2.y()));
  return sqrt(dx + dy);
}

ostream& operator<<(ostream& sortie, Coordonnees const& coordonnee)
{
  sortie << '(' << coordonnee.x() << ", " << coordonnee.y() << ')';
  return sortie;
}

ostream& operator<<(ostream& sortie, Pavillon const& pavillon)
{
  switch(pavillon)
  {
    case JollyRogers:
      sortie << "pirate";
      break;
    case CompagnieDuSenegal:
      sortie << "français";
      break;
    case CompagnieDOstende:
      sortie << "autrichien";
      break;
    default:
      sortie << "pavillon inconnu";
      break;
  }
  return sortie;
}

ostream& operator<<(ostream& sortie, Etat const& etat)
{
  switch(etat)
  {
    case Intact:
      sortie << "intact";
      break;
    case Endommage:
      sortie << "ayant subi des dommages";
      break;
    case Coule:
      sortie << "coulé";
      break;
    default:
      sortie << "état inconnu";
      break;
  }
  return sortie;
}

double distance(const Navire& navire1, const Navire& navire2)
{
  return distance(navire1.position(), navire2.position());
}

ostream& operator<<(ostream& sortie, Navire const& navire)
{
  return navire.afficher(sortie);
}

ostream& Navire::afficher(ostream& sortie) const
{
  sortie << " en " << position_ << " battant pavillon " << pavillon_ << ", " << etat_;
  return sortie;
}

void Navire::rencontrer(Navire& navire_)
{
  const bool condition_a = Coule != this->etat_ && Coule != navire_.etat_;
  const bool condition_b = this->pavillon_ != navire_.pavillon_;
  const bool condition_c = distance(*this, navire_) < static_cast<double>(rayon_rencontre);

  if (condition_a && condition_b && condition_c)
  {
    // These ships must battle!
    this->attaque(navire_);
    navire_.replique(*this);
  }
}

/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

void rencontre(Navire& ship1, Navire& ship2)
{
  cout << "Avant la rencontre :" << endl;
  cout << ship1 << endl;
  cout << ship2 << endl;
  cout << "Distance : " << distance(ship1, ship2) << endl;
  ship1.rencontrer(ship2);
  cout << "Apres la rencontre :" << endl;
  cout << ship1 << endl;
  cout << ship2 << endl;
}

int main()
{
  // Test de la partie 1
  cout << "===== Test de la partie 1 =====" << endl << endl;

  // Un bateau pirate 0,0
  Pirate ship1(0, 0, JollyRogers);
  cout << ship1 << endl;

  // Un bateau marchand en 25,0
  Marchand ship2(25, 0, CompagnieDuSenegal);
  cout << ship2 << endl;

  cout << "Distance : " << distance(ship1, ship2) << endl;

  cout << "Quelques déplacements..." << endl;
  cout << "  en haut à droite :" << endl;
  // Se déplace de 75 unités à droite et 10 en haut
  ship1.avancer(75, 10);
  cout << ship1 << endl;

  cout << "  vers le bas :" << endl;
  ship1.avancer(0, -5);
  cout << ship1 << endl;

  cout << endl << "===== Test de la partie 2 =====" << endl << endl;

  cout << "Bateau pirate et marchand ennemis (trop loins) :" << endl;
  rencontre(ship1, ship2);

  cout << endl << "Bateau pirate et marchand ennemis (proches) :" << endl;
  ship1.avancer(-40, -2);
  ship2.avancer(10, 2);
  rencontre(ship1, ship2);

  cout << endl << "Deux bateaux pirates ennemis intacts (proches) :" << endl;
  Pirate ship3(33, 8, CompagnieDOstende);
  rencontre(ship1, ship3);

  cout << endl << "Bateaux pirates avec dommages, ennemis :" << endl;
  rencontre(ship1, ship3);

  cout << endl << "Bateaux marchands ennemis :" << endl;
  Marchand ship4(21, 7, CompagnieDuSenegal);
  Marchand ship5(27, 2, CompagnieDOstende);
  rencontre(ship4, ship5);

  cout << endl << "Pirate vs Felon :" << endl;
  ship3.renflouer();
  Felon ship6(32, 10, CompagnieDuSenegal);
  rencontre(ship3, ship6);

  cout << endl << "Felon vs Pirate :" << endl;
  rencontre(ship6, ship3);

  return 0;
}
