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

            this->insert(car);
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
	if (c == head) {
		head = c->get_prev();
		head->set_next(nullptr);
	} else if (c == tail) {
		tail = c->get_next();
		tail->set_prev(nullptr);
	} else {
		Car *temp = tail;
		while (temp != nullptr) {
			if (temp == c) {
				temp->get_next()->set_prev(temp->get_prev());
				temp->get_prev()->set_next(temp->get_next());
				break;
			}
			temp = temp->get_next();
		}
	}

	c->set_next(nullptr);
	c->set_prev(nullptr);
}

void Platoon::append(Car* c)
{
	if (c->get_position() > this->get_tail()->get_position()) {
		this->insert(c);
	}
}

void Platoon::prepend(Car* c)
{
	if (c->get_position() < this->get_head()->get_position()) {
		this->insert(c);
	}
}

void Platoon::insert(Car* c)
{
	if (tail == nullptr && head == nullptr) {
		head = c;
		tail = c;
		return;
	} else {
		if (tail == head) {
			if (c->get_position() < head->get_position()) {
				head = c;
				c->set_prev(tail);
				c->set_next(nullptr);
				tail->set_next(head);
				tail->set_prev(nullptr);
				return;
			} else {
				tail = c;
				c->set_prev(nullptr);
				c->set_next(head);
				head->set_prev(tail);
				head->set_next(nullptr);
				return;
			}
		} else {
			if (c->get_position() > tail->get_position()) {
				tail->set_prev(c);
				c->set_next(tail);
				tail = c;
				return;
			} else if (c->get_position() < head->get_position()) {
				head->set_next(c);
				c->set_prev(head);
				head = c;
				return;
			}
			Car *temp = tail;
			while (temp != nullptr) {
				if (c->get_position() > temp->get_position()) {
					c->set_prev(temp->get_prev());
					c->get_prev()->set_next(c);
					c->set_next(temp);
					temp->set_prev(c);
					return;
				}

				temp = temp->get_next();
			}
		}
	}
	
}

Car *Platoon::search(int id)
{
	
	Car *car = this->get_tail();
	while (car != nullptr) {
		if (car->get_id() == id) {
			return car;
		}
		car = car->get_next();
	}

	return car;
	
}

Car *Platoon::searchPos(int pos)
{
	Car *car = this->get_tail();
	while (car != nullptr) {
		if (car->get_position() == pos) {
			return car;
		}
		car = car->get_next();
	} 

	return car;
}
