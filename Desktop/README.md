# IGNITE Core Desktop 0.2.0 — premier pattern local

Cette premiere tranche utilise les classes originales Pattern/Bar/Step et SequenceManager, le synthetiseur TSF original et les algorithmes JUCE d'effets extraits de Track. Elle remplace les commandes physiques par une grille de notes accessible a la souris.

Lancer `IgniteCoreDesktop.exe`. La banque est integree : aucun instrument externe, port MIDI ou machine physique n'est necessaire. Une demo de piano est chargee. Cliquer Lecture, ou choisir un instrument puis Ecouter le son. Les kits portent le prefixe Batterie ; apres selection d'un kit, Charger une demo cree un rythme kick/snare/hi-hat. Cliquer une case ajoute/retire une note ; plusieurs notes par pas sont possibles. Vider le pattern efface les notes. Tempo, filtre, resonance, reverb et volume sont actifs.

La grille montre huit hauteurs et seize pas. Les notes restent dans le modele quand on change d'instrument ; Charger une demo remplace le pattern. Une edition du pattern en cours de lecture le relance a son debut. Les controles d'effets modifient le son pendant la lecture. Stop coupe les notes et remet les effets a zero.

Portee : une piste, un pattern d'une mesure. L'arrangement de scenes, la sauvegarde de projets, les fonctions avancees de Track (boucles/repetitions de mesures, commandes auxiliaires) et les autres commandes d'effets restent a porter. Cette tranche ne pretend pas reproduire toute la machine.

Les methodes d'effets et leur ordre proviennent de fragments verifies du ZIP original dans upstream/, avec provenance et empreintes SHA-256. Le bootstrap firmware et SongManager sont retires. Les constantes de frequence/bloc deviennent des parametres du pilote audio ; les blocs mono sont traites jusqu'a 128 echantillons. Le controle de reverb a l'ecran regle le melange sec/traite du meme Reverb ; ses parametres sont appliques avant traitement. Ce raccord corrige le changement de structure de parametres non applique au processeur dans le firmware.

La sortie utilise le pilote Windows WinMM et son horloge de consommation. Si Windows n'offre aucun peripherique valide, l'erreur apparait et Lecture est desactive. Relancer l'audio rouvre la sortie par defaut. Le test CI produit du PCM hors ligne a travers les vrais clics Windows et l'interface ; le runner CI sans carte audio ne prouve pas une ecoute sur un PC physique.

Compilation : `cmake -S Desktop -B build/core-desktop`, puis `cmake --build build/core-desktop --config Release` et `ctest --test-dir build/core-desktop -C Release --output-on-failure`. Cette cible utilise JUCE 7.0.12 et le compilateur C++ de la plateforme. L'executable Windows est dans `build/core-desktop/IgniteCoreDesktop_artefacts/Release/`.
