#include "TrafficModel.h"

TrafficModel::TrafficModel() { }
TrafficModel::~TrafficModel(){ }

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
	// for (unsigned int i = 0; i < commands.size(); i++) {
	// 	string id_substr = commands[i].substr(0, commands[i].find(","));
	// 	string dir_substr = commands[i].substr(commands[i].find(",")+1);
	// 	int id;
	// 	int dir;
	// 	istringstream(id_substr) >> id;
	// 	istringstream(dir_substr) >> dir;
	// 	for (unsigned int j = 0; j < platoons.size(); j++) {
	// 		Car *car = platoons[j].search(id);
	// 		if (car == nullptr) {
	// 			break;
	// 		} else {
	// 			if (dir == 1 && j != 0 && platoons[j-1].searchPos(car->get_position()) == nullptr) {
	// 				platoons[j].remove(car);
	// 				platoons[j-1].insert(car);
	// 			} else if (dir == 2 && j != platoons.size()-1 && platoons[j+1].searchPos(car->get_position()) == nullptr) {
	// 				platoons[j].remove(car);
	// 				platoons[j+1].insert(car);
	// 			}
	// 		}		
	// 	}
	// }
	vector<int> ids;
	vector<int> dirs;

	for (unsigned int i = 0; i < commands.size(); i++) {
		string id_substr = commands[i].substr(0, commands[i].find(","));
		string dir_substr = commands[i].substr(commands[i].find(",")+1);
		int id;
		int dir;
		istringstream(id_substr) >> id;
		istringstream(dir_substr) >> dir;
		ids.push_back(id);
		dirs.push_back(dir);
	}

	for (unsigned int i = 0; i < platoons.size(); i++) {
		Car *car = platoons[i].get_head();
		vector<int>::iterator it;
		while (car != nullptr) {
			it = find(ids.begin(), ids.end(), car->get_id());	
			if (it != ids.end()) {
				int dir = dirs[distance(it,ids.begin())];
				if (dir == 1 && i != 0 && platoons[i-1].searchPos(car->get_position()) == nullptr) {
					platoons[i].remove(car);
					platoons[i-1].insert(car);
				} else if (dir == 2 && i != platoons.size()-1 && platoons[i+1].searchPos(car->get_position()) == nullptr) {
					platoons[i].remove(car);
					platoons[i+1].insert(car);
				}
			} else {	
				car->set_position(car->get_position()+1);
			}

			car = car->get_prev();
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
