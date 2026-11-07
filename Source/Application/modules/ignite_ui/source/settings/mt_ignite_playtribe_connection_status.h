
#pragma once

namespace ui
{
	class PlaytribeConnectionStatus : public juce::Component
									, public juce::Button::Listener
									, public juce::Timer
	{
	public:
		PlaytribeConnectionStatus();
		~PlaytribeConnectionStatus();

		void waitingForConnectionPopup();
		void ConnectionEstablishedPopup();

		void setConnectionState(bool state);
		bool getConnectionState();

		static PlaytribeConnectionStatus* GetPlaytribeConnectionStatusInstance()
		{
			static PlaytribeConnectionStatus* GetPlaytribeConStatusObj;
			if (NULL == GetPlaytribeConStatusObj)
			{
				GetPlaytribeConStatusObj = new PlaytribeConnectionStatus();
			}
			return GetPlaytribeConStatusObj;
		}

	private:
		ui::CommonPopUp* popupPtr = nullptr;

		bool isConnected{ false };

		CommonLabel headerLable{ "" };
		CommonLabel infoLable{ "" };
		CommonImageButton disconnectBtn{ "","btn-wifi-disconnect-default.png","btn-wifi-disconnect-default.png","btn-wifi-disconnect-default-hover.png" };

		void paint(juce::Graphics& g) override;
		void resized() override;

		void buttonClicked(juce::Button* buttonThatWasClicked) override;
		void timerCallback() override;

		void stopPlaytribeHandler();
	};
}