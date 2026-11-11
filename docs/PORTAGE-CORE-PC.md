# IGNITE : conserver le coeur musical, remplacer le materiel par une interface PC

## Correction du perimetre

Le portage attendu conserve les instruments, effets, regles musicales, patterns, pistes et scenes d'IGNITE. Il remplace la facade physique par une interface composee pour la souris et le clavier. Reproduire les ecrans tactiles du firmware ne fournit pas les commandes physiques manquantes. A l'inverse, reutiliser TinySoundFont avec un nouveau compteur de seize pas ne conserve pas le moteur musical complet.

La cible `Standalone/` actuelle est un banc d'essai de synthese et de sortie Windows. Elle possede son propre modele de pattern et ne constitue donc pas encore ce portage. Le correctif 0.1.1 ne doit pas etre presente comme la resolution de ce probleme de fond.

## Inventaire verifie dans les sources

Les chemins suivants sont relatifs a `Source/Application/modules/`.

| Domaine a conserver et adapter | Sources | Comportement a garder |
|---|---|---|
| Composition | `Common/Modules/CSong.*`, `Scene.*` | Morceaux, scenes, tempo, swing, choix des pistes et enchainement |
| Patterns | `Common/Modules/Pattern.*`, `Bar.*`, `Step.*` | Mesures, resolutions droites/triolets, notes et evenements, offsets, durees, velocites, gates, ties et skip |
| Lecture et pistes | `Common/Modules/Track.*`, `Firmware/Application/Model/SequenceManager.*` | Regles de lecture et transformation des donnees musicales d'origine |
| Instruments | `Common/Modules/Instrument.*`, `Firmware/Application/Model/InstrumentManager.*`, `tsf.h` | Affectation des sons internes, programmes et kits de percussion, voix et parametres |
| Effets | `Track::sfSynthesizeAudio`, `effectsInit`, `reverbInit`, `chorusInit`, `eqInit`, `filterInit`, `gainInit` | Reverb, chorus, EQ low/high shelf, filtre ladder et gain ; ordre d'effets parametre par l'utilisateur |
| Commandes du modele | `PatternManager`, `TrackManager`, `SceneManager`, `SongManager` | Edition, selection, sauvegarde et notifications du modele musical |

La banque usine n'est pas fournie dans le depot publie. GeneralUser GS est une banque de remplacement redistribuable ; ses sons ne doivent pas etre presentes comme les sons usine d'IGNITE.

## Dependances concretes a separer

1. `Pattern.cpp` inclut directement `PatternManager.h` et `IgniteEngine.h`. Les appels de notification de changement de mesures, de sauvegarde des references et d'effacement utilisent `_patternManager->engine.sequenceManager` ou `engine.fileHandler`. Ces services doivent etre passes par des interfaces et non remplacer les algorithmes de `Pattern`.
2. `EngineDataStruct.h` importe `Instrument.h`, `Track.h` et `Scene.h`, alors que ces classes dependent elles-memes de donnees communes. Les types de donnees musicales doivent etre isoles de cette inclusion globale et des classes de services.
3. `Track.h` importe `SongManager.h` ; `Track.cpp` depend des reglages musicaux mais aussi du moteur global. Les reglages musicaux et l'acces aux instruments doivent rester disponibles sans obliger la creation d'une facade ou de ports physiques.
4. `SongManager` combine le modele musical avec les peripheriques audio, les threads et le routage externe. Le rendu et les regles musicales doivent etre conserves ; le demarrage des services de plateforme doit devenir une responsabilite distincte.
5. `IgniteEngine` construit directement les gestionnaires musicaux et `FrontPannelManager` dans le meme assemblage. Le demarrage PC doit pouvoir instancier uniquement les services requis pour la composition locale.

Il ne suffit donc pas de changer les macros Linux en Windows ou de remplacer l'interface graphique. La separation doit aussi exister dans les dependances et dans le demarrage du programme.

## Frontieres de la version locale

| Service | Adaptation PC |
|---|---|
| Boutons, pads, encodeurs et retours de facade | Controles JUCE a la souris et au clavier, lies directement aux commandes du modele |
| UART, messages MCU, LED et GPIO | Exclus du demarrage PC ; pas de faux appareil a configurer |
| CV/Gate et connectique MIDI externe | Exclus du parcours local et de son interface |
| Notes et evenements musicaux internes | Conserves : l'absence de ports MIDI n'implique pas la suppression de la representation des notes |
| Horloge de plateforme | Adaptateur d'horloge Windows relie au rendu audio, respectant la resolution et les regles du sequenceur original |
| Peripherique sonore | Adaptateur Windows explicite, avec erreurs et consommation des tampons verifiables |
| Stockage du firmware | Fichiers locaux avec adaptation documentee ; aucune hypothese de partitions ou chemins Linux |

Le moteur ne doit pas creer des services physiques pour permettre de choisir un instrument interne ou lancer un pattern.

## Parcours ecran a fournir

Un espace de composition doit permettre de choisir et ecouter un instrument ou un kit, modifier les notes et les pas d'un pattern original, acceder aux parametres d'effets, puis lire et arreter la sequence. La souris doit donner acces aux actions auparavant reservees aux pads et encodeurs. Les pistes, mesures et scenes doivent rester des objets du modele original, et non des panneaux visuels sans commandes reliees.

Une premiere tranche peut exposer une piste et un pattern, mais doit deja utiliser leurs classes musicales originales et leur rendu avec effets. Les fonctions suivantes peuvent alors etre ajoutees progressivement sans jeter de nouveau le moteur ni changer de modele de composition.

## Ce que les verifications actuelles prouvent

Le symptome confirme par l'utilisateur, listes vides et Play grise, correspond au chemin `bankLoaded == false` de la cible `Standalone`. Le correctif 0.1.1 integre la banque dans l'EXE et passe le test de clics depuis une copie du seul executable. Cela traite ce blocage de chargement ; cela ne valide pas le portage du coeur musical original.

Le lancement Windows normal du run 43058126957 charge bien la banque integree mais indique `AUDIO_UNAVAILABLE_REPORTED`, `error=2`, `frames=0` : le runner ne possede pas de sortie WinMM utilisable. Son resultat ne doit pas etre annonce comme une reproduction sonore sur une carte physique. Le test de rendu et de clics, distinct, produit un signal mais utilise un pilote de verification.

KICK doit suivre la meme distinction : conserver son moteur AudIO et ses fonctions musicales, tout en concevant des commandes ecran exploitables sans la machine. Le prototype KICK Lab et la recente cible originale `KickHome` ne doivent pas etre confondus ; le code de KICK a seulement ete lu pendant cette analyse.
