#include <gtest/gtest.h>
#include <vector>

#include "Car.h"
#include "Platoon.h"

using std::vector;

class PlatoonTest : public ::testing::Test {
    protected:
        vector<Car*> *carVector;
        Platoon *platoon;

        PlatoonTest();
        ~PlatoonTest();

        void SetUp() override;
        void TearDown() override;
};

int run(int argc, char **argv);
