Problem:    diet
Rows:       10
Columns:    20
Non-zeros:  179
Status:     OPTIMAL
Objective:  cost = 0.1381709355 (MINimum)

   No.   Row name   St   Activity     Lower bound   Upper bound    Marginal
------ ------------ -- ------------- ------------- ------------- -------------
     1 nb[Calorie]  NS             3             3             =     0.0235412 
     2 nb[Protein]  NS            70            70             =   0.000177673 
     3 nb[Calcium]  NS           0.8           0.8             =    0.00184258 
     4 nb[Iron]     NS            12            12             =    -0.0091898 
     5 nb[Vitamin-A]
                    NS             5             5             =    0.00133941 
     6 nb[Vitamin-B1]
                    NS           1.8           1.8             =     0.0315114 
     7 nb[Vitamin-B2]
                    NS           2.7           2.7             =      0.026969 
     8 nb[Niacin]   NS            18            18             =   0.000915647 
     9 nb[Vitamin-C]
                    NS            75            75             =   0.000149308 
    10 cost         B       0.138171                             

   No. Column name  St   Activity     Lower bound   Upper bound    Marginal
------ ------------ -- ------------- ------------- ------------- -------------
     1 x[Wheat]     B      0.0180918             0               
     2 x[Cornmeal]  B      0.0170207             0               
     3 x[Cannedmilk]
                    B      0.0452014             0               
     4 x[Margarine] NL             0             0                    0.485022 
     5 x[Cheese]    NL             0             0                    0.546295 
     6 x[Peanut-B]  B     0.00317017             0               
     7 x[Lard]      B      0.0243964             0               
     8 x[Liver]     B       0.015273             0               
     9 x[Porkroast] NL             0             0                    0.448715 
    10 x[Salmon]    NL             0             0                    0.779495 
    11 x[Greenbeans]
                    NL             0             0                     1.10043 
    12 x[Cabbage]   B     0.00921709             0               
    13 x[Onions]    NL             0             0                      0.8437 
    14 x[Potatoes]  B      0.0051373             0               
    15 x[Spinach]   B    0.000663078             0               
    16 x[Sweet-Pot] NL             0             0                   0.0795885 
    17 x[Peaches]   NL             0             0                     2.04223 
    18 x[Prunes]    NL             0             0                     1.64017 
    19 x[Limabeans] NL             0             0                     2.64438 
    20 x[Navybeans] NL             0             0                     5.25144 

Karush-Kuhn-Tucker optimality conditions:

KKT.PE: max.abs.err = 2.60e-15 on row 8
        max.rel.err = 7.52e-17 on row 5
        High quality

KKT.PB: max.abs.err = 0.00e+00 on row 0
        max.rel.err = 0.00e+00 on row 0
        High quality

KKT.DE: max.abs.err = 1.99e-16 on column 19
        max.rel.err = 3.77e-17 on column 17
        High quality

KKT.DB: max.abs.err = 0.00e+00 on row 0
        max.rel.err = 0.00e+00 on row 0
        High quality

End of output
