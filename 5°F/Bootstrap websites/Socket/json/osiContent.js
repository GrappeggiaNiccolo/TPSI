const pageContent = {
    hero: {
        title: "Pila ISO/OSI",
        subtitle: "La Pila ISO/OSI è un modello concettuale che descrive il funzionamento delle reti di telecomunicazione in 7 livelli."
    },
    intro: {
        title: "Introduzione al modello ISO/OSI",
        description: "Il modello ISO/OSI è stato sviluppato per standardizzare le comunicazioni tra sistemi informatici, suddividendo le funzioni di rete in sette livelli:",
        levels: [
            "Fisico", "Collegamento dati", "Rete", "Trasporto", 
            "Sessione", "Presentazione", "Applicazione"
        ],
        image: "https://mikrotikusers.com/content/images/size/w960/2024/08/osi_layers.png"
    },
    accordionTitle: "Livelli del modello ISO/OSI",
    accordion: [
        { title: "Livello 1: Fisico", content: "Il livello fisico si occupa della strumentazione che consente il trasferimento dei dati, come cavi e router." },
        { title: "Livello 2: Collegamento dati", content: "Si occupa del trasferimento di dati tra due dispositivi adiacenti in una rete, inclusi il controllo degli errori e la gestione dell'accesso al mezzo fisico." },
        { title: "Livello 3: Rete", content: "Fornisce l'instradamento dei dati tra nodi non direttamente collegati, utilizzando indirizzi IP e protocolli di routing." },
        { title: "Livello 4: Trasporto", content: "Garantisce la consegna affidabile dei dati tra i sistemi finali, gestendo problemi come il controllo del flusso e la segmentazione dei dati." },
        { title: "Livello 5: Sessione", content: "Gestisce l'inizio, la durata e la fine delle sessioni di comunicazione tra le applicazioni." },
        { title: "Livello 6: Presentazione", content: "Converte i dati in un formato comprensibile tra diversi sistemi, gestendo la crittografia e la compressione." },
        { title: "Livello 7: Applicazione", content: "Rappresenta il livello più alto, offrendo interfacce e servizi per l'utente finale, come il trasferimento di file, la posta elettronica e la navigazione web." }
    ]
};
