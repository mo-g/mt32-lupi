//
// soundfontsynth.h
//
// mt32-pi - A bare-metal Roland MT-32 emulator for Raspberry Pi
// Copyright (C) 2020  Dale Whinham <daleyo@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#ifndef _soundfontsynth_h
#define _soundfontsynth_h

#include <circle/types.h>

#include <fluidsynth.h>

#include "synth/synthbase.h"

class CSoundFontSynth : public CSynthBase
{
public:
	CSoundFontSynth(unsigned nSampleRate, u32 nPolyphony = 128);
	virtual ~CSoundFontSynth() override;

	// CSynthBase
	virtual bool Initialize() override;
	virtual void HandleMIDIShortMessage(u32 nMessage) override;
	virtual void HandleMIDISysExMessage(const u8* pData, size_t nSize) override;
	virtual bool IsActive() const override { return fluid_synth_get_active_voice_count(m_pSynth) > 0; }
	virtual void AllSoundOff() override;
	virtual size_t Render(s16* pOutBuffer, size_t nFrames) override;
	virtual size_t Render(float* pOutBuffer, size_t nFrames) override;

private:
	unsigned m_nSampleRate;

	fluid_settings_t* m_pSettings;
	fluid_synth_t* m_pSynth;

	u32 m_nPolyphony;

	static void FluidSynthLogCallback(int nLevel, const char* pMessage, void* pUser);
};

#endif
