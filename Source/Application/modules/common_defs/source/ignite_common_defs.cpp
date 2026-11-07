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

namespace mt
{
	Ignite::Ignite() {}

	/// Utility functions...
	int Ignite::getRootNoteNumber(const juce::String& Root)
	{
		return findIndex(Root, rootNoteNamesSharps);
	}

	const juce::String& Ignite::getRootNoteName(int Number)
	{
		return rootNoteNamesSharps.at(Number);
	}

	int8_t Ignite::getNoteNumber(const juce::String& Note)
	{
		return (int8_t)findIndex(Note, midiNoteNamesSharps);
	}

	const juce::String& Ignite::getNoteName(int Number)
	{
		return midiNoteNamesSharps.at(Number);
	}

	std::vector<int> Ignite::getNotesInScale(const juce::String& Root, const juce::String& Scale, const juce::String& StartNote, const juce::String& EndNote)
	{
		int rootNum = getRootNoteNumber(Root);
		return getScaleNotesInRange(rootNum, scaleFormulas[rootNum], getNoteNumber(StartNote), getNoteNumber(EndNote));
	}

	int Ignite::getPadBankNumber(const juce::String& PadBank)
	{
		return findIndex(PadBank, padBankNames);
	}

	const juce::String& Ignite::getPadBankName(int Number)
	{
		return padBankNames.at(Number);
	}

	int Ignite::getPadNumber(const juce::String& Pad)
	{
		return findIndex(Pad, padNames);
	}

	const juce::String& Ignite::getPadName(int Number)
	{
		return padNames.at(Number);
	}

	double Ignite::getNoteLength(const juce::String& Length)
	{
		if (Length.equalsIgnoreCase("Bar")) { return 1.0; }
		if (Length.equalsIgnoreCase("1/2")) { return 0.5; }
		if (Length.equalsIgnoreCase("1/4")) { return 0.25; }
		if (Length.equalsIgnoreCase("1/4T")) { return 0.375; }
		if (Length.equalsIgnoreCase("1/8")) { return 0.125; }
		if (Length.equalsIgnoreCase("1/8T")) { return 0.1875; }
		if (Length.equalsIgnoreCase("1/16")) { return 0.0625; }
		if (Length.equalsIgnoreCase("1/16T")) { return 0.09375; }
		if (Length.equalsIgnoreCase("1/32")) { return 0.03125; }
		if (Length.equalsIgnoreCase("1/32T")) { return 0.046875; }
		if (Length.equalsIgnoreCase("1/64")) { return 0.015625; }
		if (Length.equalsIgnoreCase("1/64T")) { return 0.0234375; }
		return 0.0f;
	}

	int Ignite::findIndex(const juce::String& Note, const std::vector<juce::String>& NoteArray)
	{
		int i = 0;
		for (i = 0; i < NoteArray.size(); ++i)
		{
			if (Note.equalsIgnoreCase(NoteArray.at(i)))
				break;
		}
		return i;
	}

	std::vector<int> Ignite::getScaleNotesInRange(const int RootNote, const std::vector<int>& Scale, const int Start, const int End)
	{
		int scaleIterator = 0;
		std::vector<int> notes;

		for (int i = RootNote; i <= End; )
		{
			if (Start <= i && End >= i)
				notes.push_back(i);
			i += Scale[scaleIterator++];
			if (scaleIterator >= Scale.size())
				scaleIterator = 0;
		}
		return notes;
	}
}
