--1 Pas plus de 20 ingrédients par recettes.
CREATE OR REPLACE TRIGGER IU_Quantite1
BEFORE INSERT or UPDATE on Quantite
for EACH ROW
declare 
    pragma autonomous_transaction;
    idR_v integer;
    nbIng_v number;
begin
    idR_v := :new.idRecette;
    select count(*) into nbIng_v
    from Quantite
    where idRecette = idR_v;
    if nbIng_v >= 20 THEN
        RAISE_APPLICATION_ERROR(-20200, 'La recette ' || idR_v || ' a déjà 20 ingrédients');
    end if;
end;
/

--2 La liste des ingrédients à acheter ne peut pas être générée plus d’un mois à l’avance.
CREATE or REPLACE trigger IU_Liste
BEFORE INSERT or UPDATE on Liste
for EACH ROW
declare
    gap integer;
begin
    gap := MONTHS_BETWEEN(:new.DateExpL, SYSDATE);
    if gap >= 1 THEN
        RAISE_APPLICATION_ERROR(-20200, 'La liste des ingrédients à acheter pour l''Utilisateurs' || :new.idUtilisateur ||' ne peut pas être générée plus d’un mois à l’avance.');
    end if;
end;
/

--3 La durée d’une recette est égale au moins au minimum de la durée de ses étapes.
CREATE or REPLACE trigger IU_Recette
BEFORE INSERT or update on Recette
for EACH ROW
when (new.TTotal != (new.TPrep + new.TCuisson + new.TAttente))
begin
    RAISE_APPLICATION_ERROR(-20200, 'La durée d’une recette est égale au moins au minimum de la durée de ses étapes.');
end;
/

--4 Le nombre de calorie d’une recette est similaire à celui de la somme des calories de ses ingrédients (+/- 20%).
-- Pré : modification d'une seule recette à la fois. Après avoir essayé avec un curseur qui ne marchait pas du tout
--       nous avons decidé que celle là est la meilleure solution. L'insertion initiale  de quantité se fait avec 
--       une transaction atomique se terminant avec un update qui fait rien.  
CREATE or REPLACE TRIGGER U_Quantite4
after update on Quantite
for each row
declare
    pragma autonomous_transaction;
    KcalTheo_v INTEGER;
    kcalCalc_v number;
begin
select R.Kcal into Kcaltheo_v
from Recette R where R.idRecette = :new.idRecette;
select sum(I.Kcal * Q.Quantite /100) into kcalCalc_v
from Ingredient I, Quantite Q
where Q.idIngredient = I.idIngredient and Q.idRecette = :new.idRecette;

if (not((0.8*kcalCalc_v <= KcalTheo_v) and (KcalTheo_v <= 1.2*kcalCalc_v))) THEN
        RAISE_APPLICATION_ERROR(-20200, 'Le nombre de calorie de la recette '|| :new.idRecette ||' n''est pas similaire à celui de la somme des calories de ses ingrédients (+/- 20%).');
end if;
end;
/

declare
    pragma autonomous_transaction;
begin
    ROLLBACK;
end;
/
