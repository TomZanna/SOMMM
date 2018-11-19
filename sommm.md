# SOMMM
---

## JSON
Dalla definizione di JSON, provate a discuterne con i vostri docenti, mi sembra di capire che il formato che suggerite

	[
	{
	"stanza": "L142",
	"giorno": "2018-10-31",
	"giorno_settimana": 3
	},
	{
	"ora": "1",
	"prof1": "COBELLO GRAZIA",
	"prof2": "GIRELLI PIERLUIGI",
	"mat": "LGPI",
	"sez": "5BI"
	},
	{
	"ora": "2",
	"prof1": "COBELLO GRAZIA",
	"prof2": "GIRELLI PIERLUIGI",
	"mat": "LGPI",
	"sez": "5BI"
	}
	]

un array di elementi con struttura diversa, non sia ascrivibile a un oggetto JSON, che può essere si complesso, ma 
deve comunque poter essere ridotto in:

*Un insieme di coppie nome/valore. In diversi linguaggi, questo è realizzato come un oggetto, un record, 
	uno struct, un dizionario, una tabella hash, un elenco di chiavi o un array associativo.*

oppure

*Un elenco ordinato di valori. Nella maggior parte dei linguaggi questo si realizza con un array, 
	un vettore, un elenco o una sequenza.*

Quindi se si considera la stanza come elemento che contraddistingue l'oggetto, il file dovrebbe essere con questo formato:

	{
		"stanza": "L142",
		"giorno": "2018-10-31",
		"giorno_settimana": 3,
		"occupazione":
			[
				{
				"ora": "1",
				"prof1": "COBELLO GRAZIA",
				"prof2": "GIRELLI PIERLUIGI",
				"mat": "LGPI",
				"sez": "5BI"
				},
				{
				"ora": "2",
				"prof1": "COBELLO GRAZIA",
				"prof2": "GIRELLI PIERLUIGI",
				"mat": "LGPI",
				"sez": "5BI"
				}
			]
	}

come se fosse (in SQL) un raggruppamento per stanza.

La funzione presente di php **json_encode** utilizzata sia in orario che in TT restituisce un array di elementi json, senza 
raggruppamenti (quindi ridondante) ed escludendo per ora la materia il suo formato è il seguente

	[
		{	
			0 : "L142"
			1 : "2018-10-31"
			2 : "3"
			3 : "1"
			4 : "COBELLO GRAZIA"
			5 : "GIRELLI PIERLUIGI"
			6 : "5BI"
			stanza : "L142"
			giorno : "2018-10-31"
			giorno_settimana : "3"
			ora : "1"
			professore1 : "COBELLO GRAZIA"
			professore2 : "GIRELLI PIERLUIGI"
			risorsa : "5BI"
		},
		{
			0 : "L142"
			1 : "2018-10-31"
			2 : "3"
			3 : "2"
			4 : "COBELLO GRAZIA"
			5 : "GIRELLI PIERLUIGI"
			6 : "5BI"
			stanza : "L142"
			giorno : "2018-10-31"
			giorno_settimana : "3"
			ora : "2"
			professore1 : "COBELLO GRAZIA"
			professore2 : "GIRELLI PIERLUIGI"
			risorsa : "5BI"
		}
	]
	
Che è un array in cui ogni elemento ha la stessa struttura

## Changelog timetable5a.php

**2018-11-14 Proposta giornaliera + settimanale**

Proponiamo questa risposta in seguito alla modifica effettuata al layout del display per cui riaggiungiamo anche la visione classi per la settimana completa.


    {
        "stanza": "L142",
        "giorno": "2018-10-31",
		"giorno_settimana": 3,
		"ora_attuale": 5,
        "oggi": {
            "1": {
                "ora": "1",
                "prof1": "COBELLO GRAZIA",
                "prof2": "GIRELLI PIERLUIGI",
                "mat": "LGPI",
                "sez": "5BI"
                },
            "2": {
                "ora": "2",
                "prof1": "COBELLO GRAZIA",
                "prof2": "GIRELLI PIERLUIGI",
                "mat": "LGPI",
                "sez": "5BI"
                },
            ...
            },
        "settimana": {
            // Lunedì
            "1": {
                "1": null,
                "2": "5AI",
                "3": "5AI",
                "4": "3AI",
                "5": "3AI",
                "6": "3AI",
                "7": null,
                "8": null,
                "9": null
            },
            // Martedì
            "2": {
                "1": "5BI",
                "2": "5BI",
                "3": "5BI",
                "4": "5DI",
                "5": "5DI",
                "6": "5DI",
                "7": null,
                "8": null,
                "9": null
            },
            ...
        }
    }


**2018-11-05 Versione 03.01**

Aggiunta materia per ogni istanza di stanza
