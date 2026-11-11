# Reprise du portage Windows

Le premier portage a ete refuse. Le nouveau point de depart est [`Standalone/`](Standalone/README.md).

- `Standalone/src/core` : synthetiseur original extrait du ZIP, voix et mixage, commandes, petit sequenceur a l'echantillon. Aucune dependance JUCE, hardware Linux, UART ou routage MIDI externe.
- `Standalone/src/app` : nouvel hote JUCE, sortie Windows, choix de sons, clavier, edition de seize pas et fichiers JSON.
- `Standalone/vendor/ignite/ORIGIN.md` : provenance exacte et limites de reutilisation du code d'origine.

Les fichiers historiques dans `Source/Application` sont conserves comme reference ; aucun n'est compile dans la nouvelle cible. Le modele Song/Scene/Track/Pattern et les effets de l'appareil ne sont pas encore adaptes dans cette premiere base simple. Il faut d'abord valider cette base sur Windows, puis avancer progressivement.
