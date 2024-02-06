#ifndef CITY_CPP
#define CITY_CPP

class City {
public:
    int id;
    int distance;
    City* next;

    City() {
        this->id = -1;
        this->distance = -1;
        this->next = nullptr;
    }

    City(int id, int distance) {
        this->id = id;
        this->distance = distance;
        this->next = nullptr;
    }
    
    // Assignment operator overload
    City& operator=(const City& other) {
        if (this != &other) {
            this->id = other.id;
            this->distance = other.distance;

            // Delete existing 'next' pointer
            delete this->next;

            // Note: Assuming you want to create a new node rather than copying the 'next' pointer
            if (other.next) {
                this->next = new City(*other.next);
            } else {
                this->next = nullptr;
            }
        }
        return *this;
    }

    // Destructor to release memory for the linked list
    ~City() {
        delete next;
    }
};

#endif
