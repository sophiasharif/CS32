class Vehicle {
    
public:
    Vehicle(string id) { m_id = id; }
    string id() const {return m_id;}
    virtual string description() const = 0;
    virtual bool canHover() const {return true;};
    virtual ~Vehicle() {};
    
private:
    string m_id;
};

class Drone: public Vehicle {
public:
    Drone(string id): Vehicle(id) {}
    virtual string description() const {return "a drone";}
    virtual ~Drone() {
        cout << "Destroying " << id() << ", a drone" << endl;
    };
};

class Balloon: public Vehicle {
public:
    Balloon(string id, double diameter) :Vehicle(id) {
        if (diameter < 8) m_size = "small";
        else m_size = "large";
    }
    virtual string description() const {return "a " + m_size + " balloon";}
    virtual ~Balloon() {
        cout << "Destroying the balloon " << id() << endl;
    }
    
private:
    string m_size;
};

class Satellite: public Vehicle {
public:
    Satellite(string id) :Vehicle(id){}
    virtual string description() const {return "a satellite";}
    virtual bool canHover() const {return false;}
    virtual ~Satellite() {
        cout << "Destroying the satellite " << id() << endl;
    }
};
