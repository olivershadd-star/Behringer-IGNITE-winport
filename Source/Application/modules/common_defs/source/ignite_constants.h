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
#pragma once

using namespace juce;
using namespace ui;
namespace ignite_Constants
{
	constexpr float noteLineWidth{ 16.0f };
	constexpr double viewX1{ 20.0f };
	constexpr double viewX2{ 20.0f };

	// Alignments
	// Default
	constexpr int xStartDefault{ 0 };
	constexpr int yStartDefault{ 0 };

	// Sequence constant
	constexpr int minimumBpm{ 20 };
	constexpr int maximumBpm{ 200 };
	constexpr int defaultBpm{ 120 };

	constexpr int minimumBar{ 1 };
	constexpr int maximumBar{ 100 };
	constexpr int defaultBar{ 1 };

	// Song constant
	constexpr int minTempo{ 20 };
	constexpr int maxTempo{ 360 };
	constexpr int defTempo{ 130 };

	constexpr int minPitch{ 0 };
	constexpr int maxPitch{ 100 };
	constexpr int defPitch{ 0 };

	constexpr int minSwing{ 0 };
	constexpr int maxSwing{ 16 };
	constexpr int defSwing{ 0 };

	//Scene constant
	constexpr int minGbar{ 1 };
	constexpr int maxGbar{ 16 };
	constexpr int defGbar{ 1 };

	constexpr int minLength{ 1 };
	constexpr int maxLength{ 200 };
	constexpr int defLength{ 1 };

	constexpr int minXpose{ -12 };
	constexpr int maxXpose{ 12 };
	constexpr int defXpose{ 0 };

	//Pattern constant
	constexpr int minStepLength{ 0 };
	constexpr int maxStepLength{ 95 };
	constexpr int stepLengthStepSize{ 1 };

	constexpr int minTickLength{ 0 };
	constexpr int maxTickLength{ 31 };
	constexpr int tickLengthStepSize{ 1 };

	constexpr int lengthHoldId{ maxStepLength + 5 };

	constexpr int minDelay{ 0 };
	constexpr int maxDelay{ 31 };
	constexpr int defDelay{ 0 };
	constexpr int defDelayFactor{ 16 };////

	constexpr int minVelocity{ 0 };
	constexpr int maxVelocity{ 127 };
	constexpr int defVelocity{ 127 };

	constexpr int minBars{ 0 };
	constexpr int maxBars{ 16 };
	constexpr int defBars{ 0 };

	constexpr int minMidi{ 0 };
	constexpr int maxMidi{ 127 };
	constexpr int defMidi{ 0 };

	constexpr int minQuantPer{ 0 };
	constexpr int maxQuantPer{ 100 };
	constexpr int defQuantPer{ 0 };

	constexpr int minNotePer{ 0 };
	constexpr int maxNotePer{ 255 };
	constexpr int defNotePer{ 0 };

	constexpr int minVeloPer{ 0 };
	constexpr int maxVeloPer{ 255 };
	constexpr int defVeloPer{ 0 };

	constexpr int minLengPer{ 0 };
	constexpr int maxLengPer{ 2000 };
	constexpr int defLengPer{ 0 };
	
	constexpr int minOctave{ -4 };
	constexpr int maxOctave{ 4 };
	constexpr int defOctave{ 0 };

	constexpr int minKnob{ 0 };
	constexpr int maxKnob{ 127 };
	constexpr int defKnob{ 0 };
	
	constexpr int minReich{ -12 };
	constexpr int maxReich{ 12 };
	constexpr int defReich{ 0 };
	enum BUTTONS
	{
		CANCEL = 0,
		APPLY,
		DELETE,
		OK
	};
}

enum class GridToolType
{
	GridPencilTool,
	GridSelectTool,
	GridEraseTool,
	GridCutPasteTool,
	GridCopyPasteTool
};

enum class GridViewType
{
	DrumView,
	MidiView
};

//==============================================================================

/*
struct Thumbnail : public Component
{
	Thumbnail(tracktion_engine::TransportControl& tc)
		: transport(tc)
	{
		cursorUpdater.setCallback([this]
			{
				updateCursorPosition();

				if (smartThumbnail.isGeneratingProxy() || smartThumbnail.isOutOfDate())
					repaint();
			});
		cursor.setFill(findColour(Label::textColourId));
		addAndMakeVisible(cursor);
	}

	void setFile(const tracktion_engine::AudioFile& file)
	{
		smartThumbnail.setNewFile(file);
		cursorUpdater.startTimerHz(25);
		repaint();
	}

	void paint(Graphics& g) override
	{
		auto r = getLocalBounds();
		const auto colour = findColour(Label::textColourId);

		if (smartThumbnail.isGeneratingProxy())
		{
			g.setColour(colour.withMultipliedBrightness(0.9f));
			g.drawText("Creating proxy: " + String(roundToInt(smartThumbnail.getProxyProgress() * 100.0f)) + "%",
				r, Justification::centred);
		}
		else
		{
			const float brightness = smartThumbnail.isOutOfDate() ? 0.4f : 0.66f;
			g.setColour(colour.withMultipliedBrightness(brightness));
			smartThumbnail.drawChannels(g, r, true, { 0.0, smartThumbnail.getTotalLength() }, 1.0f);
		}
	}

	void mouseDown(const MouseEvent& e) override
	{
		transport.setUserDragging(true);
		mouseDrag(e);
	}

	void mouseDrag(const MouseEvent& e) override
	{
		jassert(getWidth() > 0);
		const float proportion = e.position.x / getWidth();
		transport.position = proportion * transport.getLoopRange().getLength();
	}

	void mouseUp(const MouseEvent&) override
	{
		transport.setUserDragging(false);
	}

private:
	tracktion_engine::TransportControl& transport;
	tracktion_engine::SmartThumbnail smartThumbnail{ transport.engine, tracktion_engine::AudioFile(transport.engine), *this, nullptr };
	DrawableRectangle cursor;
	tracktion_engine::LambdaTimer cursorUpdater;

	void updateCursorPosition()
	{
		const double loopLength = transport.getLoopRange().getLength();
		const double proportion = loopLength == 0.0 ? 0.0 : transport.getCurrentPosition() / loopLength;

		auto r = getLocalBounds().toFloat();
		const float x = r.getWidth() * float(proportion);
		cursor.setRectangle(r.withWidth(2.0f).withX(x));
	}
};
*/
