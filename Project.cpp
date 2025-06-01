#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Classe Vehicule
class Vehicule {
private:
    string marque;
    string modele;
    int kilometrage;
    bool disponible;

public:
    Vehicule(const string& marque, const string& modele, int kilometrage, bool disponible)
        : marque(marque), modele(modele), kilometrage(kilometrage), disponible(disponible) {}

    string getMarque() const { return marque; }
    string getModele() const { return modele; }
    int getKilometrage() const { return kilometrage; }
    bool getDisponible() const { return disponible; }

    void setKilometrage(int nouveauKilometrage) { kilometrage = nouveauKilometrage; }
    void setDisponibilite(bool etat) { disponible = etat; }

    void afficherDetails() const {
        cout << "Marque: " << marque << ", Modèle: " << modele
             << ", Kilométrage: " << kilometrage
             << ", Disponible: " << (disponible ? "Oui" : "Non") << endl;
    }

    friend ostream& operator<<(ostream& os, const Vehicule& v) {
        os << "Marque: " << v.marque << ", Modèle: " << v.modele
           << ", Kilométrage: " << v.kilometrage
           << ", Disponible: " << (v.disponible ? "Oui" : "Non");
        return os;
    }
};

// Classe VehiculeElectrique
class VehiculeElectrique : public Vehicule {
private:
    int autonomie;

public:
    VehiculeElectrique(const string& marque, const string& modele, int kilometrage, bool disponible, int autonomie)
        : Vehicule(marque, modele, kilometrage, disponible), autonomie(autonomie) {}

    void afficherAutonomie() const {
        cout << "Autonomie: " << autonomie << " km" << endl;
    }
};

// Classe Employe
class Employe {
private:
    string nom;
    vector<string> vehiculesReserves;

public:
    Employe(const string& nom) : nom(nom) {}

    string getNom() const { return nom; }
    vector<string> getVehiculesReserves() const { return vehiculesReserves; }

    void reserverVehicule(const string& modele) {
        vehiculesReserves.push_back(modele);
    }

    void afficherReservations() const {
        cout << "Employé: " << nom << ", Réservations: ";
        for (const auto& v : vehiculesReserves) {
            cout << v << " ";
        }
        cout << endl;
    }
};

// Classe Flotte
class Flotte {
private:
    vector<Vehicule> vehicules;
    vector<Employe> employes;

public:
    Flotte() {}
    
    void ajouterVehicule(const Vehicule& vehicule) {
        vehicules.push_back(vehicule);
    }

    void ajouterEmploye(const Employe& employe) {
        employes.push_back(employe);
    }

    void reserverVehicule(const string& modele, const string& nomEmploye) {
        for (auto& vehicule : vehicules) {
            if (vehicule.getModele() == modele && vehicule.getDisponible()) {
                for (auto& employe : employes) {
                    if (employe.getNom() == nomEmploye) {
                        vehicule.setDisponibilite(false);
                        employe.reserverVehicule(modele);
                        cout << "Réservation réussie: " << modele << " pour " << nomEmploye << endl;
                        return;
                    }
                }
            }
        }
        cout << "Réservation échouée: " << modele << " non disponible ou employé introuvable." << endl;
    }

    void miseAJourKilometrage(const string& modele, int nouveauKilometrage) {
        for (auto& vehicule : vehicules) {
            if (vehicule.getModele() == modele) {
                vehicule.setKilometrage(nouveauKilometrage);
                cout << "Kilométrage mis à jour pour " << modele << endl;
                return;
            }
        }
        cout << "Véhicule introuvable pour mise à jour." << endl;
    }

    void afficherVehiculesDisponibles() const {
        cout << "Véhicules disponibles:" << endl;
        for (const auto& vehicule : vehicules) {
            if (vehicule.getDisponible()) {
                vehicule.afficherDetails();
            }
        }
    }

    void afficherFlotte() const {
        cout << "Liste complète des véhicules:" << endl;
        for (const auto& vehicule : vehicules) {
            vehicule.afficherDetails();
        }
    }

    void afficherReservationsEmployes() const {
        cout << "Réservations des employés:" << endl;
        for (const auto& employe : employes) {
            employe.afficherReservations();
        }
    }
};

int main() {
    // 1. Création de véhicules
    Vehicule v1("Toyota", "Corolla", 50000, true);
    Vehicule v2("Renault", "Clio", 30000, true);
    VehiculeElectrique ve1("BMW", "Model i4", 20000, true, 600);
    VehiculeElectrique ve2("Jaguar", "Model XE", 15000, true, 300);

    // 2. Ajout des véhicules à la flotte
    Flotte flotte;
    flotte.ajouterVehicule(v1);
    flotte.ajouterVehicule(v2);
    flotte.ajouterVehicule(ve1);
    flotte.ajouterVehicule(ve2);

    // 3. Création des employés
    Employe e1("Abdelkhalek");
    Employe e2("Aymane");

    // 4. Ajout des employés à la flotte
    flotte.ajouterEmploye(e1);
    flotte.ajouterEmploye(e2);

    // 5. Affichage initial
    flotte.afficherVehiculesDisponibles();
    flotte.afficherReservationsEmployes();

    // 6. Simuler des réservations
    flotte.reserverVehicule("Corolla", "Abdelkhalek");
    flotte.reserverVehicule("Model i4", "Aymane");

    // 7. Mise à jour des véhicules après usage
    flotte.miseAJourKilometrage("Corolla", 50500);

    // 8. Affichage final
    flotte.afficherFlotte();
    flotte.afficherReservationsEmployes();

    // Afficher détails des véhicules électriques
    cout << "Détails des véhicules électriques:" << endl;
    ve1.afficherDetails();
    ve1.afficherAutonomie();
    ve2.afficherDetails();
    ve2.afficherAutonomie();

    return 0;
}
