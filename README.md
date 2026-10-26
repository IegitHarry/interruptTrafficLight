
Inteligentny Sterownik Sygnalizacji Świetlnej

Oparty na przerwaniach system kontroli ruchu drogowego dla Arduino, zaprojektowany dla zwężenia drogi lub skrzyżowania dwukierunkowego (pas Górny/„Top” i Dolny/„Bottom”). System domyślnie utrzymuje bezpieczny stan czerwonego światła dla obu kierunków (All-Red). W momencie wykrycia pojazdu przez czujnik, uruchamiana jest 5-sekundowa faza zielonego światła dla danego pasa, zachowując 2-sekundowy bufor bezpieczeństwa (All-Red) pomiędzy zmianami faz.

🚦 Mapowanie Pinów (Hardware)


Wejścia (Czujniki)

• Pin 2: Czujnik dolnego pasa (obsługiwany przez przerwanie, wyzwalany zboczem narastającym RISING)
• Pin 3: Czujnik górnego pasa (obsługiwany przez przerwanie, wyzwalany zboczem narastającym RISING)

Wyjścia (Sygnalizatory)

• Pin 4: Czerwone światło – pas górny
• Pin 5: Zielone światło – pas górny
• Pin 6: Zielone światło – pas dolny
• Pin 7: Czerwone światło – pas dolny

🛠️ Logika Działania i Maszyna Stanów

1. Stan domyślny (Wszędzie czerwone): System uruchamia się w trybie bezpieczeństwa – piny 4 i 7 otrzymują stan HIGH (czerwone), a piny 5 i 6 stan LOW (zielone).
2. Detekcja pojazdu: Przerwania sprzętowe (detectTop / detectBottom) natychmiast rejestrują nadjeżdżający pojazd, niezależnie od aktualnie wykonywanych przez mikrokontroler operacji.
3. Faza zielona (5 sekund): Po aktywacji pasa, jego czerwone światło gaśnie, a zapala się zielone. Jeśli kolejny pojazd najedzie na czujnik w trakcie trwania zielonej fazy, licznik 5 sekund odlicza czas na nowo, zapobiegając zablokowaniu poruszających się aut.
4. Czas czyszczenia skrzyżowania (2 sekundy): Po zakończeniu zielonej fazy system wraca do stanu "wszędzie czerwone" na 2000 milisekund. Dopiero po tym czasie przeciwny pas może zażądać zielonego światła. Gwarantuje to bezpieczne opuszczenie zwężenia przez pojazdy.

💻 Struktura Kodu

• setup(): Konfiguruje tryby pracy pinów GPIO, przypisuje przerwania zewnętrzne do pinów 2 i 3 oraz wymusza początkowy stan bezpieczeństwa.
• loop(): Analizuje aktywne fazy, monitoruje upływ czasu za pomocą nieblokującej funkcji millis(), zarządza czasem czyszczenia skrzyżowania i przełącza stany sygnalizacji.
• detectTop() / detectBottom(): Szybkie procedury obsługi przerwań (ISR), które natychmiast zmieniają flagi stanu typu volatile po wykryciu pojazdu.
• allRed(): Funkcja pomocnicza przywracająca czerwone światło na wszystkich semaforach.

🚀 Jak zacząć


Wymagania

• Arduino IDE
• Płytka Arduino obsługująca przerwania zewnętrzne na pinach 2 i 3 (np. Arduino Uno, Nano, Mega)

Instalacja

1. Sklonuj to repozytorium:bash
git clone https://github.com
Używaj kodu z rozwagą.
2. Otwórz plik źródłowy w Arduino IDE.
3. Zweryfikuj i wgraj program na swój mikrokontroler.
