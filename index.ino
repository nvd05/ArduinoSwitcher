class PinListener
{
private:
	int _milliseconds;
	int _signal;
	int _pin;

protected:
	void update(int signal, int milliseconds)
	{
		Serial.println("voltage: " + String(signal) + ", millis: " + String(milliseconds));
		Serial.println();
	}

public:
	void listen()
	{
		int signal = digitalRead(_pin);

		if (_signal == signal)
		{
			return;
		}

		int milliseconds = millis();
		int time_passed = milliseconds - _milliseconds;

		update(signal, time_passed);
		_milliseconds = milliseconds;
		_signal = signal;
	}

	PinListener(int pin)
	{
		pinMode(pin, INPUT);
		_pin = pin;
	}
};

class PinSwitcher
{
private:
	bool _active;
	int _pin;

public:
	void update()
	{
		if (millis() % 5000 != 0)
		{
			return;
		}

		Serial.println("[" + String(_pin) + "] switch: " + String(_active));
		digitalWrite(_pin, _active);
		_active = !_active;
	}

	PinSwitcher(int pin)
	{
		pinMode(pin, OUTPUT);
		_pin = pin;
	}
};

PinListener pin1(13);
PinSwitcher pin2(12);

void setup()
{
	Serial.begin(9600);
	Serial.println("running...");
}

void loop()
{
	pin1.listen();
	pin2.update();
	delay(1);
}
