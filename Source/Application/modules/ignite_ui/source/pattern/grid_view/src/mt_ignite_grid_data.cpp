#include "../inc/mt_ignite_grid_data.h"

namespace ui
{

	GridData::GridData()
	{
		calculateBarWidthHeight();
		recalculate();
	}

	void GridData::deleteTimeSig(int atBar)
	{
		if (atBar == 1)
			return;

		int pos = 0;
		int currentRangeStart = 1;
		auto it = barsRange.begin();
		for (; it < barsRange.end(); it++)
		{
			if (atBar == currentRangeStart)
			{
				break;
			}
			pos++;
			currentRangeStart = (*it) + 1;
		}

		if (it != barsRange.end())
		{
			auto itPrev = it - 1;
			(*itPrev) = (*it);
			barsRange.erase(it);
			auto timeSigIt = barTimeSig.begin() + pos;
			barTimeSig.erase(timeSigIt);
		}
		recalculate();
	}

	void GridData::insertTimeSig(int atBar, int num, int den)
	{
		unsigned int pos = 0;
		int currentRangeStart = 1;
		for (auto it = barsRange.begin(); it < barsRange.end(); it++)
		{
			if (atBar <= (*it))
			{
				break;
			}
			pos++;
			currentRangeStart = (*it) + 1;
		}
		if (currentRangeStart == atBar)
		{
			std::pair<int, int>& timeSig = barTimeSig.at(pos);
			timeSig.first = num;
			timeSig.second = den;
		}
		else //split
		{
			std::pair<int, int> timeSig(num, den);
			auto itr = barsRange.begin() + pos;
			barsRange.insert(itr, atBar - 1);

			auto timeSigIt = barTimeSig.begin() + pos + 1;
			barTimeSig.insert(timeSigIt, timeSig);
		}
		recalculate();
	}

	void GridData::insertBars(int newBarLength, int /*timSigNum*/, int /*timeSigDen*/)
	{
		if (newBarLength > bars)
		{
			int& lastVal = barsRange.back();
			lastVal = newBarLength;
		}
		else
		{
			int pos = 0;
			for (auto it = barsRange.begin(); it != barsRange.end(); it++)
			{
				pos++;
				if (newBarLength <= (*it))
				{
					(*it) = newBarLength;
					barsRange.erase(it + 1, barsRange.end());
					auto its = barTimeSig.begin() + pos;
					barTimeSig.erase(its, barTimeSig.end());
					break;
				}
			}
		}
		recalculate();
	}

	void GridData::calculateBarWidthHeight()
	{
		barWidth = (700.0f * horizontalZoom) / 15;

		BarData barData;
		getBarData(bars, barData);
		recommendedWidth = barData.barStartPos;
		recommendedWidth += barData.widthOfBar;
		if (recommendedWidth < visibleViewPort.getWidth())
		{
			float viewPortWidth = static_cast<float>(visibleViewPort.getWidth());
			barWidth = (barWidth * viewPortWidth) / recommendedWidth;
			horizontalZoom = (15 * barWidth) / 700.0f;
		}

		noteHeight = (ignite_Constants::noteLineWidth * verticalZoom) / 30;
		if ((noteHeight * totalPianoKeys + 1) < visibleViewPort.getHeight())
		{
			float viewPortHeight = static_cast<float>(visibleViewPort.getHeight());
			noteHeight = viewPortHeight / (totalPianoKeys + 1);
			verticalZoom = (30 * noteHeight) / ignite_Constants::noteLineWidth;
		}
	}

