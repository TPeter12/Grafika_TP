# RTS egységkezelési mechanika

Ez a projekt egy alap RTS-stílusú egységkijelölés és egység mozgatáshoz való mechanika

- Több egység kijelölése egérrel (drag selection)
- Egységek mozgatása jobb klikk segítségével
- Kamera mozgatása az egér pozíciójával (screen edge scroll)


# Funkciók

- Egység kijelölés: Egér bal gombjának lenyomásával és húzásával egy téglalap jelenik meg, amely kijelöli az egységeket.
- Mozgatás: Jobb egérgombbal kattintva a kijelölt egységek a célpontra mozognak.
- Kamera mozgatás**: Ha az egérkurzor a képernyő széléhez közel kerül, a térkép elmozdul a megfelelő irányba.

# Kód: C és SDL2 használata

# Jövőbeli fejlesztések:

- Pathfinding algoritmus implementálása (WHCA* - Windowed Hierarchy Cooperative A*)
- Köd, fények használata
- Épületek és más objektumok hozzáadása
- Csapatok kialakítása (Player1, player2 stb.)
- Egységek más egységekhez/objektumokhoz való viszonyulása, mint például támadás vagy gyógyítás, javítás
