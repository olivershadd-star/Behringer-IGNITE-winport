namespace ui
{
	GridSelectTool::GridSelectTool(NoteManagement& gridComponent, GridData& gData)
		: gridComp(gridComponent), gridData(gData)
	{
		setType(GridToolType::GridSelectTool);
		touchPoints.fill(TouchPoint());
	}

	void GridSelectTool::clearSelectRegion()
	{
		startX = endX = startY = endY = 0;
	}

	bool GridSelectTool::isSelectRegionValid()
	{
		bool isValid = false;
		if (startX >= 0 && startY >= 0 && endX > 0 && endY > 0) isValid = true;
		return isValid;
	}

	void GridSelectTool::paint(Graphics& g)
	{
		//draw selection region
		if (isSelectRegionValid())
		{
			juce::Rectangle<float> selRect(startX, startY, (endX - startX), (endY - startY));
			g.setColour(Theme::Instance().selectionColour(1));
			g.drawRect(selRect, 1.5f);
		}
	}

	void GridSelectTool::mouseDown(const juce::MouseEvent& event)
	{
		if (event.source.isTouch())
		{
			int touchId = event.source.getIndex();
			if (touchId < maxTouches)
			{
				touchPoints[touchId].startX = event.position.x;
				touchPoints[touchId].startY = event.position.y;
			}
		}
	}

	void GridSelectTool::mouseDrag(const MouseEvent& event)
	{
		if (!isActive()) return;

		int touchId = event.source.getIndex();
		float x1 = juce::jmax(0.0f, event.mouseDownPosition.getX());
		float x2 = juce::jmax(0.0f, event.position.getX());
		float y1 = juce::jmax(0.0f, event.mouseDownPosition.getY());
		float y2 = juce::jmax(0.0f, event.position.getY());

		if (touchId < maxTouches && countActiveTouches() > 1)
		{
			touchPoints[touchId].endX = x2;
			touchPoints[touchId].endY = y2;
		}
		else if (x1 != x2 || y1 != y2)
		{
			startX = juce::jmin(x1, x2);
			endX = juce::jmax(x1, x2);
			startY = juce::jmin(y1, y2);
			endY = juce::jmax(y1, y2);
		}
	}

	void GridSelectTool::mouseUp(const MouseEvent& event)
	{
		if (!isActive()) return;

		int activeTouches = countActiveTouches();

		if (activeTouches > 1)
		{
			if (!detectPinchGesture())
				detectSwipeGesture();
		}
		else
		{
			auto _pPatternPtr = IgnitePattern::getAppPatternInstance();

			float x1 = juce::jmax(0.0f, event.mouseDownPosition.getX());
			float x2 = juce::jmax(0.0f, event.position.getX());
			int stepMin = juce::jmin(gridData.findColumn(x1), gridData.findColumn(x2));
			int stepMax = juce::jmax(gridData.findColumn(x1), gridData.findColumn(x2));

			float y1 = juce::jmax(0.0f, event.mouseDownPosition.getY());
			float y2 = juce::jmax(0.0f, event.position.getY());
			int noteMin = juce::jmin(gridData.findRow(y1), gridData.findRow(y2));
			int noteMax = juce::jmax(gridData.findRow(y1), gridData.findRow(y2));

			_pPatternPtr->setSelectedNotes(stepMin, stepMax, noteMin, noteMax);
			_pPatternPtr->resetGangStepState();
			_pPatternPtr->resetGangNoteState();
			_pPatternPtr->setPasteCompletionState(false);

			if (isSelectRegionValid())
			{
				clearSelectRegion();
			}
		}

		resetTouchPoints();
	}

	int GridSelectTool::countActiveTouches()
	{
		int count = 0;
		for (const auto& tp : touchPoints)
		{
			if (tp.startX >= 0 && tp.startY >= 0)
				++count;
		}
		return count;
	}

	bool GridSelectTool::detectSwipeGesture()
	{
#ifdef _MSC_VER //TODO : fix float and int conversion, need HW to test
#pragma warning(push)
#pragma warning(disable: 4244)
#endif

		if (countActiveTouches() < 2)
			return false;

		auto& tp1 = touchPoints[0];
		auto& tp2 = touchPoints[1];

		float _deltaX = tp2.endX - tp1.startX;
		float _deltaY = tp2.endY - tp1.startY;

		//const float minSwipeDistance = 50.0f;
		auto gridPtr = AppGrid::getGridInstance();
		{
			if (std::abs(_deltaX) > std::abs(_deltaY))
			{
				if (_deltaX > 0)
					gridPtr->moveViewPortHorizontaly(_deltaX);
				else
					gridPtr->moveViewPortHorizontaly(_deltaX);
			}
			else
			{
				if (_deltaY > 0)
					gridPtr->moveViewPortVertically(0, _Direction::DOWN);
				else
					gridPtr->moveViewPortVertically(0, _Direction::UP);
			}
			return true;
		}
#ifdef _MSC_VER
#pragma warning(pop)
#endif
		return false;
	}

	bool GridSelectTool::detectPinchGesture()
	{
		if (countActiveTouches() < 2)
			return false;

		// Calculate initial and final distances between the first two active touch points
		auto& tp1 = touchPoints[0];
		auto& tp2 = touchPoints[1];

		float initialDist = static_cast<float>(std::sqrt(std::pow(tp2.startX - tp1.startX, 2) + std::pow(tp2.startY - tp1.startY, 2)));
		float finalDist = static_cast<float>(std::sqrt(std::pow(tp2.endX - tp1.endX, 2) + std::pow(tp2.endY - tp1.endY, 2)));

		DBG("Pinch magnitude = " + String(std::abs(finalDist - initialDist)));
		if (std::abs(finalDist - initialDist) > pinchThreshold)
		{
			if (finalDist > initialDist)
			{
				DBG("Pinch Out Detected (Zoom In)");
				AppGrid::getGridInstance()->setGridZoomInValue(1);
			}
			else if (finalDist < initialDist)
			{
				DBG("Pinch In Detected (Zoom Out)");
				AppGrid::getGridInstance()->setGridZoomOutValue(1);
			}
			return true;
		}
		return false;
	}

	void GridSelectTool::resetTouchPoints()
	{
		for (auto& tp : touchPoints)
		{
			tp = TouchPoint();  // Reset each touch point
		}
	}
}
