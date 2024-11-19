// Variabile globale per il timer
let timerInterval;
let tempoRimanente = 10 * 60; // 10 minuti in secondi

// Inizializza il timer di 10 minuti
function avviaTimer() {
    const timerElement = document.getElementById('timer');

    // Recupera il tempo rimanente dal localStorage o imposta 10 minuti
    tempoRimanente = parseInt(localStorage.getItem('tempoRimanente')) || 10 * 60;

    timerElement.innerText = `${Math.floor(tempoRimanente / 60)}:${(tempoRimanente % 60).toString().padStart(2, '0')}`;

    timerInterval = setInterval(() => {
        if (tempoRimanente <= 0) {
            clearInterval(timerInterval);
            localStorage.removeItem('tempoRimanente'); // Rimuovi il tempo dal localStorage
            salvaInFile(); // Salva automaticamente le risposte alla fine
            alert("Tempo scaduto! Risposte salvate.");
            location.href = "index.html"; // Torna alla homepage
        } else {
            tempoRimanente--;
            localStorage.setItem('tempoRimanente', tempoRimanente); // Salva il tempo rimanente
            timerElement.innerText = `${Math.floor(tempoRimanente / 60)}:${(tempoRimanente % 60).toString().padStart(2, '0')}`;
        }
    }, 1000);
}


// Carica domande dal file JSON
async function caricaDomande() {
    const response = await fetch('domande.json');
    return await response.json();
}

// Salva risposta nel LocalStorage
function salvaRisposta(id, risposta) {
    const risposte = JSON.parse(localStorage.getItem('risposte')) || {};
    risposte[id] = risposta;
    localStorage.setItem('risposte', JSON.stringify(risposte));
    aggiornaContatore();
}

// Carica risposta dal LocalStorage
function caricaRisposta(id) {
    const risposte = JSON.parse(localStorage.getItem('risposte')) || {};
    return risposte[id] || '';
}

// Aggiorna contatore delle risposte
function aggiornaContatore() {
    const risposte = JSON.parse(localStorage.getItem('risposte')) || {};
    const totaleRisposte = Object.keys(risposte).length;
    document.getElementById('contatore').innerText = `${totaleRisposte}/5`;
}

// Navigazione tra domande
function vaiA(tipo, id) {
    if (tipo === 'aperta') {
        location.href = `domanda_aperta.html?id=${id}`;
    } else if (tipo === 'crocetta') {
        location.href = `crocetta.html?id=${id}`;
    }
}

// Salvataggio automatico della risposta
function salvaRispostaAutomatica(tipo) {
    const id = new URLSearchParams(window.location.search).get('id');
    let risposta;
    if (tipo === 'aperta') {
        risposta = document.getElementById('risposta').value;
    } else if (tipo === 'crocetta') {
        risposta = document.querySelector('input[name=risposta]:checked')?.value;
    }
    salvaRisposta(id, risposta);
}

