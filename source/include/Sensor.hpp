#ifndef _SENSOR_H
#define _SENSOR_H

template class<T>
class Sensor {
	
public:
	Sensor(double factor);
	virtual SensorResult get_data();
	
	class SensorResult<T> {
		SensorResult();
		double error_factor;
		T value;
	}

private:
	double error_factor;

};

#endif //_SENSOR_H