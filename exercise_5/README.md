Zadání

Projekt by měl obsahovat:

Možnost za běhu přepínat scény, mělo by jich být víc, minimálně:

a) Základní scéna, určena pro testování, která bude obsahovat pouze jeden trojúhelník.

b) Scéna s lesem, (min. 50 stromů a 50 keřů), klidně rozšiřte o další modely, plane jako zem apod.

c) Scéna se čtyřmi kuličkami a světlem uprostřed (ukazovali jsme si na přednášce), budeme používat pro ověřování správnosti osvětlovacího modelu, použijeme Phongův shader na všechny čtyři kuličky (případně přepneme na jiný).

d) Scéna pro demonstraci použití všech shaderů (Konstantní, Lambert, Phong a Blinn), bude obsahovat více typu modelů a na nich různé typy shaderu.

Světlo (v budoucnu jich bude více typů), aktuálně pouze point light, využít zde můžete opět návrhový vzor Observer (). Později přidáme více světel a více typů.

Dosud použité třídy (ShaderProgram, DrowableObject, Camera, Controller).

Transformace, kde DrowableObject má možnost si uložit jednu obecnou modelovou transformaci (přenáší model z lokální do globální souřadné soustavy), která se skládá z různých (obecně n) elementárních transformací, které jsou reprezenovány třídami (posun, rotace, změna měřítka, dynamická rotace apod.).

Pokusíme se při implementaci dodržet (alespoň někde) základní principy OOP:

a) Encapsulation (zapouzdření) - pokusíme se u domluvených tříd dodržet skrýtí některých metod a atributů tak, aby zůstaly použitelné jen uvnitř třídy a zvenku byly nedostupné (privátní). Jedná se minimálně o ShaderProgram a GLinty pro identifikátor shaderu, podobně by to mělo platit i pro id proměnných ve vertex a fragment shaderu. Dále by to mělo být id modelu (VAO).

b) Inheritance (dědičnost) - nám umožňuje vytvářet nové třídy (potomky) na základě existujících tříd (rodičů) a rozšířit tak třeba funkcionalitu, hodí se na různých místech, můžete použít např. u nyní dodaného ShaderLoaderu (tuto třídu byste neměli měnit).

c) Polymorphism (polymorfismus neboli mnohotvárnost) - umožňuje používat jednotné rozhraní pro práci s různými typy objektů, každý objekt si společnou metodu implementuje po svém. Hodí se třeba u elementárních transformací, modelů atd.

Vertex a fragment shadery prosím uložte do textových souboru a použijte přiložený ShaderLoader pro jejich načítání.

Pozn.: Dodané soubory byste neměli měnit (pracujeme v teamu a přepisovat někomu něco není dobrý nápad).

Odevzdání úkolu

Odešlete pouze vytvořené zdrojové soubory CPP a H, včetně shaderu (neposílejte knihovny, modely, projekt atd.).

Při odevzdávání prosím použijte následující formulář a v krátkosti dopište ke každému bodu kde a jak danou věc máte, ke scénám přiložte prosím obrázky, případně krátké video.

Aktuální stav

Přepínání scén za běhu (Ano/Ne) (kde a jak)

a) Základní scéna (Ano/Ne)

b) Scéna s lesem (Ano/Ne)

c) Scéna se čtyřmi kuličkami (Ano/Ne)

d) Scéna pro demonstraci použití všech shaderů (Konstantní, Lambert, Phong a Blinn) (Ano/Ne)

Světlo (Ano/Ne) (kde a jak máte naimplementováno, jak se updatuje změna světla)

Základní třídy (ShaderProgram, DrowableObject, Camera, Controller) (Ano/Ne) (kdo zodpovídá za vykreslování, kde jsou uloženy modely, shadery atd.)

Transformace (Composite pattern) (Ano/Ne) (Máte pro transformace základní třídy? Co a jak jste použili?)

Základy OOP

a) Encapsulation (zapouzdření) (Ano/Ne) (Kde a jak?)

b) Inheritance (dědičnost) (Ano/Ne) (Kde a jak?)

c) Polymorphism (polymorfismus neboli mnohotvárnost) (Ano/Ne) (Kde a jak?)

Vertex a fragment shadery prosím uložte do textových souboru a použijte přiložený ShaderLoader pro jejich načítání (Ano/Ne) (Kde a jak jste použili?)
