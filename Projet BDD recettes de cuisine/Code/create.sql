CREATE TABLE Utilisateur
(
    idUtilisateur INTEGER,
    Nom varchar(32),
    Prenom varchar(32),
    Mail varchar(32),
    MDP varchar(16),
    Authentifier INTEGER,
    CONSTRAINT PK_Utilisateur PRIMARY KEY (idUtilisateur),
    CONSTRAINT CK_Utilisateur_Mail CHECK (REGEXP_LIKE (Mail, '^[A-Za-z]+[A-Za-z0-9.]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,4}$')),
    CONSTRAINT CK_Utilisateur_MDP CHECK (LENGTH(MDP) >= 6 AND MDP NOT LIKE(Mail)),
    CONSTRAINT CK_Utilisateur_Authentifier CHECK ((authentifier = 0) OR (authentifier = 1))
);

CREATE TABLE Recette
(
    idRecette INTEGER,
    idUtilisateur INTEGER,
    NomR varchar(32),
    Descriptif varchar(2048) DEFAULT NULL,
    Difficulte varchar(16),
    Prix INTEGER,
    Kcal INTEGER NOT NULL,
    NbPersonnes INTEGER,
    TTotal INTEGER NOT NULL,
    TPrep INTEGER DEFAULT 0,
    TCuisson INTEGER DEFAULT 0,
    TAttente INTEGER DEFAULT 0,
    IllustrationR BLOB DEFAULT NULL,
    CONSTRAINT PK_Recette PRIMARY KEY (idRecette),
    CONSTRAINT FK_Recette_idUtilisateur FOREIGN KEY (idUtilisateur) REFERENCES Utilisateur (idUtilisateur),
    CONSTRAINT CK_Recette_Difficulte CHECK (Difficulte IN ('Très facile', 'Facile', 'Moyenne', 'Un peu difficile', 'Difficile')),
    CONSTRAINT CK_Recette_Prix CHECK (Prix >= 1 AND Prix <= 5 ),
    CONSTRAINT CK_Recette_NbPersonnes CHECK (NbPersonnes >= 1),
    CONSTRAINT CK_Recette_TTotal CHECK (TTotal > 0),
    CONSTRAINT CK_Recette_Kcal CHECK (Kcal > 0)
);

CREATE TABLE Ingredient
(
    idIngredient INTEGER,
    NomI VARCHAR(16) NOT NULL,
    UMesure VARCHAR(4),
    --Pour 100 g/ml/unités par defaut
    Kcal INTEGER DEFAULT 0,
    Lipides DECIMAL(4,2) DEFAULT 0,
    Glucides DECIMAL(4,2) DEFAULT 0,
    Protides DECIMAL(4,2) DEFAULT 0,
    CONSTRAINT PK_Ingredient PRIMARY KEY (idIngredient),
    CONSTRAINT CK_Ingredient_UMesure CHECK (UMesure IN ('g', 'mL', 'unités'))
);

CREATE TABLE Regime
(
    idRegime INTEGER,
    Nom VARCHAR(16),
    CONSTRAINT PK_Regime PRIMARY KEY (idRegime)
);

CREATE TABLE Interdiction
(
    idIngredient INTEGER,
    idRegime INTEGER,
    CONSTRAINT PK_Interdiction PRIMARY KEY (idIngredient, idRegime),
    CONSTRAINT FK_Interdiction_idIngredient FOREIGN KEY (idIngredient) REFERENCES Ingredient (idIngredient),
    CONSTRAINT FK_Interdiction_idRegime FOREIGN KEY (idRegime) REFERENCES Regime (idRegime)
);

CREATE TABLE Categorie
(
    idCategorie INTEGER,
    Nom VARCHAR(16),
    CONSTRAINT PK_Categorie PRIMARY KEY (idCategorie)
);

CREATE TABLE Appartient
(
    idCategorie INTEGER,
    idIngredient INTEGER,
    CONSTRAINT PK_Substitutions PRIMARY KEY (idCategorie, idIngredient),
    CONSTRAINT FK_Appartient_idCategorie FOREIGN KEY (idCategorie) REFERENCES Categorie (idCategorie),
    CONSTRAINT FK_Appartient_idIngredient FOREIGN KEY (idIngredient) REFERENCES Ingredient (idIngredient)
);

