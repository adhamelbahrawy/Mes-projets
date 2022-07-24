insert into Utilisateur values (1, 'Orville', 'Bennen', 'obennen0@studiopress.com', 'F6q9PjTv', 1);
insert into Utilisateur values (2, 'Oaker', 'Loïc', 'woaker1@statcounter.com', 'YvTIffypNIHH', 1);

insert into Recette
values 
(
    1, 1, 'Béchamel au Monsieur Cuisine', 'Bien évidemment M Cuisine obligatoire!', 'Très facile', 2, 820, 6, 10, 10,
    0, 0, NULL
);
insert into Recette
values
(
    2, 2, 'blabla soup', 'bla', 'Très facile', 1, 8, 1, 2, 2, 0,
    0, NULL
);
-- L'insertion d'image se fera par un block PL/SQL

insert into Ingredient values (1, 'Farine de blé', 'g', 340, 1.2, 72, 10);
insert into Ingredient values (2, 'Lait entier', 'mL', 65, 3.6, 4.8, 3.3);
insert into Ingredient values (3, 'Noix de muscade', 'g', 480, 40, 40, 0);
insert into Ingredient values (4, 'Beurre', 'g', 717, 81, 0.1, 0.9);
insert into Ingredient values (5, 'Sel', 'g', 0, 0, 0, 0);
insert into Ingredient values (6, 'Poivre noir', 'g', 255, 3.26, 0, 0);
insert into Ingredient values (7, 'bla powder', 'g', 255, 3.26, 0, 0);
insert into Ingredient values (8, 'Céleri', 'g', 16, 0.2, 1.16, 1.2);
insert into Ingredient values (9, 'Oignon', 'g', 43, 0.59, 7.37,1.25);
insert into Ingredient values (10, 'Cartotte', 'g', 32, 0.3, 6.6, 0.8);
-- insert into Ingredient values (11, 'Cartotte', 'g', 32, 0.3, 6.6, 0.8);
-- insert into Ingredient values (12, 'Cartotte', 'g', 32, 0.3, 6.6, 0.8);
-- insert into Ingredient values (13, 'Cartotte', 'g', 32, 0.3, 6.6, 0.8);
-- insert into Ingredient values (14, 'Cartotte', 'g', 32, 0.3, 6.6, 0.8);
-- insert into Ingredient values (15, 'Cartotte', 'g', 32, 0.3, 6.6, 0.8);
-- insert into Ingredient values (16, 'Cartotte', 'g', 32, 0.3, 6.6, 0.8);
-- insert into Ingredient values (17, 'Cartotte', 'g', 32, 0.3, 6.6, 0.8);
-- insert into Ingredient values (18, 'Cartotte', 'g', 32, 0.3, 6.6, 0.8);
-- insert into Ingredient values (19, 'Cartotte', 'g', 32, 0.3, 6.6, 0.8);
-- insert into Ingredient values (20, 'Cartotte', 'g', 32, 0.3, 6.6, 0.8);
-- insert into Ingredient values (21, 'Cartotte', 'g', 32, 0.3, 6.6, 0.8);
-- insert into Ingredient values (22, 'Cartotte', 'g', 32, 0.3, 6.6, 0.8);

insert into Regime values (1, 'Végeratien');
insert into Regime values (2, 'Végan');
insert into Regime values (3, 'Sans gluten');

insert into Interdiction values (1, 3);
insert into Interdiction values (2, 2);
insert into Interdiction values (4, 2);

insert into Categorie values (1, 'Farines');
insert into Categorie values (2, 'Laits');
insert into Categorie values (3, 'Épices');
insert into Categorie values (4, 'Gras');

insert into Appartient values (1, 1);
insert into Appartient values (2, 2);
insert into Appartient values (3, 3);
insert into Appartient values (4, 4);
insert into Appartient values (3, 5);
insert into Appartient values (3, 6);

--0 UMesures = optionnel/au goût (pas pertinent pour calculer les calories)
begin
    insert into Quantite values (1, 1, 60);
    insert into Quantite values (1, 2, 500);
    insert into Quantite values (1, 3, 0.05);
    insert into Quantite values (1, 4, 40);
    insert into Quantite values (1, 5, 0.5);
    insert into Quantite values (1, 6, 0.1);
    update Quantite set Quantite = 40 where idIngredient = 4 and idRecette = 1;
end;
/
-- insert into Quantite values (1, 7, 0.1);
-- insert into Quantite values (1, 8, 0.1);
-- insert into Quantite values (1, 9, 0.1);
-- insert into Quantite values (1, 10, 0.1);
-- insert into Quantite values (1, 11, 0.1);
-- insert into Quantite values (1, 12, 0.1);
-- insert into Quantite values (1, 13, 0.1);
-- insert into Quantite values (1, 14, 0.1);
-- insert into Quantite values (1, 15, 0.1);
-- insert into Quantite values (1, 16, 0.1);
-- insert into Quantite values (1, 17, 0.1);
-- insert into Quantite values (1, 18, 0.1);
-- insert into Quantite values (1, 19, 0.1);
-- insert into Quantite values (1, 20, 0.1);
-- insert into Quantite values (1, 21, 0.1);--erreur
-- insert into Quantite values (2, 22, 0.1);
begin
    insert into Quantite values (2, 7, 3);
    update Quantite set Quantite = 100 where idIngredient = 7 and idRecette = 2;
end;
/

insert into Etape values (1, 1, 'Faites fondre le beurre dans la cuve du Monsieur Cuisine pendant 2 min / vit. 1 / 90°C.', NULL);
insert into Etape values (1, 2, 'Patientez pendant 1 minute. Laissez refroidir la cuve, puis ajoutez la farine et remuez sans colorer pendant 30 sec / vit. 3 / 0 °C. La farine doit juste épaissir pendant quelques secondes.',NULL);
insert into Etape values (1, 3, 'Progressivement, en maintenant le mélange, versez le lait jusqu’à ce que la sauce épaississe avec le batteur / 10 min / vit. 2 / 90 °C.',NULL);
insert into Etape values (1, 4, 'Assaisonnez de sel, de poivre et de muscade.',NULL);

insert into Inventaire values (1, 1, 100);
insert into Inventaire values (1, 5, 4);
insert into Inventaire values (1, 6, 3);

insert into Liste values (1, 2, 500, to_date('25/11/2021', 'DD/MM/YYYY'));
insert into Liste values (1, 3, 0.05, to_date('25/11/2021', 'DD/MM/YYYY'));
insert into Liste values (1, 4, 40, to_date('25/11/2021', 'DD/MM/YYYY'));
insert into Liste values (2, 2, 500, to_date('26/01/2022', 'DD/MM/YYYY'));--erreur

insert into Planning values (1, 1, to_date('25/11/2021', 'DD/MM/YYYY'), 6);