#include "TrafficModel.h"

TrafficModel::TrafficModel() { }
TrafficModel::~TrafficModel(){ }

void TrafficModel::update_position(Car *c)
{
	if (c == nullptr)
		return;
	if (c->get_prev() == nullptr || c->get_prev()->get_position() != c->get_position()+1) {
		c->set_position(c->get_position()+1);
	}
}

bool TrafficModel::is_command_complete(int id) {	
	for (unsigned i = 0; i < executed_commands.size(); i++) {
		if (id == executed_commands[i]) {
			return true;
		}
	}

	return false;
}

void TrafficModel::set_commands(vector<string> commands)
{
	this->commands = commands;
}

/* A helper function. 
 * Given a specific id as the input, it searches the lane change command stored in
 * "commands". Returns the value of the turn-light in the command for this car id.
 * 0 = no light, 1 = left light, 2 = right light.
 */
int TrafficModel::get_lane_change_command(int id)
{
	int count = commands.size();
	for (int i = 0; i < count; i++){
		size_t found = commands[i].find(',');
		string iter_id = commands[i].substr(0, found);
		string light = commands[i].substr(found+1, commands[i].size()-1);
		stringstream ss1(iter_id);
		int id_value;
		ss1 >> id_value;
		if (id_value == id){
			stringstream ss2(light);
			int light_value;
			ss2 >> light_value;
			return light_value;
		}
	}
	return 0;
}

/*
 * The function that updates the vehicle positions and states.
 */
void TrafficModel::update()
{
	// iterate over the platoons in the model
	for (unsigned i = 0; i < platoons.size(); i++) {
		// iterate over the platoon
		Car *car = platoons[i].get_head();
		Car *temp = nullptr;
		while (car != nullptr) {
			// check which command is being executed on the car
			switch (get_lane_change_command(car->get_id())) {
				// go straight
				case 0:
					update_position(car);
					break;
				// change lane to the left if it is available and command not yet exectuted
				case 1:
					if (is_command_complete(car->get_id())) {
						break;
					} else if (i == 0 || !platoons[i-1].is_position_empty(car->get_position())) {
						update_position(car);
					} else {
						// get next car and store it in temporary pointer
						temp = car->get_next();
						// change lanes
						platoons[i].remove(car);
						platoons[i-1].insert(car);
						// mark lane change completed in executed_commands vector
						executed_commands.push_back(car->get_id());
					}
					break;
				case 2:
					// change lane to the right if it is available and command not yet exectuted
					if (is_command_complete(car->get_id())) {
						break;
					} else if (i == platoons.size()-1 || !platoons[i+1].is_position_empty(car->get_position())) {
						update_position(car);
					} else {
						temp = car->get_next();
						platoons[i].remove(car);
						platoons[i+1].insert(car);
						executed_commands.push_back(car->get_id());
					}
					break;
				default:
					break;
			}

			// clear executed commans vector for next tick
			executed_commands.empty();
			// if a lange change has occured, pass next car through temp
			if (temp != nullptr) {
				car = temp;
				temp = nullptr;
			} else {
				car = car->get_next();
			}
		}
	}
}


/*
 * Initialization based on the input information
 */
void TrafficModel::initialize(vector<string> info)
{
	int lane_count = info.size();
	for (int i = 0; i < lane_count; i++){
		Platoon p = Platoon(info[i]);
		platoons.push_back(p);
	}
}

// Returns all the vehicle states in the system
vector<string> TrafficModel::get_system_state()
{
	vector<string> output;
	int size = platoons.size();
	for (int i = 0; i < size; i++){
		// get the last vehicle in the platoon
		Car* temp = platoons[i].get_tail();
		string s = "";
		ostringstream out;
		while (temp != NULL){
			out << ";(" << temp->get_id() << "," << i << "," << temp->get_position() << \
					 "," << get_lane_change_command(temp->get_id()) << ")";
			temp = temp->get_prev();
		}

		output.push_back(out.str());
	}
	return output;
}
