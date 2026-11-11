# Premiere separation du coeur musical original

Cette cible compile les **classes originales `Ignite::Pattern`, `Bar` et `Step`**, extraites du ZIP fourni. Elle ne compile ni le firmware, ni l'ancienne interface, ni le prototype `Standalone`, ni JUCE. Ce n'est pas encore une nouvelle application IGNITE a telecharger.

Les huit fichiers originaux sont conserves sans modification dans `upstream/`, avec leurs chemins et SHA-256 dans `provenance.json`. `tools/stage.py` verifie ces empreintes avant chaque configuration et genere une adaptation traçable dans le dossier de construction.

## Separation realisee

- Les definitions musicales sont extraites des en-tetes globaux vers `MusicalTypes.h`, sans import des gestionnaires de materiel.
- Les notifications de changement de longueur, d'effacement et de sauvegarde passent par `PatternHost`. Les algorithmes de notes, offsets, durees et mesures restent ceux des fichiers originaux.
- Les includes implicites fournis auparavant par le module JUCE sont rendus explicites.
- Les allocations des donnees de pattern, mesure et pas utilisent une propriete partagee au lieu de pointeurs sans destructeur. Les copies de patterns sont independantes et leurs pas pointent vers le bon parent.
- Deux constructeurs de `Step` oubliaient leur parent, pourtant necessaire a la validation des durees et offsets : ce lien est initialise.

## Tests

```sh
cmake -S DesktopCore -B build/original-patterns
cmake --build build/original-patterns --config Release
ctest --test-dir build/original-patterns -C Release --output-on-failure
```

Le test edite les vrais objets du modele original : plusieurs notes par pas, velocite, offset negatif, duree en ticks, gate, skip, tie, resolutions droites/triolets, ajout/copie de mesures, copie independante de patterns, notifications et persistance via l'interface de services.

## Integration restant a effectuer

Relier l'editeur PC a ces objets, puis isoler et relier la lecture des pistes et scenes, ainsi que la chaine d'effets originale de `Track`. Le petit sequenceur `Standalone` ne doit pas etre confondu avec cette cible musicale originale. Les tests ci-dessus ne valident pas encore une lecture complete d'IGNITE sous Windows.
