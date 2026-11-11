# Portage du materiel IGNITE vers Windows

## Chemin conserve

Le modele Song/Scene/Track/Pattern, le sequenceur, son horloge, les effets JUCE et le moteur TinySoundFont restent ceux du projet Music Tribe. La fenetre affiche directement `ui::getAppHome()`, l'interface tactile originale du module `ignite_ui`, a sa taille de 1024 x 600.

Le panneau virtuel ajoute lors du premier portage a ete supprime. Les dessins, dispositions et composants de navigation viennent du code fourni. Les corrections du portage visent les controles existants et leur liaison au modele.

## Adaptations de cette branche

- Les dialogues partages restent attaches a la zone de contenu Windows, au lieu d'ouvrir une surface couvrant tout le moniteur. La fenetre de diagnostic FP_TEST_KEYBRD n'est plus activee.
- F10 ouvre le selecteur JUCE des sorties audio Windows.
- Le navigateur de presets conserve la categorie et le son selectionnes a sa reouverture ; la famille Strings contient les 16 sons Strings/Ensemble du classement original.
- Les nouveaux instruments utilisent le moteur sonore interne par defaut. Les definitions existantes ne sont pas modifiees.
- GeneralUser GS 2.0.3 remplace la banque d'origine manquante. Ce n'est pas le son usine d'IGNITE. Licence et attribution sont distribuees avec la banque. Source figee : mrbumpy409/GeneralUser-GS, revision 684543d5e5efaef08d02be50dcda8d552478fa60.
- Correction de la file de messages pour proteger ses acces entre threads et du premier demarrage des donnees de calibration.

## Validation

Test de synthese TinySoundFont avec la banque fournie : chargement, piano/basse/lead, sortie non silencieuse et echantillons finis. Test du callback a tailles variables conserve.

Le workflow Windows compile puis lance l'application, verifie le chargement de la banque et produit une capture desktop-smoke.png. Il teste aussi les callbacks des boutons Instruments > Add > Preset > categorie > son > Apply, verifie le programme recu par le moteur et la selection a la reouverture. Ses rapports et captures sont publies meme en cas d'echec. Ces tests ne demontrent pas encore la creation et la lecture d'un pattern via l'interface, ni l'audibilite sur un peripherique physique. Le routage des ports MIDI externes conserve encore des conventions du materiel.

## Validation Windows confirmee

Run GitHub Actions 42967663743 (ancienne presentation) : compilation MSVC x64, test de demarrage/pause/reprise de l'horloge et lecture d'un morceau genere avec une scene, une piste et un pattern. Le mixage hors ligne produit un signal non nul, sans valeur non finie detectee. Le test ne valide pas encore la saisie du pattern a la souris ni une sortie audio physique. Consulter le dernier run pour la validation de l'interface restauree.

Les corrections incluent la course au demarrage du timer Windows, la prise en compte des groupes de pistes incomplets (moins de huit ou dernier groupe), l'acces hors limites au statut du chorus, la serialisation des commandes SoundFont avec le rendu et la suppression des boucles de sondage MCU sans materiel.
