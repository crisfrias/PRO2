// Dos tipus de correctesa:
// (MIRAR APUNTES PRO2 FIB !!!!)
/*

 ITERATIVA: (bucle)

    Invariant(Inv) -> sentencies que es compleixen
                    - abans
                    - durant
                    - després
                    (mirar les variables)

    Justificació -> 
                    - Inicialitzacions: justificar els valors que donem a les variables a la inicialitzacio
                    - Condició de sortida: justificar que les condicions de sortida fan que es compleixi l'invariant i per tant la post al sortir del bucle
                    - Cos del bucle: justificar el codi intern del bucle de manera que a cada iteració ens encarreguem que l'invariant es compleixi per la següent iteració
                    - Acabament: Justificar que el codi acaba


 
 RECURSIVA: (funció recursiva)

    Hipòtesi d'inducció ->  una per cada crida recursiva
                        ->  com la postcondició però aplicada al subconjunt afectat per la crida 

    Justificació -> 
                    - Casos senzills: Justificar casos base
                    - Cas recursiu: Basandonos en que se cumplen las hipotesis, justificar el caso recursivo
                    - Acabament: justificar que el codi s'acaba segur
*/