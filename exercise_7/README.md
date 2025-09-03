Zadání

Projekt upravte (rozšiřte) o následující části:

Zaměřte se na správné použití transformací (ukládejte jednotlivé transformace, přidejte možnosti dynamických transformací apod.)

Přidejte do projektu použití více typu světel (bodové, směrové a reflektor), dodržte jejich vlastnosti.

Použijte reflektor propojený s kamerou (rozhlížení s baterkou).

Přidejte třídu pro materiál (bude obsahovat koeficienty ra, rd, rs).

Upravte projekt tak, aby glUseProgram(id) byl volán před příkazy glUniform a glDrawArray. Následně zrušte nastavení shaderu pomocí glUseProgram(0).

Nezamykejte kurzor myši (použijte např. stisknutí pravého tlačítka pro rozhlížení), levým tlačítkem budeme vybírat objekty ve scéně.

Odevzdání úkolu

Odešlete pouze vámi vytvořené zdrojové soubory CPP a H, včetně shaderu (neposílejte knihovny, modely, projekt atd.).

Přiložte screeny pro kontrolu (v případě videa nahrajte prosím jen odkaz na youtube).

Screeny z projektu

Možnost použití více světel (bludičky v lese). login_1.png

Reflektor připojený na kameru (procházení lesa s baterkou). Vytvořte si kopii lesa a světlo nastavte na noční dobu. login_2.png

Použití více materiálů a více shaderů (ve scéně bude více modelů se stejným shaderem ale jiným materiálem). login_3.png

Textový popis

Přidejte k odeslání tento formulář a potvrďte, že máte vše v odeslaném projektu, případně napiš co nemáte a proč:

Transformace (můžete je libovolně skládat, přehazovat, přidat stejnou BasiCTransformation k více transformacím a kombinovat ji s dalšími, máte použitý Composit správně atd.).

Máte základní testovací scénu s trojúhelníkem.

Máte scénu se čtyřmi kuličkami a funkčním Phongovým osvětlovacím modelem.

Máte scenu s lesem, kde je více shaderů, více světel. Jak modely (stromy, i světla) se mohou dynamicky rotovat nebo pohybovat.

Máte noční variantu lesa, kde je lépe vidět baterka pči procházení a další typy světel.