	void GridData::recalculate()
	{
		if (barsRange.empty())
			return;

		bars = barsRange.back();

		cellWidth = barWidth / quantizationLevel;
		beatWidth = barWidth / 4;
		tickWidth = beatWidth / 960; //ticksPerQuarterNote;
		ticksPerQl = static_cast<int>(cellWidth / tickWidth);
		recommendedWidth = 0.0;
		greyWidth = 0.0;

		noteMarkingWidth = 0.0;
		for (int i = 1; i <= 4; i++)
		{
			float effBeatWidth = CommonUtils::convertToPrecision(i * beatWidth);
			for (unsigned int j = 1; j <= quantizationLevel; j++)
			{
				float val = CommonUtils::convertToPrecision(j * cellWidth);
				if (val > effBeatWidth) break;

				if (val == effBeatWidth)
				{
					noteMarkingWidth = effBeatWidth;
					break;
				}
			}

			if (noteMarkingWidth != 0.0) break;
		}
		DBG("noteMarkingWidth : " + String(noteMarkingWidth));
		BarData barData;
		getBarData(bars, barData);
		recommendedWidth = barData.barStartPos;
		recommendedWidth += barData.widthOfBar;

		float clmstmp = CommonUtils::convertToPrecision(recommendedWidth / cellWidth);
		columns = static_cast<int>(std::ceil(clmstmp));
		greyWidth = (columns * cellWidth) - recommendedWidth;

		gridChanged.emit();
	}

	int GridData::getRequiredGridWidth()
	{
		return static_cast<int>(std::ceil(recommendedWidth + greyWidth));
	}

	Rectangle<float> GridData::getCellRect(int row, int column) const
	{
		Rectangle<float> cellRect(cellWidth * column, row * noteHeight /* - 9*/, cellWidth, noteHeight);
		return  cellRect;
	}

	void GridData::getBarData(int bar, BarData& barData) const
	{
		barData.barStartPos = 0;
		int barCount = 1;
		for (unsigned int i = 0; i < barsRange.size(); i++)
		{
			auto timeSig = barTimeSig[i];
			int barDivisionFraction = timeSig.second / 4;
			barData.widthOfBar = barWidth / barDivisionFraction;
			float widthOf4and4beat = barData.widthOfBar / 4;
			int diff = timeSig.first - 4;
			barData.widthOfBar += widthOf4and4beat * diff;
			barData.totalBeats = timeSig.first;
			barData.timeSigNum = timeSig.first;
			barData.timeSigDen = timeSig.second;

			for (; barCount <= barsRange[i]; barCount++)
			{
				if (barCount >= bar) return;

				barData.barStartPos += barData.widthOfBar;
			}
		}
	}

	int GridData::findRow(float yPos) const
	{
		int row = static_cast<int>(yPos / noteHeight);
		return (totalPianoKeys - (row));
	}

	int GridData::findColumn(float xPos) const
	{
		int col = static_cast<int>(xPos / cellWidth);
		(col > 15) ? col = 15 : col;
		return col;
	}

	float GridData::findX(int col) const
	{
		return (cellWidth * col);
	}

	float GridData::findY(int row) const
	{
		row = 127 - row;
		return (noteHeight * row);
	}

	void GridData::setQl(unsigned int ql)
	{
		quantizationLevel = ql;
		recalculate();
	}

	void GridData::getTimeSignatureForBar(int atBar, int& num, int& den, bool& hasOnlyOneBar)
	{
		hasOnlyOneBar = false;
		num = -1;
		den = -1;
		unsigned int pos = 0;
		if (barsRange.size() == 1)
		{
			hasOnlyOneBar = true;
			return;
		}

		int currentRangeStart = 1;
		for (auto it = barsRange.begin(); it < barsRange.end(); it++)
		{
			if (atBar <= (*it))
			{
				break;
			}
			pos++;
			currentRangeStart = (*it) + 1;
		}

		if (currentRangeStart == atBar)
		{
			std::pair<int, int>& timeSig = barTimeSig.at(pos);
			num = timeSig.first;
			den = timeSig.second;
		}
	}

	void GridData::setZoomFactor(float horizontalFactor, float verticalFactor)
	{
		bool changed = false;
		float horTemp = horizontalFactor;

		DBG(String(__FUNCTION__) + "::" + String(__LINE__) + "::" + "horizontalFactor : " + String(horizontalFactor) + "verticalFactor : " + String(verticalFactor));

		if (horTemp >= 5 && horTemp <= 100)
		{
			if (horTemp != horizontalZoom)
				changed = true;

			horizontalZoom = horTemp;
		}

		float verTemp = verticalFactor;
		if (verTemp >= 5 && verTemp <= 100)
		{
			if (verTemp != verticalZoom)
				changed = true;

			verticalZoom = verTemp;
		}

		if (changed)
			calculateBarWidthHeight();

		recalculate();
	}
}

