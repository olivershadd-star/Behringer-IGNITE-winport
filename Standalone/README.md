# IGNITE Standalone 0.1 — nouvelle base

Petite groovebox Windows autonome : six pistes (kick, snare, charley, basse, clavier, lead), seize pas, instruments internes et kits de batterie. Aucun appareil IGNITE et aucune configuration MIDI ne sont necessaires. Cette cible remplace le prototype refuse ; elle ne compile aucun fichier de l'ancien portage.

## Utiliser

Extraire une fois le ZIP **Ignite-Standalone-Windows**, conserver ses cinq fichiers ensemble et lancer **IgniteStandalone.exe**. Le pattern de demonstration est charge au demarrage : cliquer **PLAY** pour l'entendre. **STOP** arrete la lecture et les notes. **Sortie audio** choisit la carte son Windows et son volume. Le moteur suit sa frequence reelle, notamment 44100, 48000 et 96000 Hz.

- **Instrument / kit** : choisir directement un son dans la liste de la piste. **Jouer** permet de l'ecouter immediatement.
- **Pas 1–16** : cliquer pour activer/desactiver. Clic droit pour choisir la note de ce pas. Le champ **Note** change la note de tous les pas de la piste.
- **Nom de piste** : selectionner le son a jouer sur le clavier en bas. **M** coupe la piste.
- **Demo** restaure le groove de depart. **Effacer** donne un pattern vide. **Enregistrer / Ouvrir** sauvegardent/rechargent un fichier JSON avec sons, tempo, notes et pas.

La banque GeneralUser GS 2.0.3 de S. Christian Collins est incluse avec sa licence. Elle fournit les sons : ce n'est pas la banque usine d'IGNITE.

## Ce qui vient du code IGNITE

Le synthetiseur TinySoundFont est extrait directement du ZIP source fourni, depuis `Source/Application/modules/Firmware/Application/Model/tsf.h`. Il est utilise pour les voix et les banques internes, comme dans le moteur sonore d'origine. Voir `vendor/ignite/ORIGIN.md`.

Le nouveau `src/core` gere six instances partageant la meme banque, les commandes de notes, les programmes, le mixage stereo et une horloge de seize pas calculee a l'echantillon. Il ne depend ni de JUCE, ni de Linux, ni du hardware. Le nouveau `src/app` est l'hote JUCE : souris, clavier, fichiers et sortie audio Windows.

Le modele de pattern de cette premiere etape est nouveau et volontairement simple. Le sequenceur original Song/Scene/Track/Pattern, les effets JUCE d'origine, l'enregistrement et l'import des projets firmware ne sont pas encore portes dans cette cible. Les fichiers JSON de cette application ne sont pas des projets firmware IGNITE.

## Construire

Visual Studio 2022 Desktop C++, CMake 3.22+, Git :

```powershell
cmake -S Standalone -B build/standalone -A x64
cmake --build build/standalone --config Release --parallel 2
ctest --test-dir build/standalone -C Release --output-on-failure
```

JUCE 7.0.12 est recupere automatiquement. La cible `ignite_audio_core` peut etre compilee/testee seule avec `-DIGNITE_BUILD_APP=OFF`, sans telecharger JUCE.

## Verification

Les tests du coeur verifient les six sons, le rendu non silencieux et fini a plusieurs frequences, les tailles de buffers variables, le nombre exact de pas, l'arret des notes et l'effet d'un changement d'instrument sur le signal. Le test Windows `--ui-self-test` utilise **SendInput** pour les clics et touches systeme et analyse le signal issu du callback audio de l'application. Sans carte son sur le runner, ce callback est appele par un pilote de test. Le test publie captures, rapport et WAV ; il ne prouve pas la sortie physique sur la carte son de l'utilisateur.

Source Music Tribe et nouveau code sous AGPL-3.0-or-later ; TinySoundFont conserve sa licence MIT dans son en-tete ; JUCE et GeneralUser GS conservent leurs licences respectives.
