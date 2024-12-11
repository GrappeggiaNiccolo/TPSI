const pageContent = {
    hero: {
        title: "Le Socket: La base della comunicazione in rete",
        subtitle: "Scopri come le socket permettono la connessione tra client e server nel mondo digitale."
    },
    definition: {
        title: "Cos'è una Socket?",
        text: "Una <strong>socket</strong> è un'interfaccia per la comunicazione tra processi, utilizzata per creare una connessione tra due sistemi. È fondamentale per i protocolli di rete come TCP e UDP, e permette di inviare e ricevere dati in modo efficace.",
        image: "https://socket.io/assets/images/homepage-server-40e4108715950ea259baf9ff4a30d3ef.png"
    },
    socketTypes: [
        {
            title: "Stream Socket (TCP)",
            text: "Fornisce una comunicazione affidabile e ordinata basata sul protocollo TCP. Ideale per applicazioni come il trasferimento di file o email."
        },
        {
            title: "Datagram Socket (UDP)",
            text: "Offre comunicazione veloce ma senza garanzie di consegna, basandosi sul protocollo UDP. Utilizzato spesso per lo streaming o i giochi online."
        }
    ],
    clientServer: {
        text: "Nel modello <strong>client-server</strong>, una socket viene utilizzata per stabilire una connessione tra il client, che invia richieste, e il server, che le elabora e risponde. Questo modello è alla base di applicazioni come:",
        image: "https://darvishdarab.github.io/cs421_f20/assets/images/client-server-1-d85a93ea16590c10bed340dd78294d0d.png",
        applications: [
            ["Email", "bi-envelope"],
            ["Archiviazione cloud", "bi-cloud"],
            ["Navigazione web", "bi-browser-chrome"],
            ["Videochiamate", "bi-phone"],
            ["Streaming musicale", "bi-music-note"],
            ["Gaming online", "bi-controller"]
        ]
    }
};