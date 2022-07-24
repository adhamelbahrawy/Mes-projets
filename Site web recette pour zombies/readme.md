# PROJET DÉVELOPPEMENT WEB 2

J'ai plutot choisi une architecture multipage parceque c'était plus simple et évident pour moi à faire.

## Les différentes pages sont :

### index.php : Page principale

### newrecep.php : Contient le formulaire de saisie

### receps.php : Contient les différentes recettes dans la BD

### contact.php : Contient la section contactez nous

### about.php : Contient la section à propos de nous

## La BDD recep.db contient la table recep dont les champs sont :

### id : clé primaire de la table; INTEGER (entier)

### recep_name : Nom de la recette; VARCHAR(50) NOT NULL

### first_name : Prénom de l'auteur de la recette; VARCHAR(50) NOT NULL

### last_name : Son nom; VARCHAR(50) NOT NULL

### recepie : La recette elle-même TEXT NOT NULL

## Front
Le répertoire Front contient la feuille de style ainsi que le javascript s'occupant du formulaire
## Back
Le répertoire Back contient les sections redondantes ainsi que la traduction