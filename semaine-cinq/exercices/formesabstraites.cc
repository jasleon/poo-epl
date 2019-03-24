#include <iostream>
#include <cmath>
using namespace std;

class Forme
{
    public:
        
        virtual void description() const
        {
            cout << "Ceci est une forme!" << endl;
        }

        virtual double aire() const = 0;
};

class Cercle : public Forme
{
    private:
        unsigned int rayon;

    public:
        
        /**
         * Subclass constructor
         */ 
        Cercle(unsigned int radius) : Forme(), rayon(radius) {}
        
        virtual void description() const override
        {
            cout << "Ceci est un cercle." << endl;
        }

        virtual double aire() const override
        {
            return (M_PI * pow(rayon, 2U));
        }
};

class Triangle : public Forme
{
    private:
        unsigned int base;
        unsigned int hauteur;

    public:
        
        /**
         * Subclass constructor
         */ 
        Triangle(unsigned int base, unsigned int height) : Forme(), base(base), hauteur(height) {}
        
        virtual void description() const override
        {
            cout << "Ceci est un triangle." << endl;
        }

        virtual double aire() const override
        {
            return (static_cast<double>(base * hauteur) / 2.0);
        }
};

void affichageDesc(Forme& f)
{
	f.description();
    cout << "L'aire de la forme géométrique est: " << f.aire() << endl;
}

int main()
{
    Cercle c(5);
    Triangle t(10, 2);
    affichageDesc(t);
    affichageDesc(c);
    return 0;
}
