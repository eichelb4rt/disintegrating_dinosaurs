//
// Created by nickw on 08.03.22.
//
#include "dataframe.h"
#include "csv.h"
#include "catch.h"

TEST_CASE("Check dataframe copy with dataframe containing numbers 1-5 in x and y", "correctness"){
    dataframe d = dataframe(5);
    for (int i = 0; i < 5; i++){
        d.y[i] = i;
        d.x[i] = i;
    }
    dataframe r = d.copy();
    for (int i = 0; i < 5; i++){
        REQUIRE(((d.y[i] == r.y[i] && d.y[i] == i) && (d.x[i] == r.x[i] && r.x[i] ==  i)) );
    }

}