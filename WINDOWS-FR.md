# IGNITE sur Windows x64

Cette version de developpement conserve le moteur musical et l'interface JUCE d'origine, dans une fenetre Windows de 1024 x 600 pixels. Ce n'est pas une version officielle Behringer.

## Installer une compilation

Dans GitHub Actions, ouvrir le dernier run reussi de Windows desktop build, puis telecharger l'artefact Ignite-Windows-x64. Une seule extraction : `Ignite.exe`, `assets/` et `Ignite.sf2` se trouvent ensemble. Lancer Ignite.exe depuis ce dossier. Les anciennes archives du premier prototype ne correspondent pas a ce portage.

La banque GeneralUser GS de S. Christian Collins est incluse avec sa licence. Elle remplace la banque usine non redistribuee ; elle ne reproduit pas exactement ses sons.

## Commandes

Les ecrans Menu, Song, Scene, Track, Pattern, les boutons de transport et le navigateur de presets proviennent de `Source/Application/modules/ignite_ui`. Le panneau de commandes ajoute dans le premier portage a ete retire. Les dialogues d'origine restent dans la fenetre de l'application.

Pour choisir un son : Menu > Instruments > Add New > Preset, choisir une categorie puis un son et Apply. Les nouveaux instruments utilisent les sons internes par defaut. Pour une definition ancienne, activer Internal Sound dans ses reglages. F10 ouvre le choix de la sortie audio Windows ; choisir 48000 Hz.

## Compiler

Installer Visual Studio 2022 avec Developpement Desktop en C++, le SDK Windows, CMake 3.20+ et Git. Depuis PowerShell, dans la racine du depot :

```powershell
./build-windows.ps1
```

JUCE 7.0.12 est recupere par CMake. La sortie est dans dist/Ignite-Windows-x64. La banque fournie est copiee automatiquement. L'option -SoundFont permet de fournir sa propre banque SF2.

## Donnees et limites

Donnees dans %APPDATA%/IgniteCommunity/Data. Aucune migration automatique depuis C:/Ignite_Files. Moteur interne mono, 48 kHz, blocs de 960 echantillons, 8 voix par instance ; le callback accepte des tailles variables, sans reechantillonnage vers d'autres frequences. Choisir une sortie a 48000 Hz.

La compilation et le lancement seuls ne prouvent pas tout le fonctionnement musical. Le workflow teste egalement la lecture du sequenceur avec mixage hors ligne et publie son rapport ; consulter son resultat. L'audibilite sur une sortie physique, les interactions completes et le routage MIDI externe generique restent a tester. Les ports MIDI gardent encore des conventions du materiel. CV/Gate physiques necessitent le materiel adequat.

Code Music Tribe sous AGPL-3.0-or-later ; dependances et banque sous leurs licences respectives. Voir LICENSE et GeneralUser-GS-LICENSE.txt.
