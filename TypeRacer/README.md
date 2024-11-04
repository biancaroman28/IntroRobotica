# Joc TypeRacer

## Descrierea Proiectului

Acest proiect implementeaza un joc tip typeracer, in care jucatorul trebuie sa tasteze corect cuvintele afisate in consola in timp limitat. Scopul jocului este de a tasta corect cat mai multe cuvinte in 30 de secunde. Jucatorul poate selecta nivelul de dificultate, iar LED-ul RGB indica daca un cuvant a fost tastat corect sau incorect.

## Cerinte

Componente
- **Arduino UNO** (microcontroller ATmega328P)
- **1x LED RGB** pentru a semnaliza corectitudinea cuvintelor tastate
- **2x Butoane** pentru start/stop si pentru selectarea dificultatii
- **5x Rezistori** (3x 220/330 ohm pentru LED RGB si 2x 1000 ohm pentru butoane)
- **Breadboard** pentru montajul circuitului
- **Fire de legatura** pentru conexiunile pe breadboard

## Video Demonstrativ




https://github.com/user-attachments/assets/9f87dbdd-09d5-42ce-886e-56d32d76c809




## Setup Fizic
![WhatsApp Image 2024-11-05 at 01 32 10](https://github.com/user-attachments/assets/079fb30b-bbb8-4917-9e4f-2c9905a12d1e)
![WhatsApp Image 2024-11-05 at 01 32 10 (1)](https://github.com/user-attachments/assets/02be1e7b-e0d6-4488-9721-daa6ef4b478b)


[Link catre Video Demonstrativ](#)

## Schema Electrica


![image](https://github.com/user-attachments/assets/860f5027-e8bc-4d4f-9944-c1135d2486e4)


## Cum Functioneaza Jocul

1. Utilizatorul apasa butonul de start pentru a incepe jocul. LED-ul RGB va semnaliza inceputul printr-o numaratoare inversa.

2. Utilizatorul poate selecta dificultatea jocului apasand butonul de dificultate. Exista trei nivele de dificultate:
     - Usor (10 secunde pentru fiecare cuvant)
     - Mediu (7 secunde pentru fiecare cuvant)
     - Dificil (5 secunde pentru fiecare cuvant)

3. Un cuvant este afisat in consola, iar utilizatorul trebuie sa-l tasteze in intervalul de timp specificat.
   - LED-ul RGB ofera feedback vizual:
     - **Verde**: Cuvantul a fost tastat corect.
     - **Rosu**: Cuvantul a fost tastat incorect.
   - Fiecare cuvant corect este adaugat la contorul de cuvinte corecte.

4. Utilizatorul poate opri jocul in orice moment apasand butonul de start/stop. LED-ul RGB se va stinge, semnalizand oprirea jocului.

5. Utilizatorul nu poate apasa butonul de dificultate cand jocul este pornit.


