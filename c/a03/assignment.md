Innlevering 3: Full-tekst søk
 
I denne oppgaven skal dere lage en søkemotor.
 
Input er en eller flere bøker fra Project Gutenberg.
Programmet skal så søke i boken etter ord ved hjelp av et binært
søketre[1]. Binære søketrær lar deg finne et ord i snitt med O(log n)
kjøretid, noe som er svært mye raskere enn å grep-e. Den samme teknikken
brukes av databaser og store søkemotorer som Google.
 
 
Oppgave
 
Les inn en bok (tekst-fil) og lag et binært søketre over alle ordene i boken. Brukeren
skal kunne søke på ord i ordboken.
 
Vurdering
 
Minstekrav:
Opprett et binært søketre med alle ordene i boken. Brukeren kan søke etter
ord i treet og se om ordet er brukt i boken.
 
Bruk denne boken som utgangspunkt: http://home.nith.no/~esphav/pg4300.txt
 
Forbedringer:
- Støtt case-insensitive søk
- Vis hvilke linjer ordet forekommer på
- Støtt flere filer
- Tenk at du er Google og skal lese inn over 100 000 000 dokumenter.
  Hvordan må du strukturere programmet ditt da?
 
Innlevering
 
Kommentert kildekode med Makefile leveres innen fristen.
Legg gjerne ved en rapport hvis du har tatt noen spesielle betrakninger.
 
[1] http://en.wikipedia.org/wiki/Binary_search_tree
