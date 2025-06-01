#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <memory>
using namespace std;

// Classe Vehicule
class Vehicule {
protected:
    string marque;
    string modele;
    int kilometrage;
    bool disponible;

public:
    Vehicule(const string& marque, const string& modele, int kilometrage, bool disponible)
        : marque(marque), modele(modele), kilometrage(kilometrage), disponible(disponible) {}

    virtual ~Vehicule() = default;  // libérer correctement ces ressources lorsque l'objet est détruit.

    string getMarque() const { return marque; }
    string getModele() const { return modele; }
    int getKilometrage() const { return kilometrage; }
    bool getDisponible() const { return disponible; }

    void setKilometrage(int nouveauKilometrage) { kilometrage = nouveauKilometrage; }
    void setDisponibilite(bool etat) { disponible = etat; }

    virtual string getType() const { return "Vehicule"; }  // Méthode virtuelle destinée à être redéfinie dans les classes dérivées pour préciser le type 

    virtual void afficherDetails() const {
        cout << "Marque: " << marque << ", Modèle: " << modele
             << ", Kilométrage: " << kilometrage
             << ", Disponible: " << (disponible ? "Oui" : "Non") << endl;
    }
};

// Classe VehiculeElectrique
class VehiculeElectrique : public Vehicule {
private:
    int autonomie; 

public:
    VehiculeElectrique(const string& marque, const string& modele, int kilometrage, bool disponible, int autonomie)
        : Vehicule(marque, modele, kilometrage, disponible), autonomie(autonomie) {}

    int getAutonomie() const { return autonomie; }

    string getType() const override { return "VehiculeElectrique"; }

    void afficherDetails() const override {
        Vehicule::afficherDetails();
        cout << "Autonomie: " << autonomie << " km" << endl;
    }
};

// Classe Employe
class Employe {
private:
    string nom;
    vector<string> vehiculesReserves;

public:
    Employe() : nom("") {}
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
    vector<unique_ptr<Vehicule>> vehicules; // Liste de pointeurs uniques vers des véhicules.
    map<string, Employe> employes; // Map associant un nom d'employé à un objet Employe.

public:
    ~Flotte() {
        // Les pointeurs uniques sont automatiquement détruits ici
    }

    void ajouterVehicule(unique_ptr<Vehicule> vehicule) {
        vehicules.push_back(move(vehicule));               // move pour transférer la propriété du pointeur (gestion mémoire sécurisée)
    }

    void ajouterEmploye(const Employe& employe) {
        employes[employe.getNom()] = employe;
    }

    void reserverVehicule(const string& modele, const string& nomEmploye) {
        for (auto& vehicule : vehicules) {
            if (vehicule->getModele() == modele) {
                if (!vehicule->getDisponible()) {
                    cout << "Véhicule '" << modele << "' déjà réservé." << endl;
                    return;
                }

                auto it = employes.find(nomEmploye);
                if (it != employes.end()) {
                    vehicule->setDisponibilite(false);
                    it->second.reserverVehicule(modele);
                    cout << "Réservation réussie: " << modele << " pour " << nomEmploye << endl;
                    return;
                } else {
                    cout << "Employé '" << nomEmploye << "' introuvable." << endl;
                    return;
                }
            }
        }
        cout << "Réservation échouée: " << modele << " non disponible ou introuvable." << endl;
    }

    void miseAJourKilometrage(const string& modele, int nouveauKilometrage) {
        for (auto& vehicule : vehicules) {
            if (vehicule->getModele() == modele) {
                if (nouveauKilometrage >= vehicule->getKilometrage()) {
                    vehicule->setKilometrage(nouveauKilometrage);
                    cout << "Kilométrage mis à jour pour " << modele << endl;
                } else {
                    cout << "Nouveau kilométrage inférieur à l'actuel. Mise à jour ignorée." << endl;
                }
                return;
            }
        }
        cout << "Véhicule introuvable pour mise à jour." << endl;
    }

    void afficherVehiculesDisponibles() const {
        cout << "Véhicules disponibles:" << endl;
        for (const auto& vehicule : vehicules) {
            if (vehicule->getDisponible()) {
                vehicule->afficherDetails();
            }
        }
    }

    void afficherFlotte() const {
        cout << "Liste complète des véhicules:" << endl;
        for (const auto& vehicule : vehicules) {
            vehicule->afficherDetails();
        }
    }

    void afficherReservationsEmployes() const {
        cout << "Réservations des employés:" << endl;
        for (const auto& pair : employes) {
            const string& nom = pair.first;
            const Employe& employe = pair.second;
            employe.afficherReservations();
        }
    }

    void genererRapport() const {               // Génère un rapport sur l'état de la flotte
        int totalVehicules = vehicules.size();
        int vehiculesDisponibles = 0;
        int vehiculesElectriques = 0;
        int vehiculesNormaux = 0;

        for (const auto& vehicule : vehicules) {
            if (vehicule->getDisponible()) {
                vehiculesDisponibles++;
            }
            if (vehicule->getType() == "VehiculeElectrique") {
                vehiculesElectriques++;
            } else {
                vehiculesNormaux++;
            }
        }

        cout << "Rapport de la flotte:" << endl;
        cout << "Nombre total de véhicules: " << totalVehicules << endl;
        cout << "Nombre de véhicules disponibles: " << vehiculesDisponibles << endl;
        cout << "Véhicules électriques: " << vehiculesElectriques << endl;
        cout << "Véhicules normaux: " << vehiculesNormaux << endl;
    }
};

int main() {
    // 1. Création de véhicules
    Flotte flotte;
    flotte.ajouterVehicule(make_unique<Vehicule>("Toyota", "Corolla", 50000, true));
    flotte.ajouterVehicule(make_unique<Vehicule>("Renault", "Clio", 30000, true));
    flotte.ajouterVehicule(make_unique<VehiculeElectrique>("BMW", "Model i4", 20000, true, 600));
    flotte.ajouterVehicule(make_unique<VehiculeElectrique>("Jaguar", "Model XE", 15000, true, 300));

    // 2. Création des employés
    flotte.ajouterEmploye(Employe("Abdelkhalek"));
    flotte.ajouterEmploye(Employe("Aymane"));

    // 3. Affichage initial avant les modifications.
    flotte.afficherVehiculesDisponibles();
    flotte.afficherReservationsEmployes();

    // 4. Simuler des réservations
    flotte.reserverVehicule("Corolla", "Abdelkhalek");
    flotte.reserverVehicule("Model i4", "Aymane");
    flotte.reserverVehicule("Clio", "Inexistant"); // Test employé inexistant

    // 5. Mise à jour des véhicules après usage
    flotte.miseAJourKilometrage("Corolla", 50500);
    flotte.miseAJourKilometrage("Corolla", 49000); // Test avec kilométrage invalide

    // 6. Affichage final apret les modifications.
    flotte.afficherFlotte();
    flotte.afficherReservationsEmployes();

    // 7. Génération de rapport
    flotte.genererRapport();

    return 0;
}
