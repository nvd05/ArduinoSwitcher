class PinListener
{
private:
	int _milliseconds;
	int _signal;
	int _pin;

protected:
	void update(int signal, int milliseconds)
	{
		#pragma region debugger
		Serial.println("voltage: " + String(signal) + ", millis: " + String(milliseconds));
		Serial.println();
		#pragma endregion
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

	int _milliseconds;
	int _pin;

public:
	void update()
	{
		if (millis() % _milliseconds != 0)
		{
			return;
		}

		#pragma region debugger
		Serial.println("[" + String(_pin) + "] switch: " + String(_active));
		#pragma endregion

		digitalWrite(_pin, _active);
		_active = !_active;
	}

	PinSwitcher(int pin, int milliseconds)
	{
		pinMode(pin, OUTPUT);

		_milliseconds = milliseconds;
		_pin = pin;
	}
};

PinListener pin1(13);
PinSwitcher pin2(12);

void setup()
{
	#pragma region debugger
	Serial.begin(9600);
	Serial.println("running...");
	#pragma endregion
}

void loop()
{
	pin1.listen();
	pin2.update();
	delay(1);
}
