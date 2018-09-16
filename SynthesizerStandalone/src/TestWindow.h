#pragma once

namespace clr
{

	class TestWindow
	{
	private:
		void InitMessageLoop();
		double mMasterVolume;
	public:
		TestWindow();
		~TestWindow();

		void SetMasterVolume(const double& dNewVolume);
	};

}
