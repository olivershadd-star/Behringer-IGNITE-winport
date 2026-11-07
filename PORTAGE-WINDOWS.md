# Portage du materiel IGNITE vers Windows

## Chemin conserve

Le modele Song/Scene/Track/Pattern, le sequenceur, son horloge, les effets JUCE et le moteur TinySoundFont restent ceux du projet Music Tribe. L'ecran central reste l'interface tactile originale.

Le panneau virtuel remplace les boutons et encodeurs physiques, sans ajouter de sequenceur ou de synthetiseur parallele. Ses evenements traversent FrontPanneExternalReadQ puis FrontPannelUtility::KeyMessageHandlerFromMCU, comme les messages du microcontroleur. Les boutons emettent pression, maintien et relachement (1,3,2). Leurs voyants lisent les etats publies par le moteur.

## Adaptations de cette branche

- Une fenetre unique rassemble l'ecran, le transport, les modes, les 16 pads, leurs commandes d'encodeurs et les huit commandes sonores. La fenetre de diagnostic FP_TEST_KEYBRD n'est plus activee.
- Le bouton Audio settings ouvre les sorties Windows reelles. Le statut affiche la sortie, sa frequence et la disponibilite de la banque.
- Les nouveaux instruments utilisent le moteur sonore interne par defaut. Les definitions existantes ne sont pas modifiees.
- GeneralUser GS 2.0.3 remplace la banque d'origine manquante. Ce n'est pas le son usine d'IGNITE. Licence et attribution sont distribuees avec la banque. Source figee : mrbumpy409/GeneralUser-GS, revision 684543d5e5efaef08d02be50dcda8d552478fa60.
- Correction de la file de messages pour proteger ses acces entre threads et du premier demarrage des donnees de calibration.

## Validation

Test de synthese TinySoundFont avec la banque fournie : chargement, piano/basse/lead, sortie non silencieuse et echantillons finis. Test du callback a tailles variables conserve.

Le workflow Windows compile puis lance l'application, verifie le chargement de la banque et produit une capture desktop-smoke.png. Ce test ne demontre pas encore la creation et la lecture d'un pattern via l'interface, ni l'audibilite sur un peripherique physique. Ces essais restent necessaires avant de qualifier le portage de fonctionnel. Le routage des ports MIDI externes conserve encore des conventions du materiel.
