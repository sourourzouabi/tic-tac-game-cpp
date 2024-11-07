#include <iostream>
#include <vector>

using namespace std;

class Personne {
protected:
    string nom;
    string prenom;

public:
    Personne(const string& n, const string& p) : nom(n), prenom(p) {}
    string getNom() const { return nom; }
    string getPrenom() const { return prenom; }
};

class Joueur : public Personne {
private:
    char symbole;

public:
    Joueur(const string& n, const string& p, char s) : Personne(n, p), symbole(s) {}
    char getSymbole() const { return symbole; }
};

class Jeu {
private:
    vector<vector<char>> grille;
    Joueur joueur1;
    Joueur joueur2;
    char tour;
    bool partieTerminee;

public:
    Jeu(const Joueur& j1, const Joueur& j2) : joueur1(j1), joueur2(j2), tour('X'), partieTerminee(false) {
        grille = { {'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'} };
    }

    void afficherGrille() {
        cout << "XO game" << endl;
        cout << "FOR 2 PLAYERS" << endl;
        cout << "-------------------" << endl;
        for (const auto& row : grille) {
            for (char cell : row) {
                cout << cell << " ";
            }
            cout << endl;
        }
        cout << "-------------------" << endl;
    }

    bool jouerTour(int choix) {
        char symboleJoueur = (tour == 'X') ? joueur1.getSymbole() : joueur2.getSymbole();
        for (auto& row : grille) {
            for (char& cell : row) {
                if (cell == choix + '0') {
                    cell = symboleJoueur;
                    return true;
                }
            }
        }
        return false;
    }

    bool verifiePartie() {
        // Vérification des lignes et colonnes
        for (int i = 0; i < 3; ++i) {
            if (grille[i][0] == grille[i][1] && grille[i][1] == grille[i][2]) {
                partieTerminee = true;
                return true;
            }
            if (grille[0][i] == grille[1][i] && grille[1][i] == grille[2][i]) {
                partieTerminee = true;
                return true;
            }
        }
        // Vérification des diagonales
        if (grille[0][0] == grille[1][1] && grille[1][1] == grille[2][2]) {
            partieTerminee = true;
            return true;
        }
        if (grille[0][2] == grille[1][1] && grille[1][1] == grille[2][0]) {
            partieTerminee = true;
            return true;
        }
        // Vérification du match nul
        bool matchNul = true;
        for (const auto& row : grille) {
            for (char cell : row) {
                if (cell != 'X' && cell != 'O') {
                    matchNul = false;
                    break;
                }
            }
            if (!matchNul) break;
        }
        if (matchNul) partieTerminee = true;
        return matchNul;
    }

    void jouer() {
        while (!partieTerminee) {
            afficherGrille();
            int choix;
            cout << "Joueur " << ((tour == 'X') ? joueur1.getNom() : joueur2.getNom()) << ", entrez votre choix: ";
            cin >> choix;
            if (choix < 1 || choix > 9 || !jouerTour(choix)) {
                cout << "Choix invalide. Veuillez choisir une case valide." << endl;
                continue;
            }
            if (verifiePartie()) {
                afficherGrille();
                if (partieTerminee) {
                    cout << "Partie terminée." << endl;
                    if (joueurGagnant() == ' ') {
                        cout << "Match nul!" << endl;
                    }
                    else {
                        cout << "Le joueur " << joueurGagnant() << " a gagné!" << endl;
                    }
                }
                break;
            }
            tour = (tour == 'X') ? 'O' : 'X';
        }
    }

    char joueurGagnant() {
        // Vérification des lignes et colonnes
        for (int i = 0; i < 3; ++i) {
            if (grille[i][0] == grille[i][1] && grille[i][1] == grille[i][2]) {
                return grille[i][0];
            }
            if (grille[0][i] == grille[1][i] && grille[1][i] == grille[2][i]) {
                return grille[0][i];
            }
        }
        // Vérification des diagonales
        if (grille[0][0] == grille[1][1] && grille[1][1] == grille[2][2]) {
            return grille[0][0];
        }
        if (grille[0][2] == grille[1][1] && grille[1][1] == grille[2][0]) {
            return grille[0][2];
        }
        return ' ';
    }
};

int main() {
    cout << "Bienvenue dans le jeu Tic-Tac-Toe!" << endl;
    string nomJoueur1, nomJoueur2;
    cout << "Joueur 1, entrez votre nom: ";
    cin >> nomJoueur1;
    cout << "Joueur 2, entrez votre nom: ";
    cin >> nomJoueur2;
    Joueur joueur1(nomJoueur1, "", 'X'); // prénom vide
    Joueur joueur2(nomJoueur2, "", 'O'); // prénom vide
    Jeu jeu(joueur1, joueur2);
    jeu.jouer();
    return 0;
}
