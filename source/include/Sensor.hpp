#ifndef _SENSOR_H
#define _SENSOR_H

template<class T>
class Sensor {
	
public:
	Sensor(double factor) : error_factor{ factor }
	virtual SensorResult get_data() = 0;
	
	class SensorResult<T> {
		SensorResult() error_factor { 0.0f }, value{}
		SensorResult(double error_factor, T value) : error_factor{ error_factor }, value{ value } {}

		double get_error_factor() { return error_factor; }
		T get_value() { return value; }

	private:
		double error_factor;
		T value;
	}

private:
	double error_factor;

};

#endif //_SENSOR_H