#include "../source/include/Sensor.hpp"

namespace r2d2 {

	// Sensor that only return the remainder of its initial value (1)
	// plus 3 divided by 10
	// (value + 3) % 10
	// Example: first call yields 4, then 7, then 0, then 3...
	class CustomModuloSensor : public Sensor<unsigned long>
	{
	public:
		CustomModuloSensor(double factor) : Sensor{ factor } {}

		SensorResult get_data() override {
			this->value = (this->value + 3) % 10;
			return SensorResult(error_factor, this->value);
		}

	private:
		unsigned long value = 1;
	};

	// Starts at zero, everytime get_data is called,
	// it increments it immediately and returns this value.
	// Example: first call yields 1, second call yields 2, third call yields 3
	class CustomIncementalSensor : public Sensor<int>
	{
	public:
		CustomIncementalSensor(double factor) : Sensor{ factor } {}

		SensorResult get_data() {
			return SensorResult(error_factor, ++this->value);
		}
	private:
		int value = 0;
	};

	// Starts at zero, everytime get_data is called,
	// it decrements it immediately and returns this value.
	// Example: first call yields -1, second call yields -2, third call yields -3
	class CustomDecrementalSensor : public Sensor<int>
	{
	public:
		CustomDecrementalSensor(double factor) : Sensor{ factor } {}

		SensorResult get_data() {
			return SensorResult(error_factor, --this->value);
		}
	private:
		int value = 0;
	};

}