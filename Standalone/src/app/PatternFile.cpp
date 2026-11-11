// SPDX-License-Identifier: AGPL-3.0-or-later
#include "PatternFile.h"
#include <cmath>
juce::String encodePattern(const ignite::Pattern& p) {
    auto* root=new juce::DynamicObject();root->setProperty("format","ignite-standalone-pattern");root->setProperty("version",1);root->setProperty("tempo",p.bpm);
    juce::Array<juce::var> tracks;
    for(const auto& tr:p.tracks) {
        auto* t=new juce::DynamicObject();t->setProperty("bank",tr.bank);t->setProperty("program",tr.program);t->setProperty("note",tr.note);t->setProperty("muted",tr.muted);
        juce::Array<juce::var> steps;
        for(const auto& s:tr.steps) {auto* step=new juce::DynamicObject();step->setProperty("on",s.enabled);step->setProperty("note",static_cast<int>(s.note));step->setProperty("velocity",static_cast<int>(s.velocity));steps.add(juce::var(step));}
        t->setProperty("steps",steps);tracks.add(juce::var(t));
    }
    root->setProperty("tracks",tracks);return juce::JSON::toString(juce::var(root),true);
}
bool decodePattern(const juce::String& text,const ignite::AudioCore& core,ignite::Pattern& output,juce::String& error) {
    const auto json=juce::JSON::parse(text);
    auto fail=[&](const juce::String& reason){error=reason;return false;};
    if(!json.isObject()||json["format"].toString()!="ignite-standalone-pattern"||static_cast<int>(json["version"])!=1)return fail("Format de pattern inconnu.");
    auto p=ignite::makeEmpty();p.bpm=static_cast<double>(json["tempo"]);
    if(!std::isfinite(p.bpm)||p.bpm<40||p.bpm>240)return fail("Tempo invalide.");
    const auto* tracks=json["tracks"].getArray();if(!tracks||tracks->size()!=ignite::trackCount)return fail("Le pattern doit contenir six pistes.");
    for(int i=0;i<ignite::trackCount;++i) {
        const auto& item=tracks->getReference(i);if(!item.isObject())return fail("Piste invalide.");
        auto& tr=p.tracks[static_cast<size_t>(i)];tr.bank=static_cast<int>(item["bank"]);tr.program=static_cast<int>(item["program"]);tr.note=static_cast<int>(item["note"]);tr.muted=static_cast<bool>(item["muted"]);
        if((tr.bank!=(i<3?128:0))||tr.program<0||tr.program>127||!core.hasPreset(tr.bank,tr.program)||tr.note<0||tr.note>127)return fail("Instrument ou note indisponible.");
        const auto* steps=item["steps"].getArray();if(!steps||steps->size()!=ignite::stepCount)return fail("Chaque piste doit contenir seize pas.");
        for(int j=0;j<ignite::stepCount;++j) {
            const auto& s=steps->getReference(j);if(!s.isObject()||!s["on"].isBool()||!s.hasProperty("note")||!s.hasProperty("velocity"))return fail("Pas invalide.");
            const auto note=static_cast<int>(s["note"]),vel=static_cast<int>(s["velocity"]);
            if(note<0||note>127||vel<1||vel>127)return fail("Note ou velocite invalide.");
            tr.steps[static_cast<size_t>(j)]={static_cast<bool>(s["on"]),static_cast<uint8_t>(note),static_cast<uint8_t>(vel)};
        }
    }
    output=p;return true;
}
