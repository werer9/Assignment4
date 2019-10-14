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
	Car *car = this->get_tail();
	do {
		if (car == c) {
			c->get_prev()->set_next(c->get_next());
			c->get_next()->set_prev(c->get_prev());
			c->set_next(nullptr);
			c->set_prev(nullptr);
		}
		car = car->get_next();
	} while (car != nullptr);
}

void Platoon::append(Car* c)
{
	Car *car = this->get_tail();
	if (car == nullptr && this->get_head() == nullptr) {
		this->tail = c;
		this->head = c;
	} else if (car->get_position() > c->get_position()) {
		car->set_prev(c);
		c->set_next(car);
		this->tail = c;
	}
}

void Platoon::prepend(Car* c)
{
	Car *car = this->get_head();
	if (car == nullptr && this->get_tail() == nullptr) {
		this->tail = c;
		this->head = c;
	} else if (c->get_position() > car->get_position()) {
		c->set_prev(car);
		car->set_next(c);
		this->head = c;
	}
}

void Platoon::insert(Car* c)
{
	Car *car = this->get_tail();
	if (car == nullptr) {
		this->head = c;
		this->tail = c;
	} else {
		if (car->get_next() == nullptr) {
			if (car->get_position() > c->get_position()) {
				this->tail = c;
				c->set_next(car);
				car->set_prev(c);
			} else {
				this->head = c;
				c->set_prev(car);
				car->set_next(c);
			}
		} else {
			do {
				
				if (car == this->head && c->get_position() > car->get_position()) {
					this->head->set_next(c);
					c->set_prev(this->head);
					c->set_next(nullptr);
					this->head = c;
					break;
				} else if(car->get_position() < c->get_position() && car->get_next() != nullptr && car->get_next()->get_position() > c->get_position()) {
					c->set_next(car->get_next());
					c->set_prev(car);
					car->get_next()->set_prev(c);
					car->set_next(c);
					break;
				}
				car = car->get_next();
			} while (car != nullptr);
		}
	}
}

Car *Platoon::search(int id)
{
	
	Car *car = this->get_tail();
	if (car == nullptr) {
		return car;
	} else {
		do {
			if (car->get_id() == id) {
				return car;
			}
			car = car->get_next();
		} while (car != nullptr);
	}

	return car;
	
}

Car *Platoon::searchPos(int pos)
{
	Car *car = this->get_tail();
	if (car == nullptr) {
		return car;
	} else {
		do {
			if (car->get_position() == pos) {
				return car;
			}
			car = car->get_next();
		} while (car != nullptr);
	}

	return car;
}