// Inizializza pagina con navigazione e caricamento risposte
async function inizializzaPagina(tipo) {
    const urlParams = new URLSearchParams(window.location.search);
    const id = urlParams.get('id'); // Ottieni l'ID dall'URL

    if (!id) {
        alert("Parametro ID mancante! Verrai reindirizzato alla homepage.");
        location.href = 'index.html';
        return;
    }    

    const domande = await caricaDomande();

    // Controlla se l'ID è valido
    let domanda, indice;
    if (tipo === 'aperta') {
        domanda = domande.domande_aperta.find(d => d.id === parseInt(id));
        indice = domande.domande_aperta.findIndex(d => d.id === parseInt(id));
    } else if (tipo === 'crocetta') {
        domanda = domande.domande_crocetta.find(d => d.id === id);
        indice = domande.domande_crocetta.findIndex(d => d.id === id);
    }

    // Se la domanda non è trovata, reindirizza alla homepage
    if (!domanda) {
        alert("Domanda non trovata! Verrai reindirizzato alla homepage.");
        location.href = 'index.html';
        return;
    }

    // Mostra la domanda e le risposte in base al tipo
    if (tipo === 'aperta') {
        document.getElementById('domanda').innerText = domanda.testo;
        document.getElementById('risposta').value = caricaRisposta(id);
        document.getElementById('risposta').addEventListener('input', () => salvaRispostaAutomatica(tipo));
    } else if (tipo === 'crocetta') {
        document.getElementById('domanda').innerText = domanda.testo;

        // Carica opzioni di risposta
        const opzioniContainer = document.getElementById('opzioni');
        opzioniContainer.innerHTML = '';
        domanda.opzioni.forEach(opzione => {
            const radio = document.createElement('input');
            radio.type = 'radio';
            radio.name = 'risposta';
            radio.value = opzione;
            if (opzione === caricaRisposta(id)) radio.checked = true;
            radio.addEventListener('change', () => salvaRispostaAutomatica(tipo));

            const label = document.createElement('label');
            label.innerText = opzione;
            opzioniContainer.appendChild(radio);
            opzioniContainer.appendChild(label);
            opzioniContainer.appendChild(document.createElement('br'));
        });
    }

    // Configura la navigazione
    configuraNavigazione(tipo, id, domande);
}




// Configurazione dei pulsanti di navigazione
function configuraNavigazione(tipo, id, domande) {
    const precedenteButton = document.getElementById('precedente');
    const successivoButton = document.getElementById('successivo');
    const contatoreElement = document.getElementById('contatore');

    // Unifica tutte le domande in un unico array con un ordine sequenziale
    const tutteLeDomande = [
        ...domande.domande_aperta.map(d => ({ ...d, tipo: 'aperta' })),
        ...domande.domande_crocetta.map(d => ({ ...d, tipo: 'crocetta' }))
    ];

    // Trova la domanda corrente
    const domandaAttuale = tutteLeDomande.find(d => d.tipo === tipo && d.id == id);
    const indiceGlobale = tutteLeDomande.indexOf(domandaAttuale);

    // Aggiorna il contatore (es. "Domanda 2/5")
    contatoreElement.innerText = `${indiceGlobale + 1}/${tutteLeDomande.length}`;

    // Configura il pulsante "Precedente"
    if (indiceGlobale > 0) {
        const domandaPrecedente = tutteLeDomande[indiceGlobale - 1];
        precedenteButton.onclick = () => vaiA(domandaPrecedente.tipo, domandaPrecedente.id);
        precedenteButton.disabled = false;
    } else {
        precedenteButton.disabled = true; // Disabilita se è la prima domanda
    }

    // Configura il pulsante "Successivo"
    if (indiceGlobale < tutteLeDomande.length - 1) {
        const domandaSuccessiva = tutteLeDomande[indiceGlobale + 1];
        successivoButton.onclick = () => vaiA(domandaSuccessiva.tipo, domandaSuccessiva.id);
        successivoButton.disabled = false;
    } else {
        successivoButton.disabled = true; // Disabilita se è l'ultima domanda
    }
}

async function correggiTest() {
    const domande = await caricaDomande(); // Carica le domande dal file JSON
    const risposteUtente = JSON.parse(localStorage.getItem('risposte')) || {};

    let risposteCorrette = 0;

    // Confronta solo le domande a crocetta
    domande.domande_crocetta.forEach(domanda => {
        if (risposteUtente[domanda.id] === domanda.corretta) {
            risposteCorrette++;
        }
    });

    // Mostra il risultato all'utente
    alert(`Hai risposto correttamente a ${risposteCorrette}/${domande.domande_crocetta.length} domande a crocetta.`);

    // Resetta il test
    localStorage.clear(); // Cancella tutte le risposte e il tempo rimanente
    tempoRimanente = 10 * 60; // Reimposta il tempo a 10 minuti
    clearInterval(timerInterval); // Ferma il timer corrente
    location.href = 'index.html'; // Riporta l'utente alla homepage
}
