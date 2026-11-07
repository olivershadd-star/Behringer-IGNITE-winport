# IGNITE : adaptation communautaire Windows x64

Prototype source issu de l'archive 0716-AAF. Ce portage n'est pas une version officielle Behringer. La compilation Windows x64 a reussi dans GitHub Actions (run 42388196042) ; l'archive produite contient Ignite.exe et ses ressources. Le fonctionnement interactif et audio reste a tester sur un PC Windows.

## Compiler

Installer Visual Studio 2022 avec la charge Developpement Desktop en C++, le SDK Windows, CMake 3.20+ et Git. Une connexion Internet est necessaire pour recuperer JUCE 7.0.12 via CPM.
Depuis PowerShell, dans ce dossier :

```powershell
./build-windows.ps1
# Ou avec votre propre banque General MIDI compatible :
./build-windows.ps1 -SoundFont 'D:\Samples\MaBanque.sf2'
```

Le resultat attendu est `dist/Ignite-Windows-x64/Ignite.exe` avec `assets/` a ses cotes. L'archive portable est dans `dist/`. Elle contient directement `Ignite.exe` et `assets/` : une seule extraction suffit. Le telechargement Actions emballe directement les fichiers, sans ZIP intermediaire. En cas de nouvelle construction, renommer le dossier et le ZIP precedents. Le workflow `.github/workflows/windows-desktop.yml` permet la meme compilation sur GitHub Actions ; il a ete execute avec succes sur GitHub Actions.

## Sons et donnees

La banque originale n'est pas redistribuee. Fournir une banque SF2 compatible General MIDI sous le nom `Ignite.sf2`, a cote de l'executable ou dans `%APPDATA%/IgniteCommunity/`. Relancer apres ajout. Sans banque valide, la synthese est desactivee. Les donnees de travail sont dans `%APPDATA%/IgniteCommunity/Data` ; aucun transfert automatique depuis l'ancien `C:/Ignite_Files` n'est effectue.

Le DSP conserve son fonctionnement mono, 48 kHz, blocs de 960 echantillons, 8 voix par instance. L'adaptateur accepte des callbacks de tailles differentes sans depassement ; il ne reduit pas la granularite interne de 20 ms. Une frequence de peripherique differente de 48 kHz produit du silence avec un message de log : aucun reechantillonnage n'est implemente.

## Commandes desktop

Le simulateur de facade fourni dans le projet original est active sous Windows. Cliquer dans sa fenetre avant les raccourcis. J = lecture, H = stop, F = enregistrement, Z/X/C/V = morceau/scene/piste/pattern, M = menu, A ou K = sauvegarde, chiffres 1 a 8 = selection des pistes (Shift pour 9 a 16). Cette interface de developpement reste a valider et a remplacer par des commandes desktop ergonomiques. Les touches [ et ] sont des sequences de diagnostic du simulateur d'origine.

## Changements

- Option CMake IGNITE_DESKTOP, barre de titre Windows et simulateur clavier.
- Tests materiels desactives par defaut.
- Chargement de SoundFont pres de l'executable et protection des appels de pistes sans banque.
- Stockage dans le profil utilisateur et creation recursive du dossier.
- Signature du callback JUCE corrigee, adaptation des tailles de buffers et protection de frequence.
- Copie des ressources independante du type de configuration.
- Script PowerShell et workflow de compilation Windows.

## Verification et limites

Le test C++ de l'adaptateur audio verifie la continuite du flux, les tailles de buffers variables, les canaux nuls, les sentinelles et le reset ; il a ete execute sous Linux avec AddressSanitizer et UndefinedBehaviorSanitizer. L'application complete a ete compilee en Release sous Windows avec MSVC ; elle n'a pas ete testee interactivement. L'integrite du ZIP, le format PE x64 de l'executable et la presence des ressources ont ete verifies. Des erreurs heritees du projet peuvent subsister. Le routage MIDI garde les noms et conventions du materiel d'origine : un selecteur de ports Windows generique reste a developper. CV/Gate et firmware MCU necessitent du materiel. Sauvegarde, restauration, fermeture des threads, commandes du simulateur et synchronisation notes/audio doivent etre testes sur Windows. Cette livraison est une base de portage, pas une application finalisee.

Code Music Tribe sous AGPL-3.0-or-later ; conserver les notices et licences tierces. Les marques et images ne sont pas couvertes par la licence du code. Voir README.md et LICENSE.
