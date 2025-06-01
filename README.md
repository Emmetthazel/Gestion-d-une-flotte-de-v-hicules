# 📝 Cahier des charges

## 🎯 Projet : Gestion d'une flotte de véhicules

### 🎯 Objectif

Modéliser une flotte de véhicules pour une société, où chaque véhicule peut être suivi en termes :

- de marque,
- de modèle,
- de kilométrage,
- et de disponibilité.

Les employés peuvent réserver des véhicules pour **usage professionnel**.

---

## 🧱 Classes identifiées

### 1. Classe `Vehicule`

Représente un véhicule dans la flotte.

**Attributs privés :**

- `std::string marque` : la marque du véhicule (ex. : "Toyota")
- `std::string modele` : le modèle du véhicule (ex. : "Corolla")
- `int kilometrage` : le kilométrage actuel
- `bool disponible` : indique si le véhicule est disponible ou non

**Méthodes :**

- Constructeur : initialise les attributs
- Getters :
  - `std::string getMarque() const;`
  - `std::string getModele() const;`
  - `int getKilometrage() const;`
  - `bool getDisponible() const;`
- Setters :
  - `void setKilometrage(int nouveauKilometrage);`
  - `void setDisponibilite(bool etat);`
- Surcharge d’opérateur :
  - `std::ostream& operator<<(std::ostream& os, const Vehicule& v);`
- Autres :
  - `void afficherDetails() const;`

---

### 2. Classe `Employe`

Représente les employés qui peuvent réserver des véhicules.

**Attributs privés :**

- `std::string nom` : le nom de l’employé
- `std::vector<std::string> vehiculesReserves` : liste des modèles réservés

**Méthodes :**

- Constructeur
- Getters :
  - `std::string getNom() const;`
  - `std::vector<std::string> getVehiculesReserves() const;`
- Autres :
  - `void reserverVehicule(const std::string& modele);`
  - `void afficherReservations() const;`

---

### 3. Classe `Flotte`

Représente la flotte complète de véhicules.

**Attributs privés :**

- `std::vector<Vehicule> vehicules`
- `std::vector<Employe> employes`

**Méthodes :**

- Constructeur
- `void ajouterVehicule(const Vehicule& vehicule);`
- `void ajouterEmploye(const Employe& employe);`
- `void reserverVehicule(const std::string& modele, const std::string& nomEmploye);`
- `void miseAJourKilometrage(const std::string& modele, int nouveauKilometrage);`
- `void afficherVehiculesDisponibles() const;`
- `void afficherFlotte() const;`
- `void afficherReservationsEmployes() const;`

---

## 🔧 Travail demandé dans `main()`

1. Créer plusieurs véhicules avec des caractéristiques différentes.
2. Les ajouter à la flotte.
3. Créer plusieurs employés.
4. Les ajouter à la flotte.
5. Afficher les véhicules disponibles et les employés.
6. Simuler des réservations.
7. Mettre à jour le kilométrage après usage.
8. Afficher l’état final de la flotte.
9. Ajouter une classe dérivée `VehiculeElectrique` avec :

   - Attribut supplémentaire : `int autonomie`
   - Constructeur avec initialisation complète
   - Méthode : `void afficherAutonomie() const;`

   a. Créer des objets `VehiculeElectrique`
   b. Les ajouter à la flotte
   c. Afficher leurs détails avec `afficherAutonomie`

---

Souhaite-tu aussi que je t’aide à créer le code C++ correspondant à ce cahier des charges ?
