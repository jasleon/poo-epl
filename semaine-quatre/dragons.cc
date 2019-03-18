#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int distance(int x, int y)
{
  return abs(x - y);
}

class Creature
{
  /*****************************************************
   * Compléter le code à partir d'ici
   *****************************************************/
    protected:
        const string nom_;
        int niveau_;
        int points_de_vie_;
        int force_;
        int position_;
    
    public:

        /**
         * Superclass constructor
         */
        Creature(string name, int level, int health_points, int force, int position = 0)
            : nom_(name), niveau_(level), points_de_vie_(health_points), force_(force), position_(position) {}

        /**
         * A method returning true if the creature is alive
         */
        bool vivant() const
        {
            return (points_de_vie_ > 0);
        }

        /**
         * A method returning the number of attack points that can be inflicted by the creature to others
         */ 
        int points_attaque() const
        {
            return (vivant() ? (niveau_ * force_) : 0);
        }

        /**
         * A method to add an integer to the position of the creature
         */ 
        void deplacer(int valeur) 
        {
            if(vivant())
            {
                position_ += valeur;
            }
        }

        /**
         * A method to say goodbye
         */ 
        void adieux() const
        {
            cout << nom_ << " n'est plus !" << endl;
        }

        /**
         * A method to substract an integer from the number of health points of the creature (if alive)
         * If the creature dies, its number of health points is set to zero and the method adieux is called
         */ 
        void faiblir(int valeur)
        {
            if(vivant())
            {
                points_de_vie_ -= valeur;
                if(!vivant())
                {
                    points_de_vie_ = 0;
                    adieux();
                }
            }
        }

        /**
         * A method to display information about the creature
         */ 
        void afficher() const
        {
            cout                    << nom_             <<  
            ", niveau: "            << niveau_          << 
            ", points de vie: "     << points_de_vie_   << 
            ", force: "             << force_           << 
            ", points d'attaque: "  << points_attaque() << 
            ", position: "          << position_        << endl;
        }

        /**
         * A method to get the distance of the creature
         */
        int position() const { return position_; }
};

class Dragon : public Creature
{
    private:
        int portee_flamme_;

    public:
        
        /**
         * Subclass constructor
         */ 
        Dragon(string name, int level, int health_points, int force, int flame_range, int position = 0)
            : Creature(name, level, health_points, force, position), portee_flamme_(flame_range) {}

        /**
         * A method to allow to any given position
         */
        void voler(int pos)
        {
            if(vivant())
            {
                position_ = pos;
            }
        }

        /**
         * A method to blow flames over another creature
         */ 
        void souffle_sur(Creature& bete)
        {
            const int d = distance(position_, bete.position());
            const bool a_portee = (d <= portee_flamme_);
            if(vivant() && bete.vivant() && a_portee)
            {
                bete.faiblir(points_attaque());
                faiblir(d);
                if(vivant() && !bete.vivant())
                {
                    niveau_++;
                }
            }
        }
};

class Hydre : public Creature
{
    private:
        int longueur_cou_;
        int dose_poison_;

    public:

        /**
         * Subclass constructor
         */
        Hydre(string name, int level, int health_points, int force, int neck_length, int poison_dose, int position = 0)
            : Creature(name, level, health_points, force, position), longueur_cou_(neck_length), dose_poison_(poison_dose) {}

        /**
         * A method to poison another creature
         */
        void empoisonne(Creature& bete)
        {
            const int d = distance(position_, bete.position());
            const bool a_portee = (d <= longueur_cou_);
            if(vivant() && bete.vivant() && a_portee)
            {
                bete.faiblir((points_attaque() + dose_poison_));
                if(vivant() && !bete.vivant())
                {
                    niveau_++;
                }
            }
        }
};

void combat(Dragon& dragon, Hydre& hydre)
{
    hydre.empoisonne(dragon);
    dragon.souffle_sur(hydre);
}
/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/
int main()
{
  Dragon dragon("Dragon rouge"   , 2, 10, 3, 20         );
  Hydre  hydre ("Hydre maléfique", 2, 10, 1, 10, 1,  42 );

  dragon.afficher();
  cout << "se prépare au combat avec :" << endl;
  hydre.afficher();

  cout << endl;
  cout << "1er combat :" << endl;
  cout << "    les créatures ne sont pas à portée, donc ne peuvent pas s'attaquer."
       << endl;
  combat(dragon, hydre);

  cout << "Après le combat :" << endl;
  dragon.afficher();
  hydre.afficher();

  cout << endl;
  cout << "Le dragon vole à proximité de l'hydre :" << endl;
  dragon.voler(hydre.position() - 1);
  dragon.afficher();

  cout << endl;
  cout << "L'hydre recule d'un pas :" << endl;
  hydre.deplacer(1);
  hydre.afficher();

  cout << endl;
  cout << "2e combat :" << endl;
  cout << "\
  + l'hydre inflige au dragon une attaque de 3 points\n\
      [ niveau (2) * force (1) + poison (1) = 3 ] ;\n\
  + le dragon inflige à l'hydre une attaque de 6 points\n\
      [ niveau (2) * force (3) = 6 ] ;\n\
  + pendant son attaque, le dragon perd 2 points de vie supplémentaires\n\
       [ correspondant à la distance entre le dragon et l'hydre : 43 - 41 = 2 ].\
" << endl;
  combat(dragon, hydre);

  cout << "Après le combat :" << endl;
  dragon.afficher();
  hydre.afficher();

  cout << endl;
  cout << "Le dragon avance d'un pas :" << endl;
  dragon.deplacer(1);
  dragon.afficher();

  cout << endl;
  cout << "3e combat :" << endl;
  cout << "\
  + l'hydre inflige au dragon une attaque de 3 points\n\
      [ niveau (2) * force (1) + poison (1) = 3 ] ;\n\
  + le dragon inflige à l'hydre une attaque de 6 points\n\
      [ niveau (2) * force (3) = 6 ] ;\n\
  + pendant son attaque, le dragon perd 1 point de vie supplémentaire\n\
       [ correspondant à la distance entre le dragon et l'hydre : 43 - 42 = 1 ] ;\n\
  + l'hydre est vaincue et le dragon monte au niveau 3.\
" << endl;
  combat(dragon, hydre);

  cout << "Après le combat :" << endl;
  dragon.afficher();
  hydre.afficher();

  cout << endl;
  cout << "4e Combat :" << endl;
  cout << "    quand une créature est vaincue, rien ne se passe." << endl;
  combat(dragon, hydre);

  cout << "Après le combat :" << endl;
  dragon.afficher();
  hydre.afficher();

  return 0;
}
