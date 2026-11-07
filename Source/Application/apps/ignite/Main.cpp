/*
 * Copyright (c) - 2022 - MUSIC Tribe, MY
 * This file is part of IGNITE.
 *
 * IGNITE is free software: you can redistribute it and/or modify it under the
 * terms of the GNU Affero General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * IGNITE is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with IGNITE. If not, see <https://www.gnu.org/licenses/>.
 *
 * SPDX-License-Identifier: AGPL-3.0-or-later
 */
 /*
   ==============================================================================

	 This file contains the basic startup code for a JUCE application.

   ==============================================================================
 */
#include <JuceHeader.h>
#include <cstdlib>

using namespace Ignite;
using namespace Ignite::Midi;
std::unique_ptr<IListener> _PUiInterface;
std::unique_ptr<IDevice> _PUiVirtualEngine;
extern IDevice* EngineInit(void);
#if defined(IGNITE_DESKTOP)
#include "DesktopPanel.h"
#endif

//==============================================================================
#define SHOW_BOOT_IMAGE
#if defined SHOW_BOOT_IMAGE
#define ENGINE_READY_WAIT_TIME_SEC 5

class waitpopup : public juce::Component
{
public:
	waitpopup()
	{
		Component::setSize(ui::layout::screen.getWidth(), ui::layout::screen.getHeight());
		Component::setTopLeftPosition(0, 0);
		Component::setFocusContainerType(FocusContainerType::focusContainer);
	};
	~waitpopup() = default;
	void mouseUp(const MouseEvent& event)override { return; };
	void mouseDown(const MouseEvent& event)override { return; };
	void paint(juce::Graphics& g)
	{
		Image dropImage = juce::ImageCache::getFromFile(Theme::getAssetsDirectory().getChildFile("boot-screen.png"));
		g.drawImageAt(dropImage, 0, 0);
	}
};
waitpopup* _waitpopup;
void showWaitForBootComplete(bool isClose)
{
	if (isClose)
	{
		if (_waitpopup)
		{
			_waitpopup->removeFromDesktop();
			delete _waitpopup;
		}
	}
	else // create
	{
		_waitpopup = new waitpopup;
		_waitpopup->setVisible(true);
		_waitpopup->addToDesktop(ComponentPeer::windowHasDropShadow);
	}
}
#endif //SHOW_BOOT_IMAGE
void UiEngineInterfaceInit()
{
	//Engine init, Interface init and linking interface end points
	_PUiVirtualEngine = (std::unique_ptr<IDevice>) EngineInit();
	_PUiInterface = std::make_unique<UiInterface>(_PUiVirtualEngine.get());
}

class IgniteApplication : public juce::JUCEApplication
{
public:
	//==============================================================================
	IgniteApplication()
	{
	}

	const juce::String getApplicationName() override { return ProjectInfo::projectName; }
	const juce::String getApplicationVersion() override { return ProjectInfo::versionString; }
	bool moreThanOneInstanceAllowed() override { return true; }

