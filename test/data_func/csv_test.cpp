//
// Created by nickw on 08.03.22.
//

#include "dataframe.h"
#include "csv.h"
#include "catch.h"


TEST_CASE("Check if read equals write to csv", "correctness"){
    dataframe d = dataframe(5);
    int err = 1;
    for (int i = 0; i < 5; i++){
        d.y[i] = i;
        d.x[i] = i;
    }
    std::string DATA_PATH = "./test.out";
    write_csv(DATA_PATH, d);
    dataframe r = read_csv(DATA_PATH, &err);
    for (int i = 0; i < 5; i++){
        REQUIRE(((d.y[i] == r.y[i] && d.y[i] == i) && (d.x[i] == r.x[i] && r.x[i] == i)));
    }

}