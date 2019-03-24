#include <iostream>
using namespace std;

class Forme
{
    public:
        virtual void description()
        {
            cout << "Ceci est une forme!" << endl;
        }
};

class Cercle : public Forme
{
    public:
        void description()
        {
            cout << "Ceci est un cercle." << endl;
        }      
};

void affichageDesc(Forme& f)
{
	f.description();	
}

int main()
{
    Forme f; 
    Cercle c; 
    affichageDesc(f);
    affichageDesc(c); 
    return 0;
}
