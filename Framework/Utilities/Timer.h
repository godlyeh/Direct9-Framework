/*

	File: Timer

	Used for countdown and other timings

*/

namespace CoreTimer
{
	// Tick count
	static double CoreTick = 0;

	static void PerformCoreTick()
	{
#ifdef _WIN64
		static FDWORD CoreTickStart = GetTickCount64();
		CoreTick = (double)(GetTickCount64() - CoreTickStart);
#else
		static FDWORD CoreTickStart = (GetTickCount() - CoreTickStart);
		CoreTick = (double)GetTickCount();
#endif
	}

	// Count down timer
	class Countdown
	{
	private:
		bool bSet = false;
		double dTimeSet = 0.0;
		double dStartTime = 0.0;

	public:
		double Timeleft() { return (dStartTime + dTimeSet) - CoreTick; }
		bool Running() { return CoreTick <= (dStartTime + dTimeSet); }

		void Start(double Milliseconds)
		{
			if (bSet == false)
			{
				dTimeSet = Milliseconds;
				dStartTime = CoreTick;
				bSet = true;
			}
		}

		void Stop()
		{
			if (bSet == false) return;
			dStartTime -= dTimeSet;
		}

		void Reset()
		{
			bSet = false;
			Start(dTimeSet);
		}

		Countdown(double Milliseconds) { Start(Milliseconds); }
		~Countdown() { }
	};
}