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

			// use insert function
			insert(car);

            // if (head == NULL)
            // {
            //     head = car;
            //     tail = car;
            // }
            // else
            // {
            //     tail->set_next(car);
            //     car->set_prev(tail);
            //     tail = car;
            //     car->set_next(NULL);
            // }
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
	if (c == head && head == tail) {
		head = nullptr;
		tail = nullptr;
		c->set_next(nullptr);
		c->set_prev(nullptr);
	} else if (c == head) {
		c->get_next()->set_prev(nullptr);
		head = c->get_next();
		c->set_next(nullptr);
		c->set_prev(nullptr);
	} else if (c == tail) {
		c->get_prev()->set_next(nullptr);
		tail = c->get_prev();
		c->set_prev(nullptr);
		c->set_next(nullptr);
	} else {
		// iterate through platoon
		Car *car = tail;
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
	if (tail == nullptr && head == nullptr) {
		tail = c;
		head = c;
		c->set_next(nullptr);
		c->set_prev(nullptr);
	}	
	
	// check if c has larger position than head or smaller than tail
	// if so set to prepend or append otherwise, insert normally
	else if (c->get_position() > head->get_position()) {
		prepend(c);
		return;
	} else if (c->get_position() < tail->get_position()) {
		append(c);
		return;
	} else {
		Car *car = tail->get_prev();
		while (car != nullptr) {
			// if c has a smaller position than car
			if (car->get_position() > c->get_position()) {
				// insert it as car's next pointer
				// and make car's previous pointer's previous pointer 
				// point to c then make c point to car's old next and previous points to car
				c->set_next(car->get_next());
				c->set_prev(car);
				c->get_next()->set_prev(c);
				car->set_next(c);
				return;
			}
			// keep looping
			car = car->get_prev();
		}
	}
}

bool Platoon::is_position_empty(int pos)
{
	Car *car = head;
	while (car != nullptr) {
		// return false if car is in position, pos
		if (car->get_position() == pos)
			return false;
		car = car->get_next();
	}

	// if loop finishes iterating, return true
	return true;
}