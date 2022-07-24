--1 Les recettes qui ont moins de 200 calories par personne, dont tous les ingrédients sont sans
--  gluten et qui apparaissent sur le planning d’un utilisateur.
with noSgI as --Igrédients avec gluten
(
    select idIngredient  
    from Interdiction I
    natural join Regime Reg 
    where Reg.Nom = 'Sans gluten'
),
noSgR as --Recettes contenant des ingrédients avec gluten
(
    select distinct Q.idRecette 
    from Quantite Q, noSgI
    where 
    Q.idIngredient in (select * from noSgI)
)
select distinct R.idRecette
from Recette R, noSgR, Planning P
where
    R.idRecette != noSgR.idRecette And (R.Kcal/R.NbPersonnes) <= 200 And P.idRecette = R.idRecette;

--2 La recette la plus souvent présente dans des plannings d’utilisateurs.
with T as (select idRecette, count(*) as c from Planning group by idRecette order by idRecette desc)
select idRecette
from T
where T.c = (select max(c) from T);

--3 Pour chaque ingrédient, nombre de recette et nombre de catégorie dans lesquelles il apparaît
select I.idIngredient, count(A.idIngredient) as nbCat, count(Q.idIngredient) as nbR 
from Ingredient I, Appartient A, Quantite Q
where (I.idIngredient = A.idIngredient And I.idIngredient = Q.idIngredient)
group by I.idIngredient
order by I.idIngredient asc;

--4 Les utilisateurs qui n’ont ajouté à la base de données que des recettes végétariennes.
with noVegeI as --Igrédients pas végétariens
(
    select idIngredient  
    from Interdiction I
    natural join Regime Reg 
    where Reg.Nom = 'Végetarien'
),
noVegeR as --Recettes pas végetariennes
(
    select distinct Q.idRecette 
    from Quantite Q, noVegeI
    where 
    Q.idIngredient in (select * from noVegeI)
)
select distinct R.idUtilisateur
from Recette R
where R.idRecette not in (select * from noVegeR);

--5 Pour chaque utilisateur, son login, son nom, son prénom, son adresse, son nombre de recette créé, son nombre d’ingrédients
--  enregistrés, le nombre de recette qu’il a prévu de réaliser
with NbR as
(
    select U.idUtilisateur, count(R.idRecette) as NbR
    from Utilisateur U
    left outer join Recette R on U.idUtilisateur = R.idUtilisateur
    group by U.idUtilisateur
),
NbI as
(
    select U.idUtilisateur, count(I.idIngredient) as NbI
    from Utilisateur U
    left outer join Inventaire I on U.idUtilisateur = I.idUtilisateur
    group by U.idUtilisateur
),
NbP as
(
    select U.idUtilisateur, count(P.idRecette) as NbP
    from Utilisateur U
    left outer join Planning P on U.idUtilisateur = P.idUtilisateur
    group by U.idUtilisateur
)
select U.idUtilisateur, Nom, Prenom, Mail, NbR.NbR "Recettes créées", NbI.NbI "Ingrédients enregistrés", NbP.NbP "Recettes planifiées"
from Utilisateur U, NbR, NbI, NbP
where U.idUtilisateur = NbR.idUtilisateur and U.idUtilisateur = NbI.idUtilisateur and U.idUtilisateur = NbP.idUtilisateur;