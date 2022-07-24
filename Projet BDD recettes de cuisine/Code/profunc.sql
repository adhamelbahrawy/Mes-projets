--1 Définir une fonction qui change le nom d’un ingrédient par un autre dans les étapes de réalisation d’une recette.
CREATE OR REPLACE FUNCTION chNomIEt(idR_p integer, ing_p varchar, sub_p varchar)
return varchar
is
begin
    update Etape
       set Instruction = REPLACE(Instruction, 'beurre', 'huile')
    where idRecette = 1;
    return 'Done';
end;
/
show ERRORS FUNCTION chNomIEt;
--test
declare
    string varchar(8);
begin
    commit;
    string := chNomIEt(1, 'beurre', 'huile');
    DBMS_OUTPUT.PUT_LINE(string);
    commit;
end;
/
-- declare
--     res integer;
-- begin
--     commit;
--     res := 2 * 8;
--     DBMS_OUTPUT.PUT_LINE(res);
--     commit;
-- end;
-- /

--2
