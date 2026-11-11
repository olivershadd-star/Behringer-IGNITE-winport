# Premiere separation du coeur musical original

Cette cible compile les **classes originales `Ignite::Pattern`, `Bar`, `Step` et `SequenceManager`**, extraites du ZIP fourni. Elle ne compile ni le firmware, ni l'ancienne interface, ni le prototype `Standalone`, ni JUCE. Ce n'est pas encore une nouvelle application IGNITE a telecharger.

Les dix fichiers originaux sont conserves sans modification dans `upstream/`, avec leurs chemins et SHA-256 dans `provenance.json`. `tools/stage.py` verifie ces empreintes avant chaque configuration et genere une adaptation traçable dans le dossier de construction.

## Separation realisee

- Les definitions musicales sont extraites des en-tetes globaux vers `MusicalTypes.h`, sans import des gestionnaires de materiel.
- Les notifications de changement de longueur, d'effacement et de sauvegarde passent par `PatternHost`. Les algorithmes de notes, offsets, durees et mesures restent ceux des fichiers originaux.
- Les includes implicites fournis auparavant par le module JUCE sont rendus explicites.
- Les allocations des donnees de pattern, mesure et pas utilisent une propriete partagee au lieu de pointeurs sans destructeur. Les copies de patterns sont independantes et leurs pas pointent vers le bon parent.
- Deux constructeurs de `Step` oubliaient leur parent, pourtant necessaire a la validation des durees et offsets : ce lien est initialise.
- `SequenceHost` donne au vrai `SequenceManager` l'acces aux patterns du document. Les interfaces du protocole firmware, l'enregistrement des modules et le parcours du morceau pendant le demarrage sont retires ; le document PC enregistre explicitement ses patterns. Les calculs de directions et d'evenements restent ceux du sequenceur original.
- Les directions inversees et pendulaires acceptent maintenant une mesure vide ou avec un seul pas, sans former de plage d'iterateurs invalide.
- `PatternPlayback` traduit les evenements calcules par `SequenceManager` en rendu PCM par le TSF original deja present dans le depot. L'horloge vient du nombre d'echantillons, avec les 48 ticks musicaux par noire du modele original. Les instruments sont locaux.

## Tests

```sh
cmake -S DesktopCore -B build/original-patterns
cmake --build build/original-patterns --config Release
ctest --test-dir build/original-patterns -C Release --output-on-failure
```

Les tests editent les vrais objets du modele original : plusieurs notes par pas, velocite, offset negatif, duree en ticks, gate, skip, tie, resolutions droites/triolets, ajout/copie de mesures, copie independante de patterns, notifications et persistance via l'interface de services. Ils verifient aussi les note-on/off, les directions et les mesures vides dans le vrai sequenceur.

Le test audio charge la banque locale, rend un piano puis un kick, controle les echantillons effectivement calcules, la position d'une note retardee, la repetition et Stop a 44,1/48/96 kHz avec des blocs de tailles variables. Il produit `original-core-audio.wav`. Ce rendu hors ligne ne teste pas une carte son physique.

`PatternPlayback` est une premiere passerelle pour les notes d'un pattern ; elle ne remplace pas `Track`. Elle refuse explicitement les commandes auxiliaires, repetitions/boucles de mesures, synchro globale et notes sans fin associee, qui necessitent encore l'adaptateur de piste original. Les valeurs compilees et le syntheseur ont un seul proprietaire : ne pas lire ou modifier les gestionnaires originaux concurremment depuis l'interface et le callback audio.

## Integration restant a effectuer

Relier l'editeur PC a ces objets, isoler et relier la lecture complete des pistes et scenes, ainsi que la chaine d'effets originale de `Track`, puis valider la sortie audio Windows. Le petit sequenceur `Standalone` ne doit pas etre confondu avec cette cible musicale originale. Les tests ci-dessus ne valident pas encore une lecture complete d'IGNITE sous Windows.
