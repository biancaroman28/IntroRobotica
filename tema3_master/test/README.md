
# Tema 3
Coechipier: Radu Daniel - Dumitru https://github.com/dvmizew

## Descrierea temei
Tema presupune crearea unui joc de reflex competitiv pentru doi jucători. Ambii participanți concurează pentru cel mai mare punctaj (nimic special până aici), întrecându-se în viteza de reacție.

Fiecare jucător are propriile butoane și LED-uri.
Jocul se desfășoară în mai multe runde.
Punctajul fiecărui jucător este afișat pe un ecran LCD și este actualizat pe parcursul jocului.
La final, jucătorul cu cel mai mare punctaj este declarat câștigător.

## Componente utilizate
6x LED-uri (2 grupuri de câte 3 leduri, în cadrul unui grup trebuie să avem culori diferite)
2x LED RGB (1 pentru fiecare jucător)
6x butoane (3 pentru fiecare jucător)
1x LCD
1x Servomotor
2x Breadboard
Fire de legatură
2x Arduino Uno
Flow

## Inițializare
Jocul pornește cu afișarea unui mesaj de bun venit pe LCD. Apăsarea unui buton declanșează startul jocului.

Pentru începerea jocului, butonul de start poate fi implementat într-un mod flexibil, rămânând la latitudinea studenților să aleagă una dintre următoarele variante: în această variantă, jocul pornește la apăsarea oricărui buton. Un buton specific începe jocul* - se poate desemna un buton anume, clar marcat pe breadboard, pentru a porni jocul. Un al 7-lea buton dedicat* – se poate adăuga un buton suplimentar destinat exclusiv pornirii jocului.

## Desfășurarea Rundelor
Fiecare jucător are trei butoane, fiecare asociat unui LED de o culoare diferită și un al 4-lea LED RGB. La fiecare rundă, fiecare jucător este cel activ. LED-ul RGB al jucătorului activ se aprinde într-o culoare corespunzătoare unuia dintre butoanele sale.Jucătorul trebuie să apese cât mai rapid butonul care corespunde culorii LED-ului RGB, pentru a obține puncte. Cu cât reacționează mai repede, cu atât primește mai multe puncte. La finalul unei runde LCD-ul afișează punctajul actualizat al ambilor jucători. Pe tot parcursul jocului display-ul LCD va arata punctajul fiecarui jucator

## Timpul și Finalizarea Jocului
Servomotorul se rotește pe parcursul jocului, indicând progresul. O rotație completă a servomotorului marchează sfârșitul jocului (voi decideti cat de repede se misca). La final, LCD-ul afișează numele câștigătorului și scorul final pentru câteva secunde, apoi revine la ecranul de start cu mesajul de bun venit.
