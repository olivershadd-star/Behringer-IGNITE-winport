/*
 * Copyright (c) - 2021 - MUSIC Tribe, MY.
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

#ifndef IGNITE_LAYOUT_H
#define IGNITE_LAYOUT_H

namespace ui
{
	// Application Width/Height...
	enum { appWidth = 570, appHeight = 358 };

	// Screen Resolution...
	enum { screenWidth = 1024, screenHeight = 600 };

	// Scale Factor (Screen to Application ration)
	constexpr int _scaledX(float v) { return (int)(v * (float)screenWidth / (float)appWidth); }
	constexpr int _scaledY(float v) { return (int)(v * (float)screenHeight / (float)appHeight); }
	constexpr float _scaledXF(int v) { return (float)(v * (float)screenWidth / (float)appWidth); }
	constexpr float _scaledYF(int v) { return (float)(v * (float)screenHeight / (float)appHeight); }
	constexpr float _scaledHeightfactor(int v) { return ((float)v / ((float)screenHeight / (float)appHeight)); }
	constexpr float _scaledHeightfactor(float v) { return ((float)v / ((float)screenHeight / (float)appHeight)); }
	constexpr float _scaledWidthfactor(int v) { return((float)v / ((float)screenWidth / (float)appWidth)); }
	constexpr float _scaledWidthfactor(float v) { return((float)v / ((float)screenWidth / (float)appWidth)); }

	constexpr float scalingFactorWidth{ (float)screenWidth / (float)appWidth };
	constexpr float scalingFactorHeight{ (float)screenHeight / (float)appHeight };

	constexpr int widthDailog{ int(456.0f * scalingFactorWidth) };
	constexpr int heightDailog{ int(286.46f * scalingFactorHeight) };

	constexpr int widthNumpad{ int(335.9f * scalingFactorWidth) };
	constexpr int heightNumpad{ int(287.42f * scalingFactorHeight) };

	constexpr int xStartNumpadCmp{ int(16.7f * scalingFactorWidth) };
	constexpr int widthNumpadCmp{ int(302.9f * scalingFactorWidth) };

	constexpr int yStartNumpadCmpVal{ int(41.91f * scalingFactorHeight) };
	constexpr int yStartNumpadNumbers{ int(95.80f * scalingFactorHeight) };
	constexpr int yStartNumpadCtrl{ int(214.0f * scalingFactorHeight) };

	constexpr int heightNumpadTitle{ int(40.71f * scalingFactorHeight) };
	constexpr int heightNumpadValue{ int(29.94f * scalingFactorHeight) };
	constexpr int heightNumpadNumbers{ int(112.57f * scalingFactorHeight) };
	constexpr int heightNumpadCtrl{ int(26.34f * scalingFactorHeight) };

	constexpr int widthScreen{ int(570.0f * scalingFactorWidth) };
	constexpr int heightSceen{ int(358.08f * scalingFactorHeight) };

	constexpr int widthTop{ int(570.0f * scalingFactorWidth) };
	constexpr int heightTop{ int(38.19f * scalingFactorHeight) };

	constexpr int widthMainMode{ int(570.0f * scalingFactorWidth) };
	constexpr int heightMainMode{ int(334.53f * scalingFactorHeight) };

	constexpr int yStartMainMode1{ int(19.09f * scalingFactorHeight) };
	constexpr int widthMainMode1{ int(570.0f * scalingFactorWidth) };
	constexpr int heightMainMode1{ int(338.34f * scalingFactorHeight) };

	constexpr int yStartSetting{ int(38.19f * scalingFactorHeight) };
	constexpr int widthSetting{ int(570.0f * scalingFactorWidth) };
	constexpr int heightSetting{ int(312.03f * scalingFactorHeight) };

	constexpr int yStartBottom{ int(309.77f * scalingFactorHeight) };
	constexpr int widthBottom{ int(570.0f * scalingFactorWidth) };
	constexpr int heightBottom{ int(67.66f * scalingFactorHeight) };

	constexpr int xStartParambar{ int(317.66f * scalingFactorWidth) };
	constexpr int widthParambar{ int(253.22f * scalingFactorWidth) };
	constexpr int heightParambar{ int(45.50f * scalingFactorHeight) };

	constexpr int yStartMiddle{ int(66.91f * scalingFactorHeight) };
	constexpr int widthMiddle{ int(570.0f * scalingFactorWidth) };
	constexpr int heightMiddle{ int(290.97f * scalingFactorHeight) };

	constexpr int xStartRow{ int(0.0f * scalingFactorWidth) };
	constexpr int widthRow{ int(130.0f * scalingFactorWidth) };
	constexpr int heightRow{ int(37.87f * scalingFactorHeight) };

	constexpr int yStartStatusBar{ int(341.51f * scalingFactorHeight) };
	constexpr int widthStatusBar{ int(570.0f * scalingFactorWidth) };
	constexpr int heightStatusBar{ int(17.09f * scalingFactorHeight) };

	constexpr int yStartSongBar1{ int(336.72f * scalingFactorHeight) };
	constexpr int widthSongBar1{ int(337.72f * scalingFactorWidth) };
	constexpr int heightSongBar1{ int(9.021f * scalingFactorHeight) };

	constexpr int yStartSongBar2{ int(332.93f * scalingFactorHeight) };
	constexpr int widthSongBar2{ int(570.0f * scalingFactorWidth) };
	constexpr int heightSongBar2{ int(4.02f * scalingFactorHeight) };

	constexpr int yStartGridCtrl{ int(75.93f * scalingFactorHeight) };
	constexpr int widthGridCtrl{ int(421.0f * scalingFactorWidth) };
	constexpr int heightGridCtrl{ int(43.5 * scalingFactorHeight) };

	//Soft keyboard size
	constexpr int widthKeypad{ int(500.0f * scalingFactorWidth) };
	constexpr int heightKeypad{ int(192.31f * scalingFactorHeight) };

	namespace layout
	{
		constexpr float barHeight = ((float)screenHeight / (float)appHeight) * 55.55f;
		constexpr float  rowHeight = ((float)screenHeight / (float)appHeight) * 39.68f;
		/// < Rectangle > ::: < X, Y, Width, Height >
	//	enum { barHeight = 70, rowHeight = 50 };


		// Dialog window size...
		const juce::Rectangle<int> dialog{ (0),(0), widthDailog,heightDailog };
		//const juce::Rectangle<int> dialog{ (0),(0), 350,200 };
		// Numeric component size...
		const juce::Rectangle<int> numpad{ (0),(0),widthNumpad ,heightNumpad };
		//Soft keybroad component size...
		const juce::Rectangle<int> keypad{ (0),(0),710 ,240 };
		// Complete Screen
		const juce::Rectangle<int> screen{ (0),(0), widthScreen,heightSceen };

		// Top and Bottom control bar.
		const juce::Rectangle<int> top{ _scaledX(0), _scaledY(0), widthTop, heightTop };
		const juce::Rectangle<int> mainmode{ _scaledX(0), _scaledY(0), widthMainMode, heightMainMode };
		const juce::Rectangle<int> mainmode1{ _scaledX(0), 28, widthMainMode1, heightMainMode1 };
		const juce::Rectangle<int> setting{ _scaledX(0), yStartSetting, widthSetting, heightSetting };
		const juce::Rectangle<int> bottom{ _scaledX(0), yStartBottom, widthBottom, heightBottom };
		const juce::Rectangle<int> paramsbar{ xStartParambar, _scaledY(0), widthParambar, heightParambar };

		// Central main view area.
		const juce::Rectangle<int> middle{ _scaledX(0),yStartMiddle, widthMiddle, heightMiddle };

		const juce::Rectangle<int> row{ xStartRow, _scaledY(0), widthRow, heightRow };
		const juce::Rectangle<int> statusBar{ _scaledX(0),yStartStatusBar, widthStatusBar ,heightStatusBar };
		const juce::Rectangle<int> songBar1{ _scaledX(0),(yStartSongBar1), widthSongBar2,heightSongBar2 };
		const juce::Rectangle<int> songBar2{ _scaledX(0),(556), widthSongBar2,heightSongBar2 };

		const juce::Rectangle<int> gridCtrlbar{ _scaledX(0),yStartGridCtrl, widthGridCtrl,heightGridCtrl };

		///
			// Scaling

	};

	// Font Calculations Factor
	constexpr float scalingForFont{ scalingFactorWidth };
	constexpr int font_8{ int(scalingForFont * 8.0f) };
	constexpr int font_10{ int(scalingForFont * 10.0f) };
	constexpr int font_11{ int(scalingForFont * 11.0f) };
	constexpr int font_12{ int(scalingForFont * 12.0f) };
	constexpr int font_13{ int(scalingForFont * 13.0f) };
	constexpr int font_14{ int(scalingForFont * 14.0f) };
	constexpr int font_15{ int(scalingForFont * 15.0f) };
	constexpr int font_16{ int(scalingForFont * 16.0f) };
	constexpr int font_20{ int(scalingForFont * 20.0f) };
	constexpr int font_24{ int(scalingForFont * 24.0f) };
	constexpr int font_40{ int(scalingForFont * 40.0f) };

	// Container for song/scene/track/pattern
	constexpr int xStartContainer{ int(0.0f * scalingFactorWidth) };
	constexpr int yStartContainer{ int(28.86f * scalingFactorHeight) };
	constexpr int widthContainer{ int(142.85f * scalingFactorWidth) };
	constexpr int heightContainer{ int(265.67f * scalingFactorHeight) };

	// Detailed common view for song/scene/track/pattern
	constexpr int xStartCommonView{ int(142.54f * scalingFactorWidth) };
	constexpr int yStartCommonView{ int(23.30f * scalingFactorHeight) };
	constexpr int widthCommonView{ int(442.85f * scalingFactorWidth) };
	constexpr int heightCommonView{ int(276.69f * scalingFactorHeight) };

	constexpr int _xStartCommonView{ widthRow + int(widthRow * .074f) };
	constexpr int _yStartCommonView{ 50 };
	constexpr int _widthCommonView{ widthScreen - widthRow };
	constexpr int _heightCommonView{ heightSceen - (heightStatusBar + heightSongBar1 + heightSongBar2) };

	constexpr float xStartInstBox1{ int(0.0f * scalingFactorWidth) };
	constexpr float yStartInstBox{ int(15.03f * scalingFactorHeight) };
	constexpr float widthInstBox1{ int(107.14f * scalingFactorWidth) };
	constexpr float heightInstBox{ int(299.0f * scalingFactorHeight) };

	constexpr float xStartInstBox2{ int(109.92f * scalingFactorWidth) };
	constexpr float widthInstBox2{ int(100.0f * scalingFactorWidth) };

	constexpr float xStartInstBox3{ int(214.28f * scalingFactorWidth) };
	constexpr float widthInstBox3{ int(107.14f * scalingFactorWidth) };

	constexpr float xStartInstBox4{ int(325.00f * scalingFactorWidth) };
	constexpr float widthInstBox4{ int(100.00f * scalingFactorWidth) };

	//Common Add new box
	constexpr int xStartCommonBox{ int(0.0f * scalingFactorWidth) };
	constexpr int yStartCommonBox{ int(261.58f * scalingFactorHeight) };
	constexpr int widthCommonBox{ int(135.42f * scalingFactorWidth) };
	constexpr int heightCommonBox{ int(37.36f * scalingFactorHeight) };

	//Common  detaild box for song/scene/track/pattern
	constexpr int xStartBox1{ int(0.0f * scalingFactorWidth) };
	constexpr int yStartBox1{ int(32.33f * scalingFactorHeight) };
	constexpr int widthBox1{ int(558.9f * scalingFactorWidth) };

	constexpr int xStartBox2{ int(60.0f * scalingFactorWidth) };
	constexpr int yStartBox2{ int(121.55f * scalingFactorHeight) };
	constexpr int widthBox2{ int(427.65f * scalingFactorWidth) };

	constexpr int xStartBox3{ int(60.0f * scalingFactorWidth) };
	constexpr int yStartBox3{ int(191.61f * scalingFactorHeight) };
	constexpr int widthBox3{ int(427.65f * scalingFactorWidth) };

	constexpr int xStartSceneBox1{ int(22.22f * scalingFactorWidth) };
	constexpr int yStartSceneBox1{ int(17.91f * scalingFactorHeight) };
	constexpr int widthSceneBox1{ int(427.65f * scalingFactorWidth) };

	constexpr int xStartSceneBox2{ int(60.0f * scalingFactorWidth) };
	constexpr int yStartSceneBox2{ int(77.61f * scalingFactorHeight) };
	constexpr int widthSceneBox2{ int(427.65f * scalingFactorWidth) };

	constexpr int xStartSceneBox3{ int(60.0f * scalingFactorWidth) };
	constexpr int yStartSceneBox3{ int(137.31f * scalingFactorHeight) };
	constexpr int widthSceneBox3{ int(427.65f * scalingFactorWidth) };

	constexpr int yStartSceneBox4{ int(197.01f * scalingFactorHeight) };
	constexpr int widthSceneBox4{ int(83.51f * scalingFactorWidth) };

	constexpr int heightBox{ int(98.2f * scalingFactorHeight) };
	constexpr int heightSceneBox{ int(48.0f * scalingFactorHeight) };

	//Instrument
	constexpr int xStartInstrView{ int(0.0f * scalingFactorWidth) };
	constexpr int yStartInstrView{ int(33.63f * scalingFactorHeight) };
	constexpr int widthInstrView{ int(136.01f * scalingFactorWidth) };
	constexpr int heightInstrView{ int(259.4f * scalingFactorHeight) };

	// AppTopbar
	constexpr int xStartAppTopbar{ int(2.0f * scalingFactorWidth) };
	constexpr int yStartAppTopbar{ int(2.0f * scalingFactorHeight) };
	constexpr int widthAppTopbar{ int(100.0f * scalingFactorWidth) };
	constexpr int heightAppTopbar{ int(10.0f * scalingFactorHeight) };

	constexpr int yStartTopbar{ int(0.0f * scalingFactorHeight) };
	constexpr int widthTopbar{ int(35.0f * scalingFactorWidth) };
	constexpr int heightTopbar{ int(35.0f * scalingFactorHeight) };

	constexpr int xStartTopOpenP{ int(232.0f * scalingFactorWidth) };
	constexpr int yStartTopOpenP{ yStartTopbar };
	constexpr int widthTopOpenP{ int(292.0f * scalingFactorWidth) };
	constexpr int heightTopOpenP{ heightTopbar };

	constexpr int xStartTopHome{ int(0.0f * scalingFactorWidth) };
	constexpr int xStartMainMode{ int(0.0f * scalingFactorWidth) };
	constexpr int xStartTopMainMode{ int(10.0f * scalingFactorWidth) };

	constexpr int xStartTopGrid{ int(76.0f * scalingFactorWidth) };

	constexpr int xStartTopTrkMix{ int(114.0f * scalingFactorWidth) };

	constexpr int xStartTopStepSeq{ int(152.0f * scalingFactorWidth) };

	constexpr int xStartTopSetting{ int(530.0f * scalingFactorWidth) };

	constexpr int xStartTopAxis{ int(200.0f * scalingFactorWidth) };
	constexpr int yStartTopAxis{ int(10.0f * scalingFactorHeight) };
	constexpr int widthTopAxis{ int(20.0f * scalingFactorWidth) };
	constexpr int heightTopAxis{ int(20.0f * scalingFactorHeight) };

	constexpr int xStartTopSave{ int(472.0f * scalingFactorWidth) };
	constexpr int yStartTopSave{ int(10.0f * scalingFactorHeight) };
	constexpr int widthTopSave{ int(15.0f * scalingFactorWidth) };
	constexpr int heightTopSave{ int(15.0f * scalingFactorHeight) };

	constexpr int xStartTopBrow{ int(500.0f * scalingFactorWidth) };
	constexpr int yStartTopBrow{ int(10.0f * scalingFactorHeight) };
	constexpr int widthTopBrow{ int(15.0f * scalingFactorWidth) };
	constexpr int heightTopBrow{ int(15.0f * scalingFactorHeight) };

	constexpr int xStartTopPlay{ int(440.0f * scalingFactorWidth) };
	constexpr int yStartTopPlay{ int(8.0f * scalingFactorHeight) };
	constexpr int widthTopPlay{ int(25.0f * scalingFactorWidth) };
	constexpr int heightTopPlay{ int(20.0f * scalingFactorHeight) };

	// AppMainmode
	constexpr int xStartAppMainmode{ xStartMainMode };
	constexpr int yStartAppMainmode{ int(23.0f * scalingFactorHeight) };
	constexpr int widthAppMainmode{ widthAppTopbar - 70 };
	constexpr int heightAppMainmode{ int(187.0f * scalingFactorHeight) };
	constexpr int depthAppMainmode{ int(30.0f * scalingFactorHeight) };

	// AppGrid
	constexpr int xStartAppGrid{ xStartAppTopbar };
	constexpr int yStartAppGrid{ int(43.0f * scalingFactorHeight) + depthAppMainmode };
	constexpr int widthAppGrid{ widthAppTopbar };
	constexpr int heightAppGrid{ heightAppMainmode - depthAppMainmode };
	constexpr int kiBlueStripHeight{ 15 };
	const int totalPianoKeys = 127;
	const int minimumBarOrBeatWidthToDraw = 19;
	const int minimumCellWidthToDraw = 5;
	const int gridParameterControlHeight = 25;
	const int parameterValueLimit = 127;
	const int paramVelocityMax = 128;
	const int paramDelayMax = 96;
	const int paramLengthSteps = 96;
	const int paramLengthTicks = 96;
	//  constexpr int ticksPerQuarterNote{ tracktion_engine::Edit::ticksPerQuarterNote };

	  // Menu
	constexpr int xStartMenu{ xStartAppTopbar };
	constexpr int yStartMenu{ int(37.0f * scalingFactorHeight) };
	constexpr int widthMenu{ widthAppTopbar };
	constexpr int heightMenu{ int(312.0f * scalingFactorHeight) };

	constexpr int widthMenuButton{ int(100.0f * scalingFactorWidth) };
	constexpr int heightMenuButton{ int(55.0f * scalingFactorHeight) };

	constexpr int xMenuButtonRow1{ int(30.0f * scalingFactorWidth) };
	constexpr int yMenuButtonCol1{ int(20.0f * scalingFactorHeight) };
	constexpr int xMenuButtonRow2{ int(165.0f * scalingFactorWidth) };
	constexpr int yMenuButtonCol2{ int(95.0f * scalingFactorHeight) };
	constexpr int xMenuButtonRow3{ int(300.0f * scalingFactorWidth) };
	constexpr int yMenuButtonCol3{ int(170.0f * scalingFactorHeight) };
	constexpr int xMenuButtonRow4{ int(435.0f * scalingFactorWidth) };
	constexpr int yMenuButtonCol4{ int(245.0f * scalingFactorHeight) };

	// StepSequencer
	const int stepControlHeight = 33;
	const int stepButtonViewHeight = 25;
	const int stepButtonHeight = 24;
	const int presetWidth = 45;

	// AppGrid Control
	constexpr int xStartAppGc{ int(0.0f * scalingFactorWidth) };
	constexpr int yStartAppGc{ yStartAppMainmode };
	constexpr int widthAppGc{ int(230.0f * scalingFactorWidth) };
	constexpr int heightAppGc{ int(20.0f * scalingFactorHeight) };

	constexpr int xStartAppGcPencil{ int(52.0f * scalingFactorWidth) };
	constexpr int xStartAppGcErase{ int(92.0f * scalingFactorWidth) };
	constexpr int xStartAppGcSelect{ int(132.0f * scalingFactorWidth) };
	constexpr int yStartAppGcComp{ int(2.0f * scalingFactorHeight) };
	constexpr int widthAppGcComp{ int(16.0f * scalingFactorWidth) };
	constexpr int heightAppGcComp{ int(16.0f * scalingFactorHeight) };

	// Paint
	constexpr int xStartGCPaint1{ int(50.0f * scalingFactorWidth) };
	constexpr int xStartGCPaint2{ int(90.0f * scalingFactorWidth) };
	constexpr int xStartGCPaint3{ int(130.0f * scalingFactorWidth) };
	constexpr int yStartGCPaint{ int(0.0f * scalingFactorHeight) };
	constexpr int widthGCPaint{ int(20.0f * scalingFactorWidth) };
	constexpr int heightGCPaint{ int(20.0f * scalingFactorHeight) };

	constexpr int xStartGcPaint4{ int(50.0f * scalingFactorWidth) };
	constexpr int yStartGcPaint4{ int(0.0f * scalingFactorHeight) };
	constexpr int widthGcPaint4{ int(100.0f * scalingFactorWidth) };
	constexpr int heightGcPaint4{ int(20.0f * scalingFactorHeight) };

	// AppStatusbar
	constexpr int xStartAppStatusbar{ xStartAppTopbar };
	constexpr int yStartAppStatusbar{ int(333.0f * scalingFactorHeight) };
	constexpr int widthAppStatusbar{ widthAppTopbar };
	constexpr int heightAppStatusbar{ int(20.0f * scalingFactorHeight) };

	// Appdnp
	constexpr int xStartAppDnp{ xStartAppTopbar };
	constexpr int yStartAppDnp{ yStartAppMainmode };
	constexpr int widthAppDnp{ widthAppTopbar };
	constexpr int heightAppDnp{ heightAppMainmode };

	// Record
	constexpr int xStartRecordBox{ int(55.67f * scalingFactorWidth) };
	constexpr int xStartFilterBox{ int(58.46f * scalingFactorWidth) };

	constexpr int yStartRecordBox1{ int(32.83f * scalingFactorHeight) };
	constexpr int yStartRecordBox2{ int(86.56f * scalingFactorHeight) };
	constexpr int yStartFilterBox{ int(173.13f * scalingFactorHeight) };
	constexpr int yStartEventLable{ int(149.25f * scalingFactorHeight) };

	constexpr int widthRecordBox1{ int(417.59f * scalingFactorWidth) };
	constexpr int widthRecordBox2{ int(278.39f * scalingFactorWidth) };
	constexpr int widthFilterBox{ int(417.59f * scalingFactorWidth) };
	constexpr int widthEventLable{ int(122.49f * scalingFactorWidth) };

	constexpr int heightRecordBox{ int(50.74f * scalingFactorHeight) };
	constexpr int heightFilterBox{ int(113.43f * scalingFactorHeight) };
	constexpr int heightEventLable{ int(35.82f * scalingFactorHeight) };

	//AppSequence
	constexpr int xWidthAppSequence{ widthAppTopbar };
	constexpr int yHeightAppSequence{ appHeight - depthAppMainmode - yStartAppMainmode - heightAppStatusbar };

	// App pad group
	constexpr int xWidthPG{ int(175.0f * scalingFactorWidth) };
	constexpr int yHeightPG{ int(280.0f * scalingFactorHeight) };

	constexpr int xWidthPadGroup{ int(85.0f * scalingFactorWidth) };
	constexpr int xHeightPadGroup{ int(25.0f * scalingFactorHeight) };

	constexpr int xWidthXtraPadGroup{ int(171.0f * scalingFactorWidth) };
	constexpr int xHeighXtratPadGroup{ int(34.0f * scalingFactorHeight) };

	constexpr int xStartPGCOL1{ int(2.0f * scalingFactorWidth) };
	constexpr int xStartPGCOL2{ int(88.0f * scalingFactorWidth) };

	constexpr int xStartPGROW1{ int(0.0f * scalingFactorHeight) };
	constexpr int xStartPGROW2{ int(35.0f * scalingFactorHeight) };
	constexpr int xStartPGROW3{ int(70.0f * scalingFactorHeight) };
	constexpr int xStartPGROW4{ int(96.0f * scalingFactorHeight) };
	constexpr int xStartPGROW5{ int(122.0f * scalingFactorHeight) };
	constexpr int xStartPGROW6{ int(148.0f * scalingFactorHeight) };
	constexpr int xStartPGROW7{ int(174.0f * scalingFactorHeight) };
	constexpr int xStartPGROW8{ int(200.0f * scalingFactorHeight) };
	constexpr int xStartPGROW9{ int(226.0f * scalingFactorHeight) };
	constexpr int xStartPGROW10{ int(252.0f * scalingFactorHeight) };

	// App pad mute
	constexpr int xWidthPadMuteList{ int(175.0f * scalingFactorWidth) };
	constexpr int yHeightPadMuteList{ int(280.0f * scalingFactorHeight) };

	constexpr int xWidthPMLPad{ int(12.0f * scalingFactorHeight) };
	constexpr int yHeightPMLPad{ int(12.0f * scalingFactorHeight) };

	constexpr int xStartPMLROW1{ int(20.0f * scalingFactorHeight) };
	constexpr int xStartPMLROW2{ int(36.0f * scalingFactorHeight) };
	constexpr int xStartPMLROW3{ int(52.0f * scalingFactorHeight) };
	constexpr int xStartPMLROW4{ int(68.0f * scalingFactorHeight) };

	constexpr int xStartPMLROW5{ int(92.0f * scalingFactorHeight) };
	constexpr int xStartPMLROW6{ int(108.0f * scalingFactorHeight) };
	constexpr int xStartPMLROW7{ int(124.0f * scalingFactorHeight) };
	constexpr int xStartPMLROW8{ int(140.0f * scalingFactorHeight) };

	constexpr int xStartPMLCOL1{ int(5.0f * scalingFactorHeight) };
	constexpr int xStartPMLCOL2{ int(21.0f * scalingFactorHeight) };
	constexpr int xStartPMLCOL3{ int(37.0f * scalingFactorHeight) };
	constexpr int xStartPMLCOL4{ int(53.0f * scalingFactorHeight) };

	constexpr int xStartPMLCOL5{ int(77.0f * scalingFactorHeight) };
	constexpr int xStartPMLCOL6{ int(93.0f * scalingFactorHeight) };
	constexpr int xStartPMLCOL7{ int(109.0f * scalingFactorHeight) };
	constexpr int xStartPMLCOL8{ int(125.0f * scalingFactorHeight) };

	constexpr int xStartPMLCOL9{ int(149.0f * scalingFactorHeight) };
	constexpr int xStartPMLCOL10{ int(165.0f * scalingFactorHeight) };
	constexpr int xStartPMLCOL11{ int(181.0f * scalingFactorHeight) };
	constexpr int xStartPMLCOL12{ int(197.0f * scalingFactorHeight) };

	constexpr int xStartPMLCOL13{ int(221.0f * scalingFactorHeight) };
	constexpr int xStartPMLCOL14{ int(237.0f * scalingFactorHeight) };
	constexpr int xStartPMLCOL15{ int(253.0f * scalingFactorHeight) };
	constexpr int xStartPMLCOL16{ int(269.0f * scalingFactorHeight) };

	constexpr int xWidthPMLPadName{ int(16.0f * scalingFactorHeight) };
	constexpr int yHeightPMLPadName{ int(16.0f * scalingFactorHeight) };

	constexpr int xStartPMLBankLeft{ int(0.0f * scalingFactorHeight) };
	constexpr int yStartPMLBankA{ int(25.0f * scalingFactorHeight) };
	constexpr int yStartPMLBankC{ int(97.0f * scalingFactorHeight) };
	constexpr int yStartPMLBankE{ int(169.0f * scalingFactorHeight) };
	constexpr int yStartPMLBankG{ int(241.0f * scalingFactorHeight) };

	constexpr int xStartPMLBankRight{ int(156.0f * scalingFactorHeight) };
	constexpr int yStartPMLBankB{ int(25.0f * scalingFactorHeight) };
	constexpr int yStartPMLBankD{ int(97.0f * scalingFactorHeight) };
	constexpr int yStartPMLBankF{ int(169.0f * scalingFactorHeight) };
	constexpr int yStartPMLBankH{ int(241.0f * scalingFactorHeight) };

	// App pad Settings
	constexpr int widthAppPadSettings{ int(566.0f * scalingFactorWidth) };
	constexpr int heightAppPadSettings{ int(355.0f * scalingFactorHeight) };

	constexpr int xStartPMProg{ int(10.0f * scalingFactorWidth) };
	constexpr int yStartPMProg{ int(2.0f * scalingFactorHeight) };
	constexpr int widthPMProg{ int(100.0f * scalingFactorWidth) };
	constexpr int heightPMProg{ int(28.0f * scalingFactorHeight) };

	constexpr int xStartPadSettings{ int(2.0f * scalingFactorWidth) };
	constexpr int yStartPadSettings{ int(71.0f * scalingFactorHeight) };
	constexpr int widthPadSettings{ int(190.0f * scalingFactorWidth) };
	constexpr int heightPadSettings{ int(234.0f * scalingFactorHeight) };

	constexpr int xStartPadModeComp{ int(8.0f * scalingFactorWidth) };
	constexpr int yStartPadModeComp{ int(31.0f * scalingFactorHeight) };
	constexpr int widthPadModeComp{ int(175.0f * scalingFactorWidth) };
	constexpr int heightPadModeComp{ int(280.0f * scalingFactorHeight) };

	constexpr int xStartPadSetCancel{ int(8.0f * scalingFactorWidth) };
	constexpr int yStartPadSetCancel{ int(31.0f * scalingFactorHeight) };

	constexpr int widthPadBankShift{ int(30.0f * scalingFactorWidth) };
	constexpr int heightPadBankShift{ int(25.0f * scalingFactorHeight) };

	constexpr int widthPadSettingsNrlBtn{ int(100.0f * scalingFactorWidth) };
	constexpr int heightPadSettingsNrlBtn{ int(25.0f * scalingFactorHeight) };

	constexpr int xStartPadBankLeft{ int(243.0f * scalingFactorWidth) };
	constexpr int xStartPadBankRight{ int(387.0f * scalingFactorWidth) };

	constexpr int xStartPadBtnCancel{ int(455.0f * scalingFactorWidth) };
	constexpr int yStartPadBtnCancel{ int(319.0f * scalingFactorHeight) };

	constexpr int xStartPadBtnBank{ int(280.0f * scalingFactorWidth) };
	constexpr int yStartPadBtnBank{ yStartPadBtnCancel };

	constexpr int xStartPadBtnList{ int(10.0f * scalingFactorWidth) };
	constexpr int yStartPadBtnList{ yStartPadBtnCancel };

	constexpr int xStartPadBtnGrp{ int(124.0f * scalingFactorWidth) };
	constexpr int yStartPadBtnGrp{ yStartPadBtnCancel };

	constexpr int widthPadSettingsBtn{ int(82.0f * scalingFactorWidth) };
	constexpr int heightPadSettingsBtn{ int(60.0f * scalingFactorHeight) };

	constexpr int xStartPadSettingsR1{ int(198.0f * scalingFactorWidth) };
	constexpr int xStartPadSettingsR2{ int(290.0f * scalingFactorWidth) };
	constexpr int xStartPadSettingsR3{ int(382.0f * scalingFactorWidth) };
	constexpr int xStartPadSettingsR4{ int(474.0f * scalingFactorWidth) };

	constexpr int yStartPadSettingsC1{ int(35.0f * scalingFactorHeight) };
	constexpr int yStartPadSettingsC2{ int(105.0f * scalingFactorHeight) };
	constexpr int yStartPadSettingsC3{ int(175.0f * scalingFactorHeight) };
	constexpr int yStartPadSettingsC4{ int(245.0f * scalingFactorHeight) };

	// App Assign Samples
	constexpr int widthAppAssignSample{ int(570.0f * scalingFactorWidth) };
	constexpr int heightAppAssignSample{ int(355.0f * scalingFactorHeight) };

	constexpr int xStartAASListBox{ int(2.0f * scalingFactorWidth) };
	constexpr int yStartAASListBox{ int(71.0f * scalingFactorHeight) };
	constexpr int widthAASListBox{ int(190.0f * scalingFactorWidth) };
	constexpr int heightAASListBox{ int(234.0f * scalingFactorHeight) };

	constexpr int xStartAASProgName{ int(0.0f * scalingFactorWidth) };
	constexpr int yStartAASProgName{ int(0.0f * scalingFactorHeight) };
	constexpr int widthAASProgName{ int(570.0f * scalingFactorWidth) };
	constexpr int heightAASProgname{ int(25.0f * scalingFactorHeight) };

	constexpr int xStartAASPadLoad{ int(216.0f * scalingFactorWidth) };
	constexpr int yStartAASPadLoad{ int(320.0f * scalingFactorHeight) };
	constexpr int widthAASPadLoad{ int(100.0f * scalingFactorWidth) };
	constexpr int heightAASPadLoad{ int(25.0f * scalingFactorHeight) };

	constexpr int xStartAASPadClose{ int(456.0f * scalingFactorWidth) };
	constexpr int yStartAASPadClose{ int(320.0f * scalingFactorHeight) };
	constexpr int widthAASPadClose{ int(100.0f * scalingFactorWidth) };
	constexpr int heightAASPadClose{ int(25.0f * scalingFactorHeight) };

	constexpr int xStartAASPadClr{ int(336.0f * scalingFactorWidth) };
	constexpr int yStartAASPadClr{ int(320.0f * scalingFactorHeight) };
	constexpr int widthAASPadClr{ int(100.0f * scalingFactorWidth) };
	constexpr int heightAASPadClr{ int(25.0f * scalingFactorHeight) };

	constexpr int xStartAASBankPad{ int(46.0f * scalingFactorWidth) };
	constexpr int yStartAASBankPad{ (yStartAASPadLoad) };
	constexpr int widthAASBankPad{ int(100.0f * scalingFactorWidth) };
	constexpr int heightAASBankPad{ heightAASPadLoad };

	constexpr int xStartAASBankPadLeft{ int(25.0f * scalingFactorWidth) };
	constexpr int yStartAASBankPadLeft{ (yStartAASPadLoad) };
	constexpr int widthAASBankPadLeft{ int(20.0f * scalingFactorWidth) };
	constexpr int heightAASBankPadLeft{ heightAASPadLoad };

	constexpr int xStartAASBankPadRight{ int(147.0f * scalingFactorWidth) };
	constexpr int yStartAASBankPadRight{ (yStartAASPadLoad) };
	constexpr int widthAASBankPadRight{ int(20.0f * scalingFactorWidth) };
	constexpr int heightAASBankPadRight{ heightAASPadLoad };

	constexpr int xStartAASLst{ int(2.0f * scalingFactorWidth) };
	constexpr int yStartAASLst{ int(36.0f * scalingFactorHeight) };
	constexpr int widthAASLst{ int(190.0f * scalingFactorWidth) };
	constexpr int heightAASLst{ int(34.0f * scalingFactorHeight) };

	constexpr int xStartAASPad13{ int(198.0f * scalingFactorWidth) };
	constexpr int yStartAASPad13{ int(35.0f * scalingFactorHeight) };
	constexpr int widthAASPad13{ int(82.0f * scalingFactorWidth) };
	constexpr int heightAASPad13{ int(60.0f * scalingFactorHeight) };

	constexpr int xStartAASPad14{ int(290.0f * scalingFactorWidth) };
	constexpr int yStartAASPad14{ yStartAASPad13 };
	constexpr int widthAASPad14{ widthAASPad13 };
	constexpr int heightAASPad14{ heightAASPad13 };

	constexpr int xStartAASPad15{ int(382.0f * scalingFactorWidth) };
	constexpr int yStartAASPad15{ yStartAASPad13 };
	constexpr int widthAASPad15{ widthAASPad13 };
	constexpr int heightAASPad15{ heightAASPad13 };

	constexpr int xStartAASPad16{ int(474.0f * scalingFactorWidth) };
	constexpr int yStartAASPad16{ yStartAASPad13 };
	constexpr int widthAASPad16{ widthAASPad13 };
	constexpr int heightAASPad16{ heightAASPad13 };

	constexpr int xStartAASPad12{ xStartAASPad16 };
	constexpr int yStartAASPad12{ int(105.0f * scalingFactorHeight) };
	constexpr int widthAASPad12{ widthAASPad13 };
	constexpr int heightAASPad12{ heightAASPad13 };

	constexpr int xStartAASPad11{ xStartAASPad15 };
	constexpr int yStartAASPad11{ yStartAASPad12 };
	constexpr int widthAASPad11{ widthAASPad13 };
	constexpr int heightAASPad11{ heightAASPad13 };

	constexpr int xStartAASPad10{ xStartAASPad14 };
	constexpr int yStartAASPad10{ yStartAASPad12 };
	constexpr int widthAASPad10{ widthAASPad13 };
	constexpr int heightAASPad10{ heightAASPad13 };

	constexpr int xStartAASPad9{ xStartAASPad13 };
	constexpr int yStartAASPad9{ yStartAASPad12 };
	constexpr int widthAASPad9{ widthAASPad13 };
	constexpr int heightAASPad9{ heightAASPad13 };

	constexpr int xStartAASPad8{ xStartAASPad16 };
	constexpr int yStartAASPad8{ int(175.0f * scalingFactorHeight) };
	constexpr int widthAASPad8{ widthAASPad13 };
	constexpr int heightAASPad8{ heightAASPad13 };

	constexpr int xStartAASPad7{ xStartAASPad15 };
	constexpr int yStartAASPad7{ yStartAASPad8 };
	constexpr int widthAASPad7{ widthAASPad13 };
	constexpr int heightAASPad7{ heightAASPad13 };

	constexpr int xStartAASPad6{ xStartAASPad14 };
	constexpr int yStartAASPad6{ yStartAASPad8 };
	constexpr int widthAASPad6{ widthAASPad13 };
	constexpr int heightAASPad6{ heightAASPad13 };

	constexpr int xStartAASPad5{ xStartAASPad13 };
	constexpr int yStartAASPad5{ yStartAASPad8 };
	constexpr int widthAASPad5{ widthAASPad13 };
	constexpr int heightAASPad5{ heightAASPad13 };

	constexpr int xStartAASPad4{ xStartAASPad16 };
	constexpr int yStartAASPad4{ int(245.0f * scalingFactorHeight) };
	constexpr int widthAASPad4{ widthAASPad13 };
	constexpr int heightAASPad4{ heightAASPad13 };

	constexpr int xStartAASPad3{ xStartAASPad15 };
	constexpr int yStartAASPad3{ yStartAASPad4 };
	constexpr int widthAASPad3{ widthAASPad13 };
	constexpr int heightAASPad3{ heightAASPad13 };

	constexpr int xStartAASPad2{ xStartAASPad14 };
	constexpr int yStartAASPad2{ yStartAASPad4 };
	constexpr int widthAASPad2{ widthAASPad13 };
	constexpr int heightAASPad2{ heightAASPad13 };

	constexpr int xStartAASPad1{ xStartAASPad13 };
	constexpr int yStartAASPad1{ yStartAASPad4 };
	constexpr int widthAASPad1{ widthAASPad13 };
	constexpr int heightAASPad1{ heightAASPad13 };

	// Assign Key Group
	constexpr int widthAppAssignKeyGrp{ int(570.0f * scalingFactorWidth) };
	constexpr int heightAppAssignKeyGrp{ int(355.0f * scalingFactorHeight) };

	constexpr int xStartAAKGListBox{ int(2.0f * scalingFactorWidth) };
	constexpr int yStartAAKGListBox{ int(36.0f * scalingFactorHeight) };
	constexpr int widthAAKGListBox{ int(190.0f * scalingFactorWidth) };
	constexpr int heightAAKGListBox{ int(34.0f * scalingFactorHeight) };

	constexpr int xStartAAKGProgName{ int(0.0f * scalingFactorWidth) };
	constexpr int yStartAAKGProgName{ int(0.0f * scalingFactorHeight) };
	constexpr int widthAAKGProgName{ int(570.0f * scalingFactorWidth) };
	constexpr int heightAAKGProgName{ int(25.0f * scalingFactorHeight) };

	constexpr int xStartAAKGListBoxAssigned{ int(410.0f * scalingFactorWidth) };
	constexpr int yStartAAKGListBoxAssigned{ int(36.0f * scalingFactorHeight) };
	constexpr int widthAAKGListBoxAssigned{ int(158.0f * scalingFactorWidth) };
	constexpr int heightAAKGListBoxAssigned{ int(34.0f * scalingFactorHeight) };

	constexpr int xStartAAAListBox{ int(410.0f * scalingFactorWidth) };
	constexpr int yStartAAAListBox{ int(71.0f * scalingFactorHeight) };
	constexpr int widthAAAListBox{ int(190.0f * scalingFactorWidth) };
	constexpr int heightAAAListBox{ int(234.0f * scalingFactorHeight) };

	constexpr int xStartAAKGRoot{ int(266.0f * scalingFactorWidth) };
	constexpr int yStartAAKGRoot{ int(100.0f * scalingFactorHeight) };
	constexpr int widthAAKGRoot{ int(70.0f * scalingFactorWidth) };
	constexpr int heightAAKGRoot{ int(38.0f * scalingFactorHeight) };

	constexpr int xStartAAKGStartNote{ int(266.0f * scalingFactorWidth) };
	constexpr int yStartAAKGStartNote{ int(170.0f * scalingFactorHeight) };
	constexpr int widthAAKGStartNote{ int(70.0f * scalingFactorWidth) };
	constexpr int heightAAKGStartNote{ int(38.0f * scalingFactorHeight) };

	constexpr int xStartAAKGEndNote{ int(266.0f * scalingFactorWidth) };
	constexpr int yStartAAKGEndNote{ int(240.0f * scalingFactorHeight) };
	constexpr int widthAAKGEndNote{ int(70.0f * scalingFactorWidth) };
	constexpr int heightAAKGEndNote{ int(38.0f * scalingFactorHeight) };

	// App Seq Components
	constexpr int widthAppSeqComp{ int(560.0f * scalingFactorWidth) };
	constexpr int heightAppSeqComp{ int(65.0f * scalingFactorHeight) };

	constexpr int yStartAppSeqCompBtn{ int(3.0f * scalingFactorHeight) };
	constexpr int widthAppSeqCompBtn{ int(55.0f * scalingFactorWidth) };
	constexpr int heightAppSeqCompBtn{ int(35.0f * scalingFactorHeight) };

	constexpr int xStartAppSeqEndBar{ int(378.0f * scalingFactorWidth) };
	constexpr int xStartAppSeqStartBar{ int(315.0f * scalingFactorWidth) };
	constexpr int xStartAppSeqBars{ int(245.0f * scalingFactorWidth) };
	constexpr int xStartAppSeqBpm{ int(175.0f * scalingFactorWidth) };

	constexpr int xStartAppSeqNameText{ int(45.0f * scalingFactorWidth) };
	constexpr int yStartAppSeqNameText{ int(15.0f * scalingFactorHeight) };
	constexpr int widthAppSeqNameText{ int(120.0f * scalingFactorWidth) };
	constexpr int heightAppSeqNameText{ int(30.0f * scalingFactorHeight) };

	constexpr int xStartAppSeqOptBtn{ int(520.0f * scalingFactorWidth) };
	constexpr int yStartAppSeqOptBtn{ int(0.0f * scalingFactorHeight) };
	constexpr int widthAppSeqOptBtn{ int(36.0f * scalingFactorWidth) };
	constexpr int heightAppSeqOptBtn{ int(60.0f * scalingFactorHeight) };

	constexpr int xStartAppSeqSNoL{ int(0.0f * scalingFactorWidth) };
	constexpr int yStartAppSeqSNoL{ int(0.0f * scalingFactorHeight) };
	constexpr int widthAppSeqSNoL{ int(30.0f * scalingFactorWidth) };
	constexpr int heightAppSeqSNoL{ int(30.0f * scalingFactorHeight) };

	constexpr int xStartAppSeqTransComp{ int(448.0f * scalingFactorWidth) };
	constexpr int yStartAppSeqTransComp{ int(3.0f * scalingFactorHeight) };
	constexpr int widthAppSeqTransComp{ int(70.0f * scalingFactorWidth) };
	constexpr int heightAppSeqTransComp{ int(48.0f * scalingFactorHeight) };

	constexpr int xStartAppSeqSlash{ int(367.0f * scalingFactorWidth) };
	constexpr int yStartAppSeqSlash{ int(0.0f * scalingFactorHeight) };
	constexpr int widthAppSeqSlash{ int(14.0f * scalingFactorWidth) };
	constexpr int heightAppSeqSlash{ int(24.0f * scalingFactorHeight) };

	constexpr int xStartAppSeqAsBpm{ int(176.0f * scalingFactorWidth) };
	constexpr int yStartAppSeqAsBpm{ int(42.0f * scalingFactorHeight) };
	constexpr int widthAppSeqAsBpm{ int(55.0f * scalingFactorWidth) };
	constexpr int heightAppSeqAsBpm{ int(15.0f * scalingFactorHeight) };

	constexpr int xStartAppSeqLoop{ int(344.0f * scalingFactorWidth) };
	constexpr int yStartAppSeqLoop{ int(42.0f * scalingFactorHeight) };
	constexpr int widthAppSeqLoop{ int(55.0f * scalingFactorWidth) };
	constexpr int heightAppSeqLoop{ int(15.0f * scalingFactorHeight) };

	constexpr int xStartAppSeqEmp{ int(0.0f * scalingFactorWidth) };
	constexpr int yStartAppSeqEmp{ int(30.0f * scalingFactorHeight) };
	constexpr int widthAppSeqEmp{ int(30.0f * scalingFactorWidth) };
	constexpr int heightAppSeqEmp{ int(35.0f * scalingFactorHeight) };

	// AddNewButton
	constexpr int xStartAddNewButton{ int(1.0f * scalingFactorWidth) };
	constexpr int yStartAddNewButton{ int(235.0f * scalingFactorHeight) };
	constexpr int widthAddNewButton{ int(555.0f * scalingFactorWidth) };
	constexpr int heightAddNewButton{ int(25.0f * scalingFactorHeight) };

	// SeqViewPort
	constexpr int xStartSeqViewPort{ int(0.0f * scalingFactorWidth) };
	constexpr int yStartSeqViewPort{ int(5.0f * scalingFactorHeight) };
	constexpr int widthSeqViewPort{ widthAppTopbar };
	constexpr int heightSeqViewPort{ yStartAddNewButton };

	// SeqContainer
	constexpr int xStartSeqContainer{ int(5.0f * scalingFactorWidth) };
	constexpr int yStartSeqContainer{ int(0.0f * scalingFactorHeight) };
	constexpr int xWidthSeqContainer{ widthAppTopbar - 10 };
	constexpr int yHeightSeqContainer{ int(62.0f * scalingFactorHeight) };
	constexpr int yHeightSeqContainerOffset{ int(8.0f * scalingFactorHeight) };

	// TrackViewPort
	constexpr int xStartTrackViewPort{ xStartSeqViewPort };
	constexpr int yStartTrackViewPort{ yStartSeqViewPort };
	constexpr int widthTrackViewPort{ widthSeqViewPort };
	constexpr int heightTrackViewPort{ heightSeqViewPort };

	// TrackContainer
	constexpr int xStartTrackContainer{ xStartSeqContainer };
	constexpr int yStartTrackContainer{ yStartSeqContainer };
	constexpr int xWidthTrackContainer{ xWidthSeqContainer };
	constexpr int yHeightTrackContainer{ yHeightSeqContainer };
	constexpr int yHeightTrackContainerOffset{ yHeightSeqContainerOffset };

	//AppTrack
	constexpr int xWidthAppTrack{ xWidthAppSequence };
	constexpr int yHeightAppTrack{ yHeightAppSequence };

	// Program ViewPort
	constexpr int xStartProgViewPort{ xStartSeqViewPort };
	constexpr int yStartProgViewPort{ yStartSeqViewPort };
	constexpr int widthProgViewPort{ widthSeqViewPort };
	constexpr int heightProgViewPort{ heightSeqViewPort };

	// ProgContainer
	constexpr int xStartProgContainer{ xStartSeqContainer };
	constexpr int yStartProgContainer{ yStartSeqContainer };
	constexpr int xWidthProgContainer{ xWidthSeqContainer };
	constexpr int yHeightProgContainer{ yHeightSeqContainer };
	constexpr int yHeightProgContainerOffset{ yHeightSeqContainerOffset };

	//AppProgram
	constexpr int xWidthAppProg{ xWidthAppSequence };
	constexpr int yHeightAppProg{ yHeightAppSequence };

	constexpr int widthAppProg{ int(566.0f * scalingFactorWidth) };
	constexpr int heightAppProg{ int(272.0f * scalingFactorHeight) };

	constexpr int widthAppProgComp{ int(560.0f * scalingFactorWidth) };
	constexpr int heightAppProgComp{ int(65.0f * scalingFactorHeight) };

	constexpr int xStartAppProgNum{ int(0.0f * scalingFactorWidth) };
	constexpr int yStartAppProgNum{ int(0.0f * scalingFactorHeight) };
	constexpr int widthAppProgNum{ int(30.0f * scalingFactorWidth) };
	constexpr int heightAppProgNum{ int(30.0f * scalingFactorHeight) };

	constexpr int xStartAppProgNum2{ int(0.0f * scalingFactorWidth) };
	constexpr int yStartAppProgNum2{ int(30.0f * scalingFactorHeight) };
	constexpr int widthAppProgNum2{ int(30.0f * scalingFactorWidth) };
	constexpr int heightAppProgNum2{ int(30.0f * scalingFactorHeight) };

	constexpr int xStartAppProgLoad{ int(272.0f * scalingFactorWidth) };
	constexpr int yStartAppProgLoad{ int(15.0f * scalingFactorHeight) };
	constexpr int widthAppProgLoad{ int(100.0f * scalingFactorWidth) };
	constexpr int heightAppProgLoad{ int(30.0f * scalingFactorHeight) };

	constexpr int xStartAppProgName{ int(45.0f * scalingFactorWidth) };
	constexpr int yStartAppProgName{ int(15.0f * scalingFactorHeight) };
	constexpr int widthAppProgName{ int(120.0f * scalingFactorWidth) };
	constexpr int heightAppProgName{ int(30.0f * scalingFactorHeight) };

	constexpr int xStartAppProgImgBtn{ int(183.0f * scalingFactorWidth) };
	constexpr int yStartAppProgImgBtn{ int(15.0f * scalingFactorHeight) };
	constexpr int widthAppProgImgBtn{ int(35.0f * scalingFactorWidth) };
	constexpr int heightAppProgImgBtn{ int(25.0f * scalingFactorHeight) };

	// App Prog Sort
	constexpr int widthAppProgSort{ int(350.0f * scalingFactorWidth) };
	constexpr int heightAppProgSort{ int(250.0f * scalingFactorHeight) };

	constexpr int widthDefAppProgSort{ int(80.0f * scalingFactorWidth) };
	constexpr int heightDefAppProgSort{ int(20.0f * scalingFactorHeight) };

	constexpr int xStartAPSDrum{ int(40.0f * scalingFactorWidth) };
	constexpr int yStartAPSDrum{ int(35.0f * scalingFactorHeight) };

	constexpr int xStartAPSKg{ int(40.0f * scalingFactorWidth) };
	constexpr int yStartAPSKg{ int(57.0f * scalingFactorHeight) };

	constexpr int xStartAPSClip{ int(40.0f * scalingFactorWidth) };
	constexpr int yStartAPSClip{ int(79.0f * scalingFactorHeight) };

	constexpr int xStartAPSPlug{ int(40.0f * scalingFactorWidth) };
	constexpr int yStartAPSPlug{ int(101.0f * scalingFactorHeight) };

	constexpr int xStartAPSMidi{ int(40.0f * scalingFactorWidth) };
	constexpr int yStartAPSMidi{ int(123.0f * scalingFactorHeight) };

	constexpr int xStartAPSAud{ int(40.0f * scalingFactorWidth) };
	constexpr int yStartAPSAud{ int(145.0f * scalingFactorHeight) };

	constexpr int xStartAPSApply{ int(96.0f * scalingFactorWidth) };
	constexpr int yStartAPSApply{ int(190.0f * scalingFactorHeight) };

	constexpr int xStartAPSCancel{ int(208.0f * scalingFactorWidth) };
	constexpr int yStartAPSCancel{ int(190.0f * scalingFactorHeight) };

	constexpr int xStartAPSList{ int(140.0f * scalingFactorWidth) };
	constexpr int yStartAPSList{ int(35.0f * scalingFactorHeight) };
	constexpr int widthAPSList{ int(170.0f * scalingFactorWidth) };
	constexpr int heightAPSList{ int(130.0f * scalingFactorHeight) };

	//App Transport Components
	constexpr int xStartTransComp{ int(60.0f * scalingFactorWidth) };
	constexpr int yStartTransComp{ int(0.0f * scalingFactorHeight) };
	constexpr int widthTransComp{ int(24.0f * scalingFactorWidth) };
	constexpr int heightTransComp{ int(20.0f * scalingFactorHeight) };

	constexpr int xStartTransCompBpmF{ int(0.0f * scalingFactorWidth) };

	constexpr int xStartTransCompBpmV{ int(24.0f * scalingFactorWidth) };

	constexpr int xStartTransCompBarF{ int(48.0f * scalingFactorWidth) };

	constexpr int xStartTransCompBarV{ int(72.0f * scalingFactorWidth) };

	constexpr int xStartTransCompTimSigF{ int(96.0f * scalingFactorWidth) };

	constexpr int xStartTransCompTimeSigV{ int(120.0f * scalingFactorWidth) };

	constexpr int xStartTransCompTcF{ int(141.0f * scalingFactorWidth) };
	constexpr int widthTransCompTcF{ int(18.0f * scalingFactorWidth) };

	constexpr int xStartTransCompTcV{ int(159.0f * scalingFactorWidth) };
	constexpr int widthTransCompTcV{ int(33.0f * scalingFactorWidth) };

	constexpr int widthTransCompDia{ int(350.0f * scalingFactorWidth) };
	constexpr int heightTransCompDia{ int(250.0f * scalingFactorHeight) };

	// App Transport Options
   // constexpr int xStartTransComp{ int(60.0f * scalingFactorHeight) };
   // constexpr int yStartTransComp{ int(0.0f * scalingFactorHeight) };
   // constexpr int widthTransComp{ int(24.0f * scalingFactorWidth) };
   // constexpr int heightTransComp{ int(20.0f * scalingFactorHeight) };

	constexpr int xStartAppTrans{ int(255.0f * scalingFactorWidth) };
	constexpr int yStartAppTrans{ yStartAppMainmode };
	constexpr int widthAppTrans{ int(315.0f * scalingFactorWidth) };
	constexpr int heightAppTrans{ heightAppGc };

	constexpr int xStartAppTransMet{ int(0.0f * scalingFactorWidth) };
	constexpr int yStartAppTransMet{ int(0.0f * scalingFactorHeight) };
	constexpr int widthAppTransMet{ int(20.0f * scalingFactorWidth) };
	constexpr int heightAppTransMet{ heightAppGc };

	constexpr int xStartAppTransBpm{ int(25.0f * scalingFactorWidth) };
	constexpr int yStartAppTransBpm{ int(0.0f * scalingFactorHeight) };
	constexpr int widthAppTransBpm{ int(180.0f * scalingFactorWidth) };
	constexpr int heightAppTransBpm{ heightAppGc };

	constexpr int xStartAppTransBbtF{ int(205.0f * scalingFactorWidth) };
	constexpr int yStartAppTransBbtF{ int(0.0f * scalingFactorHeight) };
	constexpr int widthAppTransBbtF{ int(40.0f * scalingFactorWidth) };
	constexpr int heightAppTransBbtF{ heightAppGc };

	constexpr int xStartAppTransBbtV{ int(255.0f * scalingFactorWidth) };
	constexpr int yStartAppTransBbtV{ int(0.0f * scalingFactorHeight) };
	constexpr int widthAppTransBbtV{ int(55.0f * scalingFactorWidth) };
	constexpr int heightAppTransBbtV{ heightAppGc };

	//App Sequence Paint
	constexpr int xStartSeqPaint1{ int(237.0f * scalingFactorWidth) };
	constexpr int xStartSeqPaint2{ int(440.0f * scalingFactorWidth) };
	constexpr int xStartSeqPaint3{ int(308.0f * scalingFactorWidth) };
	constexpr int yStartSeqPaint{ int(4.0f * scalingFactorHeight) };
	constexpr int widthSeqPaint{ int(1.0f * scalingFactorWidth) };
	constexpr int heightSeqPaint{ int(54.0f * scalingFactorHeight) };

	constexpr int xStartSeqPaint4{ int(520.0f * scalingFactorWidth) };
	constexpr int yStartSeqPaint4{ int(0.0f * scalingFactorHeight) };
	constexpr int widthSeqPaint4{ int(36.0f * scalingFactorWidth) };
	constexpr int heightSeqPaint4{ int(65.0f * scalingFactorHeight) };

	//App Sequence Options Paint
	constexpr int xStartSeqOptPaint4{ int(528.0f * scalingFactorWidth) };
	constexpr int yStartSeqOtpPaint4{ int(0.0f * scalingFactorHeight) };
	constexpr int widthSeqOptPaint4{ int(40.0f * scalingFactorWidth) };
	constexpr int heightSeqOptPaint4{ int(58.0f * scalingFactorHeight) };

	//App Sequence Track
	constexpr int xStartTrkPaint1{ int(230.0f * scalingFactorWidth) };
	constexpr int xStartTrkPaint2{ int(397.0f * scalingFactorWidth) };
	constexpr int xStartTrkPaint3{ int(314.0f * scalingFactorWidth) };
	constexpr int yStartTrkPaint{ int(4.0f * scalingFactorHeight) };
	constexpr int widthTrkPaint{ int(1.0f * scalingFactorWidth) };
	constexpr int heightTrkPaint{ int(54.0f * scalingFactorHeight) };

	constexpr int xStartTrkPaint4{ int(520.0f * scalingFactorWidth) };
	constexpr int yStartTrkPaint4{ int(0.0f * scalingFactorHeight) };
	constexpr int widthTrkPaint4{ int(36.0f * scalingFactorWidth) };
	constexpr int heightTrkPaint4{ int(65.0f * scalingFactorHeight) };

	// App Trans Options
	constexpr int xStartTransCompOpt{ int(33.0f * scalingFactorHeight) };
	constexpr int yStartTransCompOpt{ int(0.0f * scalingFactorHeight) };
	constexpr int widthTransCompOpt{ int(50.0f * scalingFactorWidth) };
	constexpr int heightTransCompOpt{ int(38.0f * scalingFactorHeight) };

	constexpr int xStartTransOptBpmL{ int(33.0f * scalingFactorWidth) };
	constexpr int yStartTransOptBpmL{ int(35.0f * scalingFactorHeight) };

	constexpr int xStartTransOptBarsL{ int(33.0f * scalingFactorWidth) };
	constexpr int yStartTransOptBarsL{ int(89.0f * scalingFactorHeight) };

	constexpr int xStartTransOptSigL{ int(33.0f * scalingFactorWidth) };
	constexpr int yStartTransOptSigL{ int(139.0f * scalingFactorHeight) };

	constexpr int xStartTransOptSlash{ int(154.0f * scalingFactorWidth) };
	constexpr int yStartTransOptSlash{ int(131.0f * scalingFactorHeight) };
	constexpr int widthTransOptSlash{ int(16.0f * scalingFactorWidth) };

	constexpr int xStartTransOptBpmComp{ int(91.0f * scalingFactorWidth) };
	constexpr int yStartTransOptBpmComp{ int(37.0f * scalingFactorHeight) };
	constexpr int widthTransOptBpmComp{ int(56.0f * scalingFactorWidth) };

	constexpr int xStartTransOptBarComp{ int(91.0f * scalingFactorWidth) };
	constexpr int yStartTransOptBarComp{ int(88.0f * scalingFactorHeight) };
	constexpr int widthTransOptBarComp{ int(56.0f * scalingFactorWidth) };

	constexpr int xStartTransOptSigComp{ int(91.0f * scalingFactorWidth) };
	constexpr int yStartTransOptSigComp{ int(139.0f * scalingFactorHeight) };
	constexpr int widthTransOptSigComp{ int(56.0f * scalingFactorWidth) };

	constexpr int xStartTransOptSigDComp{ int(176.0f * scalingFactorWidth) };
	constexpr int yStartTransOptSigDComp{ int(139.0f * scalingFactorHeight) };
	constexpr int widthTransOptSigDComp{ int(56.0f * scalingFactorWidth) };

	constexpr int xStartTransOptTcL{ int(193.0f * scalingFactorWidth) };
	constexpr int yStartTransOptTcL{ int(56.0f * scalingFactorHeight) };
	constexpr int widthTransOptTcL{ int(60.0f * scalingFactorWidth) };

	constexpr int xStartTransOptTcComp{ int(251.0f * scalingFactorWidth) };
	constexpr int yStartTransOptTcComp{ int(58.0f * scalingFactorHeight) };
	constexpr int widthTransOptTcComp{ int(80.0f * scalingFactorWidth) };

	// App Split event
	constexpr int xStartSESetL{ int(10.0f * scalingFactorWidth) };
	constexpr int yStartSESetL{ int(20.0f * scalingFactorHeight) };
	constexpr int widthSESetL{ int(150.0f * scalingFactorWidth) };
	constexpr int heightSESetL{ int(25.0f * scalingFactorHeight) };

	constexpr int xStartSESlider{ int(10.0f * scalingFactorWidth) };
	constexpr int yStartSESlider{ int(75.0f * scalingFactorHeight) };
	constexpr int widthSESlider{ int(380.0f * scalingFactorWidth) };
	constexpr int heightSESlider{ int(25.0f * scalingFactorHeight) };

	constexpr int xStartSEIntoL{ int(158.0f * scalingFactorWidth) };
	constexpr int yStartSEIntoL{ int(53.0f * scalingFactorHeight) };
	constexpr int widthSEIntoL{ int(80.0f * scalingFactorWidth) };
	constexpr int heightSEIntoL{ int(18.0f * scalingFactorHeight) };

	constexpr int xStartSESelCheck{ int(10.0f * scalingFactorWidth) };
	constexpr int yStartSESelCheck{ int(130.0f * scalingFactorHeight) };
	constexpr int widthSESelCheck{ int(180.0f * scalingFactorWidth) };
	constexpr int heightSESelCheck{ int(25.0f * scalingFactorHeight) };

	constexpr int xStartSEApply{ int(100.0f * scalingFactorWidth) };
	constexpr int yStartSEApply{ int(190.0f * scalingFactorHeight) };
	constexpr int widthSEApply{ int(80.0f * scalingFactorWidth) };
	constexpr int heightSEApply{ int(25.0f * scalingFactorHeight) };

	constexpr int xStartSECancel{ int(220.0f * scalingFactorWidth) };
	constexpr int yStartSECancel{ int(189.0f * scalingFactorHeight) };
	constexpr int widthSECancel{ int(80.0f * scalingFactorWidth) };
	constexpr int heightSECancel{ int(25.0f * scalingFactorHeight) };

	constexpr int yStartSEE1{ int(45.0f * scalingFactorHeight) };
	constexpr int xStartSEElement{ int(10.0f * scalingFactorWidth) };
	constexpr int widthSEElement{ int(380.0f * scalingFactorWidth) };
	constexpr int heightSEElement{ int(1.0f * scalingFactorHeight) };

	// Copy Track

	constexpr int widthDefCpTrk{ int(300.0f * scalingFactorWidth) };
	constexpr int heightDefCpTrk{ int(230.0f * scalingFactorHeight) };

	constexpr int xStartCpTrkCpCont{ int(80.0f * scalingFactorWidth) };
	constexpr int yStartCpTrkCpCont{ int(15.0f * scalingFactorHeight) };
	constexpr int widthCpTrkCpCont{ int(140.0f * scalingFactorWidth) };
	constexpr int heightCpTrkCpCont{ int(17.0f * scalingFactorHeight) };

	constexpr int xStartCpTrkCpContComp{ int(50.0f * scalingFactorWidth) };
	constexpr int yStartCpTrkCpContComp{ int(32.0f * scalingFactorHeight) };
	constexpr int widthCpTrkCpContComp{ int(200.0f * scalingFactorWidth) };
	constexpr int heightCpTrkCpContComp{ int(45.0f * scalingFactorHeight) };

	constexpr int xStartCpTrkOverCont{ int(80.0f * scalingFactorWidth) };
	constexpr int yStartCpTrkOverCont{ int(90.0f * scalingFactorHeight) };
	constexpr int widthCpTrkOverCont{ int(140.0f * scalingFactorWidth) };
	constexpr int heightCpTrkOverCont{ int(20.0f * scalingFactorHeight) };

	constexpr int xStartCpTrkOvrCntComp{ int(50.0f * scalingFactorWidth) };
	constexpr int yStartCpTrkOvrCntComp{ int(110.0f * scalingFactorHeight) };
	constexpr int widthCpTrkOvrCntComp{ int(200.0f * scalingFactorWidth) };
	constexpr int heightCpTrkOvrCntComp{ int(45.0f * scalingFactorHeight) };

	constexpr int xStartCpTrkApply{ int(48.0f * scalingFactorWidth) };
	constexpr int yStartCpTrkApply{ int(185.0f * scalingFactorHeight) };
	constexpr int widthCpTrkApply{ int(80.0f * scalingFactorWidth) };
	constexpr int heightCpTrkApply{ int(25.0f * scalingFactorHeight) };

	constexpr int xStartCpTrkCancel{ int(170.0f * scalingFactorWidth) };
	constexpr int yStartCpTrkCancel{ int(185.0f * scalingFactorHeight) };
	constexpr int widthCpTrkCancel{ int(80.0f * scalingFactorWidth) };
	constexpr int heightCpTrkCancel{ int(25.0f * scalingFactorHeight) };

	constexpr int widthTrkOptDia{ int(400.0f * scalingFactorWidth) };
	constexpr int heightTrkOptDia{ int(250.0f * scalingFactorHeight) };

	constexpr int xStartPQSetL{ int(10.0f * scalingFactorWidth) };
	constexpr int yStartPQSetL{ int(10.0f * scalingFactorHeight) };
	constexpr int widthPQSetL{ int(150.0f * scalingFactorWidth) };
	constexpr int heightPQSetL{ int(25.0f * scalingFactorHeight) };

	constexpr int widthDefPQ{ int(80.0f * scalingFactorWidth) };
	constexpr int heightDefPQ{ int(40.0f * scalingFactorHeight) };

	constexpr int widthDefPQView{ int(455.0f * scalingFactorWidth) };
	constexpr int heightDefPQView{ int(350.0f * scalingFactorHeight) };
	constexpr int widthDefPQDia{ int(445.0f * scalingFactorWidth) };
	constexpr int heightDefPQDia{ int(350.0f * scalingFactorHeight) };

	constexpr int xStartPQRootComp{ int(10.0f * scalingFactorWidth) };
	constexpr int yStartPQRootComp{ int(45.0f * scalingFactorHeight) };
	constexpr int widthPQRootComp{ int(80.0f * scalingFactorWidth) };
	constexpr int heightPQRootComp{ int(40.0f * scalingFactorHeight) };

	constexpr int xStartPQScaleComp{ int(270.0f * scalingFactorWidth) };
	constexpr int yStartPQScaleComp{ int(45.0f * scalingFactorHeight) };
	constexpr int widthPQScaleComp{ int(80.0f * scalingFactorWidth) };
	constexpr int heightPQScaleComp{ int(40.0f * scalingFactorHeight) };

	constexpr int xStartPQFilter{ int(10.0f * scalingFactorWidth) };
	constexpr int yStartPQFilter{ int(95.0f * scalingFactorHeight) };
	constexpr int widthPQFilter{ int(150.0f * scalingFactorWidth) };
	constexpr int heightPQFilter{ int(25.0f * scalingFactorHeight) };

	constexpr int xStartPQSelCheck{ int(10.0f * scalingFactorWidth) };
	constexpr int yStartPQSelCheck{ int(130.0f * scalingFactorHeight) };
	constexpr int widthPQSelCheck{ int(214.0f * scalingFactorWidth) };
	constexpr int heightPQSelCheck{ int(25.0f * scalingFactorHeight) };

	constexpr int xStartPQFilter2{ int(10.0f * scalingFactorWidth) };
	constexpr int yStartPQFilter2{ int(170.0f * scalingFactorHeight) };
	constexpr int widthPQFilter2{ int(150.0f * scalingFactorWidth) };
	constexpr int heightPQFilter2{ int(25.0f * scalingFactorHeight) };

	constexpr int xStartPQFilter3{ int(10.0f * scalingFactorWidth) };
	constexpr int yStartPQFilter3{ int(198.0f * scalingFactorHeight) };
	constexpr int widthPQFilter3{ int(374.0f * scalingFactorWidth) };
	constexpr int heightPQFilter3{ int(20.0f * scalingFactorHeight) };

	constexpr int xStartPQStartComp{ int(10.0f * scalingFactorWidth) };
	constexpr int yStartPQStartComp{ int(225.0f * scalingFactorHeight) };
	constexpr int widthPQStartComp{ int(80.0f * scalingFactorWidth) };
	constexpr int heightPQStartComp{ int(40.0f * scalingFactorHeight) };

	constexpr int xStartPQEndComp{ int(270.0f * scalingFactorWidth) };
	constexpr int yStartPQEndComp{ int(225.0f * scalingFactorHeight) };
	constexpr int widthPQEndComp{ int(80.0f * scalingFactorWidth) };
	constexpr int heightPQEndComp{ int(40.0f * scalingFactorHeight) };

	constexpr int xStartPQApply{ int(120.0f * scalingFactorWidth) };
	constexpr int yStartPQApply{ int(304.0f * scalingFactorHeight) };
	constexpr int widthPQApply{ int(80.0f * scalingFactorWidth) };
	constexpr int heightPQApply{ int(24.0f * scalingFactorHeight) };

	constexpr int xStartPQCancel{ int(240.0f * scalingFactorWidth) };
	constexpr int yStartPQCancel{ int(304.0f * scalingFactorHeight) };
	constexpr int widthPQCancel{ int(80.0f * scalingFactorWidth) };
	constexpr int heightPQCancel{ int(24.0f * scalingFactorHeight) };

	constexpr int yStartPQE1{ int(35.0f * scalingFactorHeight) };
	constexpr int yStartPQE2{ int(120.0f * scalingFactorHeight) };
	constexpr int yStartPQE3{ int(200.0f * scalingFactorHeight) };
	constexpr int xStartPQElement{ int(10.0f * scalingFactorWidth) };
	constexpr int widthPQElement{ int(430.0f * scalingFactorWidth) };
	constexpr int heightPQElement{ int(1.0f * scalingFactorHeight) };

	// App Humanize
	constexpr int widthHumView{ widthDefPQView };
	constexpr int HeightHumView{ int(760.0f * scalingFactorHeight) };

	constexpr int widthHumDia{ int(440.0f * scalingFactorWidth) };
	constexpr int heightHumDia{ int(760.0f * scalingFactorHeight) };

	constexpr int widthLenDia{ int(425.0f * scalingFactorWidth) };
	constexpr int heightLenDia{ int(270.0f * scalingFactorHeight) };

	constexpr int widthCopy{ int(337.4f * scalingFactorWidth) };
	constexpr int heightCopy{ int(173.65f * scalingFactorHeight) };

	constexpr int xStartHumFilter{ int(10.0f * scalingFactorWidth) };
	constexpr int yStartHumFilter{ int(614.0f * scalingFactorHeight) };
	constexpr int widthHumFilter{ int(150.0f * scalingFactorWidth) };
	constexpr int heightHumFilter{ int(25.0f * scalingFactorHeight) };

	constexpr int xStartHumSelCheck{ int(10.0f * scalingFactorWidth) };
	constexpr int yStartHumSelCheck{ int(652.0f * scalingFactorHeight) };
	constexpr int widthHumSelCheck{ int(238.0f * scalingFactorWidth) };
	constexpr int heightHumSelCheck{ int(25.0f * scalingFactorHeight) };

	constexpr int xStartHumStrenL{ int(176.0f * scalingFactorWidth) };
	constexpr int yStartHumStrenL{ int(534.0f * scalingFactorHeight) };
	constexpr int widthHumStrenL{ int(96.0f * scalingFactorWidth) };
	constexpr int heightHumStrenL{ int(18.0f * scalingFactorHeight) };

	constexpr int xStartHumVelSlider{ int(10.0f * scalingFactorWidth) };
	constexpr int yStartHumVelSlider{ int(559.0f * scalingFactorHeight) };
	constexpr int widthHumVelSlider{ int(425.0f * scalingFactorWidth) };
	constexpr int heightHumVelSlider{ int(25.0f * scalingFactorHeight) };

	constexpr int xStartHumVelL{ int(10.0f * scalingFactorWidth) };
	constexpr int yStartHumVelL{ int(459.0f * scalingFactorHeight) };
	constexpr int widthHumVelL{ int(150.0f * scalingFactorWidth) };
	constexpr int heightHumVelL{ int(25.0f * scalingFactorHeight) };

	constexpr int xStartHumVelSel{ int(10.0f * scalingFactorWidth) };
	constexpr int yStartHumVelSel{ int(497.0f * scalingFactorHeight) };
	constexpr int widthHumVelSel{ int(214.0f * scalingFactorWidth) };
	constexpr int heightHumVelSel{ int(25.0f * scalingFactorHeight) };

	constexpr int xStartHumLenValL{ int(176.0f * scalingFactorWidth) };
	constexpr int yStartHumLenValL{ int(387.0f * scalingFactorHeight) };
	constexpr int widthHumLenValL{ int(96.0f * scalingFactorWidth) };
	constexpr int heightHumLenValL{ int(18.0f * scalingFactorHeight) };

	constexpr int xStartHumLenSlider{ int(10.0f * scalingFactorWidth) };
	constexpr int yStartHumLenSlider{ int(412.0f * scalingFactorHeight) };
	constexpr int widthHumLenSlider{ int(425.0f * scalingFactorWidth) };
	constexpr int heightHumLenSlider{ int(25.0f * scalingFactorHeight) };

	constexpr int xStartHumLenL{ int(10.0f * scalingFactorWidth) };
	constexpr int yStartHumLenL{ int(312.0f * scalingFactorHeight) };
	constexpr int widthHumLenL{ int(150.0f * scalingFactorWidth) };
	constexpr int heightHumLenL{ int(25.0f * scalingFactorHeight) };

	constexpr int xStartHumEagL{ int(176.0f * scalingFactorWidth) };
	constexpr int yStartHumEagL{ int(100.0f * scalingFactorHeight) };
	constexpr int widthHumEagL{ int(96.0f * scalingFactorWidth) };
	constexpr int heightHumEagL{ int(18.0f * scalingFactorHeight) };

	constexpr int xStartHumEagSlider{ int(23.0f * scalingFactorWidth) };
	constexpr int yStartHumEagSlider{ int(125.0f * scalingFactorHeight) };
	constexpr int widthHumEagSlider{ int(400.0f * scalingFactorWidth) };
	constexpr int heightHumEagSlider{ int(25.0f * scalingFactorHeight) };

	constexpr int xStartHumEagN{ int(10.0f * scalingFactorWidth) };
	constexpr int yStartHumEagN{ int(267.0f * scalingFactorHeight) };
	constexpr int widthHumEagN{ int(422.0f * scalingFactorWidth) };
	constexpr int heightHumEagN{ int(25.0f * scalingFactorHeight) };

	constexpr int xStartHumTimL{ int(176.0f * scalingFactorWidth) };
	constexpr int yStartHumTimL{ int(80.0f * scalingFactorHeight) };
	constexpr int widthHumTimL{ int(96.0f * scalingFactorWidth) };
	constexpr int heightHumTimL{ int(18.0f * scalingFactorHeight) };

	constexpr int xStartHumTimSlider{ int(23.0f * scalingFactorWidth) };
	constexpr int yStartHumTimSlider{ int(70.0f * scalingFactorHeight) };
	constexpr int widthHumTimSlider{ int(400.0f * scalingFactorWidth) };
	constexpr int heightHumTimSlider{ int(25.0f * scalingFactorHeight) };

	constexpr int xStartHumTimSliN{ int(10.0f * scalingFactorWidth) };
	constexpr int yStartHumTimSliN{ int(152.0f * scalingFactorHeight) };
	constexpr int widthHumTimSliN{ int(422.0f * scalingFactorWidth) };
	constexpr int heightHumTimSliN{ int(25.0f * scalingFactorHeight) };

	constexpr int xStartHumInto{ int(176.0f * scalingFactorWidth) };
	constexpr int yStartHumInto{ int(45.0f * scalingFactorHeight) };
	constexpr int widthHumInto{ int(96.0f * scalingFactorWidth) };
	constexpr int heightHumInto{ int(18.0f * scalingFactorHeight) };

	constexpr int xStartHumTimSel{ int(10.0f * scalingFactorWidth) };
	constexpr int yStartHumTimSel{ int(10.0f * scalingFactorHeight) };
	constexpr int widthHumTimSel{ int(214.0f * scalingFactorWidth) };
	constexpr int heightHumTimSel{ int(25.0f * scalingFactorHeight) };

	constexpr int xStartHumCancel{ int(240.0f * scalingFactorWidth) };
	constexpr int yStartHumCancel{ int(210.0f * scalingFactorHeight) };
	constexpr int widthHumCancel{ int(80.0f * scalingFactorWidth) };
	constexpr int heightHumCancel{ int(24.0f * scalingFactorHeight) };

	constexpr int xStartHumApply{ int(120.0f * scalingFactorWidth) };
	constexpr int yStartHumApply{ int(210.0f * scalingFactorHeight) };
	constexpr int widthHumApply{ int(80.0f * scalingFactorWidth) };
	constexpr int heightHumApply{ int(24.0f * scalingFactorHeight) };

	constexpr int xStartHumLenSel{ int(10.0f * scalingFactorWidth) };
	constexpr int yStartHumLenSel{ int(350.0f * scalingFactorHeight) };
	constexpr int widthHumLenSel{ int(214.0f * scalingFactorWidth) };
	constexpr int heightHumLenSel{ int(25.0f * scalingFactorHeight) };

	constexpr int xStartHumnoteFilter{ int(10.0f * scalingFactorWidth) };
	constexpr int yStartHumnoteFilter{ int(152.0f * scalingFactorHeight) };
	constexpr int widthHumnoteFilter{ int(422.0f * scalingFactorWidth) };
	constexpr int heightHumnoteFilter{ int(25.0f * scalingFactorHeight) };

	constexpr int xStartHumTimeL{ int(10.0f * scalingFactorWidth) };
	constexpr int yStartHumTimeL{ int(10.0f * scalingFactorHeight) };
	constexpr int widthHumTimeL{ int(150.0f * scalingFactorWidth) };
	constexpr int heightHumTimeL{ int(25.0f * scalingFactorHeight) };

	constexpr int xStartHumPaint{ int(10.0f * scalingFactorWidth) };
	constexpr int yStartHumPaint{ int(35.0f * scalingFactorHeight) };
	constexpr int yStartHumPaint2{ int(340.0f * scalingFactorHeight) };
	constexpr int yStartHumPaint3{ int(484.0f * scalingFactorHeight) };
	constexpr int yStartHumPaint4{ int(640.0f * scalingFactorHeight) };
	constexpr int widthHumPaint{ int(430.0f * scalingFactorWidth) };
	constexpr int heightHumPaint{ int(1.0f * scalingFactorHeight) };

	// App Gen Rand
	constexpr int widthGenRandDia{ int(440.0f * scalingFactorWidth) };
	constexpr int heightGenRandDia{ int(595.0f * scalingFactorHeight) };

	constexpr int widthRandGenView{ widthDefPQView };
	constexpr int heightRandGenView{ int(595.0f * scalingFactorHeight) };

	constexpr int xStartRandGenMelL{ int(10.0f * scalingFactorWidth) };
	constexpr int yStartRandGenMelL{ int(230.0f * scalingFactorHeight) };
	constexpr int widthRandGenMelL{ int(150.0f * scalingFactorWidth) };
	constexpr int heightRandGenMelL{ int(25.0f * scalingFactorHeight) };

	constexpr int widthRandGenNote{ int(80.0f * scalingFactorWidth) };
	constexpr int heightRandGenNote{ int(40.0f * scalingFactorHeight) };

	constexpr int xStartRandGenendNote{ int(215.0f * scalingFactorWidth) };
	constexpr int yStartRandGenendNote{ int(272.0f * scalingFactorHeight) };

	constexpr int xStartRandGenstartNote{ int(10.0f * scalingFactorWidth) };
	constexpr int yStartRandGenstartNote{ int(272.0f * scalingFactorHeight) };

	constexpr int xStartRandGenBank{ int(10.0f * scalingFactorWidth) };
	constexpr int yStartRandGenBank{ int(272.0f * scalingFactorHeight) };

	constexpr int xStartRandGenRootNote{ int(10.0f * scalingFactorWidth) };
	constexpr int yStartRandGenRootNote{ int(332.0f * scalingFactorHeight) };

	constexpr int xStartRandGenStartPad{ int(10.0f * scalingFactorWidth) };
	constexpr int yStartRandGenStartPad{ int(332.0f * scalingFactorHeight) };

	constexpr int xStartRandGenScale{ int(215.0f * scalingFactorWidth) };
	constexpr int yStartRandGenScale{ int(332.0f * scalingFactorHeight) };

	constexpr int xStartRandGenEndPad{ int(215.0f * scalingFactorWidth) };
	constexpr int yStartRandGenEndPad{ int(332.0f * scalingFactorHeight) };

	constexpr int xStartRandGenLabelGen{ int(10.0f * scalingFactorWidth) };
	constexpr int yStartRandGenLabelGen{ int(10.0f * scalingFactorHeight) };
	constexpr int widthRandGenLabelGen{ int(150.0f * scalingFactorWidth) };
	constexpr int heightRandGenLabelGen{ int(25.0f * scalingFactorHeight) };

	constexpr int xStartRandGenEveType{ int(10.0f * scalingFactorWidth) };
	constexpr int yStartRandGenEveType{ int(50.0f * scalingFactorHeight) };
	constexpr int widthRandGenEveType{ int(430.0f * scalingFactorWidth) };
	constexpr int heightRandGenEveType{ int(40.0f * scalingFactorHeight) };

	constexpr int xStartRandGenReplace{ int(10.0f * scalingFactorWidth) };
	constexpr int yStartRandGenReplace{ int(110.0f * scalingFactorHeight) };
	constexpr int widthRandGenReplace{ int(430.0f * scalingFactorWidth) };
	constexpr int heightRandGenReplace{ int(40.0f * scalingFactorHeight) };

	constexpr int xStartRandGenNoteLen{ int(215.0f * scalingFactorWidth) };
	constexpr int yStartRandGenNoteLen{ int(170.0f * scalingFactorHeight) };

	constexpr int xStartRandGenPatSize{ int(10.0f * scalingFactorWidth) };
	constexpr int yStartRandGenPatSize{ int(170.0f * scalingFactorHeight) };

	constexpr int xStartRandGenDrumL{ int(10.0f * scalingFactorWidth) };
	constexpr int yStartRandGenDrumL{ int(230.0f * scalingFactorHeight) };
	constexpr int widthRandGenDrumL{ int(150.0f * scalingFactorWidth) };
	constexpr int heightRandGenDrumL{ int(25.0f * scalingFactorHeight) };

	constexpr int xStartRandGenLegato{ int(144.0f * scalingFactorWidth) };
	constexpr int yStartRandGenLegato{ int(487.0f * scalingFactorHeight) };
	constexpr int widthRandGenLegato{ int(88.0f * scalingFactorWidth) };
	constexpr int heightRandGenLegato{ int(25.0f * scalingFactorHeight) };

	constexpr int xStartRandGenNoteCheck{ int(250.0f * scalingFactorWidth) };
	constexpr int yStartRandGenNoteCheck{ int(487.0f * scalingFactorHeight) };
	constexpr int widthRandGenNoteCheck{ int(184.0f * scalingFactorWidth) };
	constexpr int heightRandGenNoteCheck{ int(25.0f * scalingFactorHeight) };

	constexpr int xStartRandGenPoly{ int(10.0f * scalingFactorWidth) };
	constexpr int yStartRandGenPoly{ int(472.0f * scalingFactorHeight) };

	constexpr int xStartRandGenDenSlider{ int(10.0f * scalingFactorWidth) };
	constexpr int yStartRandGenDenSlider{ int(420.0f * scalingFactorHeight) };
	constexpr int widthRandGenDenSlider{ int(425.0f * scalingFactorWidth) };
	constexpr int heightRandGenDenSlider{ int(25.0f * scalingFactorHeight) };

	constexpr int xStartRandGenDenL{ int(176.0f * scalingFactorWidth) };
	constexpr int yStartRandGenDenL{ int(395.0f * scalingFactorHeight) };
	constexpr int widthRandGenDenL{ int(96.0f * scalingFactorWidth) };
	constexpr int heightRandGenDenL{ int(18.0f * scalingFactorHeight) };

	constexpr int xStartRandGenRhyL{ int(160.0f * scalingFactorWidth) };
	constexpr int yStartRandGenRhyL{ int(462.0f * scalingFactorHeight) };
	constexpr int widthRandGenRhyL{ int(128.0f * scalingFactorWidth) };
	constexpr int heightRandGenRhyL{ int(18.0f * scalingFactorHeight) };

	constexpr int xStartRandGenRhySlider{ int(10.0f * scalingFactorWidth) };
	constexpr int yStartRandGenRhySlider{ int(487.0f * scalingFactorHeight) };
	constexpr int widthRandGenRhySlider{ int(425.0f * scalingFactorWidth) };
	constexpr int heightRandGenRhySlider{ int(25.0f * scalingFactorHeight) };

	constexpr int xStartRandGenApply{ int(109.0f * scalingFactorWidth) };
	constexpr int yStartRandGenApply{ int(554.0f * scalingFactorHeight) };
	constexpr int widthRandGenApply{ int(80.0f * scalingFactorWidth) };
	constexpr int heightRandGenApply{ int(24.0f * scalingFactorHeight) };

	constexpr int xStartRandGenCancel{ int(229.0f * scalingFactorWidth) };
	constexpr int yStartRandGenCancel{ int(554.0f * scalingFactorHeight) };
	constexpr int widthRandGenCancel{ int(80.0f * scalingFactorWidth) };
	constexpr int heightRandGenCancel{ int(24.0f * scalingFactorHeight) };

	constexpr int xStartRandGenPaint{ int(10.0f * scalingFactorWidth) };
	constexpr int yStartRandGenPaint{ int(35.0f * scalingFactorHeight) };
	constexpr int yStartRandGenPaint2{ int(255.0f * scalingFactorHeight) };
	constexpr int widthRandGenPaint{ int(430.0f * scalingFactorWidth) };
	constexpr int heightRandGenPaint{ int(1.0f * scalingFactorHeight) };
	// App Modify
	constexpr int widthModDia{ int(300.0f * scalingFactorWidth) };
	constexpr int heightModDia{ int(230.0f * scalingFactorHeight) };

	constexpr int xStartModNumBars{ int(30.0f * scalingFactorWidth) };
	constexpr int yStartModNumBars{ int(60.0f * scalingFactorHeight) };
	constexpr int widthModNumBars{ int(80.0f * scalingFactorWidth) };
	constexpr int heightModNumBars{ int(40.0f * scalingFactorHeight) };

	constexpr int xStartModBarPos{ int(190.0f * scalingFactorWidth) };
	constexpr int yStartModBarPos{ int(60.0f * scalingFactorHeight) };
	constexpr int widthModBarPos{ int(80.0f * scalingFactorWidth) };
	constexpr int heightModBarPos{ int(40.0f * scalingFactorHeight) };

	constexpr int xStartModTimSigNum{ int(112.0f * scalingFactorWidth) };
	constexpr int yStartModTimSigNum{ int(120.0f * scalingFactorHeight) };
	constexpr int widthModTimSigNum{ int(70.0f * scalingFactorWidth) };
	constexpr int heightModTimSigNum{ int(40.0f * scalingFactorHeight) };

	constexpr int xStartModTimSigDen{ int(200.0f * scalingFactorWidth) };
	constexpr int yStartModTimSigDen{ int(120.0f * scalingFactorHeight) };
	constexpr int widthModTimSigDen{ int(70.0f * scalingFactorWidth) };
	constexpr int heightModTimSigDen{ int(40.0f * scalingFactorHeight) };

	constexpr int xStartModTimSigL{ int(30.0f * scalingFactorWidth) };
	constexpr int yStartModTimSigL{ int(140.0f * scalingFactorHeight) };
	constexpr int widthModTimSigL{ int(80.0f * scalingFactorWidth) };
	constexpr int heightModTimSigL{ int(24.0f * scalingFactorHeight) };

	constexpr int xStartModTimSigSlash{ int(184.0f * scalingFactorWidth) };
	constexpr int yStartModTimSigSlash{ int(140.0f * scalingFactorHeight) };
	constexpr int widthModTimSigSlash{ int(15.0f * scalingFactorWidth) };
	constexpr int heightModTimSigSlash{ int(24.0f * scalingFactorHeight) };

	constexpr int xStartModApply{ int(56.0f * scalingFactorWidth) };
	constexpr int yStartModApply{ int(180.0f * scalingFactorHeight) };
	constexpr int widthModApply{ int(80.0f * scalingFactorWidth) };
	constexpr int heightModApply{ int(24.0f * scalingFactorHeight) };

	constexpr int xStartModCancel{ int(164.0f * scalingFactorWidth) };
	constexpr int yStartModCancel{ int(180.0f * scalingFactorHeight) };
	constexpr int widthModCancel{ int(80.0f * scalingFactorWidth) };
	constexpr int heightModCancel{ int(24.0f * scalingFactorHeight) };

	constexpr int xStartModArrow{ int(112.0f * scalingFactorWidth) };
	constexpr int yStartModArrow{ int(76.0f * scalingFactorHeight) };
	constexpr int widthModArrow{ int(65.0f * scalingFactorWidth) };
	constexpr int heightModArrow{ int(24.0f * scalingFactorHeight) };

	constexpr int xStartModLabe{ int(30.0f * scalingFactorWidth) };
	constexpr int yStartModLabe{ int(19.0f * scalingFactorHeight) };
	constexpr int widthModLabe{ int(120.0f * scalingFactorWidth) };
	constexpr int heightModLabe{ int(25.0f * scalingFactorHeight) };

	constexpr int xStartModSeqName{ int(150.0f * scalingFactorWidth) };
	constexpr int yStartModSeqName{ int(19.0f * scalingFactorHeight) };
	constexpr int widthModSeqName{ int(120.0f * scalingFactorWidth) };
	constexpr int heightModSeqName{ int(25.0f * scalingFactorHeight) };

	//   constexpr int xStartTransOptBarsL{ int(33.0f * scalingFactorHeight) };
	//   constexpr int yStartTransOptBarsL{ int(0.0f * scalingFactorHeight) };

	// Back Ground
	constexpr int xStartBackGnd{ int(0.0f * scalingFactorWidth) };
	constexpr int yStartBackGnd{ int(0.0f * scalingFactorHeight) };
	constexpr int widthBackGnd{ screenWidth };
	constexpr int heightBackGnd{ screenHeight };

	//Song Options
	constexpr int xStartSongOpt{ xStartAppTopbar };
	constexpr int yStartSongOpt{ yStartAppMainmode };
	constexpr int widthSongOpt{ widthAppTopbar };
	constexpr int heightSongOpt{ heightAppMainmode };

	constexpr int xStartSongOptName{ int(45.0f * scalingFactorWidth) };
	constexpr int yStartSongOptName{ int(15.0f * scalingFactorHeight) };
	constexpr int widthSongOptName{ int(120.0f * scalingFactorWidth) };
	constexpr int heightSongOptName{ int(30.0f * scalingFactorHeight) };

	constexpr int xStartSongOptBtn{ int(528.0f * scalingFactorWidth) };
	constexpr int yStartSongOptBtn{ int(0.0f * scalingFactorHeight) };
	constexpr int widthSongOptBtn{ int(40.0f * scalingFactorWidth) };
	constexpr int heightSongOptBtn{ int(58.0f * scalingFactorHeight) };

	constexpr int xStartSongOptSno{ int(0.0f * scalingFactorWidth) };
	constexpr int yStartSongOptSno{ int(0.0f * scalingFactorHeight) };
	constexpr int widthSongOptSno{ int(30.0f * scalingFactorWidth) };
	constexpr int heightSongOptSno{ int(50.0f * scalingFactorHeight) };

	constexpr int xStartSongOptBpm{ int(175.0f * scalingFactorWidth) };
	constexpr int yStartSongOptBpm{ int(10.0f * scalingFactorHeight) };
	constexpr int widthSongOptBpm{ int(55.0f * scalingFactorWidth) };
	constexpr int heightSongOptBpm{ int(35.0f * scalingFactorHeight) };

	constexpr int xStartSongOptTrans{ int(448.0f * scalingFactorWidth) };
	constexpr int yStartSongOptTrans{ int(10.0f * scalingFactorHeight) };
	constexpr int widthSongOptTrans{ int(70.0f * scalingFactorWidth) };
	constexpr int heightSongOptTrans{ int(48.0f * scalingFactorHeight) };

	constexpr int xStartSongOptBar{ int(245.0f * scalingFactorWidth) };
	constexpr int yStartSongOptBar{ int(10.0f * scalingFactorHeight) };
	constexpr int widthSongOptBar{ int(55.0f * scalingFactorWidth) };
	constexpr int heightSongOptBar{ int(35.0f * scalingFactorHeight) };

	constexpr int xStartSongOptSBar{ int(315.0f * scalingFactorWidth) };
	constexpr int yStartSongOptSBar{ yStartSongOptBar };
	constexpr int widthSongOptSBar{ widthSongOptBar };
	constexpr int heightSongOptSBar{ heightSongOptBar };

	constexpr int xStartSongOptEBar{ int(378.0f * scalingFactorWidth) };
	constexpr int yStartSongOptEBar{ yStartSongOptBar };
	constexpr int widthSongOptEBar{ widthSongOptBar };
	constexpr int heightSongOptEBar{ heightSongOptBar };

	constexpr int xStartSongOptSlash{ int(367.0f * scalingFactorWidth) };
	constexpr int yStartSongOptSlash{ int(7.0f * scalingFactorHeight) };
	constexpr int widthSongOptSlash{ int(14.0f * scalingFactorWidth) };
	constexpr int heightSongOptSlash{ int(24.0f * scalingFactorHeight) };

	constexpr int xStartSongOptABpm{ int(176.0f * scalingFactorWidth) };
	constexpr int yStartSongOptABpm{ int(49.0f * scalingFactorHeight) };
	constexpr int widthSongOptABpm{ int(55.0f * scalingFactorWidth) };
	constexpr int heightSongOptABpm{ int(15.0f * scalingFactorHeight) };

	constexpr int xStartSongOptSno2{ int(0.0f * scalingFactorWidth) };
	constexpr int yStartSongOptSno2{ int(50.0f * scalingFactorHeight) };
	constexpr int widthSongOptSno2{ int(30.0f * scalingFactorWidth) };
	constexpr int heightSongOptSno2{ int(276.0f * scalingFactorHeight) };

	constexpr int widthOptionButton{ int(115.0f * scalingFactorWidth) };
	constexpr int heightOptionButton{ int(65.0f * scalingFactorHeight) };

	constexpr int xStartSongOptEra{ int(40.0f * scalingFactorWidth) };
	constexpr int yStartSongOptEra{ int(75.0f * scalingFactorHeight) };

	constexpr int xStartSongOptClr{ int(160.0f * scalingFactorWidth) };
	constexpr int yStartSongOptClr{ yStartSongOptEra };

	constexpr int xStartSongOptTra{ int(280.0f * scalingFactorWidth) };
	constexpr int yStartSongOptTra{ yStartSongOptEra };

	constexpr int xStartSongOptB2S{ int(400.0f * scalingFactorWidth) };
	constexpr int yStartSongOptB2S{ yStartSongOptEra };

	constexpr int xStartSongOptDelB{ xStartSongOptEra };
	constexpr int yStartSongOptDelB{ int(145.0f * scalingFactorHeight) };

	constexpr int xStartSongOptInsB{ xStartSongOptClr };
	constexpr int yStartSongOptInsB{ yStartSongOptDelB };

	constexpr int xStartSongOptHalf{ xStartSongOptTra };
	constexpr int yStartSongOptHalf{ yStartSongOptDelB };

	constexpr int xStartSongOptDoub{ xStartSongOptB2S };
	constexpr int yStartSongOptDoub{ yStartSongOptDelB };

	constexpr int xStartSongOptSongB{ xStartSongOptEra };
	constexpr int yStartSongOptSongB{ int(215.0f * scalingFactorHeight) };

	constexpr int xStartSongOptBarB{ xStartSongOptClr };
	constexpr int yStartSongOptBarB{ yStartSongOptSongB };

	constexpr int xStartSongOptEveB{ xStartSongOptTra };
	constexpr int yStartSongOptEveB{ yStartSongOptSongB };

	constexpr int xStartSongOptSavB{ xStartSongOptB2S };
	constexpr int yStartSongOptSavB{ yStartSongOptSongB };

	constexpr int xStartSongOptLoop{ int(345.0f * scalingFactorWidth) };
	constexpr int yStartSongOptLoop{ int(49.0f * scalingFactorHeight) };
	constexpr int widthSongOptLoop{ int(55.0f * scalingFactorWidth) };
	constexpr int heightSongOptLoop{ int(15.0f * scalingFactorHeight) };

	constexpr int xStartSongOptBox{ int(185.25f * scalingFactorWidth) };
	constexpr int yStartSongOptBox{ int(7.5f * scalingFactorHeight) };
	constexpr int widthSongOptBox{ int(392.5f * scalingFactorWidth) };
	constexpr int heightSongOptBox{ int(45.0f * scalingFactorHeight) };

	constexpr int yStartSongOptSBox{ int(52.5f * scalingFactorHeight) };
	constexpr int widthSongOptSBox{ int(313.5f * scalingFactorWidth) };

	//Track Options
	constexpr int xStartTrackOptSno{ int(0.0f * scalingFactorWidth) };
	constexpr int yStartTrackOptSno{ int(0.0f * scalingFactorHeight) };
	constexpr int widthTrackOptSno{ int(30.0f * scalingFactorWidth) };
	constexpr int heightTrackOptSno{ int(50.0f * scalingFactorHeight) };

	constexpr int xStartTrackOptName{ int(45.0f * scalingFactorWidth) };
	constexpr int yStartTrackOptName{ int(15.0f * scalingFactorHeight) };
	constexpr int widthTrackOptName{ int(120.0f * scalingFactorWidth) };
	constexpr int heightTrackOptName{ int(30.0f * scalingFactorHeight) };

	constexpr int xStartTrackOptBox{ int(185.25f * scalingFactorWidth) };
	constexpr int yStartTrackOptBox{ int(7.5f * scalingFactorHeight) };
	constexpr int widthTrackOptBox{ int(392.5f * scalingFactorWidth) };
	constexpr int heightTrackOptBox{ int(45.0f * scalingFactorHeight) };

	constexpr int yStartTrackOptSBox{ int(52.5f * scalingFactorHeight) };
	constexpr int widthTrackOptSBox{ int(313.5f * scalingFactorWidth) };

	//options ctl
	constexpr int xStartOptctl{ int(80.0f * scalingFactorWidth) };
	constexpr int yStartOptctl{ int(240.0f * scalingFactorHeight) };
	constexpr int widthOptctl{ int(375.0f * scalingFactorWidth) };
	constexpr int heightOptctlt{ int(40.0f * scalingFactorHeight) };

	// Seq Options
	constexpr int xStartSeqOpt{ xStartAppTopbar };
	constexpr int yStartSeqOpt{ yStartAppMainmode };
	constexpr int widthSeqOpt{ widthAppTopbar };
	constexpr int heightSeqOpt{ heightAppMainmode };

	constexpr int xStartSeqOptName{ int(45.0f * scalingFactorWidth) };
	constexpr int yStartSeqOptName{ int(15.0f * scalingFactorHeight) };
	constexpr int widthSeqOptName{ int(120.0f * scalingFactorWidth) };
	constexpr int heightSeqOptName{ int(30.0f * scalingFactorHeight) };

	constexpr int xStartSeqOptBtn{ int(528.0f * scalingFactorWidth) };
	constexpr int yStartSeqOptBtn{ int(0.0f * scalingFactorHeight) };
	constexpr int widthSeqOptBtn{ int(40.0f * scalingFactorWidth) };
	constexpr int heightSeqOptBtn{ int(58.0f * scalingFactorHeight) };

	constexpr int xStartSeqOptSno{ int(0.0f * scalingFactorWidth) };
	constexpr int yStartSeqOptSno{ int(0.0f * scalingFactorHeight) };
	constexpr int widthSeqOptSno{ int(30.0f * scalingFactorWidth) };
	constexpr int heightSeqOptSno{ int(50.0f * scalingFactorHeight) };

	constexpr int xStartSeqOptBpm{ int(175.0f * scalingFactorWidth) };
	constexpr int yStartSeqOptBpm{ int(10.0f * scalingFactorHeight) };
	constexpr int widthSeqOptBpm{ int(55.0f * scalingFactorWidth) };
	constexpr int heightSeqOptBpm{ int(35.0f * scalingFactorHeight) };

	constexpr int xStartSeqOptTrans{ int(448.0f * scalingFactorWidth) };
	constexpr int yStartSeqOptTrans{ int(10.0f * scalingFactorHeight) };
	constexpr int widthSeqOptTrans{ int(70.0f * scalingFactorWidth) };
	constexpr int heightSeqOptTrans{ int(48.0f * scalingFactorHeight) };

	constexpr int xStartSeqOptBar{ int(245.0f * scalingFactorWidth) };
	constexpr int yStartSeqOptBar{ int(10.0f * scalingFactorHeight) };
	constexpr int widthSeqOptBar{ int(55.0f * scalingFactorWidth) };
	constexpr int heightSeqOptBar{ int(35.0f * scalingFactorHeight) };

	constexpr int xStartSeqOptSBar{ int(315.0f * scalingFactorWidth) };
	constexpr int yStartSeqOptSBar{ yStartSeqOptBar };
	constexpr int widthSeqOptSBar{ widthSeqOptBar };
	constexpr int heightSeqOptSBar{ heightSeqOptBar };

	constexpr int xStartSeqOptEBar{ int(378.0f * scalingFactorWidth) };
	constexpr int yStartSeqOptEBar{ yStartSeqOptBar };
	constexpr int widthSeqOptEBar{ widthSeqOptBar };
	constexpr int heightSeqOptEBar{ heightSeqOptBar };

	constexpr int xStartSeqOptSlash{ int(367.0f * scalingFactorWidth) };
	constexpr int yStartSeqOptSlash{ int(7.0f * scalingFactorHeight) };
	constexpr int widthSeqOptSlash{ int(14.0f * scalingFactorWidth) };
	constexpr int heightSeqOptSlash{ int(24.0f * scalingFactorHeight) };

	constexpr int xStartSeqOptABpm{ int(176.0f * scalingFactorWidth) };
	constexpr int yStartSeqOptABpm{ int(49.0f * scalingFactorHeight) };
	constexpr int widthSeqOptABpm{ int(55.0f * scalingFactorWidth) };
	constexpr int heightSeqOptABpm{ int(15.0f * scalingFactorHeight) };

	constexpr int xStartSeqOptSno2{ int(0.0f * scalingFactorWidth) };
	constexpr int yStartSeqOptSno2{ int(50.0f * scalingFactorHeight) };
	constexpr int widthSeqOptSno2{ int(30.0f * scalingFactorWidth) };
	constexpr int heightSeqOptSno2{ int(276.0f * scalingFactorHeight) };

	constexpr int xStartSeqOptEra{ int(40.0f * scalingFactorWidth) };
	constexpr int yStartSeqOptEra{ int(75.0f * scalingFactorHeight) };

	constexpr int xStartSeqOptClr{ int(160.0f * scalingFactorWidth) };
	constexpr int yStartSeqOptClr{ yStartSeqOptEra };

	constexpr int xStartSeqOptTra{ int(280.0f * scalingFactorWidth) };
	constexpr int yStartSeqOptTra{ yStartSeqOptEra };

	constexpr int xStartSeqOptB2S{ int(400.0f * scalingFactorWidth) };
	constexpr int yStartSeqOptB2S{ yStartSeqOptEra };

	constexpr int xStartSeqOptDelB{ xStartSeqOptEra };
	constexpr int yStartSeqOptDelB{ int(145.0f * scalingFactorHeight) };

	constexpr int xStartSeqOptInsB{ xStartSeqOptClr };
	constexpr int yStartSeqOptInsB{ yStartSeqOptDelB };

	constexpr int xStartSeqOptHalf{ xStartSeqOptTra };
	constexpr int yStartSeqOptHalf{ yStartSeqOptDelB };

	constexpr int xStartSeqOptDoub{ xStartSeqOptB2S };
	constexpr int yStartSeqOptDoub{ yStartSeqOptDelB };

	constexpr int xStartSeqOptSeqB{ xStartSeqOptEra };
	constexpr int yStartSeqOptSeqB{ int(215.0f * scalingFactorHeight) };

	constexpr int xStartSeqOptBarB{ xStartSeqOptClr };
	constexpr int yStartSeqOptBarB{ yStartSeqOptSeqB };

	constexpr int xStartSeqOptEveB{ xStartSeqOptTra };
	constexpr int yStartSeqOptEveB{ yStartSeqOptSeqB };

	constexpr int xStartSeqOptSavB{ xStartSeqOptB2S };
	constexpr int yStartSeqOptSavB{ yStartSeqOptSeqB };

	constexpr int xStartSeqOptLoop{ int(345.0f * scalingFactorWidth) };
	constexpr int yStartSeqOptLoop{ int(49.0f * scalingFactorHeight) };
	constexpr int widthSeqOptLoop{ int(55.0f * scalingFactorWidth) };
	constexpr int heightSeqOptLoop{ int(15.0f * scalingFactorHeight) };

	// Track Comp
	constexpr int xStartTrkCompName{ int(45.0f * scalingFactorWidth) };
	constexpr int yStartTrkCompName{ int(15.0f * scalingFactorHeight) };
	constexpr int widthTrkCompName{ int(120.0f * scalingFactorWidth) };
	constexpr int heightTrkCompName{ int(30.0f * scalingFactorHeight) };

	constexpr int xStartTrkCompProgName{ int(45.0f * scalingFactorWidth) };
	constexpr int yStartTrkCompProgName{ int(45.0f * scalingFactorHeight) };
	constexpr int widthTrkCompProgName{ int(120.0f * scalingFactorWidth) };
	constexpr int heightTrkCompProgName{ int(18.0f * scalingFactorHeight) };

	constexpr int xStartTrkMode{ int(183.0f * scalingFactorWidth) };
	constexpr int yStartTrkMode{ int(15.0f * scalingFactorHeight) };
	constexpr int widthTrkMode{ int(35.0f * scalingFactorWidth) };
	constexpr int heightTrkMode{ int(25.0f * scalingFactorHeight) };

	constexpr int xStartTrkMute{ int(480.0f * scalingFactorWidth) };
	constexpr int yStartTrkMute{ int(11.0f * scalingFactorHeight) };
	constexpr int widthTrkMute{ int(35.0f * scalingFactorWidth) };
	constexpr int heightTrkMute{ int(18.0f * scalingFactorHeight) };

	constexpr int xStartTrkSolo{ int(480.0f * scalingFactorWidth) };
	constexpr int yStartTrkSolo{ int(32.0f * scalingFactorHeight) };
	constexpr int widthTrkSolo{ int(35.0f * scalingFactorWidth) };
	constexpr int heightTrkSolo{ int(18.0f * scalingFactorHeight) };

	constexpr int xStartTrkOptButton{ int(520.0f * scalingFactorWidth) };
	constexpr int yStartTrkOptButton{ int(0.0f * scalingFactorHeight) };
	constexpr int widthTrkOptButton{ int(36.0f * scalingFactorWidth) };
	constexpr int heightTrkOptButton{ int(60.0f * scalingFactorHeight) };

	constexpr int xStartTrkSNoL{ int(0.0f * scalingFactorWidth) };
	constexpr int yStartTrkSNoL{ int(0.0f * scalingFactorHeight) };
	constexpr int widthTrkSNoL{ int(30.0f * scalingFactorWidth) };
	constexpr int heightTrkSNoL{ int(30.0f * scalingFactorHeight) };

	constexpr int xStartTrkLenComp{ int(238.0f * scalingFactorWidth) };
	constexpr int yStartTrkLenComp{ int(11.0f * scalingFactorHeight) };
	constexpr int widthTrkLenComp{ int(70.0f * scalingFactorWidth) };
	constexpr int heightTrkLenComp{ int(38.0f * scalingFactorHeight) };

	constexpr int xStartTrkTranComp{ int(321.0f * scalingFactorWidth) };
	constexpr int yStartTrkTranComp{ int(11.0f * scalingFactorHeight) };
	constexpr int widthTrkTranComp{ int(70.0f * scalingFactorWidth) };
	constexpr int heightTrkTranComp{ int(38.0f * scalingFactorHeight) };

	constexpr int xStartTrkVelComp{ int(404.0f * scalingFactorWidth) };
	constexpr int yStartTrkVelComp{ int(11.0f * scalingFactorHeight) };
	constexpr int widthTrkVelComp{ int(70.0f * scalingFactorWidth) };
	constexpr int heightTrkVelComp{ int(38.0f * scalingFactorHeight) };

	constexpr int xStartTrkEmtL{ int(0.0f * scalingFactorWidth) };
	constexpr int yStartTrkEmtL{ int(30.0f * scalingFactorHeight) };
	constexpr int widthTrkEmtL{ int(30.0f * scalingFactorWidth) };
	constexpr int heightTrkEmtL{ int(35.0f * scalingFactorHeight) };

	constexpr int widthTrk{ int(560.0f * scalingFactorWidth) };
	constexpr int heightTrk{ int(65.0f * scalingFactorHeight) };

	// Track Options
	constexpr int xStartTrkOpt{ xStartSeqOpt };
	constexpr int yStartTrkOpt{ yStartSeqOpt };
	constexpr int widthTrkOpt{ widthSeqOpt };
	constexpr int heightTrkOpt{ heightSeqOpt };

	constexpr int xStartTrkOptPaint1{ int(217.0f * scalingFactorWidth) };
	constexpr int xStartTrkOptPaint2{ int(384.0f * scalingFactorWidth) };
	constexpr int xStartTrkOptPaint3{ int(301.0f * scalingFactorWidth) };
	constexpr int yStartTrkOptPaint{ int(4.0f * scalingFactorHeight) };
	constexpr int widthTrkOptPaint{ int(1.0f * scalingFactorWidth) };
	constexpr int heightTrkOptPaint{ int(54.0f * scalingFactorHeight) };

	constexpr int xStartTrkOptPaint4{ int(528.0f * scalingFactorWidth) };
	constexpr int yStartTrkOptPaint4{ int(0.0f * scalingFactorHeight) };
	constexpr int widthTrkOptPaint4{ int(40.0f * scalingFactorWidth) };
	constexpr int heightTrkOptPaint4{ int(58.0f * scalingFactorHeight) };

	constexpr int xStartTrkOptSavB{ int(528.0f * scalingFactorWidth) };
	constexpr int yStartTrkOptSavB{ int(0.0f * scalingFactorHeight) };
	constexpr int widthTrkOptSavB{ int(40.0f * scalingFactorWidth) };
	constexpr int heightTrkOptSavB{ int(58.0f * scalingFactorHeight) };

	constexpr int xStartTrkOptSno{ int(0.0f * scalingFactorWidth) };
	constexpr int yStartTrkOptSno{ int(0.0f * scalingFactorHeight) };
	constexpr int widthTrkOptSno{ int(30.0f * scalingFactorWidth) };
	constexpr int heightTrkOptSno{ int(50.0f * scalingFactorHeight) };

	constexpr int xStartTrkOptEl{ int(0.0f * scalingFactorWidth) };
	constexpr int yStartTrkOptEl{ int(50.0f * scalingFactorHeight) };
	constexpr int widthTrkOptEl{ int(30.0f * scalingFactorWidth) };
	constexpr int heightTrkOptEl{ int(237.0f * scalingFactorHeight) };

	constexpr int xStartTrkOptClr{ xStartSeqOptEra };
	constexpr int yStartTrkOptClr{ yStartSeqOptEra };

	constexpr int xStartTrkOptEpd{ xStartSeqOptClr };
	constexpr int yStartTrkOptEpd{ yStartSeqOptEra };

	constexpr int xStartTrkOptDoub{ xStartSeqOptTra };
	constexpr int yStartTrkOptDoub{ yStartSeqOptEra };

	constexpr int xStartTrkOptHalf{ xStartSeqOptB2S };
	constexpr int yStartTrkOptHalf{ yStartSeqOptEra };

	constexpr int xStartTrkOptSpEv{ xStartSeqOptEra };
	constexpr int yStartTrkOptSpEv{ yStartSeqOptDelB };

	constexpr int xStartTrkOptPtQt{ xStartSeqOptClr };
	constexpr int yStartTrkOptPtQt{ yStartSeqOptDelB };

	constexpr int xStartTrkOptHuma{ xStartSeqOptTra };
	constexpr int yStartTrkOptHuma{ yStartSeqOptDelB };

	constexpr int xStartTrkOptRanE{ xStartSeqOptB2S };
	constexpr int yStartTrkOptRanE{ yStartSeqOptDelB };

	constexpr int xStartTrkOptTrkC{ xStartSeqOptEra };
	constexpr int yStartTrkOptTrkC{ yStartSeqOptSeqB };

	constexpr int xStartTrkOptB2S{ xStartSeqOptClr };
	constexpr int yStartTrkOptB2S{ yStartSeqOptSeqB };

	constexpr int xStartTrkOptB2T{ xStartSeqOptTra };
	constexpr int yStartTrkOptB2T{ yStartSeqOptSeqB };

	constexpr int xStartTrkOptExPa{ xStartSeqOptB2S };
	constexpr int yStartTrkOptExPa{ yStartSeqOptSeqB };

	constexpr int xStartTrkOptName{ int(41.0f * scalingFactorWidth) };
	constexpr int yStartTrkOptName{ int(14.0f * scalingFactorHeight) };
	constexpr int widthTrkOptName{ int(110.0f * scalingFactorWidth) };
	constexpr int heightTrkOptName{ int(30.0f * scalingFactorHeight) };

	constexpr int xStartTrkOptMode{ int(170.0f * scalingFactorWidth) };
	constexpr int yStartTrkOptMode{ int(14.0f * scalingFactorHeight) };
	constexpr int widthTrkOptMode{ int(35.0f * scalingFactorWidth) };
	constexpr int heightTrkOptMode{ int(35.0f * scalingFactorHeight) };

	constexpr int xStartTrkOptMute{ int(474.0f * scalingFactorWidth) };
	constexpr int yStartTrkOptMute{ int(14.0f * scalingFactorHeight) };
	constexpr int widthTrkOptMute{ int(40.0f * scalingFactorWidth) };
	constexpr int heightTrkOptMute{ int(18.0f * scalingFactorHeight) };

	constexpr int xStartTrkOptSolo{ xStartTrkOptMute };
	constexpr int yStartTrkOptSolo{ int(35.0f * scalingFactorHeight) };
	constexpr int widthTrkOptSolo{ widthTrkOptMute };
	constexpr int heightTrkOptSolo{ heightTrkOptMute };

	constexpr int xStartTrkOptLen{ int(225.0f * scalingFactorWidth) };
	constexpr int yStartTrkOptLen{ int(14.0f * scalingFactorHeight) };
	constexpr int widthTrkOptLen{ int(70.0f * scalingFactorWidth) };
	constexpr int heightTrkOptLen{ int(38.0f * scalingFactorHeight) };

	constexpr int xStartTrkOptTransComp{ int(308.0f * scalingFactorWidth) };
	constexpr int yStartTrkOptTransComp{ yStartTrkOptLen };
	constexpr int widthTrkOptTransComp{ widthTrkOptLen };
	constexpr int heightTrkOptTransComp{ heightTrkOptLen };

	constexpr int xStartTrkOptVelComp{ int(391.0f * scalingFactorWidth) };
	constexpr int yStartTrkOptVelComp{ yStartTrkOptLen };
	constexpr int widthTrkOptVelComp{ widthTrkOptLen };
	constexpr int heightTrkOptVelComp{ heightTrkOptLen };

	// ListBox
	constexpr int widthLb{ int(140.0f * scalingFactorWidth) };
	constexpr int heightLb{ int(38.0f * scalingFactorHeight) };

	constexpr int xLbLabelField{ int(0.0f * scalingFactorWidth) };
	constexpr int yLbLabelField{ int(0.0f * scalingFactorHeight) };
	constexpr int widthLbLabelField{ int(140.0f * scalingFactorWidth) };
	constexpr int heightLbLabelField{ int(8.0f * scalingFactorHeight) };

	constexpr int xLbLabelValue{ int(0.0f * scalingFactorWidth) };
	constexpr int yLbLabelValue{ heightLbLabelField };
	constexpr int widthLbLabelValue{ int(140.0f * scalingFactorWidth) };
	constexpr int heightLbLabelValue{ int(22.0f * scalingFactorHeight) };

	constexpr int widthLbDialog{ int(568.0f * scalingFactorWidth) };
	constexpr int heightLbDialog{ int(334.0f * scalingFactorHeight) };

	// ListBox Options
	constexpr int widthLbOptions{ int(568.0f * scalingFactorWidth) };
	constexpr int heightLbOptions{ heightLbDialog };

	constexpr int xLbOptionsListBox{ int(0.0f * scalingFactorWidth) };
	constexpr int yLbOptionsListBox{ int(1.0f * scalingFactorHeight) };
	constexpr int widthLbOptionsListBox{ int(190.0f * scalingFactorWidth) };
	constexpr int heightLbOptionsListBox{ heightLbDialog };

	constexpr int xLbOptionsApply{ int(288.0f * scalingFactorWidth) };
	constexpr int yLbOptionsApply{ int(230.0f * scalingFactorHeight) };
	constexpr int widthLbOptionsApply{ int(80.0f * scalingFactorWidth) };
	constexpr int heightLbOptionsApply{ int(24.0f * scalingFactorHeight) };

	constexpr int xLbOptionsCancel{ int(400.0f * scalingFactorWidth) };
	constexpr int yLbOptionsCancel{ yLbOptionsApply };
	constexpr int widthLbOptionsCancel{ widthLbOptionsApply };
	constexpr int heightLbOptionsCancel{ heightLbOptionsApply };

	constexpr int xLbOptionsLbValue{ int(390.0f * scalingFactorWidth) };
	constexpr int yLbOptionsLbValue{ int(80.0f * scalingFactorHeight) };
	constexpr int widthLbOptionsLbValue{ int(150.0f * scalingFactorWidth) };
	constexpr int heightLbOptionsLbValue{ int(35.0f * scalingFactorHeight) };

	constexpr int xLbOptionsLbField{ int(220.0f * scalingFactorWidth) };
	constexpr int yLbOptionsLbField{ int(80.0f * scalingFactorHeight) };
	constexpr int widthLbOptionsLbField{ int(140.0f * scalingFactorWidth) };
	constexpr int heightLbOptionsLbField{ int(35.0f * scalingFactorHeight) };

	// Numeric Component
	constexpr int widthNc{ int(70.0f * scalingFactorWidth) };
	constexpr int heightNc{ int(38.0f * scalingFactorHeight) };

	constexpr int xNcNumField{ int(0.0f * scalingFactorWidth) };
	constexpr int yNcNumField{ int(0.0f * scalingFactorHeight) };
	constexpr int widthNcNumField{ int(70.0f * scalingFactorWidth) };
	constexpr int heightNcNumField{ int(8.0f * scalingFactorHeight) };

	constexpr int xNcNumValue{ int(0.0f * scalingFactorWidth) };
	constexpr int yNcNumValue{ int(5.0f * scalingFactorHeight) };
	constexpr int widthNcNumValue{ int(70.0f * scalingFactorWidth) };
	constexpr int heightNcNumValue{ int(22.0f * scalingFactorHeight) };

	constexpr int widthNcDialog{ int(300.0f * scalingFactorWidth) };
	constexpr int heightNcDialog{ int(230.0f * scalingFactorHeight) };

	// Numeric Comp Options
	constexpr int widthNcOptions{ int(300.0f * scalingFactorWidth) };
	constexpr int heightNcOptions{ int(200.0f * scalingFactorHeight) };

	constexpr int widthNcNumButton{ int(40.0f * scalingFactorWidth) };
	constexpr int heightNcNumButton{ int(30.0f * scalingFactorHeight) };

	constexpr int xNcNum1{ int(149.0f * scalingFactorWidth) };
	constexpr int yNcNum1{ int(98.0f * scalingFactorHeight) };

	constexpr int xNcNum2{ int(189.0f * scalingFactorWidth) };
	constexpr int yNcNum2{ yNcNum1 };

	constexpr int xNcNum3{ int(229.0f * scalingFactorWidth) };
	constexpr int yNcNum3{ yNcNum1 };

	constexpr int xNcNum4{ xNcNum1 };
	constexpr int yNcNum4{ int(68.0f * scalingFactorHeight) };

	constexpr int xNcNum5{ xNcNum2 };
	constexpr int yNcNum5{ yNcNum4 };

	constexpr int xNcNum6{ xNcNum3 };
	constexpr int yNcNum6{ yNcNum4 };

	constexpr int xNcNum7{ xNcNum1 };
	constexpr int yNcNum7{ int(38.0f * scalingFactorHeight) };

	constexpr int xNcNum8{ xNcNum2 };
	constexpr int yNcNum8{ yNcNum7 };

	constexpr int xNcNum9{ xNcNum3 };
	constexpr int yNcNum9{ yNcNum7 };

	constexpr int xNcNumSign{ xNcNum1 };
	constexpr int yNcNumSign{ int(128.0f * scalingFactorHeight) };

	constexpr int xNcNum0{ xNcNum2 };
	constexpr int yNcNum0{ yNcNumSign };

	constexpr int xNcNumDel{ xNcNum3 };
	constexpr int yNcNumDel{ yNcNumSign };

	constexpr int xNcOptionsText{ int(16.0f * scalingFactorWidth) };
	constexpr int yNcOptionsText{ int(64.0f * scalingFactorHeight) };
	constexpr int widthNcOptionsText{ int(128.0f * scalingFactorWidth) };
	constexpr int heightNcOptionsText{ int(56.0f * scalingFactorHeight) };

	constexpr int xNcOptionsApply{ int(40.0f * scalingFactorWidth) };
	constexpr int yNcOptionsApply{ int(176.0f * scalingFactorHeight) };
	constexpr int widthNcOptionsApply{ int(88.0f * scalingFactorWidth) };
	constexpr int heightNcOptionsApply{ int(24.0f * scalingFactorHeight) };

	constexpr int xNcOptionsCancel{ int(160.0f * scalingFactorWidth) };
	constexpr int yNcOptionsCancel{ yNcOptionsApply };
	constexpr int widthNcOptionsCancel{ widthNcOptionsApply };
	constexpr int heightNcOptionsCancel{ heightNcOptionsApply };

	// App Prog Mode
	constexpr int widthProgMode{ int(300.0f * scalingFactorWidth) };
	constexpr int heightProgMode{ int(200.0f * scalingFactorHeight) };

	constexpr int xStartProgModeL{ int(16.0f * scalingFactorWidth) };
	constexpr int yStartProgModeL{ int(62.0f * scalingFactorHeight) };
	constexpr int widthProgModeL{ int(72.0f * scalingFactorWidth) };
	constexpr int heightProgModeL{ int(36.0f * scalingFactorHeight) };

	constexpr int xStartProgModeDrum{ int(100.0f * scalingFactorWidth) };
	constexpr int yStartProgModeDrum{ int(25.0f * scalingFactorHeight) };
	constexpr int widthProgModeDrum{ int(35.0f * scalingFactorWidth) };
	constexpr int heightProgModeDrum{ int(35.0f * scalingFactorHeight) };

	constexpr int xStartProgModeKg{ int(165.0f * scalingFactorWidth) };
	constexpr int yStartProgModeKg{ int(35.0f * scalingFactorHeight) };
	constexpr int widthProgModeKg{ int(35.0f * scalingFactorWidth) };
	constexpr int heightProgModeKg{ int(25.0f * scalingFactorHeight) };

	constexpr int xStartProgModeImgBtn{ int(230.0f * scalingFactorWidth) };
	constexpr int yStartProgModeImgBtn{ int(35.0f * scalingFactorHeight) };
	constexpr int widthProgModeImgBtn{ int(35.0f * scalingFactorWidth) };
	constexpr int heightProgModeImgBtn{ int(25.0f * scalingFactorHeight) };

	constexpr int xStartProgModeImgP{ int(100.0f * scalingFactorWidth) };
	constexpr int yStartProgModeImgP{ int(95.0f * scalingFactorHeight) };
	constexpr int widthProgModeImgP{ int(35.0f * scalingFactorWidth) };
	constexpr int heightProgModeImgP{ int(35.0f * scalingFactorHeight) };

	constexpr int xStartProgModeImgMidi{ int(165.0f * scalingFactorWidth) };
	constexpr int yStartProgModeImgMidi{ int(95.0f * scalingFactorHeight) };
	constexpr int widthProgModeImgMidi{ int(35.0f * scalingFactorWidth) };
	constexpr int heightProgModeImgMidi{ int(35.0f * scalingFactorHeight) };

	constexpr int xStartProgModeImgDrum6{ int(230.0f * scalingFactorWidth) };
	constexpr int yStartProgModeImgDrum6{ int(95.0f * scalingFactorHeight) };
	constexpr int widthProgModeImgDrum6{ int(35.0f * scalingFactorWidth) };
	constexpr int heightProgModeImgDrum6{ int(35.0f * scalingFactorHeight) };

	constexpr int xStartProgModeApply{ int(43.0f * scalingFactorWidth) };
	constexpr int yStartProgModeApply{ int(158.0f * scalingFactorHeight) };
	constexpr int widthProgModeApply{ int(88.0f * scalingFactorWidth) };
	constexpr int heightProgModeApply{ int(24.0f * scalingFactorHeight) };

	constexpr int xStartProgModeCancel{ int(163.0f * scalingFactorWidth) };
	constexpr int yStartProgModeCancel{ int(158.0f * scalingFactorHeight) };
	constexpr int widthProgModeCancel{ int(88.0f * scalingFactorWidth) };
	constexpr int heightProgModeCancel{ int(24.0f * scalingFactorHeight) };

	//Pattern bar view constatnt

	constexpr int xStartStepControl{ int(0.0f * scalingFactorWidth) };
	constexpr int yStartStepControl{ int(262.47f * scalingFactorHeight) };
	constexpr int widthStepControl{ int(535.71f * scalingFactorWidth) };
	constexpr int heightStepCtrl{ int(23.95f * scalingFactorHeight) };

	constexpr int xStartStepPreset{ int(535.71f * scalingFactorWidth) };
	constexpr int yStartStepPreset{ int(25.0f * scalingFactorHeight) };
	constexpr int heightStepPreset{ int(239.87f * scalingFactorHeight) };

	constexpr int xStartStepRect{ int(0.0f * scalingFactorWidth) };
	constexpr int yStartStepRect{ int(248.12f * scalingFactorHeight) };
	constexpr int widthStepRect{ int(534.39f * scalingFactorWidth) };
	constexpr int heightStepRect{ int(26.5f * scalingFactorHeight) };

	constexpr int xStartLevelRect{ int(0.0f * scalingFactorWidth) };
	constexpr int yStartLevelRect{ int(27.74f * scalingFactorHeight) };
	constexpr int widthLevelRect{ int(535.71f * scalingFactorWidth) };
	constexpr int heightLevelRect{ int(221.2f * scalingFactorHeight) };

	//mt_ignite_bar_view_control constants

	constexpr int xStartControlFlex1{ int(0.0f * scalingFactorWidth) };
	constexpr int yStartControlFlex1{ int(0.0f * scalingFactorHeight) };
	constexpr int widthControlFlex1{ int(392.1f * scalingFactorWidth) };
	constexpr int heightControlFlex1{ int(26.5f * scalingFactorHeight) };

	constexpr int xStartControlFlex2{ int(367.0f * scalingFactorWidth) };
	constexpr int yStartControlFlex2{ int(3.0f * scalingFactorHeight) };
	constexpr int widthControlFlex2{ int(168.5f * scalingFactorWidth) };
	constexpr int heightControlFlex2{ int(20.96f * scalingFactorHeight) };

	constexpr int xStartbarOptionFlex{ int(178.7f * scalingFactorWidth) };
	constexpr int yStartbarOptionFlex{ int(0.0f * scalingFactorHeight) };
	constexpr int widthbarOptionFlex{ int(501.11f * scalingFactorWidth) };
	constexpr int heightbarOptionFlex{ int(26.96f * scalingFactorHeight) };

	constexpr int xStartbarloopFlex{ int(434.30f * scalingFactorWidth) };
	constexpr int yStartbarloopFlex{ int(1.79f * scalingFactorHeight) };
	constexpr int widthbarloopFlex{ int(105.79f * scalingFactorWidth) };
	constexpr int heightbarloopFlex{ int(23.87f * scalingFactorHeight) };

	constexpr int xStartbarLoopCntFlex{ int(445.43f * scalingFactorWidth) };
	constexpr int yStartbarLoopCntFlex{ int(1.79f * scalingFactorHeight) };
	constexpr int widthbarLoopCntFlex{ int(94.65f * scalingFactorWidth) };
	constexpr int heightbarLoopCntFlex{ int(23.87f * scalingFactorHeight) };

	//mt_ignite_grid_parameter_view constants

	constexpr int xStartParam{ int(0.0f * scalingFactorWidth) };
	constexpr int xStartParameterType{ int(45.0f * scalingFactorWidth) };
	constexpr int widthParam{ int(45.0f * scalingFactorWidth) };
	constexpr int widthParameterType{ int(64.28f * scalingFactorWidth) };
	constexpr int yStartParameterType{ int(0.0f * scalingFactorHeight) };

	constexpr int xStartecBtn{ int(21.42f * scalingFactorWidth) };
	constexpr int yStartecBtn{ int(0.0f * scalingFactorHeight) };
	constexpr int widthecBtn{ int(21.42f * scalingFactorWidth) };

	constexpr int xStartGridControlFlex{ int(321.0f * scalingFactorWidth) };
	constexpr int yStartGridControlFlex{ int(2.0f * scalingFactorHeight) };
	constexpr int widthGridControlFlex{ int(96.5f * scalingFactorWidth) };
	constexpr int heightGridControlFlex{ int(20.96f * scalingFactorHeight) };

	//mt_ignite_time_sig_setting

	constexpr int xStartTimeSigNumerator{ int(34.28f * scalingFactorWidth) };
	constexpr int yStartTimeSigNumerator{ int(7.51f * scalingFactorHeight) };
	constexpr int widthTimeSigNumerator{ int(17.14f * scalingFactorWidth) };
	constexpr int heightTimeSigNumerator{ int(18.04f * scalingFactorHeight) };

	constexpr int xStartTimeSigDenominator{ int(80.0f * scalingFactorWidth) };
	constexpr int yStartTimeSigDenominator{ int(7.51f * scalingFactorHeight) };
	constexpr int widthTimeSigDenominator{ int(17.14f * scalingFactorWidth) };
	constexpr int heightTimeSigDenominator{ int(18.04f * scalingFactorHeight) };

	constexpr int xStartLabelSlash{ int(62.85f * scalingFactorWidth) };
	constexpr int yStartLabelSlash{ int(7.51f * scalingFactorHeight) };
	constexpr int widthLabelSlash{ int(10.71f * scalingFactorWidth) };
	constexpr int heightLabelSlash{ int(18.04f * scalingFactorHeight) };

	constexpr int xStartCancelButton{ int(3.57f * scalingFactorWidth) };
	constexpr int yStartCancelButton{ int(45.11f * scalingFactorHeight) };
	constexpr int widthCancelButton{ int(50.0f * scalingFactorWidth) };
	constexpr int heightCancelButton{ int(18.04f * scalingFactorHeight) };

	constexpr int xStartDeleteButton{ int(57.14f * scalingFactorWidth) };
	constexpr int yStartDeleteButton{ int(45.11f * scalingFactorHeight) };
	constexpr int widthDeleteButton{ int(50.0f * scalingFactorWidth) };
	constexpr int heightDeleteButton{ int(18.04f * scalingFactorHeight) };

	constexpr int xStartAddButton{ int(110.71f * scalingFactorWidth) };
	constexpr int yStartAddButton{ int(45.11f * scalingFactorHeight) };
	constexpr int widthAddButton{ int(50.0f * scalingFactorWidth) };
	constexpr int heightAddButton{ int(18.04f * scalingFactorHeight) };

	//mt_ignite_pattern.cpp

	constexpr int xStartAddNewBtn{ int(5.9f * scalingFactorWidth) };
	constexpr int yStartAddNewBtn{ int(6.2f * scalingFactorHeight) };
	constexpr int widthAddNewBtn{ int(559.2f * scalingFactorWidth) };
	constexpr int heightAddNewBtn{ int(26.6f * scalingFactorHeight) };

	constexpr int xStartFwdBarButton{ int(492.85f * scalingFactorWidth) };
	constexpr int yStartFwdBarButton{ int(3.75f * scalingFactorHeight) };
	constexpr int widthFwdBarButton{ int(71.42f * scalingFactorWidth) };
	constexpr int heightFwdBarButton{ int(20.30f * scalingFactorHeight) };

	constexpr int xStartBackBarButton{ int(414.28f * scalingFactorWidth) };
	constexpr int yStartBackBarButton{ int(3.75f * scalingFactorHeight) };
	constexpr int widthBackBarButton{ int(71.42f * scalingFactorWidth) };
	constexpr int heightBackBarButton{ int(20.30f * scalingFactorHeight) };

	constexpr int xStartEmptyComp{ int(5.9f * scalingFactorWidth) };
	constexpr int yStartEmptyComp{ int(38.2f * scalingFactorHeight) };
	constexpr int widthEmptyComp{ int(560.2f * scalingFactorWidth) };
	constexpr int heightEmptyComp{ int(243.8f * scalingFactorHeight) };

	constexpr int xStartPatternView{ int(150.0f * scalingFactorWidth) };
	constexpr int yStartPatternView{ int(0.0f * scalingFactorHeight) };
	constexpr int widthPatternView{ int(50.0f * scalingFactorWidth) };
	constexpr int heightPatternView{ int(15.03f * scalingFactorHeight) };

	constexpr int xStartPatternLayout1{ int(145.1f * scalingFactorWidth) };
	constexpr int xStartPatternLayout2{ int(5.6f * scalingFactorWidth) };
	constexpr int yStartPatternLayout1{ int(5.98f * scalingFactorHeight) };
	constexpr int yStartPatternLayout2{ int(39.40f * scalingFactorHeight) };
	constexpr int widthPatternLayout{ int(104.0f * scalingFactorWidth) };
	constexpr int heightPatternLayout{ int(27.76f * scalingFactorHeight) };

	constexpr int xStartPatternListLayout{ int(5.9f * scalingFactorWidth) };
	constexpr int yStartPatternListLayout{ int(70.44f * scalingFactorHeight) };
	constexpr int widthPatternListLayout{ int(564.58f * scalingFactorWidth) };
	constexpr int heightPatternListLayout{ int(194.62f * scalingFactorHeight) };

	//mt_ignite_scene.cpp
	constexpr int xStartAddNew{ int(14.28f * scalingFactorWidth) };
	constexpr int yStartAddNew{ int(3.75f * scalingFactorHeight) };
	constexpr int widthAddNew{ int(535.71f * scalingFactorWidth) };
	constexpr int heightAddNew{ int(37.59f * scalingFactorHeight) };

	constexpr int xStartLoopCmp{ int(142.85f * scalingFactorWidth) };
	constexpr int yStartLoopCmp{ int(75.18f * scalingFactorHeight) };
	constexpr int widthLoopCmp{ int(321.42f * scalingFactorWidth) };
	constexpr int heightLoopCmp{ int(150.37f * scalingFactorHeight) };

	//mt_ignite_loop.cpp
	constexpr int xStartloop{ int(21.42f * scalingFactorWidth) };
	constexpr int widthloop{ int(285.71f * scalingFactorWidth) };

	constexpr int yStartLoopBox{ int(15.03f * scalingFactorHeight) };
	constexpr int heightLoopBox{ int(75.18f * scalingFactorHeight) };
	constexpr int heightSwapBox{ int(38.18f * scalingFactorHeight) };
	constexpr int heightCopyBox{ int(58.18f * scalingFactorHeight) };

	constexpr int xStartbarInsert{ int(16.75f * scalingFactorWidth) };
	constexpr int yStartbarInsert{ int(15.03f * scalingFactorHeight) };
	constexpr int widthbarInsert{ int(303.91f * scalingFactorWidth) };
	constexpr int heightbarInsert{ int(29.94f * scalingFactorHeight) };
	constexpr int yStartBarInsertCtlBox{ int(106.58f * scalingFactorHeight) };

	constexpr int yStartCtlBox{ int(112.78f * scalingFactorHeight) };
	constexpr int heightCtlBox{ int(30.07f * scalingFactorHeight) };

	//mt_ignite_settings
	constexpr int xStartbrightnessLabel{ int(506.68f * scalingFactorWidth) };
	constexpr int yStartbrightnessLabel{ int(268.51f * scalingFactorHeight) };
	constexpr int widthbrightnessLabel{ int(55.68f * scalingFactorWidth) };
	constexpr int heightbrightnessLabel{ int(11.93f * scalingFactorHeight) };

	constexpr int xStartbrightnesSlider{ int(523.39f * scalingFactorWidth) };
	constexpr int yStartbrightnesSlider{ int(50.72f * scalingFactorHeight) };
	constexpr int widthbrightnesSlider{ int(22.27f * scalingFactorWidth) };
	constexpr int heightbrightnesSlider{ int(214.81f * scalingFactorHeight) };

	constexpr int xStartSettingBox{ int(27.84f * scalingFactorWidth) };
	constexpr int yStartSettingBox{ int(41.77f * scalingFactorHeight) };
	constexpr int widthSettingBox{ int(476.06f * scalingFactorWidth) };
	constexpr int heightSettingBox{ int(238.68f * scalingFactorHeight) };

	//mt_ignite_song_detail.cpp

	constexpr int xStartSongRow{ int(0.0f * scalingFactorWidth) };
	constexpr int yStartSongRow{ int(0.0f * scalingFactorHeight) };
	constexpr int widthSongRow{ int(558.9f * scalingFactorWidth) };
	constexpr int heightSongRow{ int(26.34f * scalingFactorHeight) };

	//mt_ignite_songConfig.cpp

	constexpr int xStartSongMenuBox1{ int(5.6f * scalingFactorWidth) };
	constexpr int yStartSongMenuBox1{ int(41.9f * scalingFactorHeight) };
	constexpr int widthSongMenuBox1{ int(563.5f * scalingFactorWidth) };
	constexpr int heightSongMenuBox1{ int(53.90f * scalingFactorHeight) };
	constexpr int xStartSongMenuBox2{ int(27.83f * scalingFactorWidth) };
	constexpr int yStartSongMenuBox2{ int(95.8f * scalingFactorHeight) };
	constexpr int widthSongMenuBox2{ int(334.00f * scalingFactorWidth) };
	constexpr int heightSongMenuBox2{ int(59.66f * scalingFactorHeight) };
	constexpr int xStartSongMenuBox3{ int(55.66f * scalingFactorWidth) };
	constexpr int yStartSongMenuBox3{ int(208.84f * scalingFactorHeight) };
	constexpr int widthSongMenuBox3{ int(417.50f * scalingFactorWidth) };
	constexpr int heightSongMenuBox3{ int(59.66f * scalingFactorHeight) };
	constexpr int xStartfillConfigLable{ int(33.40f * scalingFactorWidth) };
	constexpr int yStartfillConfigLable{ int(184.97f * scalingFactorHeight) };
	constexpr int widthfillConfigLable{ int(122.46f * scalingFactorWidth) };
	constexpr int heightfillConfigLable{ int(35.80f * scalingFactorHeight) };
	constexpr int widthfillMode{ int(211.53f * scalingFactorWidth) };
	constexpr int heightfillMode{ int(179.00f * scalingFactorHeight) };
	constexpr int widthfillRelease{ int(211.53f * scalingFactorWidth) };
	constexpr int heightfillRelease{ int(155.14f * scalingFactorHeight) };

	//song.cpp

	constexpr int xStartAddNewInList{ int(5.6f * scalingFactorWidth) };
	constexpr int yStartAddNewInList{ int(254.1f * scalingFactorHeight) };
	constexpr int widthAddNewInList{ int(559.2f * scalingFactorWidth) };
	constexpr int heightAddNewInList{ int(26.34f * scalingFactorHeight) };

	constexpr int xStartSongView{ int(0.0f * scalingFactorWidth) };
	constexpr int yStartSongView{ int(38.32f * scalingFactorHeight) };
	constexpr int widthSongView{ int(559.2f * scalingFactorWidth) };
	constexpr int heightSongView{ int(217.19f * scalingFactorHeight) };

	constexpr int xStartSongView1{ int(5.6f * scalingFactorWidth) };
	constexpr int yStartSongView1{ int(38.3f * scalingFactorHeight) };
	constexpr int widthSongView1{ int(559.3f * scalingFactorWidth) };
	constexpr int heightSongView1{ int(270.67f * scalingFactorHeight) };

	constexpr int xStartBackBtn{ int(1.57f * scalingFactorWidth) };
	constexpr int yStartBackBtn{ int(1.7f * scalingFactorHeight) };
	constexpr int widthBackBtn{ int(26.1f * scalingFactorWidth) };
	constexpr int heightBackBtn{ int(27.55f * scalingFactorHeight) };

	constexpr int xStartViewBtn{ int(5.9f * scalingFactorWidth) };
	constexpr int yStartViewBtn{ int(6.1f * scalingFactorHeight) };
	constexpr int widthViewBtn{ int(51.5f * scalingFactorWidth) };
	constexpr int heightViewBtn{ int(27.54f * scalingFactorHeight) };

	constexpr int xStartFillModeBtn{ int(491.0f * scalingFactorWidth) };
	constexpr int widthFillModeBtn{ int(73.6f * scalingFactorWidth) };

	constexpr int xStartSongList{ int(5.6f * scalingFactorWidth) };
	constexpr int yStartSongList{ int(79.8f * scalingFactorHeight) };
	constexpr int widthSongList{ int(559.2f * scalingFactorWidth) };
	constexpr int heightSongList{ int(26.34f * scalingFactorHeight) };

	constexpr int widthSongContainer{ int(560.89f * scalingFactorWidth) };
	constexpr int heightSongContainer{ int(26.34f * scalingFactorHeight) };


	//mt_ignite_track.cpp

	constexpr int xStartSwapBtn{ int(7.5f * scalingFactorWidth) };
	constexpr int widthSwapBtn{ int(92.85f * scalingFactorWidth) };

	constexpr int xStartFwdBtn{ int(534.72f * scalingFactorWidth) };
	constexpr int xStartBckBtn{ int(506.2f * scalingFactorWidth) };
	constexpr int yStartNavigationBtn{ int(7.9f * scalingFactorHeight) };
	constexpr int widthNavigationBtn{ int(25.55f * scalingFactorWidth) };
	constexpr int heightNavigationBtn{ int(27.6f * scalingFactorHeight) };

	constexpr int yStartFwdBtn{ int(120.30f * scalingFactorHeight) };
	constexpr int widthFwdBtn{ int(42.85f * scalingFactorWidth) };
	constexpr int heightFwdBtn{ int(22.55f * scalingFactorHeight) };

	constexpr int xStartTrackName{ int(0.0f * scalingFactorWidth) };
	constexpr int yStartTrackName{ int(10.18f * scalingFactorHeight) };
	constexpr int widthTrackName{ int(521.42f * scalingFactorWidth) };
	constexpr int heightTrackName{ int(50.37f * scalingFactorHeight) };

	constexpr int xStartTrackParam1{ int(60.0f * scalingFactorWidth) };
	constexpr int yStartTrackParam1{ int(50.18f * scalingFactorHeight) };
	constexpr int widthTrackParam1{ int(522.42f * scalingFactorWidth) };
	constexpr int heightTrackParam1{ int(60.37f * scalingFactorHeight) };

	constexpr int xStartTrackParam2{ int(65.0f * scalingFactorWidth) };
	constexpr int yStartTrackParam2{ int(130.18f * scalingFactorHeight) };
	constexpr int widthTrackParam2{ int(348.0f * scalingFactorWidth) };
	constexpr int heightTrackParam2{ int(50.37f * scalingFactorHeight) };

	constexpr int xStartTrackValueSel{ int(142.85f * scalingFactorWidth) };
	constexpr int yStartTrackValueSel{ int(75.18f * scalingFactorHeight) };
	constexpr int widthTrackValueSel{ int(321.42f * scalingFactorWidth) };
	constexpr int heightTrackValueSel{ int(150.37f * scalingFactorHeight) };

	constexpr int xStartTrackChild{ int(21.42f * scalingFactorWidth) };
	constexpr int yStartTrackChild{ int(10.55f * scalingFactorHeight) };
	constexpr int widthTrackChild{ int(535.71f * scalingFactorWidth) };
	constexpr int heightTrackChild{ int(235.11f * scalingFactorHeight) };

	//mt_ignite_track_values.cpp
	constexpr int xStartTrackValueAddBtn{ int(14.28f * scalingFactorWidth) };
	constexpr int yStartTrackValueAddBtn{ int(30.07f * scalingFactorHeight) };
	constexpr int widthTrackValueAddBtn{ int(535.71f * scalingFactorWidth) };
	constexpr int heightTrackValueAddBtn{ int(30.07f * scalingFactorHeight) };

	constexpr int yStartTrackValueBtmAddBtn{ int(263.15f * scalingFactorHeight) };

	constexpr int xStartTrackValueBackBtn{ int(3.57f * scalingFactorWidth) };
	constexpr int yStartTrackValueBackBtn{ int(5.25f * scalingFactorHeight) };
	constexpr int widthTrackValueBackBtn{ int(25.85f * scalingFactorWidth) };
	constexpr int heightTrackValueBackBtn{ int(27.85f * scalingFactorHeight) };

	constexpr int xStartTrackValueHeader{ int(14.28 * scalingFactorWidth) };
	constexpr int yStartTrackValueHeader{ int(0.0f * scalingFactorHeight) };
	constexpr int widthTrackValueHeader{ int(535.71f * scalingFactorWidth) };
	constexpr int heightTrackValueHeader{ int(35.55f * scalingFactorHeight) };

	constexpr float xStartTrackValueEmptyComp{ float(14.28 * scalingFactorWidth) };
	constexpr int yStartTrackValueEmptyComp{ int(67.66f * scalingFactorHeight) };
	constexpr int widthTrackValueEmptyComp{ int(535.71f * scalingFactorWidth) };
	constexpr int heightTrackValueEmptyComp{ int(225.56f * scalingFactorHeight) };

	constexpr int widthTrackValueHeaderFill{ int(571.42f * scalingFactorWidth) };
	constexpr int heightTrackValueHeaderFill{ int(35.55f * scalingFactorHeight) };

	constexpr int xStartTrackValueFlexBox{ int(0.0 * scalingFactorWidth) };
	constexpr int yStartTrackValueFlexBox{ int(45.55f * scalingFactorHeight) };
	constexpr int widthTrackValueFlexBox{ int(570.0f * scalingFactorWidth) };
	constexpr int heightTrackValueFlexBox{ int(260.15f * scalingFactorHeight) };

	//track_grid.cpp

	constexpr int xStartTrackGrid{ int(3.57f * scalingFactorWidth) };
	constexpr int widthTrackGrid{ int(563.4f * scalingFactorWidth) };
	constexpr int heightTrackGrid{ int(242.42f * scalingFactorHeight) };
	constexpr int yStartTrackGrid{ int(38.1f * scalingFactorHeight) };

	//menuModeInstance

	constexpr int heightMenuInstance{ int(30.31f * scalingFactorHeight) };

	constexpr int xStartMenuHeader{ int(214.28f * scalingFactorWidth) };
	constexpr int yStartMenuHeader{ int(3.0f * scalingFactorHeight) };
	constexpr int widthMenuHeader{ int(142.85f * scalingFactorWidth) };
	constexpr int heightMenuHeader{ int(28.55f * scalingFactorHeight) };

	constexpr int widthMenuBox{ int(282.40f * scalingFactorHeight) };
	constexpr int heightMenuBox{ int(widthMenuBox * 114.28) };

	//instrument
	constexpr int widthInstMenu{ int(128.5f * scalingFactorWidth) };

	//Pattern steps

	constexpr int xStartAux1{ int(10.71f * scalingFactorWidth) };
	constexpr int widthAux1{ int(214.3f * scalingFactorWidth) };
	constexpr int heightAux1{ int(26.7f * scalingFactorHeight) };

	constexpr int xStartAux2{ int(228.57f * scalingFactorWidth) };

	constexpr int yStartAux1{ int(15.2f * scalingFactorHeight) };
	constexpr int yStartAux2{ int(57.1f * scalingFactorHeight) };
	constexpr int yStartAux3{ int(98.4f * scalingFactorHeight) };
	constexpr int yStartAux4{ int(139.9f * scalingFactorHeight) };

	constexpr int xStartStepNum{ int(5.55f * scalingFactorWidth) };
	constexpr int yStartStepNum{ int(77.84f * scalingFactorHeight) };
	constexpr int widthStepNum{ int(411.11f * scalingFactorWidth) };
	constexpr int heightStepNum{ int(45.7f * scalingFactorHeight) };

	constexpr int xStartPatternInfo1{ int(8.14f * scalingFactorWidth) };
	constexpr int yStartPatternInfo1{ int(179.64f * scalingFactorHeight) };
	constexpr int widthPatternInfo1{ int(400.0f * scalingFactorWidth) };
	constexpr int heightPatternInfo1{ int(50.7f * scalingFactorHeight) };

	constexpr int xStartPatternInfo2{ int(40.71f * scalingFactorWidth) };
	constexpr int yStartPatternInfo2{ int(8.8f * scalingFactorHeight) };
	constexpr int widthPatternInfo2{ int(400.0f * scalingFactorWidth) };
	constexpr int heightPatternInfo2{ int(28.7f * scalingFactorHeight) };

	constexpr int xStartPatternInfo3{ int(7.14f * scalingFactorWidth) };
	constexpr int yStartPatternInfo3{ int(7.9f * scalingFactorHeight) };
	constexpr int widthPatternInfo3{ int(425.0f * scalingFactorWidth) };
	constexpr int heightPatternInfo3{ int(68.17f * scalingFactorHeight) };

	constexpr int xStartStepInfo{ int(4.14f * scalingFactorWidth) };
	constexpr int yStartStepInfo{ int(125.74f * scalingFactorHeight) };
	constexpr int widthStepInfo{ int(425.5 * scalingFactorWidth) };
	constexpr int heightStepInfo{ int(40.17f * scalingFactorHeight) };

	constexpr int xStartNodeInfo{ int(18.5f * scalingFactorWidth) };
	constexpr int yStartNodeInfo{ int(200.0f * scalingFactorHeight) };
	constexpr int widthNodeInfo{ int(413.5 * scalingFactorWidth) };
	constexpr int heightNodeInfo{ int(18.9f * scalingFactorHeight) };

	//mt_ignite_bar.cpp
	constexpr int xStartBarLoopComp{ int(71.42f * scalingFactorWidth) };
	constexpr int yStartBarLoopComp{ int(75.18f * scalingFactorHeight) };
	constexpr int widthBarLoopComp{ int(321.42f * scalingFactorWidth) };
	constexpr int heightBarLoopComp{ int(150.37f * scalingFactorHeight) };

	//mt_ignite_step_length.cpp

	constexpr int widthStepLabel{ int(71.42f * scalingFactorWidth) };
	constexpr int heightStepLabel{ int(15.03f * scalingFactorHeight) };

	//Save options
	constexpr float widthSaveoption{ float(0.71f * scalingFactorWidth) };
	constexpr float heightSaveoption{ float(0.75f * scalingFactorHeight) };

	//pattern Aux
	constexpr int xStartAuxView{ int(1.0f * scalingFactorWidth) };
	constexpr int yStartAuxView{ int(11.80f * scalingFactorHeight) };
	constexpr int widthAuxView{ int(428.15f * scalingFactorWidth) };
	constexpr int heightAuxView{ int(231.9f * scalingFactorHeight) };

	constexpr int xStartAuxBoxView{ int(71.84f * scalingFactorWidth) };
	constexpr int yStartAuxBoxView{ int(181.0f * scalingFactorHeight) };
	constexpr int widthAuxBoxView{ int(285.15f * scalingFactorWidth) };
	constexpr int heightAuxBoxView{ int(30.6f * scalingFactorHeight) };

	//Pattern Bar View
	/*barHeader.performLayout(Rectangle(30, 20, 500, 50));
	barOptions.performLayout(Rectangle(30, 80, 500, 150));
	barValues.performLayout(Rectangle(30, 260, 500, 60));*/

	constexpr int xStartBarCmp{ int(43.0f * scalingFactorWidth) };
	constexpr int yStartBarHeader{ int(30.5f * scalingFactorHeight) };
	constexpr int widthBarCmp{ int(463.14f * scalingFactorWidth) };
	constexpr int heightBarHeader{ int(37.59f * scalingFactorHeight) };

	constexpr int yStartBarOptions{ int(70.15f * scalingFactorHeight) };
	constexpr int heightBarOptions{ int(112.78f * scalingFactorHeight) };

	constexpr int yStartBarValues{ int(180.48f * scalingFactorHeight) };
	constexpr int heightBarValues{ int(45.11f * scalingFactorHeight) };

	constexpr int xStartStepPresets{ int(1.42f * scalingFactorWidth) };
	constexpr int yStartStepPresets{ int(5.75f * scalingFactorHeight) };
	constexpr int widthStepPresets{ int(1.42f * scalingFactorWidth) };
	constexpr int heightStepPresets{ int(16.1f * scalingFactorHeight) };

	constexpr int heightinverseLevels{ int(22.55f * scalingFactorHeight) };
	constexpr int widthlevelSlider{ int(14.28f * scalingFactorWidth) };
	constexpr int heightlevelSlider{ int(7.51f * scalingFactorHeight) };

	constexpr int xStartlevelSlider{ int(2.14f * scalingFactorWidth) };
	constexpr int yStartflipLevels{ int(39.98f * scalingFactorHeight) };
	constexpr int heightflipLevels{ int(13.13f * scalingFactorHeight) };

	constexpr int heightInstCmp{ int(22.55f * scalingFactorHeight) };

	//track values selection

	constexpr int xStartvalueSelectionBox{ int(21.42f * scalingFactorWidth) };
	constexpr int yStartvalueSelectionBox{ int(15.15f * scalingFactorHeight) };
	constexpr int widthvalueSelectionBox{ int(285.71f * scalingFactorWidth) };
	constexpr int heightvalueSelectionBox{ int(75.75f * scalingFactorHeight) };

	constexpr int xStartctlBox{ int(21.42f * scalingFactorWidth) };
	constexpr int yStartctlBox{ int(113.63f * scalingFactorHeight) };
	constexpr int widthctlBox{ int(285.71f * scalingFactorWidth) };
	constexpr int heightctlBox{ int(30.30f * scalingFactorHeight) };

	constexpr int widthSongAdv{ int(214.28f * scalingFactorWidth) };
	constexpr int heightSongAdv{ int(128.78f * scalingFactorHeight) };

	constexpr int widthCurrentScene{ int(214.28f * scalingFactorWidth) };
	constexpr int heightCurrentScene{ int(165.78f * scalingFactorHeight) };

	constexpr int widthMuteHold{ int(214.28f * scalingFactorWidth) };
	constexpr int heightMuteHold{ int(174.24f * scalingFactorHeight) };

	constexpr int widthtracksComp{ int(250.0f * scalingFactorWidth) };
	constexpr int heighttracksComp{ int(174.24f * scalingFactorHeight) };

	constexpr int heightDailogOptCtrl{ int(83.83f * scalingFactorHeight) };

	constexpr int heightDailogTitle{ int(60.60f * scalingFactorHeight) };

	constexpr int heightOptCtrl{ int(30.30f * scalingFactorHeight) };

	constexpr int xStartNumpad{ int(7.14f * scalingFactorWidth) };
	constexpr int widthNumPad{ int(14.28f * scalingFactorWidth) };
	constexpr int heightNumPad{ int(89.82f * scalingFactorHeight) };

	constexpr int heightListBox{ int(79.54f * scalingFactorHeight) };

	constexpr int heightListBoxCtrl{ int(46.9f * scalingFactorHeight) };

	constexpr int widthtabBox{ int(316.66f * scalingFactorWidth) };
	constexpr int heighttabBox{ int(45.93f * scalingFactorHeight) };

	constexpr int xStartOpnBtn{ int(525.5f * scalingFactorWidth) };
	constexpr int widthOpnBtn{ int(80.22f * scalingFactorWidth) };
	constexpr int heightOpnBtn{ int(174.24f * scalingFactorHeight) };

	constexpr int widthCtrloption{ int(71.42f * scalingFactorWidth) };

	constexpr int xStartCtrlOpnBtn{ int(39.28f * scalingFactorWidth) };

	constexpr int widthnumOfBars{ int(285.71f * scalingFactorWidth) };
	constexpr int heightnumOfBars{ int(227.27f * scalingFactorHeight) };

	constexpr int widthBarInsert{ int(285.71f * scalingFactorWidth) };
	constexpr int heightBarInsert{ int(279.64f * scalingFactorHeight) };

	constexpr int widthtimeBase{ int(285.71f * scalingFactorWidth) };
	constexpr int heighttimeBase{ int(238.32f * scalingFactorHeight) };

	constexpr int widthlastStep{ int(285.71f * scalingFactorWidth) };
	constexpr int heightlastStep{ int(267.27f * scalingFactorHeight) };

	constexpr int widthparamValue{ int(285.71f * scalingFactorWidth) };
	constexpr int heightparamValue{ int(232.9f * scalingFactorHeight) };

	constexpr int widthspacebtwnctrl{ int(27.9f * scalingFactorWidth) };
	constexpr int widthctrloption{ int(116.9f * scalingFactorWidth) };

	constexpr int xStartOptionBtn{ int(206.2f * scalingFactorWidth) };
	constexpr int widthOptionBtn{ int(45.0f * scalingFactorWidth) };

	constexpr int xStartOptionBtn1{ int(94.7f * scalingFactorWidth) };
	constexpr int widthMenuOptions{ int(256.55f * scalingFactorWidth) };

	constexpr int xStartOptionccCmp{ int(111.73f * scalingFactorWidth) };
	 
}
#endif // COMMON_LAYOUT_H
