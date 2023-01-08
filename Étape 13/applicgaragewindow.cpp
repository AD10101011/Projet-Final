#include "applicgaragewindow.h"
#include "ui_applicgaragewindow.h"
#include <QMessageBox>
#include <QInputDialog>
#include <sstream>
#include "classe/Garage.h"
using namespace std;

#define REPERTOIRE_IMAGES "images/"

ApplicGarageWindow::ApplicGarageWindow(QWidget *parent) : QMainWindow(parent),ui(new Ui::ApplicGarageWindow)
{
    ui->setupUi(this);

    // Configuration de la table des options (projet en cours)
    ui->tableWidgetOptions->setColumnCount(3);
    ui->tableWidgetOptions->setRowCount(5);
    for (int i=0 ; i<5 ; i++) ui->tableWidgetOptions->setRowHeight(i,10);
    QStringList labelsTableOptions;
    labelsTableOptions << "Code" << "Prix" << "Intitulé";
    ui->tableWidgetOptions->setHorizontalHeaderLabels(labelsTableOptions);
    ui->tableWidgetOptions->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidgetOptions->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetOptions->horizontalHeader()->setVisible(true);
    ui->tableWidgetOptions->horizontalHeader()->setDefaultSectionSize(60);
    ui->tableWidgetOptions->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidgetOptions->verticalHeader()->setVisible(false);
    ui->tableWidgetOptions->horizontalHeader()->setStyleSheet("background-color: lightyellow");

    // Configuration de la table des employes (Personnel Garage)
    ui->tableWidgetEmployes->setColumnCount(4);
    ui->tableWidgetEmployes->setRowCount(0);
    QStringList labelsTableEmployes;
    labelsTableEmployes << "Numéro" << "Nom" << "Prénom" << "Fonction";
    ui->tableWidgetEmployes->setHorizontalHeaderLabels(labelsTableEmployes);
    ui->tableWidgetEmployes->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidgetEmployes->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetEmployes->horizontalHeader()->setVisible(true);
    ui->tableWidgetEmployes->horizontalHeader()->setDefaultSectionSize(80);
    ui->tableWidgetEmployes->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidgetEmployes->verticalHeader()->setVisible(false);
    ui->tableWidgetEmployes->horizontalHeader()->setStyleSheet("background-color: lightyellow");

    // Configuration de la table des clients
    ui->tableWidgetClients->setColumnCount(4);
    ui->tableWidgetClients->setRowCount(0);
    QStringList labelsTableClients;
    labelsTableClients << "Numéro" << "Nom" << "Prénom" << "GSM";
    ui->tableWidgetClients->setHorizontalHeaderLabels(labelsTableClients);
    ui->tableWidgetClients->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidgetClients->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetClients->horizontalHeader()->setVisible(true);
    ui->tableWidgetClients->horizontalHeader()->setDefaultSectionSize(80);
    ui->tableWidgetClients->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidgetClients->verticalHeader()->setVisible(false);
    ui->tableWidgetClients->horizontalHeader()->setStyleSheet("background-color: lightyellow");

    // Configuration de la table des contrats
    ui->tableWidgetContrats->setColumnCount(4);
    ui->tableWidgetContrats->setRowCount(0);
    QStringList labelsTableContrats;
    labelsTableContrats << "Numéro" << "Vendeur" << "Client" << "Voiture";
    ui->tableWidgetContrats->setHorizontalHeaderLabels(labelsTableContrats);
    ui->tableWidgetContrats->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidgetContrats->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetContrats->horizontalHeader()->setVisible(true);
    ui->tableWidgetContrats->horizontalHeader()->setDefaultSectionSize(80);
    ui->tableWidgetContrats->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidgetContrats->verticalHeader()->setVisible(false);
    ui->tableWidgetContrats->horizontalHeader()->setStyleSheet("background-color: lightyellow");

    // Importation des modeles (étape 10)
    // TO DO
    string FichierModeles = "FichierCSV/Modeles.csv";
    Garage::getInstance().importeModeles(FichierModeles);

    for(int i=0;i<Garage::getInstance().nbrElemModeles();i++)
    {   
        Modele m(Garage::getInstance().getModele(i));
        ajouteModeleDisponible(m.getNom(),m.getPrixDeBase());
    }

    // Importation des options (étape 10)
    // TO DO
    string FichierOptions = "FichierCSV/Options.csv";
    Garage::getInstance().importeOptions(FichierOptions);
    for(int i = 0; i<Garage::getInstance().nbrElemOptions(); i++)
    {
        Option o(Garage::getInstance().getOption(i));
        ajouteOptionDisponible(o.getIntitule(),o.getPrix());
    }

    // Ouverture (et/ou creation) du fichier Garage.data (étape 12)
    // TO DO
    ifstream fichier("Fichier Data/Garage.data",ios::in | ios::binary);
    if(fichier.is_open())
    {
        Garage::getInstance().load(fichier);
        fichier.close();
    }

    majTableClient();
    majTableEmploye();
    majTableContrat();


    setRole(0);  // acces a tout pour l'instant

    // //******* EXEMPLES (A SUPPRIMER) *******************************************
    // setTableOption(1,"XY08","Toit ouvrant",850.0);
    // ajouteModeleDisponible("Ferrari Daytona SP3",2100000.0);
    // ajouteModeleDisponible("Peugeot 208",18500.0);
    // ajouteOptionDisponible("Peinture metallisee",450.0);
    // ajouteOptionDisponible("Systeme GPS",1100.0);
    // setModele("Peugeot 308",120,1,22300.0,"308.jpg");
    // ajouteTupleTableEmployes("2;Wagner;Jean-Marc;Vendeur");
    // ajouteTupleTableClients("8;Leonard;Anne;0475/47.25.36");
    // ajouteTupleTableContrats("3;Wagner Jean-Marc;Quettier Patrick;508_ProjetQuettier");
    // //**************************************************************************
}

