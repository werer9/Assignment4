#ifndef _Platoon_H_
#define _Platoon_H_

#include <vector>
#include <string>
#include <sstream>
#include "Car.h"

using namespace std;

class Platoon
{
    private:
        Car* head = NULL;
        Car* tail = NULL;

        /**
         * @brief Add car at pointer c to tail
         * 
         * @return void
        */
        void append(Car* c); 

        /**
         * @brief Add car at pointer c to head
         * 
         * @return void
        */
        void prepend(Car* c); 

    public:
        /**
         * @brief Construct a new Platoon object
         * 
         * @param init 
         */
        Platoon(string init);
        /**
         * @brief Get the tail object
         * 
         * @return Car* 
         */
        Car* get_tail();

        /**
         * @brief Get the head object
         * 
         * @return Car* 
         */
        Car* get_head();

        /**
         * @brief Remove car pointed by c if it is in platoon
         * 
         * @return void
         * 
        */
        void remove(Car* c); 

        /**
         * @brief Insert car in correct position of platoon
         * 
         * Head contains car with highest position value and tail 
         * contains the car with the lowest position value.
         * 
         * @return void
         * 
        */
        void insert(Car* c);
};
#endif
