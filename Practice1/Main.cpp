
#include <iostream>
#include <string>
#include <vector>

class Vehicle
{
public:
	virtual std::ostream& Print(std::ostream& out) = 0;

	friend std::ostream& operator << (std::ostream& out, Vehicle& object)
	{
		return object.Print(out);
	}

	virtual ~Vehicle() = default;
};

class WaterVehicle : public Vehicle
{
public:
	WaterVehicle(const float draught) : Draught(draught) {};

	virtual std::ostream& Print(std::ostream& out) override
	{
		return out <<"Draught: " << Draught << " ";
	}

private:
	float Draught;
};

struct Point
{
public:
	Point(const float x, const float y, const float z) :X(x), Y(y), Z(z) {};

	void print(std::ostream& out)
	{
		out << "x:" << X << " " << "y:" << Y << " " << "z:" << Z << " ";
	}

private:
	float X;
	float Y;
	float Z;
};

class Circle : public Vehicle
{
public:
	Circle(const Point& location, const float diameter) :Diameter(diameter)
	{
		Location = new Point(location);
	}

	virtual std::ostream& Print(std::ostream& out)
	{
		out << "Circle point: ";
		Location->print(out);

		return out << "Diameter: " << Diameter;
	}

	~Circle() override
	{
		if (Location) delete Location;
	}

private:
	Point* Location;
	float Diameter;
};

class RoadVehicle : public Vehicle
{
public:
	RoadVehicle() {};

	RoadVehicle(const float clearance) : Clearance(clearance) {};

	virtual std::ostream& Print(std::ostream& out) override
	{
		return out << Clearance;
	}

private:
	float Clearance{ 0 };
};

class Wheel
{
public:
	Wheel(const float diameter) : Diameter(diameter) {};

	void Print(std::ostream& out)
	{
		out << Diameter << " ";
	}

private:
	float Diameter;
};

class Engine
{
public:
	Engine(float power) : Power(power) {};

	void Print(std::ostream& out)
	{
		out << Power << " ";
	}

	float GetPower() { return Power; }
private:
	float Power;
};

class Bicycle : public RoadVehicle
{
public:
	Bicycle(const Wheel& frontWheel, const Wheel& reartWheel, const float clearance) : RoadVehicle(clearance)
	{
		FrontWheel = new Wheel(frontWheel);
		RearWheel = new Wheel(reartWheel);
	}

	virtual std::ostream& Print(std::ostream& out) override
	{
		out << "Bicycle Wheels: ";
		FrontWheel->Print(out);
		RearWheel->Print(out);
		out << "Ride height: ";
		RoadVehicle::Print(out);

		return out;
	}

	~Bicycle() override
	{
		if (FrontWheel) delete FrontWheel;
		if (RearWheel) delete RearWheel;
	}
private:
	Wheel* FrontWheel;
	Wheel* RearWheel;
};

class Car : public RoadVehicle
{
public:

	Car(const Engine& carEngine, const Wheel& frontRWheel, const Wheel& frontLWheel,
		const Wheel& reartRWheel, const Wheel& reartLWheel, const float clearance) : RoadVehicle(clearance)
	{
		FrontRWheel = new Wheel(frontRWheel);
		FrontLWheel = new Wheel(frontLWheel);
		RearRWheel = new Wheel(reartRWheel);
		RearLWheel = new Wheel(reartLWheel);

		CarEngine = new Engine(carEngine);
	}

	virtual std::ostream& Print(std::ostream& out) override
	{
		out << "Car Engine: ";
		CarEngine->Print(out);
		out << "Wheels: ";
		FrontRWheel->Print(out);
		FrontLWheel->Print(out);
		RearRWheel->Print(out);
		RearLWheel->Print(out);

		RoadVehicle::Print(out << "Ride height: ");

		return out;
	}

	float GetPower()
	{
		if (CarEngine)
		{
			return CarEngine->GetPower();
		}

		return -1.f;
	}

	~Car() override
	{
		if (FrontRWheel) delete FrontRWheel;
		if (FrontLWheel) delete FrontLWheel;
		if (RearRWheel) delete RearRWheel;
		if (RearLWheel) delete RearLWheel;
		if (CarEngine) delete CarEngine;
	}
private:
	Wheel* FrontRWheel;
	Wheel* FrontLWheel;
	Wheel* RearRWheel;
	Wheel* RearLWheel;

	Engine* CarEngine;
	
};

float getHighestPower(const std::vector<Vehicle*>& vector)
{
	float HighestPower = -1.f;

	for (Vehicle* object : vector)
	{
		const auto car = dynamic_cast<Car*>(object);
		if (car)
		{
			const float Power = car->GetPower();
			if (Power > HighestPower) HighestPower = Power;
		}
	}

	return HighestPower;
}

int main()
{
	Car c(Engine(150), Wheel(17), Wheel(17), Wheel(18), Wheel(18), 150);
	std::cout << c << '\n';

	Bicycle t(Wheel(15), Wheel(15), 300);
	std::cout << t << '\n';

	std::vector<Vehicle*> v;

	v.push_back(new Car(Engine(150), Wheel(17), Wheel(17), Wheel(18), Wheel(18), 250));

	v.push_back(new Circle(Point(1, 2, 3), 7));

	v.push_back(new Car(Engine(200), Wheel(19), Wheel(19), Wheel(19), Wheel(19), 130));

	v.push_back(new WaterVehicle(5000));

	for (Vehicle*& object : v)
	{
		std::cout << *object << std::endl;
	}

	std::cout << "The highest power is " << getHighestPower(v) << '\n';

	for (Vehicle*& object : v)
	{
		delete object;
	}
	v.clear();

	return 0;
}