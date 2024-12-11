// data.js
const pageContent = {
    hero: {
        title: "Benvenuto nella guida alle Socket",
        subtitle: "Scopri cosa sono le socket, come funzionano e perché sono fondamentali nel networking.",
        buttonText: "Inizia ora",
        buttonLink: "sockets.html"
    },
    accordion: [
        {
            title: "Punto 1: Definizione di socket",
            content: "Una <strong>socket</strong> è un punto di comunicazione tra due applicazioni che operano in rete. Consente lo scambio di dati tramite protocolli di trasporto come TCP e UDP."
        },
        {
            title: "Punto 2: Tipi di socket",
            content: "Esistono due tipi principali di socket: <ul><li><strong>Stream Socket:</strong> Basate su TCP, offrono una comunicazione affidabile.</li><li><strong>Datagram Socket:</strong> Basate su UDP, per una comunicazione veloce ma meno affidabile.</li></ul>"
        },
        {
            title: "Punto 3: Socket nel modello client-server",
            content: "Le socket sono utilizzate nel modello <strong>client-server</strong> per creare una connessione tra il client (che richiede un servizio) e il server (che lo fornisce)."
        }
    ],
    cards: [
        {
            title: "Socket",
            text: "Scopri le basi delle socket, i loro tipi e il loro funzionamento nel contesto client-server.",
            image: "https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcS4YTM_dqDkYyHaKwHI9mhez1HGhMpTvwVaSA&s",
            link: "sockets.html"
        },
        {
            title: "Modello OSI",
            text: "Approfondisci il modello OSI, con particolare attenzione al livello di trasporto.",
            image: "https://static.wixstatic.com/media/bb5dcc_257608418e614ae8a6b52ca40a45d809~mv2.jpg",
            link: "osi.html"
        },
        {
            title: "TCP vs UDP",
            text: "Confronta i due principali protocolli di comunicazione e scopri le loro differenze.",
            image: "https://media.licdn.com/dms/image/v2/D4D12AQGAkp_W0K-wuw/article-cover_image-shrink_600_2000/article-cover_image-shrink_600_2000/0/1704047634787?e=2147483647&v=beta&t=9z5G-EjbDir8sqUrOEFjiqjbu9qN64lWyDcBNqm3QjE",
            link: "tcp-udp.html"
        }
    ]
};
