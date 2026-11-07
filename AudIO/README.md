# AudIO

AudIO is the audio engine library used by IGNITE. It is a patchable graph of audio objects (oscillators,
ADSR, mixer, playback and recorder, SoundFont synth, Airwindows effects) with buses, chains and a small
DAW layer. It can be used as a JUCE module (`AudIO/AudIO.h`) or on its own through CMake. See
`AudIO/Example/` for usage.

```sh
cmake -S . -B build      # out-of-source builds only
cmake --build build
```

## License

AudIO is licensed under the GNU Affero General Public License v3.0 or later, see [LICENSE](LICENSE).
Bundled third-party code keeps its own license.

## Removed from this release

- The embedded General MIDI SoundFont (`AWE32_1MB.h`, copyright E-mu Systems). It is now an empty stub,
  so supply your own `.sf2`.
- The demo drum samples in `AudIO/Samples/`.

## Third-party code included

| Component | Location | License |
|---|---|---|
| Airwindows (Chris Johnson) | `AudIO/airwindows` | MIT |
| AudioFile (Adam Stark) | `AudIO/3rdparty/AudioFile.h` | MIT |
| parallel-hashmap | `AudIO/3rdparty/phmap` | Apache-2.0 |
| smbPitchShift (Stephan M. Bernsee) | `AudIO/3rdparty/smbPitchShift.h` | Wide Open License |
| TinySoundFont / TinyMidiLoader (Bernhard Schelling) | `AudIO/Objects/SoundFontSynthesis/tsf.h`, `AudIO/Example/Synth/tml.h` | MIT |
| minisdl_audio (from TinySoundFont, based on SDL) | `AudIO/Devices/minisdl_audio.*` | zlib |
| Dear ImGui, ImGuiFileDialog, GLFW | `AudIO/Example/Synth/Thirdparty` | MIT / zlib (see each folder) |
