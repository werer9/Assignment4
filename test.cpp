#include "test.h"

PlatoonTest::PlatoonTest() 
{
    carVector = new vector<Car*>(); 
    platoon = new Platoon("");   
}

PlatoonTest::~PlatoonTest() 
{
    delete carVector;
    delete platoon;
}

void PlatoonTest::SetUp() 
{
    for (int i = 0; i < 10; i++) {
        this->carVector->push_back(new Car(i, i));
    }
}

void PlatoonTest::TearDown() {}

int run(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST_F(PlatoonTest, test_get_tail) 
{
    EXPECT_EQ(platoon->get_tail(), nullptr);
}

TEST_F(PlatoonTest, test_get_head) 
{
    EXPECT_EQ(platoon->get_head(), nullptr);
}

TEST_F(PlatoonTest, test_insert) 
{
    platoon->insert(carVector->at(3));
    Car *car = platoon->get_head();
    ASSERT_NE(nullptr, car);
    bool wasInserted = false;
    while (car != nullptr) {
        if (car == carVector->at(3)) {
            wasInserted = true;
            break;
        }
        car = car->get_prev();
    } 

    ASSERT_TRUE(wasInserted);

    platoon->insert(carVector->at(1));
    platoon->insert(carVector->at(9));

    ASSERT_EQ(platoon->get_tail(), carVector->at(9));
    ASSERT_EQ(platoon->get_head(), carVector->at(1));
    ASSERT_EQ(platoon->get_head()->get_prev(), carVector->at(3));
    ASSERT_EQ(platoon->get_tail()->get_next(), carVector->at(3));
}

TEST_F(PlatoonTest, test_append) 
{
    platoon->insert(carVector->at(1));
    platoon->insert(carVector->at(8));
    platoon->append(carVector->at(2));

    ASSERT_NE(nullptr, platoon->get_tail());
    ASSERT_EQ(carVector->at(8), platoon->get_tail());

    platoon->append(carVector->at(9));
    ASSERT_EQ(carVector->at(9), platoon->get_tail());
}

TEST_F(PlatoonTest, test_prepend) 
{
    platoon->insert(carVector->at(2));
    platoon->insert(carVector->at(9));
    platoon->prepend(carVector->at(3));

    ASSERT_NE(nullptr, platoon->get_tail());
    ASSERT_EQ(carVector->at(2), platoon->get_head());

    platoon->prepend(carVector->at(1));
    ASSERT_EQ(carVector->at(1), platoon->get_head());
}

TEST_F(PlatoonTest, test_remove) 
{
    platoon->insert(carVector->at(1));
    platoon->insert(carVector->at(3));
    platoon->insert(carVector->at(2));
    
    Car *removeCar;
    removeCar = platoon->get_head();
    ASSERT_NE(nullptr, removeCar);
    removeCar = removeCar->get_prev();
    platoon->remove(removeCar);
    Car* car = platoon->get_head();
    while (car != nullptr) {
        ASSERT_NE(car, removeCar);
        car = car->get_next();
    }
}

TEST_F(PlatoonTest, test_searches)
{
    platoon->insert(carVector->at(1));
    platoon->insert(carVector->at(3));
    platoon->insert(carVector->at(2));

    ASSERT_EQ(platoon->search(3)->get_id(), 3);
    ASSERT_EQ(platoon->search(9), nullptr);

    ASSERT_EQ(platoon->searchPos(2)->get_position(), 2);
    ASSERT_EQ(platoon->search(7), nullptr);

}
