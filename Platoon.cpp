#include "Platoon.h"

Platoon::Platoon(string init)
{
    // the string 'init' looks like:
    // a,b ; c,d ; ... where, a and c are the vehicle id, b and d are positions.
    stringstream ss(init);
	string segment;
	while(getline(ss, segment, ';'))
	{
		size_t found = segment.find(",");
		if (found!=std::string::npos){
			string id = segment.substr(0, found);
			string pos = segment.substr(found+1, segment.size()-1);

			// conversion to integer
			stringstream s1(id);
			int id_value;
			s1 >> id_value;
			stringstream s2(pos);
			int pos_value;
			s2 >> pos_value;
			Car* car = new Car(id_value, pos_value);

            if (head == NULL)
            {
                head = car;
                tail = car;
            }
            else
            {
                tail->set_next(car);
                car->set_prev(tail);
                tail = car;
                car->set_next(NULL);
            }
		}
	}
}

Car* Platoon::get_tail()
{
	return tail;
}

Car* Platoon::get_head()
{
	return head;
}

void Platoon::remove(Car* c)
{
	// iterate through platoon
	Car *car = this->get_tail();
	while (car != nullptr) {
		// check if car is equal to c, the car to be removed
		if (car == c) {
			// set c previous pointer to next car
			car->get_next()->set_prev(car->get_prev());
			// set c next pointer to previous car
			car->get_prev()->set_next(car->get_next());
			// set c next and previous pointer to null
			car->set_prev(nullptr);
			car->set_next(nullptr);
		}

		// move onto previous car
		car = car->get_prev();
	}
}

void Platoon::append(Car* c)
{
	// set tail next pointer to c, the new tail
	tail->set_next(c);
	// set c previous pointer to the old tail
	c->set_prev(tail);
	// set c next pointer to null
	c->set_next(nullptr);
	// set tail to c
	tail = c;
}

void Platoon::prepend(Car* c)
{
	// set the new head to c
	head->set_prev(c);
	c->set_next(head);
	head = c;
}

void Platoon::insert(Car* c)
{
	// check if c has larger position than head or smaller than tail
	// if so set to prepend or append otherwise, insert normally
	if (c->get_position() > head->get_position()) {
		prepend(c);
	} else if (c->get_position < tail->get_position()) {
		append(c);
	} else {
		
	}
}