// tcpUdpData.js

const tcpUdpData = {
    titleSection: {
        title: "Confronto tra TCP e UDP",
        description: "TCP (Transmission Control Protocol) e UDP (User Datagram Protocol) sono due protocolli fondamentali nelle comunicazioni di rete. Vediamo le loro caratteristiche principali e differenze."
    },
    introSection: {
        title: "Introduzione ai protocolli TCP e UDP",
        description: "Il TCP e l'UDP sono due protocolli di trasporto utilizzati per inviare dati attraverso la rete. Entrambi sono utilizzati a livello di trasporto del modello OSI, ma si differenziano per modalità di trasmissione e garanzie fornite."
    },
    protocols: [
        {
            title: "TCP (Transmission Control Protocol)",
            characteristics: [
                "Connessione: Protocollo orientato alla connessione.",
                "Affidabilità: Garantisce la consegna dei dati con controllo degli errori e gestione della congestione.",
                "Ordine dei dati: I dati vengono ricevuti nell'ordine corretto.",
                "Velocità: Più lento rispetto a UDP, a causa dei meccanismi di controllo.",
                "Uso: Adatto per applicazioni che richiedono alta affidabilità, come HTTP, FTP, e-mail."
            ]
        },
        {
            title: "UDP (User Datagram Protocol)",
            characteristics: [
                "Connessione: Protocollo senza connessione.",
                "Affidabilità: Non garantisce la consegna dei dati, non ha meccanismi di controllo.",
                "Ordine dei dati: I dati potrebbero non arrivare nell'ordine corretto.",
                "Velocità: Più veloce rispetto a TCP, ma meno affidabile.",
                "Uso: Adatto per applicazioni che richiedono alta velocità e tollerano la perdita di pacchetti, come streaming video o giochi online."
            ]
        }
    ],
    comparisonTable: [
        { feature: "Connessione", tcp: "Orientato alla connessione", udp: "Senza connessione" },
        { feature: "Affidabilità", tcp: "Alta (controllo degli errori)", udp: "Bassa (nessun controllo)" },
        { feature: "Velocità", tcp: "Lenta (a causa del controllo)", udp: "Veloce" },
        { feature: "Ordine dei dati", tcp: "Garantito", udp: "Non garantito" },
        { feature: "Uso", tcp: "HTTP, FTP, e-mail", udp: "Streaming, giochi online" }
    ]
};