	//==============================================================================
	void initialise(const juce::String& commandLine) override
	{
#if defined SHOW_BOOT_IMAGE
		int waitCount = ENGINE_READY_WAIT_TIME_SEC;
#ifdef _WIN64
		showWaitForBootComplete(false);
#endif
		std::thread engineThread(UiEngineInterfaceInit);

		while ((!_PUiVirtualEngine || (_PUiVirtualEngine && _PUiVirtualEngine->isIDeviceReady() == false) )&& waitCount-- > 0)
			Time::waitForMillisecondCounter(Time::getMillisecondCounter() + 1000);
		//if ((!_PUiVirtualEngine || (_PUiVirtualEngine && _PUiVirtualEngine->isIDeviceReady() == false)) && waitCount <= 0)
		// TODO: Do if any recovery required if engine not ready in time

		if (engineThread.joinable()) //this block the UI to load
			engineThread.join();
		mainWindow.reset(new MainWindow(getApplicationName()));
#ifdef _WIN64
		showWaitForBootComplete(true);// pop-up exits
#endif
#else //SHOW_BOOT_IMAGE
		std::thread engineThread(UiEngineInterfaceInit);
		engineThread.join();
		mainWindow.reset(new MainWindow(getApplicationName()));
#endif//SHOW_BOOT_IMAGE
#if defined(IGNITE_DESKTOP)
        if (commandLine.contains("--desktop-smoke"))
            juce::Timer::callAfterDelay(10000, [this] {
                auto image = mainWindow->getContentComponent()->createComponentSnapshot(mainWindow->getContentComponent()->getLocalBounds());
                auto stream = juce::File::getCurrentWorkingDirectory().getChildFile("desktop-smoke.png").createOutputStream();
                bool ok = stream && juce::PNGImageFormat().writeImageToStream(image, *stream);
                stream.reset();
                auto* model = static_cast<IgniteEngine*>(_PUiVirtualEngine.get());
                ok = ok && model->songManager->get_tsf_instance() != nullptr;
                // Test-only exit: the embedded upstream engine has detached perpetual threads.
                std::_Exit(ok ? 0 : 2);
            });
#endif
	}

	void shutdown() override
	{
		// Add your application's shutdown code here..
		mainWindow = nullptr; // (deletes our window)
	}

	//==============================================================================
	void systemRequestedQuit() override
	{
		// This is called when the app is being asked to quit: you can ignore this
		// request and let the app carry on running, or call quit() to allow the app to close.
		quit();
	}

	void anotherInstanceStarted(const juce::String& commandLine) override
	{
		// When another instance of the app is launched while this one is running,
		// this method is invoked, and the commandLine parameter tells you what
		// the other instance's command-line arguments were.
	}



	//==============================================================================
	/*
		This class implements the desktop window that contains an instance of
		our MainComponent class.
	*/
	class MainWindow : public juce::DocumentWindow
	{
	public:
		MainWindow(juce::String name)
			: DocumentWindow(name,
				juce::Desktop::getInstance().getDefaultLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId),
				DocumentWindow::allButtons)
		{
			#if defined(IGNITE_DESKTOP)
            setContentOwned(new DesktopPanel(*static_cast<IgniteEngine*>(_PUiVirtualEngine.get())), true);
#else
            setContentOwned(&ui::getAppHome(), true);
#endif
			#if defined(IGNITE_DESKTOP)
			setUsingNativeTitleBar(true);
#else
			setUsingNativeTitleBar(false);
			setTitleBarHeight(0);
#endif
			#if defined(IGNITE_DESKTOP)
            setContentComponentSize(1220, 900);
            setResizeLimits(854, 630, 1830, 1350);
            getConstrainer()->setFixedAspectRatio(1220.0 / 900.0);
            centreWithSize(1220, 900);
#else
            setContentComponentSize(ui::layout::screen.getWidth(), ui::layout::screen.getHeight());
#endif
#if (JUCE_IOS || JUCE_ANDROID || JUCE_LINUX || __linux__)
			setFullScreen(true);
#endif
			setResizable(true, false);
			setVisible(true);
		}

		void closeButtonPressed() override
		{
			// This is called when the user tries to close this window. Here, we'll just
			// ask the app to quit when this happens, but you can change this to do
			// whatever you need.
			JUCEApplication::getInstance()->systemRequestedQuit();
		}

		/* Note: Be careful if you override any DocumentWindow methods - the base
		   class uses a lot of them, so by overriding you might break its functionality.
		   It's best to do all your work in your content component instead, but if
		   you really have to override any DocumentWindow methods, make sure your
		   subclass also calls the superclass's method.
		*/

	private:
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainWindow)
	};

private:
	std::unique_ptr<MainWindow> mainWindow;
};

//==============================================================================
// This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION(IgniteApplication)