ApplicGarageWindow::~ApplicGarageWindow()
{
    delete ui;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Titre de la fenêtre (ne pas modifier) //////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::setTitre(string titre)
{
    this->setWindowTitle(titre.c_str());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Gestion des roles (ne pas modifier) ////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::setRole(int val)
{
    // val = 0 --> personne n'est loggé
    // val = 1 --> un administratif est loggé
    // val = 2 --> un vendeur loggé
    // val = 3 --> on a accès à tout

    if (val == 0)
    {
        ui->actionLogin->setEnabled(true);
        ui->actionLogout->setEnabled(false);
        ui->actionReset_Mot_de_passe->setEnabled(false);
        ui->menuEmployes->setEnabled(false);
        ui->menuClients->setEnabled(false);
        ui->menuVoiture->setEnabled(false);
        ui->comboBoxModelesDisponibles->setEnabled(false);
        ui->comboBoxOptionsDisponibles->setEnabled(false);
        ui->pushButtonOuvrirProjet->setEnabled(false);
        ui->pushButtonNouveauProjet->setEnabled(false);
        ui->pushButtonReduction->setEnabled(false);
        ui->pushButtonEnregistrerProjet->setEnabled(false);
        ui->pushButtonAjouterOption->setEnabled(false);
        ui->pushButtonSupprimerOption->setEnabled(false);
        ui->pushButtonChoisirModele->setEnabled(false);
        ui->pushButtonVisualiserVoiture->setEnabled(false);
        ui->pushButtonNouveauContrat->setEnabled(false);
        ui->pushButtonSupprimerContrat->setEnabled(false);
    }

    if (val == 1)
    {
        ui->actionLogin->setEnabled(false);
        ui->actionLogout->setEnabled(true);
        ui->actionReset_Mot_de_passe->setEnabled(true);
        ui->menuEmployes->setEnabled(true);
        ui->menuClients->setEnabled(false);
        ui->menuVoiture->setEnabled(false);
        ui->comboBoxModelesDisponibles->setEnabled(false);
        ui->comboBoxOptionsDisponibles->setEnabled(false);
        ui->pushButtonOuvrirProjet->setEnabled(false);
        ui->pushButtonNouveauProjet->setEnabled(false);
        ui->pushButtonReduction->setEnabled(false);
        ui->pushButtonEnregistrerProjet->setEnabled(false);
        ui->pushButtonAjouterOption->setEnabled(false);
        ui->pushButtonSupprimerOption->setEnabled(false);
        ui->pushButtonChoisirModele->setEnabled(false);
        ui->pushButtonVisualiserVoiture->setEnabled(true);
        ui->pushButtonNouveauContrat->setEnabled(false);
        ui->pushButtonSupprimerContrat->setEnabled(true);
    }

    if (val == 2)
    {
        ui->actionLogin->setEnabled(false);
        ui->actionLogout->setEnabled(true);
        ui->actionReset_Mot_de_passe->setEnabled(true);
        ui->menuEmployes->setEnabled(false);
        ui->menuClients->setEnabled(true);
        ui->menuVoiture->setEnabled(true);
        ui->comboBoxModelesDisponibles->setEnabled(true);
        ui->comboBoxOptionsDisponibles->setEnabled(true);
        ui->pushButtonOuvrirProjet->setEnabled(true);
        ui->pushButtonNouveauProjet->setEnabled(true);
        ui->pushButtonReduction->setEnabled(true);
        ui->pushButtonEnregistrerProjet->setEnabled(true);
        ui->pushButtonAjouterOption->setEnabled(true);
        ui->pushButtonSupprimerOption->setEnabled(true);
        ui->pushButtonChoisirModele->setEnabled(true);
        ui->pushButtonVisualiserVoiture->setEnabled(true);
        ui->pushButtonNouveauContrat->setEnabled(true);
        ui->pushButtonSupprimerContrat->setEnabled(true);
    }

    if (val == 3)
    {
        ui->actionLogin->setEnabled(true);
        ui->actionLogout->setEnabled(true);
        ui->actionReset_Mot_de_passe->setEnabled(true);
        ui->menuEmployes->setEnabled(true);
        ui->menuClients->setEnabled(true);
        ui->menuVoiture->setEnabled(true);
        ui->comboBoxModelesDisponibles->setEnabled(true);
        ui->comboBoxOptionsDisponibles->setEnabled(true);
        ui->pushButtonOuvrirProjet->setEnabled(true);
        ui->pushButtonNouveauProjet->setEnabled(true);
        ui->pushButtonReduction->setEnabled(true);
        ui->pushButtonEnregistrerProjet->setEnabled(true);
        ui->pushButtonAjouterOption->setEnabled(true);
        ui->pushButtonSupprimerOption->setEnabled(true);
        ui->pushButtonChoisirModele->setEnabled(true);
        ui->pushButtonVisualiserVoiture->setEnabled(true);
        ui->pushButtonNouveauContrat->setEnabled(true);
        ui->pushButtonSupprimerContrat->setEnabled(true);
    }

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Table des options du projet en cours (ne pas modifier) /////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::setTableOption(int indice,string code,string intitule,float prix)
{
    // Modifie l'option de la ligne correspondant à l'indice fourni dans la table des options de l'interface graphique
    QTableWidgetItem *item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(code.c_str());
    ui->tableWidgetOptions->setItem(indice,0,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setTextAlignment(Qt::AlignCenter);
    char tmp[20];
    sprintf(tmp,"%.2f",prix);
    if (prix < 0.0) item->setText("");
    else item->setText(tmp);
    ui->tableWidgetOptions->setItem(indice,1,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(intitule.c_str());
    ui->tableWidgetOptions->setItem(indice,2,item);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::videTableOption()
{
    for (int i=0 ; i<5 ; i++) setTableOption(i,"","",-1.0);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ApplicGarageWindow::getIndiceOptionSelectionneeTable() const
{
    // retourne l'indice de l'option selectionnee dans la table des options
    QModelIndexList liste = ui->tableWidgetOptions->selectionModel()->selectedRows();
    if (liste.size() == 0) return -1;
    QModelIndex index = liste.at(0);
    int indice = index.row();
    return indice;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Combobox des modèles disponibles (ne pas modifier) /////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::ajouteModeleDisponible(const char* nom,float prixDeBase)
{
    // ajoute un modèle dans le combobox correspondant (juste le nom et le prix)
    stringstream ss;
    char temp[20];
    sprintf(temp,"%.2f",prixDeBase);
    ss << nom << " (" << temp << ")";
    ui->comboBoxModelesDisponibles->addItem(ss.str().c_str());
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::videComboboxModelesDisponibles()
{
    ui->comboBoxModelesDisponibles->clear();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ApplicGarageWindow::getIndiceModeleSelectionneCombobox() const
{
    // retourne l'indice du modèle selectionné dans le combobox des modèles
    return ui->comboBoxModelesDisponibles->currentIndex();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Combox des options disponibles (ne pas modifier) ///////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::ajouteOptionDisponible(string intitule,float prix)
{
    // ajoute une option dans le combobox correspondant
    stringstream ss;
    char temp[20];
    sprintf(temp,"%.2f",prix);
    ss << intitule << " (" << temp << ")";
    ui->comboBoxOptionsDisponibles->addItem(ss.str().c_str());
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::videComboboxOptionsDisponibles()
{
    ui->comboBoxOptionsDisponibles->clear();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ApplicGarageWindow::getIndiceOptionSelectionneeCombobox() const
{
    // retourne l'indice de l'option selectionnée dans le combobox des options
    return ui->comboBoxOptionsDisponibles->currentIndex();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Gestion du Projet en cours (ne pas modifier) ///////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::setNomProjetEnCours(string nom)
{
    // Remplit le champ nom de l'interface graphique avec le nom reçu
    ui->lineEditNomProjet->setText(nom.c_str());
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string ApplicGarageWindow::getNomProjetEnCours() const
{
    return ui->lineEditNomProjet->text().toStdString();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::setModele(string nom,int puissance,int moteur,float prixDeBase,string imageModele)
{
    // Remplit les champs correspondants dans l'interface graphique
    // pour le moteur (int) : 0=Essence, 1=Diesel, 2=Electrique, 3=Hybride
    ui->lineEditNomModele->setText(nom.c_str());
    ui->lineEditPuissance->setText(to_string(puissance).c_str());
    char tmp[20];
    sprintf(tmp,"%.2f",prixDeBase);
    ui->lineEditPrixDeBase->setText(tmp);

    ui->radioButtonEssence->setChecked(false);
    ui->radioButtonDiesel->setChecked(false);
    ui->radioButtonElectrique->setChecked(false);
    ui->radioButtonHybride->setChecked(false);

    if (moteur == 0) ui->radioButtonEssence->setChecked(true);
    if (moteur == 1) ui->radioButtonDiesel->setChecked(true);
    if (moteur == 2) ui->radioButtonElectrique->setChecked(true);
    if (moteur == 3) ui->radioButtonHybride->setChecked(true);

    // Met à jour l'image du modèle
    string cheminComplet = REPERTOIRE_IMAGES + imageModele;
    QLabel* label = new QLabel();
    label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    label->setScaledContents(true);
    QPixmap *pixmap_img = new QPixmap(cheminComplet.c_str());
    label->setPixmap(*pixmap_img);
    label->resize(label->pixmap()->size());
    ui->scrollArea->setWidget(label);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::setPrix(float prix)
{
  char tmp[20];
  sprintf(tmp,"%.2f",prix);
  ui->lineEditPrix->setText(tmp);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions utiles Table des Employes (ne pas modifier) //////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::ajouteTupleTableEmployes(string tuple)
{
    // Controle du tuple recu et parsing
    char Tuple[200];
    strncpy(Tuple,tuple.c_str(),199);
    char* tmp;

    if ((tmp = strtok(Tuple,";")) == NULL) return;
    char numero[20];
    strcpy(numero,tmp);

    if ((tmp = strtok(NULL,";")) == NULL) return;
    char nom[40];
    strcpy(nom,tmp);

    if ((tmp = strtok(NULL,";")) == NULL) return;
    char prenom[40];
    strcpy(prenom,tmp);

    if ((tmp = strtok(NULL,";")) == NULL) return;
    char fonction[40];
    strcpy(fonction,tmp);

    // Ajout possible
    int nbLignes = ui->tableWidgetEmployes->rowCount();
    nbLignes++;
    ui->tableWidgetEmployes->setRowCount(nbLignes);
    ui->tableWidgetEmployes->setRowHeight(nbLignes-1,10);

    QTableWidgetItem *item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(numero);
    ui->tableWidgetEmployes->setItem(nbLignes-1,0,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(nom);
    ui->tableWidgetEmployes->setItem(nbLignes-1,1,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(prenom);
    ui->tableWidgetEmployes->setItem(nbLignes-1,2,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(fonction);
    ui->tableWidgetEmployes->setItem(nbLignes-1,3,item);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::videTableEmployes()
{
    ui->tableWidgetEmployes->setRowCount(0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ApplicGarageWindow::getIndiceEmployeSelectionne()
{
    QModelIndexList liste = ui->tableWidgetEmployes->selectionModel()->selectedRows();
    if (liste.size() == 0) return -1;
    QModelIndex index = liste.at(0);
    int indice = index.row();
    return indice;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions utiles Table des Clients (ne pas modifier) ///////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::ajouteTupleTableClients(string tuple)
{
    // Controle du tuple recu et parsing
    char Tuple[200];
    strncpy(Tuple,tuple.c_str(),199);
    char* tmp;

    if ((tmp = strtok(Tuple,";")) == NULL) return;
    char numero[20];
    strcpy(numero,tmp);

    if ((tmp = strtok(NULL,";")) == NULL) return;
    char nom[40];
    strcpy(nom,tmp);

    if ((tmp = strtok(NULL,";")) == NULL) return;
    char prenom[40];
    strcpy(prenom,tmp);

    if ((tmp = strtok(NULL,";")) == NULL) return;
    char gsm[40];
    strcpy(gsm,tmp);

    // Ajout possible
    int nbLignes = ui->tableWidgetClients->rowCount();
    nbLignes++;
    ui->tableWidgetClients->setRowCount(nbLignes);
    ui->tableWidgetClients->setRowHeight(nbLignes-1,10);

    QTableWidgetItem *item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(numero);
    ui->tableWidgetClients->setItem(nbLignes-1,0,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(nom);
    ui->tableWidgetClients->setItem(nbLignes-1,1,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(prenom);
    ui->tableWidgetClients->setItem(nbLignes-1,2,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(gsm);
    ui->tableWidgetClients->setItem(nbLignes-1,3,item);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::videTableClients()
{
    ui->tableWidgetClients->setRowCount(0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ApplicGarageWindow::getIndiceClientSelectionne()
{
    QModelIndexList liste = ui->tableWidgetClients->selectionModel()->selectedRows();
    if (liste.size() == 0) return -1;
    QModelIndex index = liste.at(0);
    int indice = index.row();
    return indice;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions utiles Table des Contrats (ne pas modifier) //////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::ajouteTupleTableContrats(string tuple)
{
    // Controle du tuple recu et parsing
    char Tuple[200];
    strncpy(Tuple,tuple.c_str(),199);
    char* tmp;

    if ((tmp = strtok(Tuple,";")) == NULL) return;
    char numero[20];
    strcpy(numero,tmp);

    if ((tmp = strtok(NULL,";")) == NULL) return;
    char vendeur[40];
    strcpy(vendeur,tmp);

    if ((tmp = strtok(NULL,";")) == NULL) return;
    char client[40];
    strcpy(client,tmp);

    if ((tmp = strtok(NULL,";")) == NULL) return;
    char voiture[40];
    strcpy(voiture,tmp);

    // Ajout possible
    int nbLignes = ui->tableWidgetContrats->rowCount();
    nbLignes++;
    ui->tableWidgetContrats->setRowCount(nbLignes);
    ui->tableWidgetContrats->setRowHeight(nbLignes-1,10);

    QTableWidgetItem *item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(numero);
    ui->tableWidgetContrats->setItem(nbLignes-1,0,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(vendeur);
    ui->tableWidgetContrats->setItem(nbLignes-1,1,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(client);
    ui->tableWidgetContrats->setItem(nbLignes-1,2,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(voiture);
    ui->tableWidgetContrats->setItem(nbLignes-1,3,item);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::videTableContrats()
{
    ui->tableWidgetContrats->setRowCount(0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ApplicGarageWindow::getIndiceContratSelectionne()
{
    QModelIndexList liste = ui->tableWidgetContrats->selectionModel()->selectedRows();
    if (liste.size() == 0) return -1;
    QModelIndex index = liste.at(0);
    int indice = index.row();
    return indice;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions permettant d'afficher des boites de dialogue /////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::dialogueMessage(const char* titre,const char* message)
{
   QMessageBox::information(this,titre,message);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::dialogueErreur(const char* titre,const char* message)
{
   QMessageBox::critical(this,titre,message);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string ApplicGarageWindow::dialogueDemandeTexte(const char* titre,const char* question)
{
    QString chaine = QInputDialog::getText(this,titre,question);
    return chaine.toStdString();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ApplicGarageWindow::dialogueDemandeInt(const char* titre,const char* question)
{
    return QInputDialog::getInt(this,titre,question);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
float ApplicGarageWindow::dialogueDemandeFloat(const char* titre,const char* question)
{
    return QInputDialog::getDouble(this,titre,question);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions clics sur les items de menu //////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_actionQuitter_triggered()
{
  // TO DO (étape 12)
  ofstream fichier("Fichier Data/Garage.data",ios::in | ios::trunc | ios::binary);
  if(fichier.is_open()) 
  {
    Garage::getInstance().save(fichier);
    fichier.close();
  }

  QApplication::exit();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::closeEvent(QCloseEvent *event)
{
  if (event == NULL) {}  // pour éviter le warning
  // TO DO (étape 12)
  ofstream fichier("Fichier Data/Garage.data",ios::in | ios::trunc | ios::binary);
  if(fichier.is_open())
  {
    Garage::getInstance().save(fichier); 
    fichier.close();
  }

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_actionNouveau_modele_triggered()
{
  // Saisie des informations (aucune vérification n'est faite --> à gérer si vous voulez)
  string nomModele = dialogueDemandeTexte("Nouveau modèle","Nom :");
  int puissance = dialogueDemandeInt("Nouveau modèle","Puissance :");
  int moteur = dialogueDemandeInt("Nouveau modèle :","Moteur (0=essence,1=diesel,2=électrique,3=hybride) :");
  float prixDeBase = dialogueDemandeFloat("Nouveau modèle","Prix de base :");
  string image = dialogueDemandeTexte("Nouveau modèle","Nom du fichier de l'image :");

  // TO DO (étape 9)
  Modele m(nomModele.c_str(),puissance,(enum Moteur) moteur,prixDeBase);
  m.setImage(image);
  Garage::getInstance().ajouteModele(m);
  
  ajouteModeleDisponible(nomModele.c_str(), prixDeBase); // ajoute le modèle à la check box

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_actionNouvelle_option_triggered()
{
  // Saisie des informations (aucune vérification n'est faite --> à gérer si vous voulez)
  

    string code = dialogueDemandeTexte("Nouvelle option","Code :");
    string intitule = dialogueDemandeTexte("Nouvelle option","Intitule :");
    float prix = dialogueDemandeFloat("Nouvelle option","Prix :");

      // TO DO (étape 9)
    try
    {
        Garage::getInstance().ajouteOption(Option(code,intitule,prix));
        ajouteOptionDisponible(intitule,prix);
    }
      
    catch(OptionException e)
    {
        dialogueErreur("OptionExeption",e.getMsg().c_str());  
    }
    
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_actionAjouterEmploye_triggered()
{
  // TO DO (étape 11)
    string nom = dialogueDemandeTexte("Nouveau employe","Nom : ");
    string prenom = dialogueDemandeTexte("Nouveau employe","Prénom : ");
    string login = dialogueDemandeTexte("Nouveau employe","login :");
    string fonction;
    int fonctionCPT = 1;

    
    fonction = dialogueDemandeTexte("Nouveau employe","fonction (ADMINISTRATIF , VENDEUR) : ");

    while(fonctionCPT)
    {
        if(strcasecmp(fonction.c_str(),Employe::VENDEUR.c_str())==0 || strcasecmp(fonction.c_str(),Employe::ADMINISTRATIF.c_str())==0)
        {
            fonctionCPT = 0;
        }
        else
        {
            dialogueErreur("Erreur Employe","Vous devez attribuer une fonction existante à un employe !");
            fonction = dialogueDemandeTexte("Nouveau employe" , "fonction (ADMINISTRATIF , VENDEUR) :");
        }
    }
        
    Garage::getInstance().ajouteEmploye(nom,prenom,login,fonction);
    videTableEmployes();
    majTableEmploye();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_actionSupprimerEmploye_par_numero_triggered()
{
  // TO DO (étape 11)
  int numero = dialogueDemandeInt("Suppression d'employe","Entrer le numéro de l'employé à supprimer");
  int i;

  for(i = 0 ; i<Garage::getInstance().getEmployes().size() && Garage::getInstance().getEmployes()[i].getNumero() != numero;i++);
  if(Garage::getInstance().getEmployes()[i].getNumero() != numero) dialogueErreur("Erreur employé","Vous avez rentré un numéro qui n'appartient a aucun employé !");
  else
  {
        Garage::getInstance().supprimeEmployeParNumero(numero);
        majTableEmploye();
  }

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_actionSupprimerEmploye_selection_triggered()
{
  // TO DO (étape 11)
  int ind = getIndiceEmployeSelectionne();
  if(ind == -1)
  {
    dialogueErreur("Erreur supresion employe","Vous n'avez pas sélectionner d'employe à supprimer");
  }
  else
  {
    Garage::getInstance().supprimeEmployeParIndice(ind);
    majTableEmploye();
  }

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_actionAjouterClient_triggered()
{
  // TO DO (étape 11)
    string nom = dialogueDemandeTexte("Nouveau client","Nom : ");
    string prenom = dialogueDemandeTexte("Nouveau client","Prénom : ");
    string gsm = dialogueDemandeTexte("Nouveau client","N°gsm : ");
    
    Garage::getInstance().ajouteClient(nom,prenom,gsm);
    majTableClient();

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_actionSupprimerClient_par_numero_triggered()
{
  int numero = dialogueDemandeInt("Suppression Client","Entrer le numéro du client à supprimer");
  int i;
  for(i = 0 ; i<Garage::getInstance().getClients().size() && Garage::getInstance().getClients()[i].getNumero() != numero;i++);
  if(Garage::getInstance().getClients()[i].getNumero() != numero) dialogueErreur("Erreur suppression client","Vous avez rentré un numéro qui n'appartient a aucun client !");
  else
  {
        Garage::getInstance().supprimeClientParNumero(numero);
        majTableClient();
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_actionSupprimerClient_selection_triggered()
{
  // TO DO (étape 11)
  int ind = getIndiceClientSelectionne();
  if(ind == -1)
  {
    dialogueErreur("Erreur suppression client","Vous n'avez pas sélectionner de client à supprimer !");
  }
  else
  {
    Garage::getInstance().supprimeClientParIndice(ind);
    majTableClient();
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_actionLogin_triggered()
{
  // TO DO (étape 11)
    string login = dialogueDemandeTexte("Connexion","Entrer votre nom d'utilisateur :");
    Iterateur<Employe>it(Garage::getInstance().getEmployes());
    int i;
    for(i=0,it.reset();!it.end() && Garage::getInstance().getEmployes()[i].getLogin() != login;i++,it++);

    if(Garage::getInstance().getEmployes()[i].getLogin() == login)
    {   
        try
        {   
            string MotDePasse = Garage::getInstance().getEmployes()[i].getMotDePasse();
            string mdp = dialogueDemandeTexte("Mot de passe","Entrez votre mot de passe : ");

            if(strcmp(MotDePasse.c_str(),mdp.c_str()) == 0)
            {
                setTitre( "Application Garage ("+ Garage::getInstance().getEmployes()[i].getFonction()+ ": " +  Garage::getInstance().getEmployes()[i].getNom() + " " + Garage::getInstance().getEmployes()[i].getPrenom() + ")");
                Garage::getInstance().employeLogger = new Employe(Garage::getInstance().getEmployes()[i]);
                if(strcasecmp(Garage::getInstance().getEmployes()[i].getFonction().c_str(),Employe::VENDEUR.c_str()) == 0) setRole(2);
                else setRole(1);
            }
            else dialogueErreur("Erreur connexion","Mot de passe incorrecte !");

        }
        catch(PasswordException e)
        {    
            dialogueMessage("Mot de passe",e.getMsg().c_str());
            try
            {
                string mdp = dialogueDemandeTexte("Mot de Passe","Entrez un mot de passe : ");
                Garage::getInstance().getEmployes()[i].setMotDePasse(mdp);
                setTitre( "Application Garage ("+ Garage::getInstance().getEmployes()[i].getFonction()+ ": " + Garage::getInstance().getEmployes()[i].getNom()+ " " + Garage::getInstance().getEmployes()[i].getPrenom()+ ")");
                Garage::getInstance().employeLogger = new Employe(Garage::getInstance().getEmployes()[i]);
                if(strcasecmp(Garage::getInstance().getEmployes()[i].getFonction().c_str(),Employe::VENDEUR.c_str()) == 0) setRole(2);
                else setRole(1);
            }
            catch(PasswordException e)
            {
                dialogueErreur("Mot de Passe",e.getMsg().c_str());
            }
        }   
    }
    else dialogueErreur("Erreur connexion","Le login entré ne correspond à aucun employé !");
        
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_actionLogout_triggered()
{
  // TO DO (étape 11)
  setTitre("Application Garage");
  setRole(0);
  delete Garage::getInstance().employeLogger;
  Garage::getInstance().employeLogger = NULL;
  Garage::getInstance().resetProjetEnCours();
  on_pushButtonNouveauProjet_clicked();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_actionReset_Mot_de_passe_triggered()
{
  // TO DO (étape 11)
    Iterateur<Employe> it(Garage::getInstance().getEmployes());
    int i;

    for(i = 0,it.reset();!it.end();it++,i++)
    {   
        try
        {
            if(Garage::getInstance().getEmployes()[i].getLogin() == Garage::getInstance().employeLogger->getLogin() && Garage::getInstance().getEmployes()[i].getMotDePasse() == Garage::getInstance().employeLogger->getMotDePasse())
            {
                Garage::getInstance().getEmployes()[i].resetMotDePasse();
                it.end();
                dialogueMessage("Reset mot de passe","votre mot de passe à été reset !");
            }
        }
        catch(PasswordException e)
        {
            dialogueErreur("Erreur de resetMotDePasse",e.getMsg().c_str());
        }

    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions clics sur les boutons ////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_pushButtonChoisirModele_clicked()
{
  int ind;
  videTableOption();
  Garage::getInstance().resetProjetEnCours();
  ind = getIndiceModeleSelectionneCombobox();

  if(ind == -1) 
  {
    dialogueErreur("Erreur de sélection","Vous n'avez pas sélectionné de modèle !");
  }
   
  // ajout du modèle au ProjetEnCours de Voiture
  else
  {
   
    Modele m(Garage::getInstance().getModele(ind));
    Garage::getInstance().getProjetEnCours().setModele(m);
    setModele(m.getNom(),m.getPuissance(),m.getMoteur(),m.getPrixDeBase(),m.getImage());
    setPrix(Garage::getInstance().getProjetEnCours().getPrix());
  }


}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_pushButtonAjouterOption_clicked()
{

  if(strcmp(Garage::getInstance().getProjetEnCours().getModele().getNom(),"Modele sans nom") == 0)
  {
    dialogueMessage("Choisissez un modèle","vous devez choisir un modèle pour lui attribuer des options");
  }
  else
  {
      int ind;

      ind = getIndiceOptionSelectionneeCombobox();

      if(ind == -1)
        dialogueErreur("Erreur de ajout","Vous n'avez pas sélectionné d'option à ajouter");

      else
      {
        Option o(Garage::getInstance().getOption(ind));
        try
        {   
            int i;
            Garage::getInstance().getProjetEnCours().AjouteOption(o);
            for(i = 0; i<5 && Garage::getInstance().getProjetEnCours()[i]->getCode() != o.getCode(); i++);
            setTableOption(i,o.getCode(),o.getIntitule(),o.getPrix());
            setPrix(Garage::getInstance().getProjetEnCours().getPrix());
        }
        catch(OptionException e)
        {
            dialogueErreur("Erreur lors de l'ajout",e.getMsg().c_str());
        }
      }
  }

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_pushButtonSupprimerOption_clicked()
{
  // TO DO (étape 9)

  int ind ;

  ind = getIndiceOptionSelectionneeTable();

  if(strcmp(Garage::getInstance().getProjetEnCours().getModele().getNom(),"Modele sans nom") == 0)
  {
    dialogueMessage("Choisissez un modèle","vous devez choisir un modèle pour lui enlever des options");
  }
  else
  {

    if(ind == -1)
        dialogueErreur("Erreur de suppression","Vous n'avez sélectionné aucune option !");

    else
    {
        if(Garage::getInstance().getProjetEnCours()[ind] == NULL)
        {   
            dialogueErreur("Erreur de suppression","Veuillez sélectionner une ligne comprenant une option !");
        }
        else
        {
            Garage::getInstance().getProjetEnCours().RetireOption(Garage::getInstance().getProjetEnCours()[ind]->getCode());
            setTableOption(ind);
            setPrix(Garage::getInstance().getProjetEnCours().getPrix());
        }
    }
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_pushButtonReduction_clicked()
{
  // TO DO (étape 9)
  int ind = getIndiceOptionSelectionneeTable();
  
  if(ind == -1)
    dialogueErreur("Erreur de réduction","Vous n'avez sélectionné aucune option !");
  else
  {
    if(Garage::getInstance().getProjetEnCours()[ind] == NULL)

        dialogueErreur("Erreur de réduction","Veuillez sélectionner une ligne comprenant une option !");
    else
    {
        try
        {
            (*Garage::getInstance().getProjetEnCours()[ind])--;
            for(int i = 0; i<5; i++)
            {
                if(Garage::getInstance().getProjetEnCours()[i] != NULL)
                {
                    setTableOption(i,Garage::getInstance().getProjetEnCours()[i]->getCode(),Garage::getInstance().getProjetEnCours()[i]->getIntitule(),Garage::getInstance().getProjetEnCours()[i]->getPrix());  
                }
            }
            setPrix(Garage::getInstance().getProjetEnCours().getPrix());
        }
        catch(OptionException e)
        {
           dialogueErreur("Erreur réduction",e.getMsg().c_str());
        }
    }
      
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_pushButtonEnregistrerProjet_clicked()
{
  // TO DO (étape 9)
    string nomProjet;

    nomProjet = getNomProjetEnCours();

    if(nomProjet.size() != 0)
    {
        Garage::getInstance().getProjetEnCours().setNom(nomProjet);
        Garage::getInstance().getProjetEnCours().Save();
    }
    else
        dialogueErreur("Erreur enregistrement","veuillez entrez un nom de projet !");


}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_pushButtonOuvrirProjet_clicked()
{
  // TO DO (étape 9)
    
    if(getNomProjetEnCours().size()!=0)
    {   
        string nomProjet = getNomProjetEnCours() + ".car";

        ifstream fichier("Fichier Car/" + nomProjet,ios::in);

        if(!fichier.is_open())
        {
            dialogueErreur("Erreur ouverture","Le projet que vous tentez d'ouvrir n'existe pas !");
        }
        else
        {
            fichier.close();
            majProjetVoiture(nomProjet);
        }
    }
    else
        dialogueErreur("Erreur ouverture","veuillez entrez un nom de projet !");


}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_pushButtonNouveauProjet_clicked()
{
  // TO DO (étape 9)
  Garage::getInstance().resetProjetEnCours();
  videTableOption();
  setModele("",0,0,0,"");
  setPrix(0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_pushButtonNouveauContrat_clicked()
{
  // TO DO (étape 13)

    if(Garage::getInstance().employeLogger != NULL)
    {
        if(strcasecmp(Garage::getInstance().employeLogger->getFonction().c_str(),Employe::VENDEUR.c_str()) != 0)
        {
            dialogueErreur("Erreur contrat","L'employé connecter n'est pas un vendeur !");
        }
        else
        {   int ind;

            if((ind = getIndiceClientSelectionne()) == -1)
            {
                dialogueErreur("Erreur Contrat","Veuillez sélectionner un client pour lui créer un contrat !");
            }
            else
            {
                if(getNomProjetEnCours().size() == 0)
                {
                    dialogueErreur("Erreur Contrat","Veuillez choisir une projet de voiture !");
                }
                else
                {   
                    string nom = getNomProjetEnCours() + ".car";
                    ifstream fichier("Fichier Car/" + nom, ios::in);

                    if(!fichier.is_open())
                    {
                        dialogueErreur("Erreur Contrat","Le projet de voiture n'existe pas !");
                    }
                    else
                    {
                        fichier.close();
                        Contrat c;
                        c.setVendeur(Employe(*Garage::getInstance().employeLogger));
                        c.setClient(Client(Garage::getInstance().getClients()[ind]));
                        c.setNomProjet(getNomProjetEnCours());
                        c.setNum(Contrat::numCourant);
                        Garage::getInstance().ajouteContrat(c);

                        majTableContrat();
                    }
                    
                }
            }
        }
    }
    else
    {
        dialogueErreur("Erreur new contrat","Aucun n'employer n'est logger et ne peut faire de contrat !");
    }
    



}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_pushButtonSupprimerContrat_clicked()
{
  // TO DO (étape 13)
  int ind;

    if((ind =getIndiceContratSelectionne()) == -1)
    {
        dialogueErreur("Erreur de suppression","Veuillez sélectionner un contrat à supprimer !");
    }
    else
    {
        Iterateur<Contrat> itcontrat(Garage::getInstance().getContrat());

        int i;

        for(i = 0 , itcontrat.reset(); i < ind && !itcontrat.end();itcontrat++, i++);

        if(!itcontrat.end())
        {
            Garage::getInstance().getContrat().retire(ind);
            majTableContrat();
        }
    }
}       

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_pushButtonVisualiserVoiture_clicked()
{
    int ind;

    if((ind =getIndiceContratSelectionne()) == -1)
    {
        dialogueErreur("Erreur de suppression","Veuillez sélectionner un contrat à visualiser !");
    }
    Iterateur<Contrat> itcontrat(Garage::getInstance().getContrat());

    int i;

    for(i = 0 , itcontrat.reset(); i < ind && !itcontrat.end();itcontrat++, i++);

    if(!itcontrat.end())
    {
        
        string nom = Garage::getInstance().getContrat()[ind].getNomProjet() + ".car" ;

        ifstream fichier("Fichier Car/" + nom,ios::in);

        if(!fichier.is_open())
        {
            dialogueErreur("Erreur visualiser","Le Projet que vous souhaitez visualiser n'existe plus et va être supprimer");
            on_pushButtonSupprimerContrat_clicked();
        }
        else
        {
            fichier.close();
            majProjetVoiture(nom);
        }
    }

}

// Méthode rajoutée par moi-même


void ApplicGarageWindow::majTableOption()
{   
   for(int i = 0; i<5 && Garage::getInstance().getProjetEnCours()[i] != NULL; i++)
   {
        setTableOption(i,Garage::getInstance().getProjetEnCours()[i]->getCode(),Garage::getInstance().getProjetEnCours()[i]->getIntitule(),Garage::getInstance().getProjetEnCours()[i]->getPrix());  
   }
}

void ApplicGarageWindow::majProjetVoiture(string nomFichier) // met à jour l'interface graphique avec les infos du fichier .car récupérée
{   
    videTableOption();

    Garage::getInstance().getProjetEnCours().Load(nomFichier); 
    setNomProjetEnCours(Garage::getInstance().getProjetEnCours().getNom());
    Modele m(Garage::getInstance().getProjetEnCours().getModele());
    setModele(m.getNom(),m.getPuissance(),m.getMoteur(),m.getPrixDeBase(),m.getImage());
    setPrix(Garage::getInstance().getProjetEnCours().getPrix());

    majTableOption();
}


void ApplicGarageWindow::majTableEmploye() // met à jour l'interface graphique en parcourant le vecteur trié d'employé
{
    videTableEmployes();

    Iterateur<Employe> itE(Garage::getInstance().getEmployes()); 
    int i;

    for(i = 0, itE.reset(); !itE.end(); itE++,i++)
    {
        ajouteTupleTableEmployes(Garage::getInstance().getEmployes()[i].Tuple());
    }  
}

void ApplicGarageWindow::majTableClient()// met à jour l'interface graphique en parcourant le vecteur trié de client
{
    videTableClients();

    Iterateur<Client> itE(Garage::getInstance().getClients()); 
    int i;

    for(i = 0, itE.reset(); !itE.end(); itE++,i++)
    {
        ajouteTupleTableClients(Garage::getInstance().getClients()[i].Tuple());
    }  
}

void ApplicGarageWindow::majTableContrat() // met à jour l'interface graphique en parcourant le vecteur de contrat
{
    videTableContrats();

    int i;

    Iterateur<Contrat>ItC(Garage::getInstance().getContrat());

    for(i = 0 , ItC.reset(); !ItC.end(); ItC++,i++)
    {
        ajouteTupleTableContrats(Garage::getInstance().getContrat()[i].Tuple());
    }
}