CREATE TABLE Quantite
(
    idRecette INTEGER,
    idIngredient INTEGER,
    Quantite DECIMAL(8,2),
    CONSTRAINT PK_Quantite PRIMARY KEY (idRecette, idIngredient),
    CONSTRAINT FK_Quantite_idRecette FOREIGN KEY (idRecette) REFERENCES Recette (idRecette),
    CONSTRAINT FK_Quantite_idIngredient FOREIGN KEY (idIngredient) REFERENCES Ingredient (idIngredient),
    CONSTRAINT CK_Quantite_Quantite CHECK (Quantite > 0)
);

CREATE TABLE Etape
(
    idRecette INTEGER,
    idEtape INTEGER,
    Instruction VARCHAR(2048) NOT NULL,
    IllustrationE BLOB DEFAULT NULL,
    CONSTRAINT PK_Etape PRIMARY KEY (idRecette, idEtape),
    CONSTRAINT FK_Etape_idRecette FOREIGN KEY (idRecette) REFERENCES Recette(idRecette)
);

CREATE TABLE Inventaire
(
    idUtilisateur INTEGER,
    idIngredient INTEGER,
    Quantite DECIMAL(8,2),
    CONSTRAINT PK_Inventaire PRIMARY KEY (idUtilisateur, idIngredient),
    CONSTRAINT FK_Inventaire_idUtilisateur FOREIGN KEY (idUtilisateur) REFERENCES Utilisateur(idUtilisateur),
    CONSTRAINT FK_Inventaire_idIngredient FOREIGN KEY (idIngredient) REFERENCES Ingredient(idIngredient),
    CONSTRAINT CK_Inventaire_Quantite CHECK (Quantite > 0) 
);

CREATE TABLE Liste
(
    idUtilisateur INTEGER,
    idIngredient INTEGER,
    Quantite DECIMAL(8,2),
    DateExpL date,
    CONSTRAINT PK_Liste PRIMARY KEY (idUtilisateur, idIngredient),
    CONSTRAINT FK_Liste_idUtilisateur FOREIGN KEY (idUtilisateur) REFERENCES Utilisateur(idUtilisateur),
    CONSTRAINT FK_Liste_idIngredient FOREIGN KEY (idIngredient) REFERENCES Ingredient(idIngredient),
    CONSTRAINT CK_Liste_Quantite CHECK (Quantite > 0)
);

CREATE TABLE ArchiveListe
(
    idUtilisateur INTEGER,
    idIngredient INTEGER,
    Quantite DECIMAL(8,2),
    DateExpL date,
    CONSTRAINT PK_ArchiveListe PRIMARY KEY (idUtilisateur, idIngredient),
    CONSTRAINT FK_ArchiveListe_idUtilisateur FOREIGN KEY (idUtilisateur) REFERENCES Utilisateur(idUtilisateur),
    CONSTRAINT FK_ArchiveListe_idIngredient FOREIGN KEY (idIngredient) REFERENCES Ingredient(idIngredient),
    CONSTRAINT CK_ArchiveListe_Quantite CHECK (Quantite > 0)
);

CREATE TABLE Planning
(
    idUtilisateur INTEGER,
    idRecette INTEGER,
    DateExpP date,
    NbPersonnes INTEGER,
    CONSTRAINT PK_Planning PRIMARY KEY (idUtilisateur, idRecette),
    CONSTRAINT FK_Planning_idUtilisateur FOREIGN KEY (idUtilisateur) REFERENCES Utilisateur(idUtilisateur),
    CONSTRAINT FK_Planning_idRecette FOREIGN KEY (idRecette) REFERENCES Recette(idRecette),
    CONSTRAINT CK_Panning_NbPersonnes CHECK (NbPersonnes > 0)
);

CREATE TABLE ArchivePlanning
(
    idUtilisateur INTEGER,
    idRecette INTEGER,
    DateExpAP date,
    NbPersonnes INTEGER,
    CONSTRAINT PK_Archlanning PRIMARY KEY (idUtilisateur, idRecette),
    CONSTRAINT FK_ArchPlanning_idUtilisateur FOREIGN KEY (idUtilisateur) REFERENCES Utilisateur(idUtilisateur),
    CONSTRAINT FK_ArchPlanning_idRecette FOREIGN KEY (idRecette) REFERENCES Recette(idRecette),
    CONSTRAINT CK_ArchPlanning_NbPersonnes CHECK (NbPersonnes > 0)
);