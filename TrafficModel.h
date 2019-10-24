#ifndef _TrafficModel_H_
#define _TrafficModel_H_

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <sstream>
#include <cstring>
#include "Platoon.h"

#include "Car.h"

using namespace std;

class TrafficModel
{
	private:
		vector<Platoon> platoons;
		vector<string> commands; // stores a set of lane change commands
		vector<int> executed_commands; // ids of cars that have had their command executed

		/**
		 * @brief Increment the position of a car, c
		 * 
		 * @param c 
		 */
		void update_position(Car *c);

		/**
		 * @brief Checks if car id is in list of cars that have changes lanes
		 * 
		 * @param id 
		 * @return true 
		 * @return false 
		 */
		bool is_command_complete(int id);

	public:
		TrafficModel();
		~TrafficModel();

		int get_lane_change_command(int id);
		void set_commands(vector<string> commands);
		void initialize(vector<string> info);
		void update();
		vector<string> get_system_state();
};


#endif 
