# IGNITE sur Windows x64

Cette version de developpement conserve le moteur musical et l'ecran d'origine. Une facade virtuelle integree remplace les commandes physiques. Ce n'est pas une version officielle Behringer.

## Installer une compilation

Dans GitHub Actions, ouvrir le dernier run reussi de Windows desktop build, puis telecharger l'artefact Ignite-Windows-x64. Une seule extraction : `Ignite.exe`, `assets/` et `Ignite.sf2` se trouvent ensemble. Lancer Ignite.exe depuis ce dossier. Les anciennes archives du premier prototype ne correspondent pas a ce portage.

La banque GeneralUser GS de S. Christian Collins est incluse avec sa licence. Elle remplace la banque usine non redistribuee ; elle ne reproduit pas exactement ses sons.

## Commandes

Le centre de la fenetre reste l'ecran tactile d'IGNITE. Les commandes autour remplacent sa facade : SONG/SCENE/TRACK/PATTERN, transport, INSERT/DELETE/COPY, 16 pads, appui et rotation de leurs encodeurs, ROW/BAR et huit commandes sonores. SHIFT est une touche a verrouillage. Audio settings permet de choisir la sortie Windows ; le statut indique la banque et le peripherique actifs. Les nouveaux instruments utilisent les sons internes par defaut. Les anciennes definitions d'instruments restent telles quelles : activer Internal Sound dans leurs reglages pour les utiliser avec la banque locale.

Espace = lecture, Echap = stop, fleches gauche/droite = navigation, Entree = selection. Le bouton Help explique les commandes. L'ajout d'un instrument est une definition de routage et de preset dans le modele IGNITE, pas le chargement d'un plugin VST.

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
