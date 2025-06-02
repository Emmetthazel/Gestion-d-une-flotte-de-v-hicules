# 🚗 Vehicle Fleet Management System

## 📋 Project Overview

A C++ application for managing a company's vehicle fleet, allowing employees to track and reserve vehicles for professional use.

### Key Features
- Vehicle tracking (brand, model, mileage, availability)
- Employee vehicle reservations
- Fleet management and monitoring
- Electric vehicle support

## 🏗️ System Architecture

### Core Classes

#### 1. Vehicle (`Vehicule`)
**Properties:**
- Brand (`marque`)
- Model (`modele`)
- Mileage (`kilometrage`)
- Availability status (`disponible`)

**Methods:**
```cpp
// Getters
std::string getMarque() const;
std::string getModele() const;
int getKilometrage() const;
bool getDisponible() const;

// Setters
void setKilometrage(int nouveauKilometrage);
void setDisponibilite(bool etat);

// Other
void afficherDetails() const;
```

#### 2. Employee (`Employe`)
**Properties:**
- Name (`nom`)
- Reserved vehicles list (`vehiculesReserves`)

**Methods:**
```cpp
// Getters
std::string getNom() const;
std::vector<std::string> getVehiculesReserves() const;

// Other
void reserverVehicule(const std::string& modele);
void afficherReservations() const;
```

#### 3. Fleet (`Flotte`)
**Properties:**
- Vehicle collection (`vehicules`)
- Employee collection (`employes`)

**Methods:**
```cpp
void ajouterVehicule(const Vehicule& vehicule);
void ajouterEmploye(const Employe& employe);
void reserverVehicule(const std::string& modele, const std::string& nomEmploye);
void miseAJourKilometrage(const std::string& modele, int nouveauKilometrage);
void afficherVehiculesDisponibles() const;
void afficherFlotte() const;
void afficherReservationsEmployes() const;
```

#### 4. Electric Vehicle (`VehiculeElectrique`)
**Additional Properties:**
- Range (`autonomie`)

**Methods:**
```cpp
void afficherAutonomie() const;
```

## 🚀 Implementation Guide

### Main Program Flow
1. Initialize vehicles with different characteristics
2. Add vehicles to the fleet
3. Create employee accounts
4. Add employees to the system
5. Display available vehicles and employees
6. Process vehicle reservations
7. Update vehicle mileage after use
8. Display final fleet status
9. Implement electric vehicle functionality:
   - Create electric vehicle instances
   - Add to fleet
   - Display electric vehicle details including range

## 🛠️ Technical Requirements
- C++ compiler with C++11 support or later
- Standard Template Library (STL)
- Input/Output Stream Library

## 📝 Notes
- All vehicle reservations are for professional use only
- System maintains real-time availability status
- Electric vehicles include additional range information
