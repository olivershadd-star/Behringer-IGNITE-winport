// SPDX-License-Identifier: AGPL-3.0-or-later
#include "MainComponent.h"
#include "PatternFile.h"
#include "WindowsInput.h"
#include <algorithm>
#include <cmath>

namespace {
const juce::Colour background{0xff0b1420},panel{0xff142336},line{0xff314b65},amber{0xffffb700},blue{0xff44aadd},text{0xffeff4fa};
const char* trackNames[]={"Kick","Snare","Hat","Basse","Clavier","Lead"};
juce::String noteName(int note){return juce::MidiMessage::getMidiNoteName(note,true,true,4);}
juce::String drumName(int note) {
    switch(note){case 35:return "Acoustic kick";case 36:return "Kick";case 37:return "Side stick";case 38:return "Snare";case 39:return "Clap";case 40:return "Electric snare";case 42:return "Closed hat";case 44:return "Pedal hat";case 46:return "Open hat";case 49:return "Crash";case 51:return "Ride";case 54:return "Tambourine";case 56:return "Cowbell";default:return noteName(note);}
}
int enabledSteps(const ignite::Pattern& p){int count=0;for(const auto& tr:p.tracks)for(const auto& s:tr.steps)if(s.enabled)++count;return count;}
}

MainComponent::MainComponent(bool selfTest):testing(selfTest) {
    keyboardOwners.fill(-1);
    look.setColour(juce::ResizableWindow::backgroundColourId,background);
    look.setColour(juce::TextButton::buttonColourId,panel);look.setColour(juce::TextButton::buttonOnColourId,amber.darker(.4f));
    look.setColour(juce::TextButton::textColourOffId,text);look.setColour(juce::TextButton::textColourOnId,text);
    look.setColour(juce::ComboBox::backgroundColourId,panel);look.setColour(juce::ComboBox::textColourId,text);look.setColour(juce::ComboBox::outlineColourId,line);
    look.setColour(juce::PopupMenu::backgroundColourId,panel);look.setColour(juce::PopupMenu::textColourId,text);
    look.setColour(juce::Slider::thumbColourId,amber);look.setColour(juce::Slider::trackColourId,blue);
    setLookAndFeel(&look);setSize(1040,610);
    const auto bank=juce::File::getSpecialLocation(juce::File::currentExecutableFile).getSiblingFile("Ignite.sf2");
    bankLoaded=core.loadSoundFont(std::filesystem::u8path(bank.getFullPathName().toStdString()));
    if(!bankLoaded)message="Banque Ignite.sf2 absente ou illisible : conserver tous les fichiers du ZIP ensemble.";
    for(auto* button:{&play,&stop,&demo,&clear,&save,&load,&audio})addAndMakeVisible(button);
    play.setColour(juce::TextButton::buttonColourId,juce::Colour(0xff176e50));play.setColour(juce::TextButton::buttonOnColourId,juce::Colour(0xff22a16e));
    play.onClick=[this]{if(!bankLoaded)return;if(!testing&&deviceManager.getCurrentAudioDevice()==nullptr){message="Choisissez une sortie audio Windows.";openAudio();return;}if(enabledSteps(pattern)==0){message="Pattern vide : activez des pas ou chargez Demo.";return;}core.play();message="Lecture du pattern.";};
    stop.onClick=[this]{core.stop();keyboardState.allNotesOff(0);message="Arret.";};
    demo.onClick=[this]{core.stop();pattern=ignite::makeDemo();sendPattern();syncControls();message="Demo chargee : appuyez sur PLAY.";};
    clear.onClick=[this]{core.stop();for(auto& tr:pattern.tracks)for(auto& s:tr.steps)s.enabled=false;sendPattern();syncControls();message="Pattern vide : cliquez sur les pas pour le construire.";};
    save.onClick=[this]{savePattern();};load.onClick=[this]{loadPattern();};audio.onClick=[this]{openAudio();};
    tempo.setRange(40,240,1);tempo.setValue(pattern.bpm,juce::dontSendNotification);tempo.setSliderStyle(juce::Slider::LinearHorizontal);tempo.setTextBoxStyle(juce::Slider::TextBoxLeft,false,46,24);tempo.setTooltip("Tempo en battements par minute");addAndMakeVisible(tempo);
    tempo.onValueChange=[this]{pattern.bpm=tempo.getValue();sendPattern();};
    volume.setRange(0,100,1);volume.setValue(70,juce::dontSendNotification);volume.setSliderStyle(juce::Slider::LinearHorizontal);volume.setTextBoxStyle(juce::Slider::TextBoxRight,false,40,24);volume.setTextValueSuffix(" %");addAndMakeVisible(volume);volume.onValueChange=[this]{core.setVolume(static_cast<float>(volume.getValue()/100));};
    for(int t=0;t<ignite::trackCount;++t) {
        auto& row=rows[static_cast<size_t>(t)];
        row.select.setButtonText(trackNames[t]);row.select.setTooltip("Selectionner cette piste pour le clavier");
        row.select.onClick=[this,t]{keyboardState.allNotesOff(0);selectedTrack=t;syncControls();message=juce::String(trackNames[t])+" selectionne pour le clavier.";};
        row.preview.setButtonText("Jouer");row.preview.setTooltip("Ecouter le son de cette piste");row.preview.onClick=[this,t]{if(!bankLoaded)return;if(!testing&&deviceManager.getCurrentAudioDevice()==nullptr){openAudio();return;}core.audition(t,pattern.tracks[static_cast<size_t>(t)].note);message="Ecoute : "+rows[static_cast<size_t>(t)].instrument.getText();};
        row.mute.setButtonText("M");row.mute.setClickingTogglesState(true);row.mute.setTooltip("Couper cette piste");row.mute.onClick=[this,t]{pattern.tracks[static_cast<size_t>(t)].muted=rows[static_cast<size_t>(t)].mute.getToggleState();sendPattern();};
        for(const auto& preset:core.presets())if(preset.bank==(t<3?128:0))row.instrument.addItem(juce::String::fromUTF8(preset.name.c_str()),preset.program+1);
        row.instrument.setTooltip(t<3?"Choisir une boite a rythmes":"Choisir un instrument interne");
        row.instrument.onChange=[this,t]{auto& tr=pattern.tracks[static_cast<size_t>(t)];tr.program=rows[static_cast<size_t>(t)].instrument.getSelectedId()-1;sendPattern();message="Instrument : "+rows[static_cast<size_t>(t)].instrument.getText()+". Cliquez Jouer pour l'ecouter.";};
        for(int n=0;n<128;++n)row.note.addItem(t<3?juce::String(n)+" "+drumName(n):noteName(n),n+1);
        row.note.setTooltip("Note de la piste. Clic droit sur un pas pour modifier sa note seule.");
        row.note.onChange=[this,t]{auto& tr=pattern.tracks[static_cast<size_t>(t)];tr.note=rows[static_cast<size_t>(t)].note.getSelectedId()-1;for(auto& s:tr.steps)s.note=static_cast<uint8_t>(tr.note);sendPattern();syncControls();};
        for(auto* c:std::initializer_list<juce::Component*>{&row.select,&row.instrument,&row.note,&row.preview,&row.mute})addAndMakeVisible(c);
        for(int s=0;s<ignite::stepCount;++s) {
            auto& button=row.steps[static_cast<size_t>(s)];button.setClickingTogglesState(true);addAndMakeVisible(button);
            button.setTooltip("Clic : activer/desactiver. Clic droit : choisir la note du pas.");
            button.onClick=[this,t,s]{auto& step=pattern.tracks[static_cast<size_t>(t)].steps[static_cast<size_t>(s)];step.enabled=rows[static_cast<size_t>(t)].steps[static_cast<size_t>(s)].getToggleState();sendPattern();syncControls();};
            button.onChooseNote=[this,t,s]{chooseNote(t,s);};
        }
    }
    keyboardState.addListener(this);addAndMakeVisible(keyboard);keyboard.setAvailableRange(36,96);keyboard.setLowestVisibleKey(48);keyboard.setKeyWidth(21);
    for(auto* label:{&status,&hint}){label->setColour(juce::Label::textColourId,text);label->setFont(juce::Font(12));addAndMakeVisible(label);}
    hint.setText("Clic sur les pas : on/off. Clic droit : note du pas. Selectionnez une piste pour jouer au clavier.",juce::dontSendNotification);
    syncControls();sendPattern();
    if(testing&&bankLoaded) {
        recording.resize(48000u*20u*2u);prepareToPlay(256,48000);renderTest.store(true);
        testAudio=std::thread([this]{juce::AudioBuffer<float> b(2,256);while(renderTest.load()){getNextAudioBlock({&b,0,256});std::this_thread::sleep_for(std::chrono::milliseconds(5));}});
    } else if(bankLoaded) setAudioChannels(0,2);
    startTimerHz(30);
}
MainComponent::~MainComponent(){stopTimer();renderTest.store(false);if(testAudio.joinable())testAudio.join();shutdownAudio();keyboardState.removeListener(this);setLookAndFeel(nullptr);}
void MainComponent::sendPattern(){if(!core.setPattern(pattern))message="Commandes trop rapides : lecture arretee, recommencez.";}
void MainComponent::syncControls() {
    tempo.setValue(pattern.bpm,juce::dontSendNotification);
    for(size_t t=0;t<rows.size();++t) {
        auto& row=rows[t];const auto& tr=pattern.tracks[t];row.instrument.setSelectedId(tr.program+1,juce::dontSendNotification);row.note.setSelectedId(tr.note+1,juce::dontSendNotification);row.mute.setToggleState(tr.muted,juce::dontSendNotification);
        row.select.setColour(juce::TextButton::buttonColourId,static_cast<int>(t)==selectedTrack?juce::Colour(0xff24587b):panel);
        for(size_t s=0;s<row.steps.size();++s) {
            auto& b=row.steps[s];const auto& step=tr.steps[s];b.setToggleState(step.enabled,juce::dontSendNotification);b.setButtonText(step.enabled?(t<3?juce::String(static_cast<int>(s)+1):noteName(step.note)):juce::String(static_cast<int>(s)+1));
            b.setColour(juce::TextButton::buttonColourId,static_cast<int>(s)==highlight?juce::Colour(0xff4c5d6b):panel);
            b.setColour(juce::TextButton::buttonOnColourId,static_cast<int>(s)==highlight?juce::Colour(0xffe5ddc1):(t<3?amber.darker(.35f):blue.darker(.4f)));
            b.setColour(juce::TextButton::textColourOnId,static_cast<int>(s)==highlight?background:text);
            b.setAlpha(tr.muted?.4f:1.f);
        }
    }
    play.setEnabled(bankLoaded);for(auto* b:{&demo,&clear,&save,&load})b->setEnabled(bankLoaded);
}
void MainComponent::prepareToPlay(int,double rate){core.prepare(rate);deviceRate.store(rate);}
void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& info) {
    info.clearActiveBufferRegion();if(!bankLoaded||info.buffer==nullptr||info.buffer->getNumChannels()<1)return;
    for(int start=0;start<info.numSamples;start+=2048) {
        const int n=juce::jmin(2048,info.numSamples-start);auto* l=info.buffer->getWritePointer(0,info.startSample+start);
        auto* r=info.buffer->getNumChannels()>1?info.buffer->getWritePointer(1,info.startSample+start):monoScratch.data();
        core.render(l,r,n);
        for(int i=0;i<n;++i){if(info.buffer->getNumChannels()==1)l[i]=.5f*(l[i]+r[i]);accumulatedEnergy+=static_cast<double>(l[i])*l[i]+static_cast<double>(r[i])*r[i];if(testing&&recordingPosition+2<=recording.size()){recording[recordingPosition++]=l[i];recording[recordingPosition++]=r[i];}}
    }
    callbackEnergy.store(accumulatedEnergy);callbackFrames.fetch_add(static_cast<uint64_t>(info.numSamples));
}
void MainComponent::handleNoteOn(juce::MidiKeyboardState*,int,int note,float velocity){if(!bankLoaded||(!testing&&deviceManager.getCurrentAudioDevice()==nullptr))return;keyboardOwners[static_cast<size_t>(note)]=selectedTrack;core.noteOn(selectedTrack,note,velocity);}
void MainComponent::handleNoteOff(juce::MidiKeyboardState*,int,int note,float){const auto t=keyboardOwners[static_cast<size_t>(note)];if(t>=0)core.noteOff(t,note);keyboardOwners[static_cast<size_t>(note)]=-1;}
void MainComponent::paint(juce::Graphics& g) {
    g.fillAll(background);g.setColour(text);g.setFont(juce::Font(29,juce::Font::bold));g.drawText("IGNITE",12,6,150,36,juce::Justification::centredLeft);
    g.setColour(blue);g.setFont(13);g.drawText("GROOVEBOX  /  STANDALONE 0.1",160,12,320,28,juce::Justification::centredLeft);
    g.setColour(text.withAlpha(.7f));g.setFont(11);g.drawText("BPM",562,50,32,30,juce::Justification::centred);g.drawText("VOL",730,50,32,30,juce::Justification::centred);
    const int top=112,rowHeight=(getHeight()-252)/6;
    g.setColour(text.withAlpha(.55f));g.drawText("PISTE",12,87,64,20,juce::Justification::centredLeft);g.drawText("INSTRUMENT / KIT",84,87,155,20,juce::Justification::centredLeft);g.drawText("NOTE",244,87,64,20,juce::Justification::centred);
    for(int t=0;t<6;++t){g.setColour(line);g.drawHorizontalLine(top+(t+1)*rowHeight-3,12.f,static_cast<float>(getWidth()-12));}
    auto meter=juce::Rectangle<float>(static_cast<float>(getWidth()-118),18,104,10);g.setColour(line);g.fillRoundedRectangle(meter,3);g.setColour(core.peak()>.9f?juce::Colours::orangered:juce::Colour(0xff44d69b));g.fillRoundedRectangle(meter.withWidth(meter.getWidth()*juce::jlimit(0.f,1.f,core.peak())),3);
}
void MainComponent::resized() {
    const int y=49;play.setBounds(12,y,66,32);stop.setBounds(84,y,66,32);demo.setBounds(162,y,64,32);clear.setBounds(232,y,64,32);save.setBounds(308,y,92,32);load.setBounds(406,y,64,32);audio.setBounds(476,y,84,32);tempo.setBounds(598,y,128,32);volume.setBounds(766,y,juce::jmax(110,getWidth()-780),32);
    const int top=112,rowHeight=(getHeight()-252)/6,gridX=402,gridWidth=getWidth()-gridX-12;
    for(int t=0;t<6;++t) {
        auto& r=rows[static_cast<size_t>(t)];const int ry=top+t*rowHeight+3,h=juce::jmin(34,rowHeight-8);
        r.select.setBounds(12,ry,66,h);r.instrument.setBounds(84,ry,155,h);r.note.setBounds(245,ry,65,h);r.preview.setBounds(316,ry,48,h);r.mute.setBounds(370,ry,26,h);
        for(int s=0;s<16;++s){const int x=gridX+gridWidth*s/16,w=gridWidth*(s+1)/16-gridWidth*s/16;r.steps[static_cast<size_t>(s)].setBounds(x+2,ry,w-4,h);}
    }
    hint.setBounds(12,getHeight()-130,getWidth()-24,22);keyboard.setBounds(12,getHeight()-104,getWidth()-24,70);status.setBounds(12,getHeight()-31,getWidth()-24,27);
}
void MainComponent::timerCallback() {
    const auto head=core.playhead();if(highlight!=head){highlight=head;syncControls();}play.setToggleState(head>=0,juce::dontSendNotification);
    juce::String output;
    if(testing)output="Verification audio sans carte son";
    else if(auto* device=deviceManager.getCurrentAudioDevice())output=device->getName()+" / "+juce::String(deviceRate.load(),0)+" Hz";
    else output="Aucune sortie audio : cliquez Sortie audio";
    status.setText(message+"  |  "+output,juce::dontSendNotification);repaint();if(testing)testTick();
}
void MainComponent::chooseNote(int t,int s) {
    juce::PopupMenu menu;
    for(int octave=0;octave<11;++octave){juce::PopupMenu sub;for(int n=octave*12;n<juce::jmin(128,(octave+1)*12);++n)sub.addItem(n+1,t<3?drumName(n):noteName(n),true,n==pattern.tracks[static_cast<size_t>(t)].steps[static_cast<size_t>(s)].note);menu.addSubMenu("Octave "+juce::String(octave-1),sub);}
    juce::Component::SafePointer<MainComponent> safe(this);
    menu.showMenuAsync(juce::PopupMenu::Options().withTargetComponent(&rows[static_cast<size_t>(t)].steps[static_cast<size_t>(s)]),[safe,t,s](int id){if(!safe||id<=0)return;auto& step=safe->pattern.tracks[static_cast<size_t>(t)].steps[static_cast<size_t>(s)];step.note=static_cast<uint8_t>(id-1);step.enabled=true;safe->sendPattern();safe->syncControls();});
}
void MainComponent::openAudio() {
    auto selector=std::make_unique<juce::AudioDeviceSelectorComponent>(deviceManager,0,0,0,2,false,false,true,false);selector->setSize(500,420);
    juce::DialogWindow::LaunchOptions options;options.content.setOwned(selector.release());options.dialogTitle="Sortie audio Windows";options.dialogBackgroundColour=background;options.useNativeTitleBar=true;options.escapeKeyTriggersCloseButton=true;options.launchAsync();
}
void MainComponent::savePattern() {
    chooser=std::make_unique<juce::FileChooser>("Enregistrer le pattern",juce::File::getSpecialLocation(juce::File::userDocumentsDirectory).getChildFile("Ignite-pattern.json"),"*.json");
    juce::Component::SafePointer<MainComponent> safe(this);
    chooser->launchAsync(juce::FileBrowserComponent::saveMode|juce::FileBrowserComponent::canSelectFiles|juce::FileBrowserComponent::warnAboutOverwriting,[safe](const juce::FileChooser& c){if(!safe||c.getResult()==juce::File())return;const auto file=c.getResult().withFileExtension("json");safe->message=file.replaceWithText(encodePattern(safe->pattern))?"Pattern enregistre : "+file.getFileName():"Echec de l'enregistrement.";});
}
void MainComponent::loadPattern() {
    chooser=std::make_unique<juce::FileChooser>("Ouvrir un pattern",juce::File::getSpecialLocation(juce::File::userDocumentsDirectory),"*.json");
    juce::Component::SafePointer<MainComponent> safe(this);
    chooser->launchAsync(juce::FileBrowserComponent::openMode|juce::FileBrowserComponent::canSelectFiles,[safe](const juce::FileChooser& c){if(!safe||c.getResult()==juce::File())return;ignite::Pattern loaded;juce::String error;if(!decodePattern(c.getResult().loadFileAsString(),safe->core,loaded,error)){safe->message=error;return;}safe->core.stop();safe->pattern=loaded;safe->sendPattern();safe->syncControls();safe->message="Pattern charge : "+c.getResult().getFileName();});
}
void MainComponent::capture(const juce::String& name){if(auto stream=juce::File::getCurrentWorkingDirectory().getChildFile(name).createOutputStream())juce::PNGImageFormat().writeImageToStream(createComponentSnapshot(getLocalBounds()),*stream);}
bool MainComponent::testClick(juce::Component& c){const auto point=c.localPointToGlobal(c.getLocalBounds().getCentre());return clickWindowsPoint(point.x,point.y);}
void MainComponent::testFinish(bool ok,const juce::String& reason) {
    stopTimer();renderTest.store(false);if(testAudio.joinable())testAudio.join();capture("standalone-ui-final.png");
    const auto dir=juce::File::getCurrentWorkingDirectory();
    dir.getChildFile("standalone-ui-test.txt").replaceWithText((ok?"PASS: ":"FAIL: ")+reason+"\nstage="+juce::String(testStage)+" frames="+juce::String(static_cast<juce::int64>(callbackFrames.load()))+" energy="+juce::String(callbackEnergy.load(),6)+"\nPhysical audio device not tested. Windows SendInput mouse/keyboard and the application audio callback were exercised.\n");
    if(recordingPosition>0)if(auto stream=dir.getChildFile("standalone-ui-audio.wav").createOutputStream()) {
        juce::WavAudioFormat format;std::unique_ptr<juce::AudioFormatWriter> writer(format.createWriterFor(stream.get(),48000,2,16,{},0));
        if(writer){stream.release();const int frames=static_cast<int>(recordingPosition/2);juce::AudioBuffer<float> buffer(2,frames);for(int i=0;i<frames;++i){buffer.setSample(0,i,recording[static_cast<size_t>(i*2)]);buffer.setSample(1,i,recording[static_cast<size_t>(i*2+1)]);}writer->writeFromAudioSampleBuffer(buffer,0,frames);}
    }
    juce::JUCEApplication::getInstance()->setApplicationReturnValue(ok?0:1);juce::JUCEApplication::getInstance()->quit();
}
void MainComponent::testTick() {
    if(!bankLoaded){testFinish(false,"SoundFont did not load");return;}
    if(++testTicks>1000){testFinish(false,"Native mouse/keyboard workflow timed out");return;}
    ++stageTicks;
    auto next=[this]{++testStage;stageTicks=0;};
    auto click=[this,&next](juce::Component& c){if(!testClick(c)){testFinish(false,"Windows SendInput rejected");return;}next();};
    switch(testStage) {
    case 0:if(stageTicks>15)click(play);break;
    case 1:if(stageTicks>45){if(core.playhead()<0||callbackEnergy.load()<1){testFinish(false,"PLAY click produced no running sequencer/audio");return;}capture("standalone-ui-running.png");click(stop);}break;
    case 2:if(stageTicks>12){if(core.playhead()!=-1||core.peak()>.001f){testFinish(false,"STOP click left transport/audio active");return;}click(clear);}break;
    case 3:if(stageTicks>6){if(enabledSteps(pattern)!=0){testFinish(false,"Clear click did not clear pattern");return;}click(rows[0].steps[0]);}break;
    case 4:if(stageTicks>6){if(!pattern.tracks[0].steps[0].enabled){testFinish(false,"Step click did not edit the pattern");return;}checkpointEnergy=callbackEnergy.load();click(play);}break;
    case 5:if(stageTicks>45){if(callbackEnergy.load()-checkpointEnergy<.1){testFinish(false,"Mouse-created kick pattern produced no audio");return;}click(stop);}break;
    case 6:if(stageTicks>12){oldProgram=pattern.tracks[4].program;click(rows[4].instrument);}break;
    case 7:if(stageTicks>6){if(!sendWindowsKey(0x24)||!sendWindowsKey(0x28)||!sendWindowsKey(0x0d)){testFinish(false,"Native preset selection input failed");return;}next();}break;
    case 8:if(stageTicks>12){if(pattern.tracks[4].program==oldProgram||core.programForTrack(4)!=pattern.tracks[4].program){testFinish(false,"Preset selection did not reach the audio core");return;}checkpointEnergy=callbackEnergy.load();click(rows[4].preview);}break;
    case 9:if(stageTicks>20){
        if(callbackEnergy.load()-checkpointEnergy<.01){testFinish(false,"Instrument preview click was silent");return;}
        const auto file=juce::File::getCurrentWorkingDirectory().getChildFile("standalone-test-pattern.json");file.replaceWithText(encodePattern(pattern));ignite::Pattern loaded;juce::String error;
        if(!decodePattern(file.loadFileAsString(),core,loaded,error)||encodePattern(loaded)!=encodePattern(pattern)||decodePattern("{}",core,loaded,error)){testFinish(false,"Pattern save/load validation failed");return;}next();
    }break;
    case 10:click(demo);break;
    case 11:if(stageTicks>6){if(enabledSteps(pattern)<20){testFinish(false,"Demo click did not restore a playable groove");return;}click(play);}break;
    case 12:if(stageTicks>45){capture("standalone-ui-demo.png");testFinish(true,"Native Windows clicks: demo PLAY/STOP, clear, create a kick step and play it, select another instrument, audition it, restore demo; JSON file round-trip and invalid-file rejection.");}break;
    }
}
