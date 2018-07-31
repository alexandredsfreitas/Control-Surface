#pragma once

#include <Hardware/ExtendedInputOutput/ExtendedInputOutput.h>
#include <MIDI_Inputs/MIDINote.hpp>

class MIDINoteLED_Base : public virtual MIDINote_Base {
  public:
    MIDINoteLED_Base(pin_t ledPin) : ledPin(ledPin) {}

    void begin() override { ExtIO::pinMode(ledPin, OUTPUT); }

  private:
    void display() const override {
        DEBUGFN("");
        ExtIO::digitalWrite(ledPin, getValue() >= 64);
    }

  private:
    const pin_t ledPin;
};

// -------------------------------------------------------------------------- //

class MIDINoteLED : public MIDINote, public MIDINoteLED_Base {
  public:
    MIDINoteLED(uint8_t note, uint8_t channel, pin_t ledPin)
        : MIDINote_Base(note, channel), MIDINote(note, channel),
          MIDINoteLED_Base(ledPin) {}
};

// -------------------------------------------------------------------------- //

namespace Bankable {

template <uint8_t N>
class MIDINoteLED : public MIDINote<N>, public MIDINoteLED_Base {
  public:
    MIDINoteLED(const BankConfigAddressable<N> &config, uint8_t note,
                uint8_t channel, pin_t ledPin)
        : MIDINote_Base(note, channel), MIDINote<N>(config, note,
                                                                  channel),
          MIDINoteLED_Base(ledPin) {}
};

} // namespace Bankable